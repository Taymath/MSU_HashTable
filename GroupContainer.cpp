#include "GroupContainer.h"

size_t GroupContainer::hash_func(void *key, size_t keySize, size_t size)
{
    size_t hash = 0;

    char* temp = static_cast<char*>(key);

    for (int i = 0; i < keySize; i++)
    {
        hash = 3559 * hash + temp[i];
        hash %= 8690063;
    }
    return hash % size;
}




