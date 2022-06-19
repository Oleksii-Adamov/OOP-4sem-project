#ifndef SERVER_DATABASESTUDENTCLASSROOMTYPE_H
#define SERVER_DATABASESTUDENTCLASSROOMTYPE_H

#include "DatabaseType.h"

class DatabaseStudentClassroomType : DatabaseType
{
    ID student_user_id_;
    ID classroom_id_;
public:
    DatabaseStudentClassroomType(const ID& student_user_id, const ID& classroom_id) : student_user_id_(student_user_id), classroom_id_(classroom_id) {};
    void setStudentUserId(const ID& student_user_id);
    void setClassroomId(const ID& classroom_id);
    ID getStudentUserId() const;
    ID getClassroomId() const;
};


#endif