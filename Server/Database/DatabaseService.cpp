#include "DatabaseService.h"
#include "DatabaseOperation.h"
#include "DatabaseLog.h"
#include "SQLite/SQLiteAdapter.h"


void DatabaseService::initDatabase()
{
    DatabaseOperation* db = new SQLiteAdapter();
    if(db->initDatabase())
        DatabaseLog::out("Database started!");
    else
        DatabaseLog::error("Failed to start database!");
}