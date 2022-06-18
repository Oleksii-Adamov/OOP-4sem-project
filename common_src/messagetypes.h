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
};

#endif // MESSAGETYPES_H
