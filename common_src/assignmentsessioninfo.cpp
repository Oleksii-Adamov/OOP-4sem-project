#include "assignmentsessioninfo.h"

AssignmentSessionInfo::AssignmentSessionInfo()
{

}

AssignmentSessionInfo::AssignmentSessionInfo(unsigned long long id, const std::string& name,
                                             const std::string& start_date_time, const std::string& deadline_date_time)
    : id_(id), name_(name), start_date_time_(start_date_time), deadline_date_time_(deadline_date_time)
{

}

unsigned long long AssignmentSessionInfo::getId() const
{
    return id_;
}

std::string AssignmentSessionInfo::getName() const
{
    return name_;
}

std::string AssignmentSessionInfo::getStartDateTime() const
{
    return start_date_time_;
}

std::string AssignmentSessionInfo::getDeadlineDateTime() const
{
    return deadline_date_time_;
}
