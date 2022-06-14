#ifndef CLASSROOMINFO_H
#define CLASSROOMINFO_H

#include<string>

class ClassroomInfo
{
private:
    unsigned long long id_;
    std::string name_;
    std::string teachers_name_;
public:
    ClassroomInfo(unsigned long long id, const std::string& name, const std::string& teachers_name);
    unsigned long long getId() const;
    std::string getName() const;
    std::string getTeachersName() const;
};

#endif // CLASSROOMINFO_H
