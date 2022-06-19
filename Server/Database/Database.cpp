#include "Database.h"
#include "DatabaseService.h"


void Database::init(const std::string& path)
{
    DatabaseService::initDatabase(path);
}