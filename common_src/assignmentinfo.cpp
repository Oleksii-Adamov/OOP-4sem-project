#include "assignmentinfo.h"

AssignmentInfo::AssignmentInfo()
    : id_(-1), name_(""), date_time_("")
{

}

AssignmentInfo::AssignmentInfo(unsigned long long id, const std::string& name, const std::string& date_time)
    : id_(id), name_(name), date_time_(date_time)
{

}

unsigned long long AssignmentInfo::getId() const
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
