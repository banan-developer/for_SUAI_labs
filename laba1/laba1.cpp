#include <iostream>

#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"
#include <stdexcept>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

void addObject(Keeper& keeper)
{
    std::cout << "1. Положительный герой\n2. Злодей\n3. Монстр\n";
    int type = readNumber("Выберите тип: ", 1, 3);
    if (type == 1)
    {
        Hero hero;
        hero.input();
        keeper.add(hero);
    }
    else if (type == 2)
    {
        Villain villain;
        villain.input();
        keeper.add(villain);
    }
    else
    {
        Monster monster;
        monster.input();
        keeper.add(monster);
    }
    std::cout << "Объект добавлен.\n";
}

int chooseObject(const Keeper& keeper)
{
    if (keeper.getSize() == 0)
        throw std::runtime_error("Контейнер пуст.");
    for (int i = 0; i < keeper.getSize(); ++i)
        std::cout << i + 1 << ". " << keeper[i].getName()
                  << " (" << keeper[i].getType() << ")\n";
    return readNumber("Номер объекта: ", 1, keeper.getSize()) - 1;
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    Keeper keeper;
    std::cout << "Лабораторная работа №1. Вариант 5. Герои\n";
    while (true)
    {
        std::cout << "\n1. Добавить объект\n"
                  << "2. Показать все объекты\n"
                  << "3. Показать объект по номеру\n"
                  << "4. Изменить объект\n"
                  << "5. Удалить объект\n"
                  << "6. Копировать объект\n"
                  << "7. Сохранить в файл\n"
                  << "8. Загрузить из файла (заменить текущие данные)\n"
                  << "0. Выход\n";
        try
        {
            int command = readNumber("Ваш выбор: ", 0, 8);
            switch (command)
            {
            case 0:
                return 0;
            case 1:
                addObject(keeper);
                break;
            case 2:
                keeper.print(std::cout);
                break;
            case 3:
                std::cout << keeper[chooseObject(keeper)];
                break;
            case 4:
                keeper[chooseObject(keeper)].input();
                std::cout << "Данные изменены.\n";
                break;
            case 5:
                keeper.remove(chooseObject(keeper));
                std::cout << "Объект удалён.\n";
                break;
            case 6:
                keeper.add(keeper[chooseObject(keeper)]);
                std::cout << "Копия добавлена.\n";
                break;
            case 7:
                keeper.save(readText("Имя файла для сохранения: "));
                std::cout << "Данные сохранены.\n";
                break;
            case 8:
                keeper.load(readText("Имя файла для загрузки: "));
                std::cout << "Данные загружены.\n";
                break;
            }
        }
        catch (const std::exception& error)
        {
            std::cout << "Ошибка: " << error.what() << '\n';
            if (!std::cin)
                return 0;
        }
    }
}
