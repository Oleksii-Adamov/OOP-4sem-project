#include "../common_src/net.h"
#include "../common_src/messagetypes.h"
#include "Database/Database.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace bpt = boost::property_tree;

class CustomServer : public net::server_interface<CustomMsgTypes> {
public:
	CustomServer(uint16_t nPort) : net::server_interface<CustomMsgTypes>(nPort) {

	}

protected:
	virtual bool
	OnClientConnect(std::shared_ptr<net::connection<CustomMsgTypes>> client) {
		net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}

	virtual void
	OnClientDisconnect(std::shared_ptr<net::connection<CustomMsgTypes>> client) {
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}

	virtual void
	OnMessage(std::shared_ptr<net::connection<CustomMsgTypes>> client,
						net::message<CustomMsgTypes> &msg) {
		switch (msg.header.id) {
			case CustomMsgTypes::ServerPing: {
				std::cout << "[" << client->GetID() << "]: Server Ping\n";

				client->Send(msg);
			}
				break;

			case CustomMsgTypes::MessageAll: {
				std::cout << "[" << client->GetID() << "]: Message All\n";

				net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::ServerMessage;
				msg << client->GetID();
				MessageAllClients(msg, client);

			}
				break;

			case CustomMsgTypes::ServerMessage: {
				try {
				}
				catch (std::exception &e) {
					std::cout << "Exception: " << e.what();
				}
			}
				break;
			
			case CustomMsgTypes::GET_TEST_ASSIGNMENT: {
				std::cout << "GETTING TEST ASSIGMENT..." << std::endl;
				std::ifstream file("../../from_teacher_to_server.json");
				std::stringstream json;
				bpt::ptree tree;
				if (file) {
					json << file.rdbuf();
					file.close();
					bpt::read_json(json, tree);
					json.str("");
					
					bpt::ptree &array = tree.get_child("Assignment");
					for (auto& e : array) {
						if (e.second.get<std::string>("type") == "test_assignment") {
							bpt::ptree &answers = e.second.get_child("content.answers");
							for (auto& answer : answers)
								answer.second.erase("is_correct");
						}
					}
					bpt::write_json(json, tree);
					
					net::message<CustomMsgTypes> msg;
					msg.header.id = CustomMsgTypes::RETURN_TEST_ASSIGMENT;
					uint64_t size = json.str().size();
					std::string text = json.str();
					for (char c : text)
						msg << c;
					msg << size;
					
					client->Send(msg);
				}
			}
		}
	}
};

int main()
{
    Database::init("Database.db");
	CustomServer server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}
	
	return 0;
}