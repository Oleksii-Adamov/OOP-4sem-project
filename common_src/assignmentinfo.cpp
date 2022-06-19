#include "assignmentinfo.h"

AssignmentInfo::AssignmentInfo()
{

}

AssignmentInfo::AssignmentInfo(unsigned long long id, int max_score, const std::string& name, const std::string& creation_date_time)
    : id_(id), max_score_(max_score), name_(name), creation_date_time_(creation_date_time)
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

std::string AssignmentInfo::getCreationDateTime() const
{
    return creation_date_time_;
}

int AssignmentInfo::getMaxScore() const
{
    return max_score_;
}
