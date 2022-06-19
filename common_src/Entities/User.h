#ifndef USER_H
#define USER_H

#include "Entity.h"

class User : Entity
{
    ID user_id_ = 0;
    std::string login_ = "";
    std::string user_name_ = "";
public:
    User(){};
    User(const ID& user_id, const std::string& login, const std::string& user_name) : user_id_(user_id), login_(login), user_name_(user_name) {};
    void setUserId(const ID& user_id)
    {
        user_id_ = user_id;
    }

    void setLogin(const std::string& login)
    {
        login_ = login;
    }

    void setUserName(const std::string& user_name)
    {
        user_name_ = user_name;
    }

    ID getUserId() const
    {
        return user_id_;
    }

    std::string getLogin() const
    {
        return login_;
    }

    std::string getUserName() const
    {
        return user_name_;
    }
};


#endif
