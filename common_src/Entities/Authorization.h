#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "Entity.h"

class Authorization : Entity
{
    ID user_id_ = 0;
    std::string password_ = "";
public:
    Authorization(){};
    Authorization(const ID& user_id, const std::string& password) : user_id_(user_id), password_(password) {};
    void setUserId(const ID& user_id)
    {
        user_id_ = user_id;
    }

    void setPassword(const std::string& password)
    {
        password_ = password;
    }

    ID getUserId() const
    {
        return user_id_;
    }

    std::string getPassword() const
    {
        return password_;
    }
};


#endif
