#include "DatabaseStudentClassroomType.h"


void DatabaseStudentClassroomType::setStudentUserId(const ID& student_user_id)
{
    student_user_id_ = student_user_id;
}

void DatabaseStudentClassroomType::setClassroomId(const ID& classroom_id)
{
    classroom_id_ = classroom_id;
}

ID DatabaseStudentClassroomType::getStudentUserId() const
{
    return student_user_id_;
}

ID DatabaseStudentClassroomType::getClassroomId() const
{
    return classroom_id_;
}