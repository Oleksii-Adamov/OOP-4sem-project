#ifndef TEMPLATE_OLD_NET_H
#define TEMPLATE_OLD_NET_H

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

namespace net
{
	template <typename T>
	struct message_header
	{
		T id{};
		uint32_t size = 0;
	};
	
	template <typename T>
	struct message
	{
		message_header<T> header{};
		std::vector<uint8_t> body;
		
		size_t size() const
		{
			return body.size();
		}
		
		friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
		{
			os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
			return os;
		}
		
		template<typename DataType>
		friend message<T>& operator << (message<T>& msg, const DataType& data)
		{
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");
			
			size_t i = msg.body.size();
			
			msg.body.resize(msg.body.size() + sizeof(DataType));
			
			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
			
			msg.header.size = msg.size();
			
			return msg;
		}
		
		template<typename DataType>
		friend message<T>& operator >> (message<T>& msg, DataType& data)
		{
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");
			
			size_t i = msg.body.size() - sizeof(DataType);
			
			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
			
			msg.body.resize(i);
			
			msg.header.size = msg.size();
			
			return msg;
		}
	};
	
	template <typename T>
	class connection;
	
	template <typename T>
	struct owned_message
	{
		std::shared_ptr<connection<T>> remote = nullptr;
		message<T> msg;
		
		friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
	
	template<typename T>
	class tsqueue
	{
	public:
		tsqueue() = default;
		tsqueue(const tsqueue<T>&) = delete;
		virtual ~tsqueue() { clear(); }
	
	public:
		const T& front()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.front();
		}
		
		const T& back()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.back();
		}
		
