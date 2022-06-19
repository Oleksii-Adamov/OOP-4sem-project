#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Entity.h"

class Assignment : Entity
{
    ID assignment_id_ = 0;
    ID teacher_user_id_ = 0;
    std::string assignment_name_ = "";
    DATETIME assignment_creation_date_ = "";
    DATA assignment_data_ = "";
    int assignment_max_score_ = 0;
public:
    Assignment() {}
    Assignment(const ID& assignment_id, const ID& teacher_user_id, const std::string& assignment_name,
               const DATETIME& assignment_creation_date, const DATA& assignment_data, int assignment_max_score) :
                           assignment_id_(assignment_id), teacher_user_id_(teacher_user_id), assignment_name_(assignment_name),
                           assignment_creation_date_(assignment_creation_date), assignment_data_(assignment_data), assignment_max_score_(assignment_max_score) {}
    void setAssignmentId(const ID& assignment_id)
    {
        assignment_id_ = assignment_id;
    }

    void setTeacherUserId(const ID& teacher_user_id)
    {
        teacher_user_id_ = teacher_user_id;
    }

    void setAssignmentName(const std::string& assignment_name)
    {
        assignment_name_ = assignment_name;
    }

    void setAssignmentCreationDate(const DATETIME& assignment_creation_date)
    {
        assignment_creation_date_ = assignment_creation_date;
    }

    void setAssignmentData(const DATA& assignment_data)
    {
        assignment_data_ = assignment_data;
    }

    void setAssignmentMaxScore(int assignment_max_score)
    {
        assignment_max_score_ = assignment_max_score;
    }

    ID getAssignmentId() const
    {
        return assignment_id_;
    }

    ID getTeacherUserId() const
    {
        return teacher_user_id_;
    }

    std::string getAssignmentName() const
    {
        return assignment_name_;
    }

    DATETIME getAssignmentCreationDate() const
    {
        return assignment_creation_date_;
    }

    const DATA& getAssignmentData() const
    {
        return assignment_data_;
    }

    int getAssignmentMaxScore() const
    {
        return assignment_max_score_;
    }
};


#endif
