#include "Hero.h"
#include <iomanip>
#include <stdexcept>
#include <utility>

Hero::Hero() : weapon("Не указано"), skills(nullptr), skillCount(0)
{
    std::cout << "Hero: конструктор без параметров (" << name << ")\n";
}

Hero::Hero(const std::string& name, const std::string& weapon,
           const std::string* skills, int skillCount)
    : Base(name), weapon(weapon), skills(nullptr), skillCount(0)
{
    checkText(weapon);
    setSkills(skills, skillCount);
    std::cout << "Hero: конструктор с параметрами (" << name << ")\n";
}

Hero::Hero(const Hero& other)
    : Base(other), weapon(other.weapon),
      skills(copySkills(other.skills, other.skillCount)), skillCount(other.skillCount)
{
    std::cout << "Hero: конструктор копирования (" << name << ")\n";
}

Hero::~Hero()
{
    delete[] skills;
    std::cout << "Hero: деструктор (" << name << ")\n";
}

Hero& Hero::operator=(const Hero& other)
{
    if (this != &other)
    {
        Hero copy(other);
        name.swap(copy.name);
        weapon.swap(copy.weapon);
        std::swap(skills, copy.skills);
        std::swap(skillCount, copy.skillCount);
    }
    return *this;
}

const std::string& Hero::getWeapon() const { return weapon; }

void Hero::setWeapon(const std::string& value)
{
    checkText(value);
    weapon = value;
}

int Hero::getSkillCount() const { return skillCount; }

const std::string& Hero::getSkill(int index) const
{
    if (index < 0 || index >= skillCount)
        throw std::out_of_range("Навык с таким номером не найден.");
    return skills[index];
}

void Hero::setSkills(const std::string* values, int count)
{
    if (count <= 0)
        throw std::invalid_argument("У героя должен быть хотя бы один навык.");
    std::string* replacement = copySkills(values, count);
    delete[] skills;
    skills = replacement;
    skillCount = count;
}

const char* Hero::getType() const { return "Hero"; }
Base* Hero::clone() const { return new Hero(*this); }

void Hero::input()
{
    std::string newName = readText("Имя героя: ");
    std::string newWeapon = readText("Тип оружия: ");
    int count;
    std::string* newSkills = inputSkills(count);
    name.swap(newName);
    weapon.swap(newWeapon);
    delete[] skills;
    skills = newSkills;
    skillCount = count;
}

void Hero::print(std::ostream& out) const
{
    out << "Положительный герой\nИмя: " << name << "\nТип оружия: " << weapon
        << "\nОсновные навыки:\n";
    for (int i = 0; i < skillCount; ++i)
        out << "  " << i + 1 << ". " << skills[i] << '\n';
}

void Hero::save(std::ostream& out) const
{
    out << std::quoted(name) << '\n' << std::quoted(weapon) << '\n' << skillCount << '\n';
    for (int i = 0; i < skillCount; ++i)
        out << std::quoted(skills[i]) << '\n';
}

void Hero::load(std::istream& in)
{
    std::string newName = readFileText(in);
    std::string newWeapon = readFileText(in);
    int count;
    std::string* newSkills = loadSkills(in, count);
    name.swap(newName);
    weapon.swap(newWeapon);
    delete[] skills;
    skills = newSkills;
    skillCount = count;
}
