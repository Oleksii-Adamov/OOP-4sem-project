#ifndef SERVER_DATABASEAUTHORIZATIONTYPE_H
#define SERVER_DATABASEAUTHORIZATIONTYPE_H

#include "DatabaseType.h"

class DatabaseAuthorizationType : DatabaseType
{
    ID user_id_;
    std::string password_;
public:
    DatabaseAuthorizationType(const ID& user_id, const std::string& password) : user_id_(user_id), password_(password) {};
    void setUserId(const ID& user_id);
    void setPassword(const std::string& password);
    ID getUserId() const;
    std::string getPassword() const;
};


#endif