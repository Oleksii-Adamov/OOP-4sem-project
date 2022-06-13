#include "assignmentinfo.h"
AssignmentInfo::AssignmentInfo(long long id, const std::string& name, std::string& date_time)
    : id_(id), name_(name), date_time_(date_time)
{

}

long long AssignmentInfo::getId() const
{
    return id_;
}

std::string AssignmentInfo::getName() const
{
    return name_;
}

std::string AssignmentInfo::getDateTime() const
{
    return date_time_;
}
