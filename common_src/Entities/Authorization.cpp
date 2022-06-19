#include "Authorization.h"


void Authorization::setUserId(const ID& user_id)
{
    user_id_ = user_id;
}

void Authorization::setPassword(const std::string& password)
{
    password_ = password;
}

ID Authorization::getUserId() const
{
    return user_id_;
}

std::string Authorization::getPassword() const
{
    return password_;
}