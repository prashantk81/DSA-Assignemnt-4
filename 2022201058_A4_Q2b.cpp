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
    int totalSize = 0;
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
            totalSize++;
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
                totalSize++;
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
            totalSize--;
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
            totalSize--;
            previousNode->next = currentIndex->next;
            free(currentIndex);
        }
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
};

int main()
{
    unordered_map<int, int> mp;
    int N, K;
    cin >> N >> K;
    int arr[N];
    int i;
    for (i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    i = 0;
    for (i = 0; i < K; i++)
    {
        mp.insert(arr[i], i);
    }

    cout << mp.totalSize << " ";
    int j = 0;
    while (i < N)
    {
        if (mp.find(arr[j]))
        {
            if (mp.map(arr[j]) == j)
            {
                mp.erase(arr[j]);
            }
        }
        j++;
        mp.insert(arr[i], i);
        i++;
        cout << mp.totalSize << " ";
    }
}
