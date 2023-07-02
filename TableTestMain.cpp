#include "TableList.h"
#include "Table.h"
#include "Mem.h"
#include "TableTest.h"

int main()
{
        Mem mem(200000);
        Table table(mem);

        TableTest table_test(&table);

        unsigned int start, first, second, third, fourth, fifth;
        int amount = 0;

        start = clock();

        cout << "Test for insert:" << endl;

        table_test.insert_test(2000000);

        first = clock() - start;

        cout << "Inserting Time: " << (double)first / CLOCKS_PER_SEC << " s." << endl;

        cout << "Iterator test after insert:" << endl;

        if (!table_test.value_test())
            cout << "Elements inserted correctly!" << endl;

        second = clock() - first;

        cout << "Iterator Test Time(after insert): " << (double) second / CLOCKS_PER_SEC << " s." << endl;

        cout << "\nTest for remove:" << endl;

        table_test.remove_test(8000000);

        third = clock() - first;

        cout << "Removing Time: " << (double)third / CLOCKS_PER_SEC << " s." << endl;

        cout << "Iterator test after remove of even elements:" << endl;

        if (!table_test.value_test())
            cout << "Elements removed correctly!" << endl;

        fourth = clock() - first;

        cout << "Iterator Test Time(after remove): " << (double) fourth / CLOCKS_PER_SEC << " s." << endl;

        cout<<"\nFind test:"<<endl;

        if(!table_test.find_test())
            cout<<"OK! All elements were removed correctly!"<<endl;

        fifth = clock() - first;

        cout << "Find Test Time: " << (double) fifth / CLOCKS_PER_SEC << " s." << endl;

        table.clear();

        return 0;

}
/*
        amount = table_test.null_amount(amount);

        if(amount == 0)
        {
            cout << "Null lists = " << amount << endl;

            cout << "\nDistribution test:" << endl;
            table_test.distribution_test();

            second = clock() - first;

            cout << "\nDistributing Time: " << (double) second / CLOCKS_PER_SEC << " s." << endl << endl;
        }
*/