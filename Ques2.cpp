#include <iostream>
using namespace std;

class UnorderedMap
{
public:
    class pair
    {
    public:
        int value;
        int key;
        pair *next;
        // Constructor
        pair(int k, int val)
        {
            key = k;
            value = val;
            next = NULL;
        }
    };
    pair *valArray[100000];
    int checkPresent(int k)
    {
     string s=   
    }
    void insert(int k, int value)
    {
        auto idx = checkPresent(k);
        if (valArray[idx] == NULL)
        {
        }
    }
};

int main()
{
    int Query;
    // No of queries to be executed
    cin >> Query;
    for (int i = 0; i < Query; i++)
    {
        int op;
        // Type of operation
        // 1-> Insert
        // 2-> Erase
        // 3-> Find
        // 4-> map
        cin >> op;
        int key, value;
        if (op == 1)
        {
            cin >> key >> value;
            insert(key, value);
            // insertion
        }
        else if (op == 2)
        {

            // erase
        }
        else if (op == 3)
        {
            // find
        }
        else if (op == 4)
        {

            // value associated with key
        }
    }
}