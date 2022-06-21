#ifndef SERVER_SQLITEADAPTER_H
#define SERVER_SQLITEADAPTER_H

#include "sqlite_src/sqlite3.h"
#include "../DatabaseOperation.h"

class SQLiteAdapter : public DatabaseOperation
{
    static bool openDatabase(sqlite3** db);
    static bool closeDatabase(sqlite3** db);
    static bool exec(const std::string& command);
public:
    bool initDatabase() const override;
    bool execInsert(const std::string& table_name, const std::vector<std::string>& columns, const std::vector<std::string>& values) const override;
    std::pair<bool, std::vector<std::vector<std::string>>> execSelect(const std::string& command_select, size_t n) const override;
    bool execUpdate(const std::string& table_name, const std::vector<std::string>& columns,
                            const std::vector<std::string>& column_values, const std::string& where_expression) const override;
    bool execDelete(const std::string& table_name, const std::string& where_expression) const override;
    std::pair<bool, bool> checkUniqueRecord(const std::string& table_name, const std::string& column, const std::string& column_value) const override;
    std::pair<bool, unsigned long long> getLastTableID(const std::string& table_name, const std::string& id_name) const override;
};


#endif