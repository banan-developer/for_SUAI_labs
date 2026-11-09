#pragma once

#include "Base.h"

class Keeper
{
    Base** objects;
    int size;

    void checkIndex(int index) const;
    void swap(Keeper& other) noexcept;

public:
    Keeper();
    explicit Keeper(const Base& object);
    Keeper(const Keeper& other);
    ~Keeper();
    Keeper& operator=(const Keeper& other);
    Base& operator[](int index);
    const Base& operator[](int index) const;

    int getSize() const;
    void add(const Base& object);
    void remove(int index);
    void clear();
    void print(std::ostream& out) const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
};
