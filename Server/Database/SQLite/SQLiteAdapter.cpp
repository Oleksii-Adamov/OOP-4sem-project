#include "SQLiteAdapter.h"
#include "../DatabaseLog.h"
#include "DatabasePath.h"
#include "SQLiteService.h"
#include <string>


bool SQLiteAdapter::openDatabase(sqlite3** db)
{
    bool flag = sqlite3_open(DatabasePath, db);
    if(flag)
    {
        DatabaseLog::error("Can't open database: " + std::string(sqlite3_errmsg(*db)));
        return false;
    }
    return true;
}

bool SQLiteAdapter::closeDatabase(sqlite3** db)
{
    bool flag = sqlite3_close(*db);
    if(flag)
    {
        DatabaseLog::error("Can't close database");
        return false;
    }
    return true;
}

bool SQLiteAdapter::exec(const std::string& command) const
{
    sqlite3* db = nullptr;
    bool flag;
    char* error = nullptr;
    if(SQLiteAdapter::openDatabase(&db))
    {
        flag = sqlite3_exec(db, command.c_str(), nullptr, nullptr, &error);
        if(flag)
        {
            DatabaseLog::error("Execution failure: " + std::string(sqlite3_errmsg(db)));
            DatabaseLog::error("Script: \n" + command);
        }
        sqlite3_free(error);
        SQLiteAdapter::closeDatabase(&db);
        if(flag)
            return false;
        return true;
    }
    else
        return false;
}

bool SQLiteAdapter::initDatabase() const
{
    std::string command = "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `User`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `User` (\n"
                          "  `UserID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                          "  `Login` TEXT UNIQUE NOT NULL,\n"
                          "  `UserName` TEXT NOT NULL);\n"
                          "CREATE UNIQUE INDEX IF NOT EXISTS `UserID_UNIQUE` ON `User`(`UserID`);\n"
                          "CREATE UNIQUE INDEX IF NOT EXISTS `Login_UNIQUE` ON `User`(`Login`);\n"
                          "\n"
                          "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `Authorization`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `Authorization` (\n"
                          "  `UserID` INTEGER UNIQUE NOT NULL PRIMARY KEY,\n"
                          "  `Password` TEXT NOT NULL,\n"
                          "  FOREIGN KEY (`UserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);\n"
                          "CREATE UNIQUE INDEX IF NOT EXISTS `UserID1_UNIQUE` ON `Authorization`(`UserID`);\n"
                          "\n"
                          "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `Classroom`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `Classroom` (\n"
                          "  `ClassroomID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                          "  `TeacherUserID` INTEGER NOT NULL,\n"
                          "  `ClassroomName` TEXT NOT NULL,\n"
                          "  FOREIGN KEY (`TeacherUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);\n"
                          "CREATE UNIQUE INDEX IF NOT EXISTS `ClassroomID_UNIQUE` ON `Classroom`(`ClassroomID`);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_Classroom_User_idx` ON `Classroom`(`TeacherUserID`);\n"
                          "\n"
                          "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `Assignment`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `Assignment` (\n"
                          "  `AssignmentID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                          "  `TeacherUserID` INTEGER NOT NULL,\n"
                          "  `AssignmentName` TEXT NOT NULL,\n"
                          "  `AssignmentCreationDate` DATETIME NOT NULL DEFAULT current_timestamp,\n"
                          "  `AssignmentData` TEXT NOT NULL,\n"
                          "  `AssignmentMaxScore` INTEGER NULL,\n"
                          "  FOREIGN KEY (`TeacherUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE);\n"
                          "CREATE UNIQUE INDEX IF NOT EXISTS `TaskID_UNIQUE` ON `Assignment`(`AssignmentID`);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_Assignment_User1_idx` ON `Assignment`(`TeacherUserID`);\n"
                          "\n"
                          "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `Student_Classroom`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `Student_Classroom` (\n"
                          "  `StudentUserID` INTEGER NOT NULL,\n"
                          "  `ClassroomID` INTEGER NOT NULL,\n"
                          "  FOREIGN KEY (`StudentUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE,\n"
                          "  FOREIGN KEY (`ClassroomID`) REFERENCES `Classroom`(`ClassroomID`) ON UPDATE CASCADE ON DELETE CASCADE);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_User_has_Classroom_User1_idx` ON `Student_Classroom`(`StudentUserID`);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_User_has_Classroom_Classroom1_idx` ON `Student_Classroom`(`ClassroomID`);\n"
                          "\n"
                          "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `AssignmentSession`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `AssignmentSession` (\n"
                          "  `AssignmentSessionID` INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                          "  `ClassroomID` INTEGER NOT NULL,\n"
                          "  `AssignmentID` INTEGER NOT NULL,\n"
                          "  `AssignmentSessionStartDate` DATETIME NOT NULL DEFAULT current_timestamp,\n"
                          "  `AssignmentSessionFinishDate` DATETIME NULL,\n"
                          "  FOREIGN KEY (`ClassroomID`) REFERENCES `Classroom`(`ClassroomID`) ON UPDATE CASCADE ON DELETE CASCADE,\n"
                          "  FOREIGN KEY (`AssignmentID`) REFERENCES `Assignment`(`AssignmentID`) ON UPDATE CASCADE ON DELETE CASCADE);\n"
                          "CREATE UNIQUE INDEX IF NOT EXISTS `AssignmentSessionID_UNIQUE` ON `AssignmentSession`(`AssignmentSessionID`);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_AssignmentSession_Classroom1_idx` ON `AssignmentSession`(`ClassroomID`);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_AssignmentSession_Assignment1_idx` ON `AssignmentSession`(`AssignmentID`);\n"
                          "\n"
                          "\n"
                          "-- -----------------------------------------------------\n"
                          "-- Table `Student_AssignmentSession`\n"
                          "-- -----------------------------------------------------\n"
                          "CREATE TABLE IF NOT EXISTS `Student_AssignmentSession` (\n"
                          "  `StudentUserID` INTEGER NOT NULL,\n"
                          "  `AssignmentSessionID` INTEGER NOT NULL,\n"
                          "  `StudentAssignmentSessionStatus` INTEGER NOT NULL,\n"
                          "  `StudentAssignmentSessionAnswer` TEXT NULL,\n"
                          "  `StudentAssignmentSessionScore` INTEGER NULL,\n"
                          "  `StudentAssignmentSessionFinishDate` DATETIME NULL,\n"
                          "  FOREIGN KEY (`StudentUserID`) REFERENCES `User`(`UserID`) ON UPDATE CASCADE ON DELETE CASCADE,\n"
                          "  FOREIGN KEY (`AssignmentSessionID`) REFERENCES `AssignmentSession`(`AssignmentSessionID`) ON UPDATE CASCADE ON DELETE CASCADE);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_Assignment_has_User_User1_idx` ON `Student_AssignmentSession`(`StudentUserID`);\n"
                          "CREATE INDEX IF NOT EXISTS `fk_Student_AssignmentSession_AssignmentSession1_idx` ON `Student_AssignmentSession`(`AssignmentSessionID`);\n"
                          "";
    return SQLiteAdapter::exec(command);
}

