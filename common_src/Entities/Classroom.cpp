#include "Classroom.h"


void Classroom::setClassroomId(const ID& classroom_id)
{
    classroom_id_ = classroom_id;
}

void Classroom::setTeacherUserId(const ID& teacher_user_id)
{
    teacher_user_id_ = teacher_user_id;
}

ID Classroom::getClassroomId() const
{
    return classroom_id_;
}

ID Classroom::getTeacherUserId() const
{
    return teacher_user_id_;
}