#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H


class Database
{
    static Database* database_;
protected:
    Database() = default;
public:
    Database(Database&) = delete;

    static Database& instance();
    static void init();
    static void clear();

    void operator =(const Database&) = delete;
};


#endif