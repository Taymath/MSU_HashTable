#include "GroupList.h"

// Возвращает значение, равное количеству элементов в списке.
int GroupList::size()
{
    return cells_count;
}
// Возвращает значение, равное максимальной вместимости спискаа в байтах.
size_t GroupList::max_bytes()
{
    return _memory.maxBytes();
}
// Функция создает в динамической памяти итератор, указывающий на первый элемент
// контейнера. Если контейнер пустой, возвращается нулевой указатель.
GroupList::Iterator* GroupList::newIterator()
{
    auto *iterator = new GroupListIterator();

    iterator -> current = beginning;

    if(empty())
        return nullptr;

    return iterator;
}
// Удаляет все элементы из списка.
void GroupList::clear()
{
    Cell *trash = beginning;

    while (trash != nullptr)
    {
        beginning = beginning -> next;

        _memory.freeMem(trash -> value);
        _memory.freeMem(trash);

        trash = beginning;
    }
}
// Если список пуст, возвращает true, иначе false.
bool GroupList::empty()
{
    return (beginning == nullptr);
}

// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
// Неявно возвращает размер данных.
void* GroupList::GroupListIterator::getElement(size_t &size)
{
    size = current -> value_size;

    return current -> value;
}
// Возвращает true, если есть следующий элемент, иначе false.
bool GroupList::GroupListIterator::hasNext()
{
    return (current != nullptr) && (current -> next != nullptr);
}
// Переходит к следующему элементу.
void GroupList::GroupListIterator::goToNext()
{
    if (current == nullptr)
        return;

    current = current->next;
}
// Возвращает true, если текущий итератор равен заданному, иначе false.
bool GroupList::GroupListIterator::equals(Container::Iterator *right)
{
    return (current == dynamic_cast<GroupListIterator*>(right) -> current);
}
// Добавляет элемент в начало списка.
// В случае успешного добавления возвращает значение 0, иначе 1.
int GroupList::push_front(void *elem, size_t elemSize)
{
    Cell* front = static_cast<Cell*>(_memory.allocMem(sizeof(Cell)));

    front -> value = static_cast<void*>(new char[elemSize]);

    if (front -> value == nullptr)
    {
        delete front;
        return 1;
    }

    memcpy(front -> value, elem, elemSize);

    front -> value_size = elemSize;
    front -> next = beginning;
    beginning = front;
    cells_count ++;

    return 0;
}
// Удаляет элемент из начала списка.
void GroupList::pop_front()
{
    if (beginning == nullptr)
        return;

    Cell* trash = beginning;
    beginning = beginning -> next;

    _memory.freeMem(trash->value);
    _memory.freeMem(trash);

    cells_count --;
}
// Возвращает явно указатель на элемент, находящийся в начале списка.
// Неявно возвращает размер данных.
void* GroupList::front(size_t &size)
{
    if (empty())
    {
        size = 0;
        return nullptr;
    }

    size = beginning -> value_size;

    return beginning -> value;
}
// Добавляет элемент в позицию, на которую указывает итератор iter.
// В случае успешного добавления возвращает значение 0, иначе 1.
int GroupList::insert(Container::Iterator *iter, void *elem, size_t elemSize)
{
    auto *iterator = dynamic_cast<GroupListIterator*>(iter);
    Cell* new_cell = static_cast<Cell*>(_memory.allocMem(sizeof(Cell)));

    if (iterator -> current == beginning)
    {
        new_cell -> next = beginning;
        beginning = new_cell;
    }
    else
    {
        auto *trash = dynamic_cast<GroupListIterator*>(newIterator());
        trash -> current = beginning -> next;
        Cell* previous = beginning;

        while (trash -> current != iterator -> current)
        {
            if (trash -> hasNext())
                trash -> goToNext();
            else
            {
                _memory.freeMem(new_cell);
                return 1;
            }

            previous = previous->next;
        }

        previous -> next = new_cell;
        new_cell -> next = trash -> current;
    }

    new_cell -> value = _memory.allocMem(elemSize);

    memcpy(new_cell -> value, elem, elemSize);

    new_cell -> value_size = elemSize;
    cells_count ++;

    return 0;
}
// Возвращает указатель на итератор, указывающий на первый найденный в списке элемент.
// Если элемент не найден, возвращает пустой указатель.
GroupList::Iterator* GroupList::find(void *elem, size_t size)
{
    if (empty())
        return nullptr;

    auto* tmp = dynamic_cast<GroupListIterator*>(newIterator());
    tmp -> current = beginning;

    while (tmp -> current != nullptr)
    {
        if (size != tmp -> current -> value_size)
        {
            tmp -> goToNext();
            continue;
        }

        if (!memcmp(elem, tmp -> current -> value, size))
            break;
        else
            tmp -> goToNext();
    }

    if (tmp -> current == nullptr)
        return nullptr;

    return tmp;
}
// Удаляет элемент из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void GroupList::remove(Container::Iterator *iter)
{
    auto *iterator = dynamic_cast<GroupListIterator*>(iter);

    if (iterator -> current == beginning)
        pop_front();
    else
    {
        auto *trash = dynamic_cast<GroupListIterator*>(newIterator());
        trash -> current = beginning -> next;
        Cell *previous = beginning;

        while (trash -> current != iterator -> current)
        {
            trash -> goToNext();
            previous = previous -> next;

            if (trash -> current == nullptr)
                exit(1);

        }

        previous -> next = iterator -> current -> next;

        _memory.freeMem(trash -> current -> value);
        _memory.freeMem(trash -> current);

        cells_count --;
    }

    iterator -> goToNext();
}
