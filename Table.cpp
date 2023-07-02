#include "Table.h"

//ненужная хэш функция, реализация рабочей находится в GroupContainer.cpp
size_t Table::hash_function(void *key, size_t keySize)
{
    return 0;
}
// Возвращает значение, равное максимальной вместимости контейнера в байтах.
int Table::size()
{
    return (int)elements_count;
}
// Возвращает значение, равное максимальной вместимости контейнера в байтах.(сомнительная штука)
size_t Table ::max_bytes()
{
    return _memory.maxBytes();
}
// Если контейнер пуст, возвращает true, иначе false.
bool Table::empty()
{
    return !elements_count;
}
// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
// Неявно возвращает размер данных.
void* Table::TableIterator::getElement(size_t &size)
{
	auto* temp = static_cast<ArrayCell*>(current->getElement(size));
	return temp -> elem;
}
// Возвращает true, если есть следующий элемент, иначе false.
bool Table::TableIterator::hasNext()
{
	if(current -> hasNext())
		return true;

	return false;
}
// Возвращает true, если текущий итератор равен заданному, иначе false.
bool Table::TableIterator::equals(Iterator *right)
{
    if (current == dynamic_cast<TableIterator*>(right) -> current)
        return true;
    return false;
}
// Переходит к следующему элементу.
void Table::TableIterator::goToNext()
{
	if (current -> hasNext())
		current -> goToNext();
}

// Создает итератор, соответствующий данному типу контейнера.
Table::Iterator* Table::newIterator()
{
    size_t size = _memory.size();

    for (int i = 0; i < size; i++)
    {
        if(array_table[i] != nullptr)
            return new TableIterator((array_table[i] -> newIterator()), i);
    }
    return nullptr;
}
// Добавление элемента в контейнер, с сответствующим ключом.
// В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
int Table::insertByKey(void *key, size_t keySize, void *elem, size_t elemSize)
{
	size_t index = hash_func(key, keySize, _memory.size());

	char *keyToSave = static_cast<char*>(_memory.allocMem(sizeof(keySize)));
    memcpy(keyToSave, key, keySize);

    char *elemToSave = static_cast<char*>(_memory.allocMem(sizeof(elemSize)));
	memcpy(elemToSave, elem, elemSize);

	ArrayCell temp = {keyToSave, keySize, elemToSave, elemSize};

    void* data = static_cast<void*>(&temp);
	size_t data_size = sizeof(temp);

    if(array_table[index] == nullptr)
    {
        array_table[index] = new TableList(_memory);
    }

    if(array_table[index] -> empty())
    {
        array_table[index] -> push_front(data, data_size);

        if(array_table[index]->cells_count > 50)
            re_hash();

        elements_count ++;

        return 0;
    }
    else
    {
        if (array_table[index] -> find(key, keySize) == nullptr)
        {
            array_table[index] -> push_front(data, data_size);

            if(array_table[index]->cells_count > 50)
                re_hash();

            elements_count ++;
            return 0;
        }
    }
	return 1;
}
// Удаление элемента с сответствующим ключом из контейнера.
void Table::removeByKey(void *key, size_t keySize)
{
    size_t index = hash_func(key, keySize, _memory.size());

    if(array_table[index] != nullptr)
    {
        TableList::Iterator *tmp = array_table[index]->find(key, keySize);

        if (tmp != nullptr)
        {
            array_table[index]->remove(tmp);
            elements_count--;
        }
        if (array_table[index]->empty())
        {
            _memory.freeMem(array_table[index]);
            array_table[index] = nullptr;
        }
    }
}
// Возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
// Если элемент не найден, возвращает нулевой указатель.
Container::Iterator* Table::findByKey(void *key, size_t keySize)
{
    size_t index = hash_func(key, keySize, _memory.size());

    if(array_table[index] == nullptr || array_table[index] -> empty())
        return nullptr;

    auto* temp = static_cast<TableList::Iterator*>(array_table[index] -> find(key, keySize));

    if (temp == nullptr)
        return nullptr;

    Container::Iterator * tmp = new TableIterator(temp, (int)index);

    return tmp;
}

// Возвращает указатель на элемент с ключом key.
void* Table::at(void *key, size_t keySize, size_t &valueSize)
{
    size_t index = hash_func(key, keySize, _memory.size());

    auto *findkey = static_cast<ArrayCell*>(array_table[index] -> find(key, keySize) ->getElement(valueSize));

    return findkey;
}

// Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
// Если элемент не найден, возвращает пустой указатель.
Container::Iterator* Table::find(void *elem, size_t size)
{
    auto* finder = dynamic_cast<TableIterator *>(newIterator());

    while (finder!= nullptr && finder->current != nullptr)
    {
        size_t trash;

        auto *findedCell = static_cast<ArrayCell *>(finder -> current -> getElement(trash));

        if (findedCell -> elem_size == size && memcmp(findedCell->elem, elem, size) == 0)
            return new TableIterator(finder -> current, finder -> index);

        finder -> goToNext();
    }

    return nullptr;
}

// Удаляет элемент из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void Table::remove(Iterator *iter)
{
    auto* Iter = dynamic_cast<TableIterator *>(iter);
    if(Iter != nullptr && Iter -> current != nullptr)
    {
        array_table[Iter->index]->remove(Iter -> current);
        elements_count --;
    }

    if (array_table[Iter->index]->empty())
    {
        _memory.freeMem(array_table[Iter -> index]);
        array_table[Iter -> index] = nullptr;
    }
}
// Удаляет все элементы из контейнера.
void Table::clear()
{
    size_t size = _memory.size();

    for(int i = 0; i < size; i++)
    {
        _memory.freeMem(array_table[i]);
        array_table[i] = nullptr;
    }

    elements_count = 0;

}

/*Создается вторая копия массива
Закладываются по одному все элементы
Как будто делаю ремув из одного и инсерт в другой, с помощью хэш функции. Первая ищет в старом, вторая в новом
Степени двойки для вызова*/

void Table::re_hash()
{
    size_t index;
    int original = elements_count;

    TableList **cur_array = reinterpret_cast<TableList **>(calloc(2 * _memory.size(), sizeof(TableList*)));

    for (int i = 0; i < original; i++)
    {
        removeByKey(&i, sizeof(int));

        index = hash_func(&i, sizeof(int), 2 * _memory.size());

        char *keyToSave = static_cast<char *>(_memory.allocMem(sizeof(i)));
        memcpy(keyToSave, &i, sizeof(int));

        char *elemToSave = static_cast<char *>(_memory.allocMem(sizeof(i)));
        memcpy(elemToSave, &i, sizeof(int));

        ArrayCell temp = {keyToSave, sizeof(int), elemToSave, sizeof(int)};

        void *data = static_cast<void *>(&temp);
        size_t data_size = sizeof(temp);

        if(cur_array[index] == nullptr)
        {
            cur_array[index] = new TableList(_memory);
        }

        if (cur_array[index]->empty())
            cur_array[index]->push_front(data, data_size);
        else
        {
            if (cur_array[index]->find(&i, sizeof(int)) == nullptr)
                cur_array[index]->push_front(data, data_size);
        }
    }
        array_table = cur_array;

        _memory.size_setter(2 * _memory.size());

        c_size = _memory.size();
}

