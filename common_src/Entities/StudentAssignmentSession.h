#ifndef STUDENTASSIGNMENTSESSION_H
#define STUDENTASSIGNMENTSESSION_H

#include "Entity.h"

enum class StudentAssignmentSessionStatus {not_submitted, submitted, checked};

class StudentAssignmentSession : Entity
{
    ID student_user_id_ = 0;
    ID assignment_session_id_ = 0;
    StudentAssignmentSessionStatus student_assignment_session_status_ = StudentAssignmentSessionStatus::not_submitted;
    DATA student_assignment_session_answer_ = "";
    int student_assignment_session_score_ = 0;
    DATETIME student_assignment_session_finish_date_ = "";
public:
    StudentAssignmentSession() {};
    StudentAssignmentSession(const ID& student_user_id, const ID& assignment_session_id,
                             StudentAssignmentSessionStatus student_assignment_session_status, const DATA& student_assignment_session_answer,
                             int student_assignment_session_score, const DATETIME& student_assignment_session_finish_date) :
                                         student_user_id_(student_user_id), assignment_session_id_(assignment_session_id),
                                         student_assignment_session_status_(student_assignment_session_status),
                                         student_assignment_session_answer_(student_assignment_session_answer),
                                         student_assignment_session_score_(student_assignment_session_score),
                                         student_assignment_session_finish_date_(student_assignment_session_finish_date) {};
    void setStudentUserId(const ID& student_user_id)
    {
        student_user_id_ = student_user_id;
    }

    void setAssignmentSessionId(const ID& assignment_session_id)
    {
        assignment_session_id_ = assignment_session_id;
    }

    void setStudentAssignmentSessionStatus(StudentAssignmentSessionStatus student_assignment_session_status)
    {
        student_assignment_session_status_ = student_assignment_session_status;
    }

    void setStudentAssignmentSessionAnswer(const DATA& student_assignment_session_answer)
    {
        student_assignment_session_answer_ = student_assignment_session_answer;
    }

    void setStudentAssignmentSessionScore(int student_assignment_session_score)
    {
        student_assignment_session_score_ = student_assignment_session_score;
    }

    void setStudentAssignmentSessionFinishDate(const DATETIME& student_assignment_session_finish_date)
    {
        student_assignment_session_finish_date_ = student_assignment_session_finish_date;
    }

    ID getStudentUserId() const
    {
        return student_user_id_;
    }

    ID getAssignmentSessionId() const
    {
        return assignment_session_id_;
    }

    StudentAssignmentSessionStatus getStudentAssignmentSessionStatus() const
    {
        return student_assignment_session_status_;
    }

    const DATA& getStudentAssignmentSessionAnswer() const
    {
        return student_assignment_session_answer_;
    }

    int getStudentAssignmentSessionScore() const
    {
        return student_assignment_session_score_;
    }

    DATETIME getStudentAssignmentSessionFinishDate() const
    {
        return student_assignment_session_finish_date_;
    }
};


#endif
