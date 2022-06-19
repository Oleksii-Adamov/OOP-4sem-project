#include "DatabaseLog.h"
#include <iostream>

void DatabaseLog::error(const std::string& message)
{
    std::cerr << "[DATABASE ERROR] " << message << std::endl;
}

void DatabaseLog::info(const std::string& message)
{
    std::cout << "[DATABASE INFO] " << message << std::endl;
}

void DatabaseLog::out(const std::string& message)
{
    std::cout << "[DATABASE] " << message << std::endl;
}