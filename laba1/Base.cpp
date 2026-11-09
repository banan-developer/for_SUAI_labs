#include "Base.h"
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>

Base::Base() : name("Без имени")
{
    std::cout << "Base: конструктор без параметров (" << name << ")\n";
}

Base::Base(const std::string& name) : name(name)
{
    checkText(name);
    std::cout << "Base: конструктор с параметрами (" << name << ")\n";
}

Base::Base(const Base& other) : name(other.name)
{
    std::cout << "Base: конструктор копирования (" << name << ")\n";
}

Base::~Base()
{
    std::cout << "Base: деструктор (" << name << ")\n";
}

Base& Base::operator=(const Base& other)
{
    if (this != &other)
        name = other.name;
    return *this;
}

const std::string& Base::getName() const { return name; }

void Base::setName(const std::string& value)
{
    checkText(value);
    name = value;
}

std::ostream& operator<<(std::ostream& out, const Base& object)
{
    object.print(out);
    return out;
}

void checkText(const std::string& text)
{
    if (text.find_first_not_of(" \t\r\n") == std::string::npos)
        throw std::invalid_argument("Текстовое поле не может быть пустым.");
}

std::string readText(const std::string& prompt)
{
    std::string text;
    while (true)
    {
        std::cout << prompt;
        if (!std::getline(std::cin, text))
            throw std::runtime_error("Ввод завершён.");
        try
        {
            checkText(text);
            return text;
        }
        catch (const std::invalid_argument& error)
        {
            std::cout << error.what() << '\n';
        }
    }
}

int readNumber(const std::string& prompt, int min, int max)
{
    while (true)
    {
        std::string line = readText(prompt);
        std::istringstream in(line);
        int number;
        if (in >> number && (in >> std::ws).eof() && number >= min && number <= max)
            return number;
        std::cout << "Введите целое число от " << min << " до " << max << ".\n";
    }
}

std::string readFileText(std::istream& in)
{
    std::string text;
    in >> std::ws;
    if (in.peek() != '"' || !(in >> std::quoted(text)))
        throw std::runtime_error("Не удалось прочитать текстовое поле из файла.");
    checkText(text);
    return text;
}

std::string* copySkills(const std::string* skills, int count)
{
    if (count < 0 || (count > 0 && skills == nullptr))
        throw std::invalid_argument("Некорректный список навыков.");
    for (int i = 0; i < count; ++i)
        checkText(skills[i]);

    std::string* result = new std::string[count];
    try
    {
        for (int i = 0; i < count; ++i)
            result[i] = skills[i];
    }
    catch (...)
    {
        delete[] result;
        throw;
    }
    return result;
}

std::string* inputSkills(int& count)
{
    count = readNumber("Количество навыков: ", 1, std::numeric_limits<int>::max());
    std::string* skills = new std::string[count];
    try
    {
        for (int i = 0; i < count; ++i)
            skills[i] = readText("Навык " + std::to_string(i + 1) + ": ");
    }
    catch (...)
    {
        delete[] skills;
        throw;
    }
    return skills;
}

std::string* loadSkills(std::istream& in, int& count)
{
    if (!(in >> count) || count < 0)
        throw std::runtime_error("Неверное количество навыков в файле.");
    std::string* skills = new std::string[count];
    try
    {
        for (int i = 0; i < count; ++i)
            skills[i] = readFileText(in);
    }
    catch (...)
    {
        delete[] skills;
        throw;
    }
    return skills;
}
