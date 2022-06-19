#include "DatabaseClassroomType.h"


void DatabaseClassroomType::setClassroomId(const ID& classroom_id)
{
    classroom_id_ = classroom_id;
}

void DatabaseClassroomType::setTeacherUserId(const ID& teacher_user_id)
{
    teacher_user_id_ = teacher_user_id;
}

ID DatabaseClassroomType::getClassroomId() const
{
    return classroom_id_;
}

ID DatabaseClassroomType::getTeacherUserId() const
{
    return teacher_user_id_;
}