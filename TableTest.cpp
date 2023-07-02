#include "TableTest.h"
#include "Table.h"

int TableTest::find_test()
{
    Container::Iterator *table_iterator;

    int even = 0;

    for (int i = 0; i < table->elements_count; i ++)
    {
        table_iterator = dynamic_cast<Container::Iterator *>(table->findByKey(&i, sizeof(int)));

        if(table_iterator == nullptr && i % 2 == 0)
            even ++;
    }
    if(even >= (table->elements_count / 2) - 1 || even <= (table->elements_count / 2) + 1)
    {
        cout<<"OK, only even elements was deleted!"<<endl;
        return 0;
    }
}

void TableTest::insert_test(int el)
{
    for (int i = 0; i < el; i++)
        table->insertByKey(&i, sizeof(int), &i, sizeof(int));
}

void TableTest::remove_test(int el)
{
    for(int i = 0; i < el; i += 2)
        table->removeByKey(&i, sizeof(int));
}

void TableTest::distribution_test()
{
    int biggest = 0, smallest = 0, cell_less = 0, cell_more = 0;

    biggest = table->array_table[0] -> cells_count;
    smallest = table->array_table[0] -> cells_count;

    for(int i = 0; i < 200000; i ++)
    {
        if(table->array_table[i] -> cells_count >= biggest)
            biggest = table->array_table[i] -> cells_count;
        if(table->array_table[i] -> cells_count <= smallest)
            smallest = table->array_table[i] -> cells_count;
    }
    for(int i = 0; i < 200000; i ++)
    {
        if((table->array_table[i] -> cells_count >= smallest) && (table->array_table[i] -> cells_count < (smallest + biggest) / 2))
            cell_less += (table->array_table[i] -> cells_count);
        else if((table->array_table[i] -> cells_count >= (smallest + biggest) / 2) && (table->array_table[i] -> cells_count <= biggest))
            cell_more += (table->array_table[i] -> cells_count);
    }
    if(table->elements_count == cell_more + cell_less)
        cout << "1 part = " << cell_less << ", 2 part = " << cell_more << endl;
    else
        cout << "ERROR - Missed some elements";
}

int TableTest::null_amount(int amount)
{
    for(int i = 0; i < 200000; i ++)
    {
        if(table->array_table[i] == nullptr)
            amount ++;
    }

    return amount;
}

int TableTest::value_test()
{
    int c = 0;
    auto* list_iterator = dynamic_cast<Table::TableIterator *>(table->newIterator());
    Table::TableIterator* table_iterator;

    bool* counters = (bool*)malloc(table->elements_count * sizeof(bool));

    int check;

    void* value;
    size_t size;

    for(int i = 0; i < table->elements_count; i ++)
    {
        if(list_iterator->current != nullptr)
            value = list_iterator->getElement(size);
        else
        {
            counters[i] = true;
            list_iterator->goToNext();
            continue;
        }
        check = *(int*)value;

        if((int*)value == nullptr)
            counters[i] = false;
        else
            counters[i] = true;

        if (list_iterator->hasNext())
            list_iterator->goToNext();
        else
        {
            c++;
            if(c < table->c_size)
            {
                if(table->array_table[c] == NULL || table->array_table[c]->cells_count == 0)
                    while(table->array_table[c] == NULL || table->array_table[c]->cells_count == 0)
                        c++;

                table_iterator = new Table::TableIterator((table->array_table[c]->newIterator()), c);
                list_iterator = table_iterator;
            }
            else
                break;
        }
    }

    for(int i = 0; i < table->elements_count; i ++)
        if(!counters[i])
        {
            cout << "ERROR! Incorrect value or size of element!" << endl;
            return 1;
        }
    if(table_iterator != nullptr)
        delete table_iterator;

    delete counters;

    return 0;
}
