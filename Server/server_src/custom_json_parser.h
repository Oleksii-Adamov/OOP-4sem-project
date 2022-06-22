#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../../common_src/Entities/Entities.h"
#include "../../common_src/studentassignmentsessioninfo.h"
#include "../../common_src/studentassignmentsessioninfoforteacher.h"
#include "../../common_src/assignmentsessioninfo.h"

namespace bpt = boost::property_tree;

std::string ParseToJson(const std::vector<Classroom>& classrooms) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	// Converting classrooms in json class and put in array
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

std::string ParseToJson(const std::vector<Assignment>& assignments) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	// Converting classrooms in json class and put in array
	for (const Assignment& assignment : assignments) {
		bpt::ptree element;
		element.put("assignment_id", assignment.getAssignmentId());
		element.put("teacher_user_id", assignment.getTeacherUserId());
		element.put("assignment_name", assignment.getAssignmentName());
		element.put("assignment_creation_date",
								assignment.getAssignmentCreationDate());
		element.put("assignment_data", assignment.getAssignmentData());
		element.put("assignment_max_score", assignment.getAssignmentMaxScore());
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("Assignments", array);
	bpt::write_json(text, json);
	
	return text.str();
}

std::string ParseToJson(
	const std::vector<StudentAssignmentSessionInfoForTeacher>& objects) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	for (const StudentAssignmentSessionInfoForTeacher& object : objects) {
		bpt::ptree element;
		auto r =
			object.student_assignment_session.getStudentAssignmentSessionStatus();
		std::string status;
		if (r == StudentAssignmentSessionStatus::checked)
			status = "checked";
		else if (r == StudentAssignmentSessionStatus::not_submitted)
			status = "not_submitted";
		else if (r == StudentAssignmentSessionStatus::submitted)
			status = "submitted";
		
		element.put("StudentAssignmentSession.student_user_id",
								object.student_assignment_session.getStudentUserId());
		element.put("StudentAssignmentSession.assignment_session_id",
								object.student_assignment_session.getAssignmentSessionId());
		element.put("StudentAssignmentSession.student_assignment_session_status",
								status);
		element.put("StudentAssignmentSession.student_assignment_session_answer",
				object.student_assignment_session.getStudentAssignmentSessionAnswer());
		element.put("StudentAssignmentSession.student_assignment_session_score",
					object.student_assignment_session.getStudentAssignmentSessionScore());
		element.put("StudentAssignmentSession.student_assignment_session_finish_date",
			object.student_assignment_session.getStudentAssignmentSessionFinishDate());
		
		element.put("User.user_id", object.student.getUserId());
		element.put("User.login", object.student.getLogin());
		element.put("User.user_name", object.student.getUserId());
		
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("StudentAssignmentSessionInfosForTeacher", array);
	bpt::write_json(text, json);
	
	return text.str();
}

std::string ParseToJson(const Assignment& assignment) {
	std::stringstream text;
	bpt::ptree json;
	json.put("Assignment.assignment_id", assignment.getAssignmentId());
	json.put("Assignment.teacher_user_id", assignment.getTeacherUserId());
	json.put("Assignment.assignment_name", assignment.getAssignmentName());
	json.put("Assignment.assignment_creation_date",
					 assignment.getAssignmentCreationDate());
	json.put("Assignment.assignment_data", assignment.getAssignmentData());
	json.put("Assignment.assignment_max_score",
					 assignment.getAssignmentMaxScore());
	bpt::write_json(text, json);
	return text.str();
}

std::string ParseToJson(
	const std::vector<StudentAssignmentSessionInfo>& objects) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	for (const StudentAssignmentSessionInfo& object : objects) {
		bpt::ptree element;
		auto r =
			object.student_assignment_session.getStudentAssignmentSessionStatus();
		std::string status;
		if (r == StudentAssignmentSessionStatus::checked)
			status = "checked";
		else if (r == StudentAssignmentSessionStatus::not_submitted)
			status = "not_submitted";
		else if (r == StudentAssignmentSessionStatus::submitted)
			status = "submitted";
		
		element.put("StudentAssignmentSession.student_user_id",
								object.student_assignment_session.getStudentUserId());
		element.put("StudentAssignmentSession.assignment_session_id",
								object.student_assignment_session.getAssignmentSessionId());
		element.put("StudentAssignmentSession.student_assignment_session_status",
								status);
		element.put("StudentAssignmentSession.student_assignment_session_answer",
				object.student_assignment_session.getStudentAssignmentSessionAnswer());
		element.put("StudentAssignmentSession.student_assignment_session_score",
					object.student_assignment_session.getStudentAssignmentSessionScore());
		element.put("StudentAssignmentSession.student_assignment_session_finish_date",
		object.student_assignment_session.getStudentAssignmentSessionFinishDate());
		
		element.put("AssignmentSession.assignment_session_id",
								object.assignment_session.getAssignmentSessionId());
		element.put("AssignmentSession.classroom_id",
								object.assignment_session.getClassroomId());
		element.put("AssignmentSession.assignment_id",
								object.assignment_session.getAssignmentId());
		element.put("AssignmentSession.assignment_session_start_date",
								object.assignment_session.getAssignmentSessionStartDate());
		element.put("AssignmentSession.assignment_session_end_date",
								object.assignment_session.getAssignmentSessionEndDate());
		
		element.put("Assignment.assignment_id",
								object.assignment.getAssignmentId());
		element.put("Assignment.teacher_user_id",
								object.assignment.getTeacherUserId());
		element.put("Assignment.assignment_name",
								object.assignment.getAssignmentName());
		element.put("Assignment.assignment_creation_date",
								object.assignment.getAssignmentCreationDate());
		element.put("Assignment.assignment_data",
								object.assignment.getAssignmentData());
		element.put("Assignment.assignment_max_score",
								object.assignment.getAssignmentMaxScore());
		
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("StudentAssignmentSessionInfos", array);
	bpt::write_json(text, json);
	
	return text.str();
}

std::string ParseToJson(
	const std::vector<AssignmentSessionInfo>& objects) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	for (AssignmentSessionInfo object : objects) {
		bpt::ptree element;
		
		element.put("AssignmentSession.assignment_session_id",
								object.assignment_session.getAssignmentSessionId());
		element.put("AssignmentSession.classroom_id",
								object.assignment_session.getClassroomId());
		element.put("AssignmentSession.assignment_id",
								object.assignment_session.getAssignmentId());
		element.put("AssignmentSession.assignment_session_start_date",
								object.assignment_session.getAssignmentSessionStartDate());
		element.put("AssignmentSession.assignment_session_end_date",
								object.assignment_session.getAssignmentSessionEndDate());
		
		element.put("Assignment.assignment_id",
								object.assignment.getAssignmentId());
		element.put("Assignment.teacher_user_id",
								object.assignment.getTeacherUserId());
		element.put("Assignment.assignment_name",
								object.assignment.getAssignmentName());
		element.put("Assignment.assignment_creation_date",
								object.assignment.getAssignmentCreationDate());
		element.put("Assignment.assignment_data",
								object.assignment.getAssignmentData());
		element.put("Assignment.assignment_max_score",
								object.assignment.getAssignmentMaxScore());
		
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("AssignmentSessionInfos", array);
	bpt::write_json(text, json);
	
	return text.str();
}