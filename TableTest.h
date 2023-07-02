#ifndef PRACTICUM_TABLETEST_H
#define PRACTICUM_TABLETEST_H

#include "Table.h"

class TableTest
{
private:
    Table *table;
public:

    TableTest(Table *table): table(table) {};

    void insert_test(int elements);

    void remove_test(int elements);

    int find_test();

    void distribution_test();

    int null_amount(int amount);

    int value_test();

};

#endif
