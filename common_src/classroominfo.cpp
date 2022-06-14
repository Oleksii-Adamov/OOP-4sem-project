#include "classroominfo.h"

ClassroomInfo::ClassroomInfo(unsigned long long id, const std::string& name, const std::string& teachers_name)
    : id_(id), name_(name), teachers_name_(teachers_name)
{

}
unsigned long long ClassroomInfo::getId() const
{
    return id_;
}
std::string ClassroomInfo::getName() const
{
    return name_;
}
std::string ClassroomInfo::getTeachersName() const
{
    return teachers_name_;
}
