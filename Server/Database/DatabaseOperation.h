#ifndef SERVER_DATABASEOPERATION_H
#define SERVER_DATABASEOPERATION_H

#include <string>
#include <vector>

class DatabaseOperation
{
public:
    virtual ~DatabaseOperation() {};
    virtual bool initDatabase() const;
    virtual bool execInsert(const std::string& table_name, const std::vector<std::string>& columns, const std::vector<std::string>& values) const;
    virtual std::vector<std::vector<std::string>> execSelect(const std::string& command_select) const;
    virtual bool execUpdate(const std::string& table_name, const std::vector<std::string>& columns,
                    const std::vector<std::string>& column_values, const std::string& where_expression) const;
    virtual bool execDelete(const std::string& table_name, const std::string& where_expression) const;
};


#endif
