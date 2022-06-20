#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

#include <cstdint>
enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerPing,
    MessageAll,
    ServerMessage,
    GET_TEST_ASSIGNMENT,
    RETURN_TEST_ASSIGMENT,
		
		GET_TEACHER_CLASSROOMS,
		RETURN_TEACHER_CLASSROOMS,
		
		GET_STUDENT_CLASSROOMS,
		RETURN_STUDENT_CLASSROOMS,
};

#endif // MESSAGETYPES_H
