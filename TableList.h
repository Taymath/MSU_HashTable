#pragma once
#include "ListAbstract.h"
#include "Mem.h"

struct ArrayCell
{
	void* key = nullptr;
	size_t key_size;

	void* elem = nullptr;
	size_t elem_size;
};

class TableList : public GroupList
{
	public:

	    TableList(MemoryManager &mem): GroupList(mem) {}

        Iterator* find(void *elem, size_t size) override;
};