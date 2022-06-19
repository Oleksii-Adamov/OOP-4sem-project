#include "Assignment.h"


void Assignment::setAssignmentId(const ID& assignment_id)
{
    assignment_id_ = assignment_id;
}

void Assignment::setTeacherUserId(const ID& teacher_user_id)
{
    teacher_user_id_ = teacher_user_id;
}

void Assignment::setAssignmentName(const std::string& assignment_name)
{
    assignment_name_ = assignment_name;
}

void Assignment::setAssignmentCreationDate(const DATETIME& assignment_creation_date)
{
    assignment_creation_date_ = assignment_creation_date;
}

void Assignment::setAssignmentData(const DATA& assignment_data)
{
    assignment_data_ = assignment_data;
}

void Assignment::setAssignmentMaxScore(int assignment_max_score)
{
    assignment_max_score_ = assignment_max_score;
}

ID Assignment::getAssignmentId() const
{
    return assignment_id_;
}

ID Assignment::getTeacherUserId() const
{
    return teacher_user_id_;
}

std::string Assignment::getAssignmentName() const
{
    return assignment_name_;
}

DATETIME Assignment::getAssignmentCreationDate() const
{
    return assignment_creation_date_;
}

const DATA& Assignment::getAssignmentData() const
{
    return assignment_data_;
}

int Assignment::getAssignmentMaxScore() const
{
    return assignment_max_score_;
}