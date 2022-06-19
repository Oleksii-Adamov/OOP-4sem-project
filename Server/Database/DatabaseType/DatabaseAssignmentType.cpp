#include "DatabaseAssignmentType.h"


void DatabaseAssignmentType::setAssignmentId(const ID& assignment_id)
{
    assignment_id_ = assignment_id;
}

void DatabaseAssignmentType::setTeacherUserId( const ID& teacher_user_id)
{
    teacher_user_id_ = teacher_user_id;
}

void DatabaseAssignmentType::setAssignmentName(const std::string& assignment_name)
{
    assignment_name_ = assignment_name;
}

void DatabaseAssignmentType::setAssignmentCreationDate(const DATETIME& assignment_creation_date)
{
    assignment_creation_date_ = assignment_creation_date;
}

void DatabaseAssignmentType::setAssignmentData(DATA* assignment_data)
{
    assignment_data_ = assignment_data;
}

void DatabaseAssignmentType::setAssignmentMaxScore(int assignment_max_score)
{
    assignment_max_score_ = assignment_max_score;
}

ID DatabaseAssignmentType::getAssignmentId() const
{
    return assignment_id_;
}

ID DatabaseAssignmentType::getTeacherUserId() const
{
    return teacher_user_id_;
}

std::string DatabaseAssignmentType::getAssignmentName() const
{
    return assignment_name_;
}

DATETIME DatabaseAssignmentType::getAssignmentCreationDate() const
{
    return assignment_creation_date_;
}

DATA* DatabaseAssignmentType::getAssignmentData() const
{
    return assignment_data_;
}

int DatabaseAssignmentType::getAssignmentMaxScore() const
{
    return assignment_max_score_;
}