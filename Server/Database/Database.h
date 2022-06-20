#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H

#include "../../common_src/Entities/Entities.h"
#include "../../common_src/studentassignmentsessioninfo.h"
#include <string>
#include <vector>

class Database
{
public:
    //! Initializes the database (creates if it doesn't exist)
    static void init();

    //! Returns all the user's classrooms in which he is a teacher
    static std::pair<bool, std::vector<Classroom>> selectAllClassroomsWhereUserIsTeacher(ID UserId);

    //!
    //static std::vector<StudentAssignmentSessionInfo> select
};


#endif