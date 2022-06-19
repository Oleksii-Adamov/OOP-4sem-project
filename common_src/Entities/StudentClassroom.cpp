#include "StudentClassroom.h"


void StudentClassroom::setStudentUserId(const ID& student_user_id)
{
    student_user_id_ = student_user_id;
}

void StudentClassroom::setClassroomId(const ID& classroom_id)
{
    classroom_id_ = classroom_id;
}

ID StudentClassroom::getStudentUserId() const
{
    return student_user_id_;
}

ID StudentClassroom::getClassroomId() const
{
    return classroom_id_;
}