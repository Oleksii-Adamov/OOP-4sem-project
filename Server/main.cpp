#include "../common_src/net.h"
#include "../common_src/messagetypes.h"
#include "server_src/custom_json_parser.h"
#include "Database/Database.h"
#include "Database/DatabaseLog.h"

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
	} else {
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
		"SQL REQUEST 'SELECT_ALL_CLASSROOMS_WHERE_USER_IS_TEACHER' RETURNS FALSE");
		
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
	} else {
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
			"SQL REQUEST 'SELECT_ALL_ASSIGNMENT_USER_CREATED' RETURNS FALSE");
		
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
			OutgoingMsg << c;
		OutgoingMsg << size;
		
		client->Send(OutgoingMsg);
	} else {
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
			"REQUEST 'GET_STUDENT_ASSIGNMENT_SESSION_ANSWER' RETURNS FALSE");
		
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
	} else {
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
			"REQUEST 'GET_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS' RETURNS FALSE");
		
		client->Send(OutgoingMsg);
	}
}

void RegistrationRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	std::cout << " [ " << client->GetID() << " ] "
						<< "REGISTRATION_REQUEST" << std::endl;
	uint64_t sizeLogin;
	std::string login;
	std::pair<bool, bool> UniqueLogin;
	
	msg >> sizeLogin;
	for (uint64_t i = 0; i < sizeLogin; i++) {
		char c;
		msg >> c;
		login = c + login;
	}
	
	UniqueLogin = Database::checkUniqueLogin(login);
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

void LoginRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	std::cout << "Point0" << std::endl;
	uint64_t sizeLogin;
	std::string login;
	uint64_t sizePassword;
	std::string password;
	std::pair<bool, User> checkLogIn;
	
	msg >> sizeLogin;
	for (uint64_t i = 0; i < sizeLogin; i++) {
		char c;
		msg >> c;
		login = c + login;
	}
	
	msg >> sizePassword;
	for (uint64_t i = 0; i < sizePassword; i++) {
		char c;
		msg >> c;
		password = c + password;
	}
	std::cout << "Point1" << std::endl;
	checkLogIn = Database::checkLogIn(login, password);
	std::cout << "Point2" << std::endl;
	if (checkLogIn.first) {
		std::cout << "Point3" << std::endl;
		net::message<CustomMsgTypes> OutgoingMsg;
		if (checkLogIn.second.getUserId()) {
			std::cout << "Point4.1" << std::endl;
			OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_LOGIN_REQUEST;
			ID UserId = checkLogIn.second.getUserId();
			std::string UserLogin = checkLogIn.second.getLogin();
			uint64_t sizeUserLogin = UserLogin.size();
			std::string UserName = checkLogIn.second.getUserName();
			uint64_t sizeUserName = UserName.size();
			
			for (char c : UserName)
				OutgoingMsg << c;
			OutgoingMsg << sizeUserName;
			
			for (char c : UserLogin)
				OutgoingMsg << c;
			OutgoingMsg << sizeUserLogin;
			
			OutgoingMsg << UserId;
			
			client->Send(OutgoingMsg);
		} else {
			std::cout << "Point4.2" << std::endl;
			OutgoingMsg.header.id = CustomMsgTypes::FAILURE_LOGIN_REQUEST;
			client->Send(OutgoingMsg);
		}
	}
}

void GetCreatedAssignment(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
//	static std::pair<bool, std::string> getAssignmentData(ID AssignmentId);
	ID AssignmentId;
	std::pair<bool, std::string> CreatedAssignment;
	
	msg >> AssignmentId;
	
	CreatedAssignment = Database::getAssignmentData(AssignmentId);
	
	if (CreatedAssignment.first) {
		net::message<CustomMsgTypes> OutgoingMsg;
		uint64_t size = CreatedAssignment.second.size();
		std::string assignment = CreatedAssignment.second;
		OutgoingMsg.header.id = CustomMsgTypes::RETURN_CREATED_ASSIGNMENT;
		for (char c : assignment)
			OutgoingMsg << c;
		OutgoingMsg << size;
		
		client->Send(OutgoingMsg);
	} else {
		net::message<CustomMsgTypes> OutgoingMsg;
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
		"SQL REQUEST 'GET_ASSIGNMENT_DATA' RETURNS FALSE");
		
		client->Send(OutgoingMsg);
	}
}

