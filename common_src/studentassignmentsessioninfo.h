#ifndef STUDENTASSIGNMENTSESSIONINFO_H
#define STUDENTASSIGNMENTSESSIONINFO_H

#include "string"

enum class StudentAssignmentSessionStatus {not_submitted, submitted, checked};

class StudentAssignmentSessionInfo
{
private:
    unsigned long long id_ = 0;
    StudentAssignmentSessionStatus status_;
    std::string finish_date_time_;
    std::string student_user_name_;
    long long score_;

public:
    StudentAssignmentSessionInfo();
    StudentAssignmentSessionInfo(unsigned long long id, StudentAssignmentSessionStatus status,
                                 const std::string& finish_date_time, const std::string& student_user_name,
                                 long long score = 0);
    unsigned long long getId() const;
    StudentAssignmentSessionStatus getStatus();
    std::string getFinishDateTime();
    std::string getStudentUserName() const;
    long long getScore() const;
};

#endif // STUDENTASSIGNMENTSESSIONINFO_H
