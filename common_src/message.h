#pragma once

#include "common_net.h"

namespace net
{
  /*!
  * \brief message_header - struct that implements message_header
  * 
  * This structure is part of the message structure. 
  * Stores two parameters - the id, which specifies 
  * the purpose of the message, and the size, which specifies 
  * the size in bytes of the main message.
  */
  template <typename T>
	struct message_header
	{
		T id{};
		uint32_t size = 0;
	};
	
  /*!
  * \brief message - struct that implements message.
  * 
  * The message consists of the message header and the body. The body stores 
  * the raw byte vector. Typed data when written to the message is converted 
  * to raw bytes and added to the end of the vector. When reading from 
  * a message, raw bytes are removed from the end of the vector and passed 
  * to typed data. Fixed-size data should be used to effectively write and 
  * read messages.
  */
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
			static_assert(std::is_standard_layout<DataType>::value, 
                    "Data is too complex to be pushed into vector");
			
			size_t i = msg.body.size();
			
			msg.body.resize(msg.body.size() + sizeof(DataType));
			
			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
			
			msg.header.size = msg.size();
			
			return msg;
		}
		
		template<typename DataType>
		friend message<T>& operator >> (message<T>& msg, DataType& data)
		{
			static_assert(std::is_standard_layout<DataType>::value, 
                    "Data is too complex to be pulled from vector");
			
			size_t i = msg.body.size() - sizeof(DataType);
			
			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
			
			msg.body.resize(i);
			
			msg.header.size = msg.size();
			
			return msg;
		}
	};
	
	template <typename T>
	class connection;
	
  /*!
  * \brief owned_message - struct that implements owned message.
  * 
  * The owned message differs from the common message by the 
  * presence of a connection that has an owner.
  */
	template <typename T>
	struct owned_message
	{
		std::shared_ptr<connection<T>> remote = nullptr;
		message<T> msg;
		
		friend std::ostream& operator<<(std::ostream& os,
                                    const owned_message<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
}