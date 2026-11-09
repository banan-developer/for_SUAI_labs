#include "Monster.h"
#include <iomanip>

Monster::Monster() : appearance("Не указано")
{
    std::cout << "Monster: конструктор без параметров (" << name << ")\n";
}

Monster::Monster(const std::string& name, const std::string& appearance)
    : Base(name), appearance(appearance)
{
    checkText(appearance);
    std::cout << "Monster: конструктор с параметрами (" << name << ")\n";
}

Monster::Monster(const Monster& other) : Base(other), appearance(other.appearance)
{
    std::cout << "Monster: конструктор копирования (" << name << ")\n";
}

Monster::~Monster()
{
    std::cout << "Monster: деструктор (" << name << ")\n";
}

Monster& Monster::operator=(const Monster& other)
{
    if (this != &other)
    {
        Monster copy(other);
        name.swap(copy.name);
        appearance.swap(copy.appearance);
    }
    return *this;
}

const std::string& Monster::getAppearance() const { return appearance; }

void Monster::setAppearance(const std::string& value)
{
    checkText(value);
    appearance = value;
}

const char* Monster::getType() const { return "Monster"; }
Base* Monster::clone() const { return new Monster(*this); }

void Monster::input()
{
    std::string newName = readText("Наименование монстра: ");
    std::string newAppearance = readText("Описание внешнего вида: ");
    name.swap(newName);
    appearance.swap(newAppearance);
}

void Monster::print(std::ostream& out) const
{
    out << "Монстр\nНаименование: " << name
        << "\nОписание внешнего вида: " << appearance << '\n';
}

void Monster::save(std::ostream& out) const
{
    out << std::quoted(name) << '\n' << std::quoted(appearance) << '\n';
}

void Monster::load(std::istream& in)
{
    std::string newName = readFileText(in);
    std::string newAppearance = readFileText(in);
    name.swap(newName);
    appearance.swap(newAppearance);
}
