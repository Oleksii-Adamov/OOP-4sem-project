#include "DatabaseAuthorizationType.h"


void DatabaseAuthorizationType::setUserId(const ID& user_id)
{
    user_id_ = user_id;
}

void DatabaseAuthorizationType::setPassword(const std::string& password)
{
    password_ = password;
}

ID DatabaseAuthorizationType::getUserId() const
{
    return user_id_;
}

std::string DatabaseAuthorizationType::getPassword() const
{
    return password_;
}