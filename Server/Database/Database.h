#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H

#include <string>

class Database
{
public:
    static void init(const std::string& path);
};


#endif