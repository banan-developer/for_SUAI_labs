#pragma once

#include "Base.h"

class Monster : public Base
{
    std::string appearance;

public:
    Monster();
    Monster(const std::string& name, const std::string& appearance);
    Monster(const Monster& other);
    ~Monster() override;
    Monster& operator=(const Monster& other);

    const std::string& getAppearance() const;
    void setAppearance(const std::string& value);

    const char* getType() const override;
    Base* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
