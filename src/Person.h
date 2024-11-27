#pragma once

#include <iostream>
#include <string>

class Person
{
public:
    virtual std::string getRole() const = 0;

    virtual ~Person() = default;
};
