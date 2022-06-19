#ifndef SERVER_DATABASELOG_H
#define SERVER_DATABASELOG_H

#include "string"

class DatabaseLog
{
public:
    DatabaseLog() = delete;

    static void error(const std::string& message);
    static void info(const std::string& message);
    static void out(const std::string& message);
};


#endif