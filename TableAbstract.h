#pragma once

#include "GroupContainer.h"

// Абстрактный класс - Ассоциативная таблица.
class AbstractTable: public GroupContainer
{
	public:

	// Конструктор.
	AbstractTable(MemoryManager &mem): GroupContainer(mem) {}

	// Деструктор.
	virtual ~AbstractTable() {}

	// Добавляет элемент с сответствующим ключом в контейнер.
	// В случае успешного добавления функция возвращает значение 0, иначе 1.
	virtual int insertByKey(void *key, size_t keySize, void *elem, size_t elemSize) = 0;

	// Удаляет элемент с сответствующим ключом из контейнера.
	virtual void removeByKey(void *key, size_t keySize) = 0;

	// Возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
	// Если элемент не найден, возвращает нулевой указатель.
	virtual Iterator* findByKey(void *key, size_t keySize) = 0;

	// Возвращает указатель на элемент с ключом key.
	virtual void* at(void *key, size_t keySize, size_t &valueSize) = 0;

    // хэш функция не используемая
    virtual size_t hash_function(void *key, size_t keySize) = 0;
};
