#pragma once
#include "Container.h"

// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer: public Container
{
public:

    GroupContainer(MemoryManager &mem): Container(mem) {}

    // хэш функция
    size_t hash_func(void *key, size_t keySize, size_t size);

};
