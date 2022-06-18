#include "Database.h"
Database* Database::database_= nullptr;;


Database& Database::instance()
{
    if(!database_)
    {
        database_ = new Database();
    }
    return *database_;
}

void Database::init()
{
    // build database
}

void Database::clear()
{
    delete database_;
}