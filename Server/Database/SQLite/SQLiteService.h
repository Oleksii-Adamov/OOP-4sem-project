#ifndef SERVER_SQLITESERVICE_H
#define SERVER_SQLITESERVICE_H

#include <string>
#include <vector>

class SQLiteService
{
public:
    static std::string commasList(const std::vector<std::string>& v);
};


#endif