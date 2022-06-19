#ifndef SERVER_DATABASETYPE_H
#define SERVER_DATABASETYPE_H

#include <string>

#define ID unsigned long long
#define DATETIME std::string
#define DATA std::string

class DatabaseType
{
protected:
    virtual ~DatabaseType() = 0;
};


#endif