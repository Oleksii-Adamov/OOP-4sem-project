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
    AssignmentInfo();
    AssignmentInfo(unsigned long long id, const std::string& name, const std::string& date_time);
    unsigned long long getId() const;
    std::string getName() const;
    std::string getDateTime() const;
};

#endif // ASSIGNMENTINFO_H
