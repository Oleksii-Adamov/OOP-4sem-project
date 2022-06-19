#ifndef ASSIGNMENTSESSIONINFO_H
#define ASSIGNMENTSESSIONINFO_H

#include <string>

class AssignmentSessionInfo
{
private:
    unsigned long long id_ = 0;
    std::string name_;
    std::string start_date_time_ = "";
    std::string deadline_date_time_ = "";
public:
    AssignmentSessionInfo();
    AssignmentSessionInfo(unsigned long long id, const std::string& name, const std::string& start_date_time,
                          const std::string& deadline_date_time);
    unsigned long long getId() const;
    std::string getName() const;
    std::string getStartDateTime() const;
    std::string getDeadlineDateTime() const;
};

#endif // ASSIGNMENTSESSIONINFO_H