void SubmitStudentAssignment(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
//	static bool submitStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo);
	ID StudentUserId;
	ID AssignmentSessionId;
	uint64_t sizeStudentAssignmentSessionAnswer;
	std::string StudentAssignmentSessionAnswer;
	
	StudentAssignmentSession UpdatedInfo;
	
	msg >> StudentUserId;
	msg >> AssignmentSessionId;
	
	msg >> sizeStudentAssignmentSessionAnswer;
	for (uint64_t i = 0; i < sizeStudentAssignmentSessionAnswer; i++) {
		char c;
		msg >> c;
		StudentAssignmentSessionAnswer = c + StudentAssignmentSessionAnswer;
	}
	
	UpdatedInfo.setStudentUserId(StudentUserId);
	UpdatedInfo.setAssignmentSessionId(AssignmentSessionId);
	UpdatedInfo.setStudentAssignmentSessionAnswer(StudentAssignmentSessionAnswer);
	
	net::message<CustomMsgTypes> OutgoingMsg;
	if (Database::submitStudentAssignmentSession(UpdatedInfo))
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_SUBMIT_STUDENT_ASSIGNMENT;
	else {
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
			"SQL REQUEST 'SUBMIT_STUDENT_ASSIGNMENT_SESSION' RETURNS FALSE");
	}
	
	client->Send(OutgoingMsg);
}

void EvaluateStudentAssignment(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
//	static bool evaluateStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo);
	ID StudentUserId;
	ID AssignmentSessionId;
	int32_t StudentAssignmentSessionScore;
	
	StudentAssignmentSession UpdatedInfo;
	
	msg >> StudentUserId;
	msg >> AssignmentSessionId;
	msg >> StudentAssignmentSessionScore;
	
	UpdatedInfo.setStudentUserId(StudentUserId);
	UpdatedInfo.setAssignmentSessionId(AssignmentSessionId);
	UpdatedInfo.setStudentAssignmentSessionScore(StudentAssignmentSessionScore);
	
	net::message<CustomMsgTypes> OutgoingMsg;
	if (Database::evaluateStudentAssignmentSession(UpdatedInfo))
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_EVALUATE_STUDENT_ASSIGNMENT;
	else {
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
		"SQL REQUEST 'EVALUATE_STUDENT_ASSIGNMENT_SESSION' RETURNS FALSE");
	}
	
	client->Send(OutgoingMsg);
}

void UpdateAssignment(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
//	static std::pair<bool, Assignment> updateAssignment(const Assignment& UpdatedInfo);
	ID AssignmentId;
	ID TeacherUserId;
	uint64_t sizeAssignmentData;
	std::string AssignmentData;
	int32_t AssignmentMaxScore;
	
	Assignment UpdatedInfo;
	std::pair<bool, Assignment> assignment;
	
	msg >> AssignmentId;
	msg >> TeacherUserId;
	
	msg >> sizeAssignmentData;
	for (uint64_t i = 0; i < sizeAssignmentData; i++) {
		char c;
		msg >> c;
		AssignmentData = c + AssignmentData;
	}
	
	msg >> AssignmentMaxScore;
	
	UpdatedInfo.setAssignmentId(AssignmentId);
	UpdatedInfo.setTeacherUserId(TeacherUserId);
	UpdatedInfo.setAssignmentData(AssignmentData);
	UpdatedInfo.setAssignmentMaxScore(AssignmentMaxScore);
	
	assignment = Database::updateAssignment(UpdatedInfo);
	
	net::message<CustomMsgTypes> OutgoingMsg;
	if (assignment.first) {
		std::string text = ParseToJson(assignment.second);
		uint64_t size = text.size();
		
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_UPDATE_ASSIGNMENT;
		for (char c : text)
			OutgoingMsg << c;
		OutgoingMsg << size;
	} else {
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error("SQL REQUEST 'UPDATE_ASSIGNMENT' RETURNS FALSE");
	}
	
	client->Send(OutgoingMsg);
}

void CreateNewAssignmentRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
//	static std::pair<bool, Assignment> createNewAssignment(const Assignment& NewAssignment);
	ID TeacherUserId;
	uint64_t sizeAssignmentName;
	std::string AssignmentName;
	uint64_t sizeAssignmentData;
	std::string AssignmentData;
	int32_t AssignmentMaxScore;
	
	Assignment NewAssignment;
	std::pair<bool, Assignment> assignment;
	
	msg >> TeacherUserId;
	
	msg >> sizeAssignmentName;
	for (uint64_t i = 0; i < sizeAssignmentName; i++) {
		char c;
		msg >> c;
		AssignmentName = c + AssignmentName;
	}
	
	msg >> sizeAssignmentData;
	for (uint64_t i = 0; i < sizeAssignmentData; i++) {
		char c;
		msg >> c;
		AssignmentData = c + AssignmentData;
	}
	
	msg >> AssignmentMaxScore;
	
	NewAssignment.setTeacherUserId(TeacherUserId);
	NewAssignment.setAssignmentName(AssignmentName);
	NewAssignment.setAssignmentData(AssignmentData);
	NewAssignment.setAssignmentMaxScore(AssignmentMaxScore);
	
	assignment = Database::createNewAssignment(NewAssignment);
	net::message<CustomMsgTypes> OutgoingMsg;
	if (assignment.first) {
		std::string text = ParseToJson(assignment.second);
		uint64_t size = text.size();
		
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_CREATE_NEW_ASSIGNMENT;
		for (char c : text)
			OutgoingMsg << c;
		OutgoingMsg << size;
	} else {
		OutgoingMsg.header.id = CustomMsgTypes::FAILURE_CREATE_NEW_ASSIGNMENT;
	}
	
	client->Send(OutgoingMsg);
}

