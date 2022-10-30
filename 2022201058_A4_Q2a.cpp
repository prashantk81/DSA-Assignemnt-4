#include <iostream>
#include <sstream>
#define maxSize 10000
using namespace std;
template <class X, class Y>
class unordered_map
{
    class pair
    {
    public:
        Y value;
        X key;
        pair *next;
        pair(X key, Y value)
        {
            this->key = key;
            this->value = value;
            next = 0;
        }
    };
    pair *keyValueArray[maxSize];

public:
    unordered_map()
    {
        int i = 0;
        while (i < maxSize)
        {
            keyValueArray[i] = 0;
            i++;
        }
    }
    string convertKeyToString(X key)
    {
        ostringstream temp;
        temp << key;
        return temp.str();
    }

    long long findArrayIndex(X key)
    {
        string keyString = convertKeyToString(key);
        long long finalCalvalue = keyString[0];
        long long i = 1;
        while (i < keyString.length())
        {
            finalCalvalue = finalCalvalue * 31 + keyString[i];
            i++;
        }
        return finalCalvalue % maxSize;
    }

    void insert(X key, Y value)
    {
        long long valueOfIndex = findArrayIndex(key);
        // if index is empty;
        pair *currentIndex = keyValueArray[valueOfIndex];
        bool isPresent = false;
        if (!currentIndex)
        {
            pair *insertedValue = new pair(key, value);
            keyValueArray[valueOfIndex] = insertedValue;
        }
        // IF index is not empty or key present
        else
        {
            while (currentIndex->next)
            {
                if (currentIndex->key == key)
                {
                    isPresent = true;
                    break;
                }
                else
                {
                    currentIndex = currentIndex->next;
                }
            }
            if (!isPresent && currentIndex->key != key)
            {
                pair *insertedValue = new pair(key, value);
                currentIndex->next = insertedValue;
            }
            else
            {
                currentIndex->value = value;
            }
        }
    }

    void erase(X key)
    {
        long long valueOfIndex = findArrayIndex(key);
        pair *currentIndex = keyValueArray[valueOfIndex];
        if (!currentIndex)
        {
            // cout << "Key is not present in map" << endl;
            return;
        }
        if (currentIndex->key == key)
        {
            keyValueArray[valueOfIndex] = currentIndex->next;
            free(currentIndex);
            return;
        }
        pair *previousNode;
        while (currentIndex->next && currentIndex->key != key)
        {
            previousNode = currentIndex;
            currentIndex = currentIndex->next;
        }
        if (!currentIndex->next && currentIndex->key != key)
        {
            // cout << "Key is not present in map" << endl;
            return;
        }
        else
        {
            previousNode->next = currentIndex->next;
            free(currentIndex);
        }
    }

    Y map(X key)
    {
        long long valueOfIndex = findArrayIndex(key);
        pair *currentIndex = keyValueArray[valueOfIndex];
        if (!currentIndex)
        {
            static Y defaultValue;
            return defaultValue;
        }
        while (currentIndex && currentIndex->key != key)
        {
            currentIndex = currentIndex->next;
        }
        if (!currentIndex)
        {
            static Y defaultValue;
            return defaultValue;
        }
        return currentIndex->value;
    }
    bool find(X key)
    {
        long long valueOfIndex = findArrayIndex(key);
        pair *currentIndex = keyValueArray[valueOfIndex];
        if (!currentIndex)
        {
            return false;
        }
        while (currentIndex && currentIndex->key != key)
        {
            currentIndex = currentIndex->next;
        }
        if (!currentIndex)
        {
            return false;
        }
        return true;
    }
};

int main()
{
    int Query;
    // No of queries to be executed
    cin >> Query;
    unordered_map<float, float> mp;
    for (int i = 0; i < Query; i++)
    {
        int op;
        // Type of operation
        // 1-> Insert
        // 2-> Erase
        // 3-> Find
        // 4-> map
        cin >> op;
        float key, value;
        if (op == 1)
        {
            cin >> key >> value;
            mp.insert(key, value);
        }
        else if (op == 2)
        {

            // erase
            cin >> key;
            mp.erase(key);
        }
        else if (op == 3)
        {
            // find
            cin >> key;
            cout << mp.find(key) << endl;
        }
        else if (op == 4)
        {
            // value associated with key
            cin >> key;
            cout << mp.map(key) << endl;
        }
        else
        {
            i--;
            cout << "Invalid Choice" << endl;
        }
    }
}
