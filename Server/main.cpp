#include "../common_src/net.h"
#include "../common_src/messagetypes.h"
#include "Database/Database.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace bpt = boost::property_tree;

std::string ParseToJson(const std::vector<Classroom>& classrooms) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	
	for (const Classroom& classroom : classrooms) {
		bpt::ptree element;
		element.put("classroom_id", classroom.getClassroomId());
		element.put("teacher_user_id", classroom.getTeacherUserId());
		element.put("name", classroom.getName());
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("Classrooms", array);
	bpt::write_json(text, json);
	
	return text.str();
}

void GetTeacherClassrooms(
const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
net::message<CustomMsgTypes> &msg) {
	ID UserId;
	// Get user id
	msg >> UserId;
	// Make sql request
	std::pair<bool, std::vector<Classroom>> classrooms =
	Database::selectAllClassroomsWhereUserIsTeacher(UserId);
	// If request is success -> parse vector of classrooms in text json
	if (classrooms.first) {
		// Parsing vector of classrooms in text json
		std::string text = ParseToJson(classrooms.second);
		uint64_t size = text.size();
		
		// Writing text json in outgoing message
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::RETURN_TEACHER_CLASSROOMS;
		for (char c : text)
			OutgoingMsg << c;
		OutgoingMsg << size;
		
		// Send to client
		client->Send(OutgoingMsg);
	}
}

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
				break;
			
			case CustomMsgTypes::GET_TEACHER_CLASSROOMS:
				GetTeacherClassrooms(client, msg);
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
	
	return 0;
}