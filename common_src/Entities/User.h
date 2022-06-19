#ifndef USER_H
#define USER_H

#include "Entity.h"

class User : Entity
{
    ID user_id_;
    std::string login_;
    std::string user_name_;
public:
    User(const ID& user_id, const std::string& login, const std::string& user_name) : user_id_(user_id), login_(login), user_name_(user_name) {};
    void setUserId(const ID& user_id);
    void setLogin(const std::string& login);
    void setUserName(const std::string& user_name);
    ID getUserId() const;
    std::string getLogin() const;
    std::string getUserName() const;
};


#endif