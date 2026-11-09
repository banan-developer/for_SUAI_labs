#pragma once

#include "Base.h"

class Villain : public Base
{
    std::string weapon;
    std::string evilDeed;
    std::string habitat;
    std::string* skills;
    int skillCount;

public:
    Villain();
    Villain(const std::string& name, const std::string& weapon,
            const std::string& evilDeed, const std::string& habitat,
            const std::string* skills, int skillCount);
    Villain(const Villain& other);
    ~Villain() override;
    Villain& operator=(const Villain& other);

    const std::string& getWeapon() const;
    void setWeapon(const std::string& value);
    const std::string& getEvilDeed() const;
    void setEvilDeed(const std::string& value);
    const std::string& getHabitat() const;
    void setHabitat(const std::string& value);
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
