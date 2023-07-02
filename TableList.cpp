#include "TableList.h"


GroupList::Iterator* TableList::find(void *elem, size_t size)
{
	auto* iter = dynamic_cast<GroupListIterator *>(newIterator());
	size_t trash = 0;


    if(iter == nullptr)
        return nullptr;

    while (iter -> current != nullptr)
	{
		ArrayCell tmp = *(ArrayCell*)(iter -> getElement(trash));

		if (tmp.key_size == size)
			if (memcmp(tmp.key, elem, size) == 0)
				break;

		iter -> goToNext();
	}

	if (iter -> current == nullptr)
		return nullptr;

	return iter;
}