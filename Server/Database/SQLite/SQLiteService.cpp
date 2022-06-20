#include "SQLiteService.h"


std::string SQLiteService::commasList(const std::vector<std::string>& v)
{
    std::string res;
    for(size_t i=0; i<v.size(); i++)
    {
        res += v[i];
        if(i != v.size()-1)
            res += ", ";
    }
    return res;
}