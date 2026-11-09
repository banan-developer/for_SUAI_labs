#include "Villain.h"
#include <iomanip>
#include <stdexcept>
#include <utility>

Villain::Villain()
    : weapon("Не указано"), evilDeed("Не указано"), habitat("Не указано"),
      skills(nullptr), skillCount(0)
{
    std::cout << "Villain: конструктор без параметров (" << name << ")\n";
}

Villain::Villain(const std::string& name, const std::string& weapon,
                 const std::string& evilDeed, const std::string& habitat,
                 const std::string* skills, int skillCount)
    : Base(name), weapon(weapon), evilDeed(evilDeed), habitat(habitat),
      skills(nullptr), skillCount(0)
{
    checkText(weapon);
    checkText(evilDeed);
    checkText(habitat);
    setSkills(skills, skillCount);
    std::cout << "Villain: конструктор с параметрами (" << name << ")\n";
}

Villain::Villain(const Villain& other)
    : Base(other), weapon(other.weapon), evilDeed(other.evilDeed), habitat(other.habitat),
      skills(copySkills(other.skills, other.skillCount)), skillCount(other.skillCount)
{
    std::cout << "Villain: конструктор копирования (" << name << ")\n";
}

Villain::~Villain()
{
    delete[] skills;
    std::cout << "Villain: деструктор (" << name << ")\n";
}

Villain& Villain::operator=(const Villain& other)
{
    if (this != &other)
    {
        Villain copy(other);
        name.swap(copy.name);
        weapon.swap(copy.weapon);
        evilDeed.swap(copy.evilDeed);
        habitat.swap(copy.habitat);
        std::swap(skills, copy.skills);
        std::swap(skillCount, copy.skillCount);
    }
    return *this;
}

const std::string& Villain::getWeapon() const { return weapon; }
const std::string& Villain::getEvilDeed() const { return evilDeed; }
const std::string& Villain::getHabitat() const { return habitat; }
int Villain::getSkillCount() const { return skillCount; }

void Villain::setWeapon(const std::string& value)
{
    checkText(value);
    weapon = value;
}

void Villain::setEvilDeed(const std::string& value)
{
    checkText(value);
    evilDeed = value;
}

void Villain::setHabitat(const std::string& value)
{
    checkText(value);
    habitat = value;
}

const std::string& Villain::getSkill(int index) const
{
    if (index < 0 || index >= skillCount)
        throw std::out_of_range("Навык с таким номером не найден.");
    return skills[index];
}

void Villain::setSkills(const std::string* values, int count)
{
    if (count <= 0)
        throw std::invalid_argument("У злодея должен быть хотя бы один навык.");
    std::string* replacement = copySkills(values, count);
    delete[] skills;
    skills = replacement;
    skillCount = count;
}

const char* Villain::getType() const { return "Villain"; }
Base* Villain::clone() const { return new Villain(*this); }

void Villain::input()
{
    std::string newName = readText("Имя злодея: ");
    std::string newWeapon = readText("Тип оружия: ");
    std::string newEvilDeed = readText("Совершённое злодеяние: ");
    std::string newHabitat = readText("Место обитания: ");
    int count;
    std::string* newSkills = inputSkills(count);
    name.swap(newName);
    weapon.swap(newWeapon);
    evilDeed.swap(newEvilDeed);
    habitat.swap(newHabitat);
    delete[] skills;
    skills = newSkills;
    skillCount = count;
}

void Villain::print(std::ostream& out) const
{
    out << "Злодей\nИмя: " << name << "\nТип оружия: " << weapon
        << "\nЗлодеяние: " << evilDeed << "\nМесто обитания: " << habitat
        << "\nОсновные навыки:\n";
    for (int i = 0; i < skillCount; ++i)
        out << "  " << i + 1 << ". " << skills[i] << '\n';
}

void Villain::save(std::ostream& out) const
{
    out << std::quoted(name) << '\n' << std::quoted(weapon) << '\n'
        << std::quoted(evilDeed) << '\n' << std::quoted(habitat) << '\n'
        << skillCount << '\n';
    for (int i = 0; i < skillCount; ++i)
        out << std::quoted(skills[i]) << '\n';
}

void Villain::load(std::istream& in)
{
    std::string newName = readFileText(in);
    std::string newWeapon = readFileText(in);
    std::string newEvilDeed = readFileText(in);
    std::string newHabitat = readFileText(in);
    int count;
    std::string* newSkills = loadSkills(in, count);
    name.swap(newName);
    weapon.swap(newWeapon);
    evilDeed.swap(newEvilDeed);
    habitat.swap(newHabitat);
    delete[] skills;
    skills = newSkills;
    skillCount = count;
}
