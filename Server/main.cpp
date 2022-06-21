#include "../common_src/net.h"
#include "../common_src/messagetypes.h"
#include "server_src/custom_json_parser.h"
#include "Database/Database.h"

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

void GetTeacherAssignments(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes> &msg) {
	ID UserId;
	// Get user id
	msg >> UserId;
	// Make sql request
	std::pair<bool, std::vector<Assignment>> assignments =
		Database::selectAllAssignmentUserCreated(UserId);
	// if request is success -> parse vector of assignments in text json
	if (assignments.first) {
		std::string text = ParseToJson(assignments.second);
		uint64_t size = text.size();
		
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::RETURN_TEACHER_ASSIGNMENTS;
		for (char c : text)
			OutgoingMsg << c;
		OutgoingMsg << size;
		
		// Send to client
		client->Send(OutgoingMsg);
	}
}

void JoinClassroomRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	ID UserId;
	ID ClassroomId;
	// Get user and classroom id
	msg >> UserId;
	msg >> ClassroomId;
	// if request is success -> send success message
	// else -> failure
	net::message<CustomMsgTypes> OutgoingMsg;
	if (Database::joinUserToClassroom(UserId, ClassroomId))
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_JOIN_CLASSROOM;
	else
		OutgoingMsg.header.id = CustomMsgTypes::FAILURE_JOIN_CLASSROOM;
	
	client->Send(OutgoingMsg);
}

void CreateClassroomRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	ID TeacherUserId;
	uint64_t size;
	std::string ClassroomName;
	
	// get teacher user id and classroom name
	msg >> TeacherUserId;
	msg >> size;
	for (uint64_t i = 0; i < size; i++) {
		char c;
		msg >> c;
		ClassroomName = c + ClassroomName;
	}
	// if request is success -> send success message
	// else -> failure
	net::message<CustomMsgTypes> OutgoingMsg;
	if (Database::createNewClassroom(TeacherUserId, ClassroomName))
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_CREATE_CLASSROOM;
	else
		OutgoingMsg.header.id = CustomMsgTypes::FAILURE_CREATE_CLASSROOM;

	client->Send(OutgoingMsg);
}

void GetStudentAssignmentSessionAnswer(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
//	static std::pair<bool, std::string> getStudentAssignmentSessionAnswer(ID StudentUserId, ID AssignmentSessionId);
	ID StudentUserId;
	ID AssignmentSessionId;
	msg >> StudentUserId;
	msg >> AssignmentSessionId;
	std::pair<bool, std::string> StudentAssignmentSessionAnswer =
		Database::getStudentAssignmentSessionAnswer(StudentUserId,
																								AssignmentSessionId);
	if (StudentAssignmentSessionAnswer.first) {
		uint64_t size = StudentAssignmentSessionAnswer.second.size();
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id =
			CustomMsgTypes::RETURN_STUDENT_ASSIGNMENT_SESSION_ANSWER;
		for (char c : StudentAssignmentSessionAnswer.second)
			msg << c;
		msg << size;
		
		client->Send(OutgoingMsg);
	}
}

void GetAllStudentAssignmentSessionAnswers(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	ID AssignmentSessionId;
	msg >> AssignmentSessionId;
	std::pair<bool, std::vector<StudentAssignmentSessionInfoForTeacher>>
		StudentAssignmentSessionInfosForTeacher;
	StudentAssignmentSessionInfosForTeacher =
		Database::getAllStudentAssignmentSessionAnswers(AssignmentSessionId);
	if (StudentAssignmentSessionInfosForTeacher.first) {
		std::string text =
			ParseToJson(StudentAssignmentSessionInfosForTeacher.second);
		uint64_t size = text.size();
		
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id =
			CustomMsgTypes::RETURN_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS;
		for (char c : text)
			OutgoingMsg << c;
		OutgoingMsg << size;
		
		client->Send(OutgoingMsg);
	}
}

void RegistrationRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	uint64_t sizeLogin;
	std::string login;
	std::pair<bool, bool> UniqueLogin;
	
	msg >> sizeLogin;
	for (uint64_t i = 0; i < sizeLogin; i++) {
		char c;
		msg >> c;
		login = c + login;
	}
	
	UniqueLogin = Database::checkLogIn(login);
	if (UniqueLogin.first) {
		net::message<CustomMsgTypes> OutgoingMsg;
		if (UniqueLogin.second) {
			uint64_t sizePassword;
			std::string password;
			uint64_t sizeUserName;
			std::string userName;
			
			User newUser;
			newUser.setLogin(login);
			
			msg >> sizePassword;
			for (uint64_t i = 0; i < sizePassword; i++) {
				char c;
				msg >> c;
				password = c + password;
			}
			
			msg >> sizeUserName;
			for (uint64_t i = 0; i < sizeUserName; i++) {
				char c;
				msg >> c;
				userName = c + userName;
			}
			newUser.setUserName(userName);
			
			if (Database::createNewUser(newUser, password)) {
				OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_REGISTRATION_REQUEST;
				client->Send(OutgoingMsg);
			}
		} else {
			OutgoingMsg.header.id = CustomMsgTypes::FAILURE_REGISTRATION_REQUEST;
			client->Send(OutgoingMsg);
		}
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
				
			case CustomMsgTypes::GET_TEACHER_ASSIGNMENTS:
				GetTeacherAssignments(client, msg);
				break;
				
			case CustomMsgTypes::JOIN_CLASSROOM_REQUEST:
				JoinClassroomRequest(client, msg);
				break;
				
			case CustomMsgTypes::CREATE_CLASSROOM_REQUEST:
				CreateClassroomRequest(client, msg);
				break;
				
			case CustomMsgTypes::GET_STUDENT_ASSIGNMENT_SESSION_ANSWER:
				GetStudentAssignmentSessionAnswer(client, msg);
				break;
				
			case CustomMsgTypes::GET_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS:
				GetAllStudentAssignmentSessionAnswers(client, msg);
				break;
				
			case CustomMsgTypes::REGISTRATION_REQUEST:
				RegistrationRequest(client, msg);
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