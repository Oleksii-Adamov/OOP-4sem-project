#ifndef STUDENTCLASSROOM_H
#define STUDENTCLASSROOM_H

#include "Entity.h"

class StudentClassroom : Entity
{
    ID student_user_id_;
    ID classroom_id_;
public:
    StudentClassroom(const ID& student_user_id, const ID& classroom_id) : student_user_id_(student_user_id), classroom_id_(classroom_id) {};
    void setStudentUserId(const ID& student_user_id);
    void setClassroomId(const ID& classroom_id);
    ID getStudentUserId() const;
    ID getClassroomId() const;
};


#endif