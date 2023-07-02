#pragma once
#include "Container.h"

// Базовый класс для однонаправленного и двунаправленного списков
class GroupList: public Container
{
public:

    int cells_count = 0;

    GroupList(MemoryManager &mem): Container(mem), cells_count() {}

    struct Cell
    {
        void* value;
        size_t value_size;
        Cell* next;
    };

    Cell* beginning = nullptr;

    class GroupListIterator : public Container::Iterator
    {
    public:

        Cell *current = nullptr;

        // Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
        // Неявно возвращает размер данных.
        void* getElement(size_t &size) override;

        // Возвращает true, если есть следующий элемент, иначе false.
        bool hasNext() override;

        // Переходит к следующему элементу.
        void goToNext() override;

        // Возвращает true, если текущий итератор равен заданному, иначе false.
        bool equals(Container::Iterator *right) override;

        ~GroupListIterator() = default;

        friend class GroupList;

        friend class TableTest;
    };

    // Возвращает значение, равное количеству элементов в списке.
    int size() override;

    // Возвращает значение, равное максимальной вместимости списка в байтах.
    size_t max_bytes() override;

    // Удаляет все элементы из списка.
    void clear() override;

    // Если список пуст, возвращает true, иначе false.
    bool empty() override;

    // Добавляет элемент в начало списка.
    // В случае успешного добавления возвращает значение 0, иначе 1.
    int push_front(void *elem, size_t elemSize);

    // Удаляет элемент из начала списка.
    void pop_front();

    // Возвращает явно указатель на элемент, находящийся в начале списка.
    // Неявно возвращает размер данных.
    void* front(size_t &size);

    // Добавляет элемент в позицию, на которую указывает итератор iter.
    // В случае успешного добавления возвращает значение 0, иначе 1.
    int insert(Container::Iterator *iter, void *elem, size_t elemSize);

    // Возвращает указатель на итератор, указывающий на первый найденный в списке элемент.
    // Если элемент не найден, возвращает пустой указатель.
    Iterator* find(void *elem, size_t size) override;

    // Функция создает в динамической памяти итератор, указывающий на первый элемент
    // контейнера. Если контейнер пустой, возвращается нулевой указатель.
    Iterator* newIterator() override;

    // Удаляет элемент из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
    void remove(Container::Iterator *iter) override;

    friend class TableTest;
};
