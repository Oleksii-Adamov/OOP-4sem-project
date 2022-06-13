#ifndef ASSIGNMENTINFO_H
#define ASSIGNMENTINFO_H

#include<string>

class AssignmentInfo
{
private:
    unsigned long long id_;
    std::string name_;
    std::string date_time_;
public:
    AssignmentInfo(unsigned long long id, const std::string& name, std::string& date_time);
    unsigned long long getId();
    std::string getName();
    std::string getDateTime();
};

#endif // ASSIGNMENTINFO_H
