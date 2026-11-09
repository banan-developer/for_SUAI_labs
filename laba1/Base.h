#pragma once

#include <iostream>
#include <string>

class Base
{
protected:
    std::string name;

public:
    Base();
    explicit Base(const std::string& name);
    Base(const Base& other);
    virtual ~Base();
    Base& operator=(const Base& other);

    const std::string& getName() const;
    void setName(const std::string& value);

    virtual const char* getType() const = 0;
    virtual Base* clone() const = 0;
    virtual void input() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

    friend std::ostream& operator<<(std::ostream& out, const Base& object);
};

std::string readText(const std::string& prompt);
int readNumber(const std::string& prompt, int min, int max);
void checkText(const std::string& text);
std::string readFileText(std::istream& in);
std::string* copySkills(const std::string* skills, int count);
std::string* inputSkills(int& count);
std::string* loadSkills(std::istream& in, int& count);
