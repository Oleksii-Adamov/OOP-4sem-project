#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

#include <cstdint>
enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerPing,
    MessageAll,
    ServerMessage,
};

#endif // MESSAGETYPES_H
