#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Entity.h"

class Assignment : Entity
{
    ID assignment_id_;
    ID teacher_user_id_;
    std::string assignment_name_;
    DATETIME assignment_creation_date_;
    DATA* assignment_data_;
    int assignment_max_score_;
public:
    Assignment(const ID& assignment_id, const ID& teacher_user_id, const std::string& assignment_name,
               const DATETIME& assignment_creation_date, DATA* assignment_data, int assignment_max_score) :
                           assignment_id_(assignment_id), teacher_user_id_(teacher_user_id), assignment_name_(assignment_name),
                           assignment_creation_date_(assignment_creation_date), assignment_data_(assignment_data), assignment_max_score_(assignment_max_score) {};
    void setAssignmentId(const ID& assignment_id);
    void setTeacherUserId( const ID& teacher_user_id);
    void setAssignmentName(const std::string& assignment_name);
    void setAssignmentCreationDate(const DATETIME& assignment_creation_date);
    void setAssignmentData(DATA* assignment_data);
    void setAssignmentMaxScore(int assignment_max_score);
    ID getAssignmentId() const;
    ID getTeacherUserId() const;
    std::string getAssignmentName() const;
    DATETIME getAssignmentCreationDate() const;
    DATA* getAssignmentData() const;
    int getAssignmentMaxScore() const;
};


#endif