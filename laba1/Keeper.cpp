#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"
#include <filesystem>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <utility>

Keeper::Keeper() : objects(nullptr), size(0)
{
    std::cout << "Keeper: конструктор без параметров\n";
}

Keeper::Keeper(const Base& object) : objects(nullptr), size(0)
{
    add(object);
    std::cout << "Keeper: конструктор с параметрами\n";
}

Keeper::Keeper(const Keeper& other) : objects(nullptr), size(0)
{
    try
    {
        for (int i = 0; i < other.size; ++i)
            add(*other.objects[i]);
    }
    catch (...)
    {
        clear();
        throw;
    }
    std::cout << "Keeper: конструктор копирования\n";
}

Keeper::~Keeper()
{
    clear();
    std::cout << "Keeper: деструктор\n";
}

void Keeper::swap(Keeper& other) noexcept
{
    std::swap(objects, other.objects);
    std::swap(size, other.size);
}

Keeper& Keeper::operator=(const Keeper& other)
{
    if (this != &other)
    {
        Keeper copy(other);
        swap(copy);
    }
    return *this;
}

void Keeper::checkIndex(int index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Объект с таким номером не найден.");
}

Base& Keeper::operator[](int index)
{
    checkIndex(index);
    return *objects[index];
}

const Base& Keeper::operator[](int index) const
{
    checkIndex(index);
    return *objects[index];
}

int Keeper::getSize() const { return size; }

void Keeper::add(const Base& object)
{
    if (size == std::numeric_limits<int>::max())
        throw std::length_error("Контейнер заполнен.");

    Base** replacement = new Base*[size + 1];
    for (int i = 0; i < size; ++i)
        replacement[i] = objects[i];
    try
    {
        replacement[size] = object.clone();
    }
    catch (...)
    {
        delete[] replacement;
        throw;
    }
    delete[] objects;
    objects = replacement;
    ++size;
}

void Keeper::remove(int index)
{
    checkIndex(index);
    delete objects[index];
    for (int i = index; i < size - 1; ++i)
        objects[i] = objects[i + 1];
    --size;
    objects[size] = nullptr;
}

void Keeper::clear()
{
    for (int i = 0; i < size; ++i)
        delete objects[i];
    delete[] objects;
    objects = nullptr;
    size = 0;
}

void Keeper::print(std::ostream& out) const
{
    if (size == 0)
    {
        out << "Контейнер пуст.\n";
        return;
    }
    for (int i = 0; i < size; ++i)
        out << "\nОбъект №" << i + 1 << '\n' << *objects[i];
}

void Keeper::save(const std::string& filename) const
{
    std::ofstream out(std::filesystem::u8path(filename), std::ios::binary);
    if (!out)
        throw std::runtime_error("Не удалось открыть файл для записи.");

    out << "KEEPER 1\n" << size << '\n';
    for (int i = 0; i < size; ++i)
    {
        out << objects[i]->getType() << '\n';
        objects[i]->save(out);
    }
    out.close();
    if (!out)
        throw std::runtime_error("Ошибка записи данных в файл.");
}

void Keeper::load(const std::string& filename)
{
    std::ifstream in(std::filesystem::u8path(filename), std::ios::binary);
    if (!in)
        throw std::runtime_error("Не удалось открыть файл для чтения.");

    std::string header;
    int version, count;
    if (!(in >> header >> version >> count) || header != "KEEPER" || version != 1 || count < 0)
        throw std::runtime_error("Неверный формат файла Keeper.");

    // Данные заменяются только после успешного чтения всего файла.
    Keeper loaded;
    for (int i = 0; i < count; ++i)
    {
        std::string type;
        if (!(in >> type))
            throw std::runtime_error("В файле не хватает объектов.");

        Base* object = nullptr;
        if (type == "Hero")
            object = new Hero;
        else if (type == "Villain")
            object = new Villain;
        else if (type == "Monster")
            object = new Monster;
        else
            throw std::runtime_error("Неизвестный тип объекта в файле: " + type);

        try
        {
            object->load(in);
            loaded.add(*object);
        }
        catch (...)
        {
            delete object;
            throw;
        }
        delete object;
    }
    in >> std::ws;
    if (in.bad() || !in.eof())
        throw std::runtime_error("В конце файла обнаружены лишние данные.");
    swap(loaded);
}
