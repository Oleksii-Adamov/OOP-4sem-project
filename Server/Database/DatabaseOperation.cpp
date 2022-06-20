#include "DatabaseOperation.h"
#include "DatabaseLog.h"


bool DatabaseOperation::initDatabase() const
{
    DatabaseLog::error("An empty function is called");
    return false;
}

bool DatabaseOperation::execInsert(const std::string& table_name, const std::vector<std::string>& columns, const std::vector<std::string>& values) const
{
    DatabaseLog::error("An empty function is called");
    return false;
}

std::pair<bool, std::vector<std::vector<std::string>>> DatabaseOperation::execSelect(const std::string& command_select, size_t n) const
{
    DatabaseLog::error("An empty function is called");
    return {false, {}};
}

bool DatabaseOperation::execUpdate(const std::string& table_name, const std::vector<std::string>& columns,
                                   const std::vector<std::string>& column_values, const std::string& where_expression) const
{
    DatabaseLog::error("An empty function is called");
    return false;
}

bool DatabaseOperation::execDelete(const std::string& table_name, const std::string& where_expression) const
{
    DatabaseLog::error("An empty function is called");
    return false;
}