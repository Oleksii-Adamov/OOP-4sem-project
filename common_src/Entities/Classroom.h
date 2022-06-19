#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "Entity.h"

class Classroom : Entity
{
    ID classroom_id_ = 0;
    ID teacher_user_id_ = 0;
    std::string name_ = "";
public:
    Classroom(){};
    Classroom(const ID& classroom_id, const ID& teacher_user_id, const std::string name) : classroom_id_(classroom_id), teacher_user_id_(teacher_user_id), name_(name) {};
    void setClassroomId(const ID& classroom_id)
    {
        classroom_id_ = classroom_id;
    }

    void setTeacherUserId(const ID& teacher_user_id)
    {
        teacher_user_id_ = teacher_user_id;
    }

    void setName(const std::string& name)
    {
        name_ = name;
    }

    ID getClassroomId() const
    {
        return classroom_id_;
    }

    ID getTeacherUserId() const
    {
        return teacher_user_id_;
    }

    std::string getName() const
    {
        return name_;
    }
};


#endif
