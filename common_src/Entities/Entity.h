#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#define ID unsigned long long
#define DATETIME std::string
#define DATA std::string

class Entity
{
public:
    Entity() {}
protected:
    virtual ~Entity() {}
};


#endif
