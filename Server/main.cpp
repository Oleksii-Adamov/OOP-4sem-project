#include "../common_src/net.h"
#include "Database/Database.h"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class CustomServer : public net::server_interface<CustomMsgTypes>
{
public:
	CustomServer(uint16_t nPort) : net::server_interface<CustomMsgTypes>(nPort)
	{
	
	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<net::connection<CustomMsgTypes>> client)
	{
		net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}
	
	virtual void OnClientDisconnect(std::shared_ptr<net::connection<CustomMsgTypes>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}
	
	virtual void OnMessage(std::shared_ptr<net::connection<CustomMsgTypes>> client, net::message<CustomMsgTypes>& msg)
	{
		switch (msg.header.id)
		{
			case CustomMsgTypes::ServerPing:
			{
				std::cout << "[" << client->GetID() << "]: Server Ping\n";
				
				client->Send(msg);
			}
				break;
			
			case CustomMsgTypes::MessageAll:
			{
				std::cout << "[" << client->GetID() << "]: Message All\n";
				
				net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::ServerMessage;
				msg << client->GetID();
				MessageAllClients(msg, client);
				
			}
				break;

            case CustomMsgTypes::ServerMessage:
            {
                try {
                    uint32_t string_size;
                    msg >> string_size;
                    std::string client_message_data = "";
                    for (uint32_t i = 0; i < string_size; i++) {
                        char c;
                        msg >> c;
                        client_message_data = c + client_message_data;
                    }
                    std::cout << "[" << client->GetID() << "]: Message: \n" << client_message_data << "\n";
                }
                catch(std::exception& e)
                {
                    std::cout << "Exception: " << e.what();
                }
            }
                break;
		}
	}
};

int main()
{
    Database::init();
	CustomServer server(60000);
	server.Start();
	
	while (1)
	{
		server.Update(-1, true);
	}

    Database::clear();
	return 0;
}