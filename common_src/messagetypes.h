#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

#include <cstdint>
enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	
	SERVER_DOWN,
	ERROR_DATABASE,
	
	REGISTRATION_REQUEST,
	SUCCESS_REGISTRATION_REQUEST,
	FAILURE_REGISTRATION_REQUEST,
	
	LOGIN_REQUEST,
	SUCCESS_LOGIN_REQUEST,
	FAILURE_LOGIN_REQUEST,
	
	GET_TEST_ASSIGNMENT,
	RETURN_TEST_ASSIGMENT,
	
	GET_CREATED_ASSIGNMENT,
	RETURN_CREATED_ASSIGNMENT,
	
	SUBMIT_STUDENT_ASSIGNMENT,
	SUCCESS_SUBMIT_STUDENT_ASSIGNMENT,
	EVALUATE_STUDENT_ASSIGNMENT,
	SUCCESS_EVALUATE_STUDENT_ASSIGNMENT,
	
	UPDATE_ASSIGNMENT,
	SUCCESS_UPDATE_ASSIGNMENT,
	
	CREATE_NEW_ASSIGNMENT_REQUEST,
	SUCCESS_CREATE_NEW_ASSIGNMENT,
	FAILURE_CREATE_NEW_ASSIGNMENT,
	
	SEND_ASSIGNMENT_TO_CLASSROOM_REQUEST,
	SUCCESS_SEND_ASSIGNMENT_TO_CLASSROOM,
	FAILURE_SEND_ASSIGNMENT_TO_CLASSROOM,
	
	GET_TEACHER_CLASSROOMS,
	RETURN_TEACHER_CLASSROOMS,
	
	GET_STUDENT_CLASSROOMS,
	RETURN_STUDENT_CLASSROOMS,
	
	GET_TEACHER_ASSIGNMENTS,
	RETURN_TEACHER_ASSIGNMENTS,
	
	JOIN_CLASSROOM_REQUEST,
	SUCCESS_JOIN_CLASSROOM,
	FAILURE_JOIN_CLASSROOM,
	
	CREATE_CLASSROOM_REQUEST,
	SUCCESS_CREATE_CLASSROOM,
	FAILURE_CREATE_CLASSROOM,
	
	GET_STUDENT_ASSIGNMENT_SESSION_ANSWER,
	RETURN_STUDENT_ASSIGNMENT_SESSION_ANSWER,
	
	GET_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS,
	RETURN_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS,
	
	GET_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO,
	RETURN_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO,
	
	GET_ALL_ASSIGNMENTS_OF_CLASSROOM_TEACHER_INFO,
	RETURN_ALL_ASSIGNMENTS_OF_CLASSROOM_TEACHER_INFO,
};

#endif // MESSAGETYPES_H
