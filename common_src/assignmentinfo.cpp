#include "assignmentinfo.h"
AssignmentInfo::AssignmentInfo(unsigned long long id, const std::string& name, std::string& date_time)
    : id_(id), name_(name), date_time_(date_time)
{

}
unsigned long long AssignmentInfo::getId()
{
    return id_;
}
std::string AssignmentInfo::getName()
{
    return name_;
}
std::string AssignmentInfo::getDateTime()
{
    return date_time_;
}