bool SQLiteAdapter::execInsert(const std::string& table_name, const std::vector<std::string>& columns, const std::vector<std::string>& values) const
{
    std::string command = "INSERT INTO '" + table_name + "' (" + SQLiteService::commasList(columns) + ")\n"
                        + "VALUES (" + SQLiteService::commasList(values) + ");";
    return SQLiteAdapter::exec(command);
}

std::pair<bool, std::vector<std::vector<std::string>>> SQLiteAdapter::execSelect(const std::string& command_select, size_t n) const
{
    sqlite3* db = nullptr;
    sqlite3_stmt * stmt;
    bool flag;
    std::vector<std::vector<std::string>> result;

    for(size_t i=0; i<n; i++)
        result.emplace_back();

    if(SQLiteAdapter::openDatabase(&db))
    {
        if(!sqlite3_prepare(db, command_select.c_str(), -1, &stmt, nullptr))
        {
            sqlite3_step(stmt);
            while(sqlite3_column_text(stmt,0))
            {
                for(size_t i=0; i<n; i++)
                    result[i].push_back(std::string( (char *)sqlite3_column_text(stmt, static_cast<int>(i))));
                sqlite3_step(stmt);
            }
            sqlite3_finalize(stmt);
            SQLiteAdapter::closeDatabase(&db);
            return {true, result};
        }
        else
        {
            DatabaseLog::error("Execution failure: " + std::string(sqlite3_errmsg(db)));
            DatabaseLog::error("Script: " + command_select);
            SQLiteAdapter::closeDatabase(&db);
            return {false, {}};
        }
    }
    else
        return {false, {}};
}

bool SQLiteAdapter::execUpdate(const std::string& table_name, const std::vector<std::string>& columns,
                const std::vector<std::string>& column_values, const std::string& where_expression) const
{
    if(columns.size() != column_values.size())
        DatabaseLog::error("UPDATE script failure (different vector sizes)");

    std::string resString;
    for(size_t i=0; i<columns.size(); i++)
    {
        resString += columns[i] + " = '" + column_values[i] + "'";
        if(i != columns.size()-1)
            resString += ", ";
    }

    std::string command = "UPDATE '" + table_name + "'\n"
                        + "SET " + resString + "\n"
                        + "WHERE " + where_expression + ";";
    return exec(command);
}

bool SQLiteAdapter::execDelete(const std::string& table_name, const std::string& where_expression) const
{
    std::string command = "DELETE FROM '" + table_name + "'\n"
                        + "WHERE " + where_expression + ";";
    return exec(command);
}

std::pair<bool, bool> SQLiteAdapter::checkUniqueRecord(const std::string& table_name, const std::string& column, const std::string& column_value) const
{
    std::string command = "SELECT " + table_name + "." + column + "\n"
                        + "FROM '" + table_name + "'\n"
                        + "WHERE " + table_name + "." + column + " = '" + column_value + "';";
    auto commandResFull = execSelect(command, 1);
    if(!commandResFull.first)
        return {false, false};
    const auto& commandRes = commandResFull.second;

    if(commandRes[0].empty())
        return {true, true};
    return {true, false};
}

std::pair<bool, unsigned long long> SQLiteAdapter::getLastTableID(const std::string& table_name, const std::string& id_name) const
{
    std::string command = "SELECT MAX(" + table_name + "." + id_name + ")\n"
                        + "FROM '" + table_name + "'\n";
    auto commandResFull = execSelect(command, 1);
    if(!commandResFull.first)
        return {false, 0};
    const auto& commandRes = commandResFull.second;
    return {true, std::stoull(commandRes[0][0])};
}