void SendAssignmentToClassroomRequest(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	ID AssignmentId;
	ID ClassroomId;
	uint64_t sizeEndDate;
	std::string EndDate;
	
	msg >> AssignmentId;
	msg >> ClassroomId;
	
	msg >> sizeEndDate;
	for (uint64_t i = 0; i < sizeEndDate; i++) {
		char c;
		msg >> c;
		EndDate = c + EndDate;
	}
	
	net::message<CustomMsgTypes> OutgoingMsg;
	if (Database::sendAssignmentToClassroom(AssignmentId, ClassroomId, EndDate))
		OutgoingMsg.header.id = CustomMsgTypes::SUCCESS_SEND_ASSIGNMENT_TO_CLASSROOM;
	else
		OutgoingMsg.header.id = CustomMsgTypes::FAILURE_SEND_ASSIGNMENT_TO_CLASSROOM;
	
	client->Send(OutgoingMsg);
}

void GetAllAssignmentsOfClassroomStudentInfo(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	ID StudentUserId;
	ID ClassroomId;
//	static std::pair<bool, std::vector<StudentAssignmentSessionInfo>>
//	selectAllAssignmentsOfClassroomStudentInfo(ID StudentUserId, ID ClassroomId);
	msg >> StudentUserId;
	msg >> ClassroomId;
	
	std::pair<bool, std::vector<StudentAssignmentSessionInfo>>
		AssignmentsOfClassroomStudentInfo;
	AssignmentsOfClassroomStudentInfo =
		Database::selectAllAssignmentsOfClassroomStudentInfo(StudentUserId,
																												 ClassroomId);
	net::message<CustomMsgTypes> OutgoingMsg;
	if (AssignmentsOfClassroomStudentInfo.first) {
		std::string text = ParseToJson(AssignmentsOfClassroomStudentInfo.second);
		uint64_t size = text.size();
		
		OutgoingMsg.header.id =
			CustomMsgTypes::RETURN_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO;
		for (char c : text)
			OutgoingMsg << c;
		OutgoingMsg << size;
	} else {
		OutgoingMsg.header.id = CustomMsgTypes::ERROR_DATABASE;
		DatabaseLog::error(
		"SQL REQUEST 'SELECT_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO' RETURNS FALSE");
	}
	
	client->Send(OutgoingMsg);
}

void GetAllAssignmentsOfClassroomTeacherInfo(
	const std::shared_ptr<net::connection<CustomMsgTypes>>& client,
	net::message<CustomMsgTypes>& msg) {
	
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
				
			case CustomMsgTypes::LOGIN_REQUEST:
				LoginRequest(client, msg);
				break;
				
			case CustomMsgTypes::GET_CREATED_ASSIGNMENT:
				GetCreatedAssignment(client, msg);
				break;
				
			case CustomMsgTypes::SUBMIT_STUDENT_ASSIGNMENT:
				SubmitStudentAssignment(client, msg);
				break;
			
			case CustomMsgTypes::EVALUATE_STUDENT_ASSIGNMENT:
				EvaluateStudentAssignment(client, msg);
				break;
				
			case CustomMsgTypes::UPDATE_ASSIGNMENT:
				UpdateAssignment(client, msg);
				break;
				
			case CustomMsgTypes::CREATE_NEW_ASSIGNMENT_REQUEST:
				CreateNewAssignmentRequest(client, msg);
				break;
				
			case CustomMsgTypes::SEND_ASSIGNMENT_TO_CLASSROOM_REQUEST:
				SendAssignmentToClassroomRequest(client, msg);
				break;
				
			case CustomMsgTypes::GET_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO:
				GetAllAssignmentsOfClassroomStudentInfo(client, msg);
				break;
			
			case CustomMsgTypes::GET_ALL_ASSIGNMENTS_OF_CLASSROOM_TEACHER_INFO:
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