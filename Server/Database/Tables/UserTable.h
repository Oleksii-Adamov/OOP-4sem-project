#ifndef SERVER_USERTABLE_H
#define SERVER_USERTABLE_H

#include "Table.h"

class UserTable : Table
{
    User data;
public:
    UserTable() = default;

    bool insertToDatabase() override;
    bool getFromDatabaseById() override;
    bool updateInDatabaseById() override;
    bool deleteFromDatabaseById() override;
};


#endif