#ifndef ASSIGNMENTINFO_H
#define ASSIGNMENTINFO_H

#include<string>

class AssignmentInfo
{
private:
    unsigned long long id_ = 0;
    int max_score_ = 0;
    std::string name_ = "";
    std::string creation_date_time_ = "";
public:
    AssignmentInfo();
    AssignmentInfo(unsigned long long id, int max_score, const std::string& name, const std::string& creation_date_time);
    unsigned long long getId() const;
    std::string getName() const;
    std::string getCreationDateTime() const;
    int getMaxScore() const;
};

#endif // ASSIGNMENTINFO_H
