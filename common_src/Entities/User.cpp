#include "User.h"


void User::setUserId(const ID& user_id)
{
    user_id_ = user_id;
}

void User::setLogin(const std::string& login)
{
    login_ = login;
}

void User::setUserName(const std::string& user_name)
{
    user_name_ = user_name;
}

ID User::getUserId() const
{
    return user_id_;
}

std::string User::getLogin() const
{
    return login_;
}

std::string User::getUserName() const
{
    return user_name_;
}