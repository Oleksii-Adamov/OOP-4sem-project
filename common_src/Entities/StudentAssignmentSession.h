#ifndef STUDENTASSIGNMENTSESSION_H
#define STUDENTASSIGNMENTSESSION_H

#include "Entity.h"

class StudentAssignmentSession : Entity
{
    ID student_user_id_;
    ID assignment_session_id_;
    int student_assignment_session_status_;
    DATA* student_assignment_session_answer_;
    int student_assignment_session_score_;
    DATETIME student_assignment_session_finish_date_;
public:
    StudentAssignmentSession(const ID& student_user_id, const ID& assignment_session_id,
                             int student_assignment_session_status, DATA* student_assignment_session_answer,
                             int student_assignment_session_score, const DATETIME& student_assignment_session_finish_date) :
                                         student_user_id_(student_user_id), assignment_session_id_(assignment_session_id),
                                         student_assignment_session_status_(student_assignment_session_status),
                                         student_assignment_session_answer_(student_assignment_session_answer),
                                         student_assignment_session_score_(student_assignment_session_score),
                                         student_assignment_session_finish_date_(student_assignment_session_finish_date) {};
    void setStudentUserId(const ID& student_user_id);
    void setAssignmentSessionId(const ID& assignment_session_id);
    void setStudentAssignmentSessionStatus(int student_assignment_session_status);
    void setStudentAssignmentSessionAnswer(DATA* student_assignment_session_answer);
    void setStudentAssignmentSessionScore(int student_assignment_session_score);
    void setStudentAssignmentSessionFinishDate(const DATETIME& student_assignment_session_finish_date);
    ID getStudentUserId() const;
    ID getAssignmentSessionId() const;
    int getStudentAssignmentSessionStatus() const;
    DATA* getStudentAssignmentSessionAnswer() const;
    int getStudentAssignmentSessionScore() const;
    DATETIME getStudentAssignmentSessionFinishDate() const;
};


#endif