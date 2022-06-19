#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "Entity.h"

class Authorization : Entity
{
    ID user_id_;
    std::string password_;
public:
    Authorization(const ID& user_id, const std::string& password) : user_id_(user_id), password_(password) {};
    void setUserId(const ID& user_id);
    void setPassword(const std::string& password);
    ID getUserId() const;
    std::string getPassword() const;
};


#endif