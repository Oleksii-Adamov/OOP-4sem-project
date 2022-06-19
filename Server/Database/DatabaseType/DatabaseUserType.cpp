#include "DatabaseUserType.h"


void DatabaseUserType::setUserId(const ID& user_id)
{
    user_id_ = user_id;
}

void DatabaseUserType::setLogin(const std::string& login)
{
    login_ = login;
}

void DatabaseUserType::setUserName(const std::string& user_name)
{
    user_name_ = user_name;
}

ID DatabaseUserType::getUserId() const
{
    return user_id_;
}

std::string DatabaseUserType::getLogin() const
{
    return login_;
}

std::string DatabaseUserType::getUserName() const
{
    return user_name_;
}