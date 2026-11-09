#pragma once

#include "Base.h"

class Hero : public Base
{
    std::string weapon;
    std::string* skills;
    int skillCount;

public:
    Hero();
    Hero(const std::string& name, const std::string& weapon,
         const std::string* skills, int skillCount);
    Hero(const Hero& other);
    ~Hero() override;
    Hero& operator=(const Hero& other);

    const std::string& getWeapon() const;
    void setWeapon(const std::string& value);
    int getSkillCount() const;
    const std::string& getSkill(int index) const;
    void setSkills(const std::string* values, int count);

    const char* getType() const override;
    Base* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
