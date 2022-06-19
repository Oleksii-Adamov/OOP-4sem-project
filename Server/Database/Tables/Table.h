#ifndef SERVER_TABLE_H
#define SERVER_TABLE_H

#include "../../../common_src/Entities/Entities.h"

class Table
{
protected:
    virtual ~Table() {};

    virtual bool insertToDatabase() = 0; //!ID (key) field is ignored (a new one is generated)
    virtual bool getFromDatabaseById() = 0;
    virtual bool updateInDatabaseById() = 0;
    virtual bool deleteFromDatabaseById() = 0;
};


#endif