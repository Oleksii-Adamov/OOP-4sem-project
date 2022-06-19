#ifndef SERVER_DATABASESERVICE_H
#define SERVER_DATABASESERVICE_H

#include <iostream>

class DatabaseService
{
public:
    DatabaseService() = delete;

    static void initDatabase(const std::string& path);
};


#endif