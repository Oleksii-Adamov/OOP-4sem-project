#ifndef ASSIGNMENTINFO_H
#define ASSIGNMENTINFO_H

#include<string>

class AssignmentInfo
{
private:
    long long id_;
    std::string name_;
    std::string date_time_;
public:
    AssignmentInfo(long long id, const std::string& name, std::string& date_time);
    long long getId() const;
    std::string getName() const;
    std::string getDateTime() const;
};

#endif // ASSIGNMENTINFO_H
