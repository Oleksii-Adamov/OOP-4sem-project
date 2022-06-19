#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "Entity.h"

class Classroom : Entity
{
    ID classroom_id_;
    ID teacher_user_id_;
public:
    Classroom(const ID& classroom_id, const ID& teacher_user_id) : classroom_id_(classroom_id), teacher_user_id_(teacher_user_id) {};
    void setClassroomId(const ID& classroom_id);
    void setTeacherUserId(const ID& teacher_user_id);
    ID getClassroomId() const;
    ID getTeacherUserId() const;
};


#endif