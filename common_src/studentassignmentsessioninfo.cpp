#include "studentassignmentsessioninfo.h"

StudentAssignmentSessionInfo::StudentAssignmentSessionInfo()
{

}

StudentAssignmentSessionInfo::StudentAssignmentSessionInfo(unsigned long long id, StudentAssignmentSessionStatus status,
                             const std::string& finish_date_time, const std::string& student_user_name,
                             long long score)
    :id_(id), status_(status), finish_date_time_(finish_date_time), student_user_name_(student_user_name), score_(score)
{

}

unsigned long long StudentAssignmentSessionInfo::getId() const
{
    return id_;
}

StudentAssignmentSessionStatus StudentAssignmentSessionInfo::getStatus()
{
    return status_;
}

std::string StudentAssignmentSessionInfo::getFinishDateTime()
{
    return finish_date_time_;
}

std::string StudentAssignmentSessionInfo::getStudentUserName() const
{
    return student_user_name_;
}

long long StudentAssignmentSessionInfo::getScore() const
{
    return score_;
}