		T pop_front()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.front());
			deqQueue.pop_front();
			return t;
		}
		
		T pop_back()
		{
			std::scoped_lock lock(muxQueue);
			auto t = std::move(deqQueue.back());
			deqQueue.pop_back();
			return t;
		}
		
		void push_back(const T& item)
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.emplace_back(std::move(item));
			
			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}
		
		void push_front(const T& item)
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.emplace_front(std::move(item));
			
			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}
		
		bool empty()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.empty();
		}
		
		size_t count()
		{
			std::scoped_lock lock(muxQueue);
			return deqQueue.size();
		}
		
		void clear()
		{
			std::scoped_lock lock(muxQueue);
			deqQueue.clear();
		}
		
		void wait()
		{
			while (empty())
			{
				std::unique_lock<std::mutex> ul(muxBlocking);
				cvBlocking.wait(ul);
			}
		}
	
	protected:
		std::mutex muxQueue;
		std::deque<T> deqQueue;
		std::condition_variable cvBlocking;
		std::mutex muxBlocking;
	};
	
	template<typename T>
	class server_interface;
	
	template<typename T>
	class connection : public std::enable_shared_from_this<connection<T>>
	{
	public:
		enum class owner
		{
			server,
			client
		};
	
	public:
		connection(owner parent, boost::asio::io_context& asioContext, boost::asio::ip::tcp::socket socket, tsqueue<owned_message<T>>& qIn)
		: m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
		{
			m_nOwnerType = parent;
			
			if (m_nOwnerType == owner::server)
			{
				m_nHandshakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());
				
				m_nHandshakeCheck = scramble(m_nHandshakeOut);
			}
			else
			{
				m_nHandshakeIn = 0;
				m_nHandshakeOut = 0;
			}
		}
		
		virtual ~connection()
		{}
		
		uint32_t GetID() const
		{
			return id;
		}
	
	public:
		void ConnectToClient(net::server_interface<T>* server, uint32_t uid = 0)
		{
			if (m_nOwnerType == owner::server)
			{
				if (m_socket.is_open())
				{
					id = uid;
					
					WriteValidation();
					
					ReadValidation(server);
				}
			}
		}
		
		void ConnectToServer(const boost::asio::ip::tcp::resolver::results_type& endpoints)
		{
			if (m_nOwnerType == owner::client)
			{
				boost::asio::async_connect(m_socket, endpoints,
														[this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint)
														{
															if (!ec)
															{
																ReadValidation();
															}
														});
			}
		}
		
		
		void Disconnect()
		{
			if (IsConnected())
				boost::asio::post(m_asioContext, [this]() { m_socket.close(); });
		}
		
		bool IsConnected() const
		{
			return m_socket.is_open();
		}
		
		void StartListening()
		{
		
		}
	
	public:
		void Send(const message<T>& msg)
		{
			boost::asio::post(m_asioContext,
								 [this, msg]()
								 {
									 bool bWritingMessage = !m_qMessagesOut.empty();
									 m_qMessagesOut.push_back(msg);
									 if (!bWritingMessage)
									 {
										 WriteHeader();
									 }
								 });
		}
	
	
	
	private:
		void WriteHeader()
		{
			boost::asio::async_write(m_socket, boost::asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)),
												[this](std::error_code ec, std::size_t length)
												{
													if (!ec)
													{
														if (m_qMessagesOut.front().body.size() > 0)
														{
															WriteBody();
														}
														else
														{
															m_qMessagesOut.pop_front();
															
															if (!m_qMessagesOut.empty())
															{
																WriteHeader();
															}
														}
													}
													else
													{
														std::cout << "[" << id << "] Write Header Fail.\n";
														m_socket.close();
													}
												});
		}
		
		void WriteBody()
		{
			boost::asio::async_write(m_socket, boost::asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
												[this](std::error_code ec, std::size_t length)
												{
													if (!ec)
													{
														m_qMessagesOut.pop_front();
					
														if (!m_qMessagesOut.empty())
														{
															WriteHeader();
														}
													}
													else
													{
														std::cout << "[" << id << "] Write Body Fail.\n";
														m_socket.close();
													}
												});
		}
		
		void ReadHeader()
		{
			boost::asio::async_read(m_socket, boost::asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header<T>)),
											 [this](std::error_code ec, std::size_t length)
											 {
												 if (!ec)
												 {
													 if (m_msgTemporaryIn.header.size > 0)
													 {
														 m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
														 ReadBody();
													 }
													 else
													 {
														 AddToIncomingMessageQueue();
													 }
												 }
												 else
												 {
													 std::cout << "[" << id << "] Read Header Fail.\n";
													 m_socket.close();
												 }
											 });
		}
		
		void ReadBody()
		{
			boost::asio::async_read(m_socket, boost::asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
											 [this](std::error_code ec, std::size_t length)
											 {
												 if (!ec)
												 {
													 AddToIncomingMessageQueue();
												 }
												 else
												 {
													 std::cout << "[" << id << "] Read Body Fail.\n";
													 m_socket.close();
												 }
											 });
		}
		
		uint64_t scramble(uint64_t nInput)
		{
			uint64_t out = nInput ^ 0xDEADBEEFC0DECAFE;
			out = (out & 0xF0F0F0F0F0F0F0) >> 4 | (out & 0x0F0F0F0F0F0F0F) << 4;
			return out ^ 0xC0DEFACE12345678;
		}
		
		void WriteValidation()
		{
			boost::asio::async_write(m_socket, boost::asio::buffer(&m_nHandshakeOut, sizeof(uint64_t)),
												[this](std::error_code ec, std::size_t length)
												{
													if (!ec)
													{
														if (m_nOwnerType == owner::client)
															ReadHeader();
													}
													else
													{
														m_socket.close();
													}
												});
		}
		
		void ReadValidation(net::server_interface<T>* server = nullptr)
		{
			boost::asio::async_read(m_socket, boost::asio::buffer(&m_nHandshakeIn, sizeof(uint64_t)),
											 [this, server](std::error_code ec, std::size_t length)
											 {
												 if (!ec)
												 {
													 if (m_nOwnerType == owner::server)
													 {
														 if (m_nHandshakeIn == m_nHandshakeCheck)
														 {
															 std::cout << "Client Validated" << std::endl;
															 server->OnClientValidated(this->shared_from_this());
							
															 ReadHeader();
														 }
														 else
														 {
															 std::cout << "Client Disconnected (Fail Validation)" << std::endl;
															 m_socket.close();
														 }
													 }
													 else
													 {
														 m_nHandshakeOut = scramble(m_nHandshakeIn);
						
														 WriteValidation();
													 }
												 }
												 else
												 {
													 std::cout << "Client Disconnected (ReadValidation)" << std::endl;
													 m_socket.close();
												 }
											 });
		}
		
		void AddToIncomingMessageQueue()
		{
			if(m_nOwnerType == owner::server)
				m_qMessagesIn.push_back({ this->shared_from_this(), m_msgTemporaryIn });
			else
				m_qMessagesIn.push_back({ nullptr, m_msgTemporaryIn });
			
			ReadHeader();
		}
	
	protected:
		boost::asio::ip::tcp::socket m_socket;
		
		boost::asio::io_context& m_asioContext;
		
		tsqueue<message<T>> m_qMessagesOut;
		
		tsqueue<owned_message<T>>& m_qMessagesIn;
		
		message<T> m_msgTemporaryIn;
		
		owner m_nOwnerType = owner::server;
		
		uint64_t m_nHandshakeOut = 0;
		uint64_t m_nHandshakeIn = 0;
		uint64_t m_nHandshakeCheck = 0;
		
		uint32_t id = 0;
		
	};
	
	template <typename T>
	class client_interface
	{
	public:
		client_interface()
		{}
		
		virtual ~client_interface()
		{
			Disconnect();
		}
	
	public:
		bool Connect(const std::string& host, const uint16_t port)
		{
			try
			{
				boost::asio::ip::tcp::resolver resolver(m_context);
				boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
				
				m_connection = std::make_unique<connection<T>>(connection<T>::owner::client, m_context, boost::asio::ip::tcp::socket(m_context), m_qMessagesIn);
				
				m_connection->ConnectToServer(endpoints);
				
				thrContext = std::thread([this]() { m_context.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << "Client Exception: " << e.what() << "\n";
				return false;
			}
			return true;
		}
		
		void Disconnect()
		{
			if(IsConnected())
			{
				m_connection->Disconnect();
			}
			
			m_context.stop();
			if (thrContext.joinable())
				thrContext.join();
			
			m_connection.release();
		}
		
		bool IsConnected()
		{
			if (m_connection)
				return m_connection->IsConnected();
			else
				return false;
		}
	
	public:
		void Send(const message<T>& msg)
		{
			if (IsConnected())
				m_connection->Send(msg);
		}
		
		tsqueue<owned_message<T>>& Incoming()
		{
			return m_qMessagesIn;
		}
	
	protected:
		boost::asio::io_context m_context;
		std::thread thrContext;
		std::unique_ptr<connection<T>> m_connection;
	
	private:
		tsqueue<owned_message<T>> m_qMessagesIn;
	};
	
	template<typename T>
	class server_interface
	{
	public:
		server_interface(uint16_t port)
		: m_asioAcceptor(m_asioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
		{
		
		}
		
		virtual ~server_interface()
		{
			Stop();
		}
		
		bool Start()
		{
			try
			{
				WaitForClientConnection();
				
				m_threadContext = std::thread([this]() { m_asioContext.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << "[SERVER] Exception: " << e.what() << "\n";
				return false;
			}
			
			std::cout << "[SERVER] Started!\n";
			return true;
		}
		
		void Stop()
		{
			m_asioContext.stop();
			
			if (m_threadContext.joinable()) m_threadContext.join();
			
			std::cout << "[SERVER] Stopped!\n";
		}
		
		void WaitForClientConnection()
		{
			m_asioAcceptor.async_accept(
			[this](std::error_code ec, boost::asio::ip::tcp::socket socket)
			{
				if (!ec)
				{
					std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << "\n";
					
					std::shared_ptr<connection<T>> newconn =
					std::make_shared<connection<T>>(connection<T>::owner::server,
																					m_asioContext, std::move(socket), m_qMessagesIn);
					
					if (OnClientConnect(newconn))
					{
						m_deqConnections.push_back(std::move(newconn));
						
						m_deqConnections.back()->ConnectToClient(this, nIDCounter++);
						
						std::cout << "[" << m_deqConnections.back()->GetID() << "] Connection Approved\n";
					}
					else
					{
						std::cout << "[-----] Connection Denied\n";
						
					}
				}
				else
				{
					std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
				}
				
				WaitForClientConnection();
			});
		}
		
		void MessageClient(std::shared_ptr<connection<T>> client, const message<T>& msg)
		{
			if (client && client->IsConnected())
			{
				client->Send(msg);
			}
			else
			{
				OnClientDisconnect(client);
				
				client.reset();
				
				m_deqConnections.erase(
				std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
			}
		}
		
		void MessageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr)
		{
			bool bInvalidClientExists = false;
			
			for (auto& client : m_deqConnections)
			{
				if (client && client->IsConnected())
				{
					if(client != pIgnoreClient)
						client->Send(msg);
				}
				else
				{
					OnClientDisconnect(client);
					client.reset();
					
					bInvalidClientExists = true;
				}
			}
			
			if (bInvalidClientExists)
				m_deqConnections.erase(
				std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr), m_deqConnections.end());
		}
		
		void Update(size_t nMaxMessages = -1, bool bWait = false)
		{
			if (bWait) m_qMessagesIn.wait();
			
			size_t nMessageCount = 0;
			while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty())
			{
				auto msg = m_qMessagesIn.pop_front();
				
				OnMessage(msg.remote, msg.msg);
				
				nMessageCount++;
			}
		}
	
	protected:
		virtual bool OnClientConnect(std::shared_ptr<connection<T>> client)
		{
			return false;
		}
		
		virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client)
		{
		
		}
		
		virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T>& msg)
		{
		
		}
	
	public:
		virtual void OnClientValidated(std::shared_ptr<connection<T>> client)
		{
		
		}
	
	
	protected:
		tsqueue<owned_message<T>> m_qMessagesIn;
		
		std::deque<std::shared_ptr<connection<T>>> m_deqConnections;
		
		boost::asio::io_context m_asioContext;
		std::thread m_threadContext;
		
		boost::asio::ip::tcp::acceptor m_asioAcceptor;
		
		uint32_t nIDCounter = 10000;
	};
}



#endif //TEMPLATE_OLD_NET_H
