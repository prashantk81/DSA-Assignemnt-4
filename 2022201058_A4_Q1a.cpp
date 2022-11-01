#include <iostream>
#include <vector>
using namespace std;
void suffixArray(vector<int> &arrayOfSuffix, vector<int> &hightestPrefix, string str)
{
    int x, i = 0;
    x = (int)(str).size();
    x = x + 1;
    while (i < x)
    {
        arrayOfSuffix[i] = i;
        i++;
    }
    int maxLimit = 256;
    int h;
    int a, b;
    // cout << x;
    h = 0;
    vector<int> vt1(begin(str), end(str) + 1);
    vector<int> vt2(x);
    vector<int> sizing(x);
    vector<int> windowSize(max(x, maxLimit));
    for (int j = 0, p = 0; p < x; j = max(1, j * 2), maxLimit = p)
    {
        p = j;
        int i = 0;
        while (i < x)
        {
            vt2[i] = x - j + i;
            i++;
        }
        i = 0;
        while (i < x)
        {
            if (arrayOfSuffix[i] >= j)
            {
                vt2[p] = arrayOfSuffix[i] - j;
                p = p + 1;
            }
            i++;
        }
        i = 0;
        while (i < windowSize.size())
        {
            windowSize[i] = 0;
            i++;
        }
        for (int k = 0; k < x; k++)
        {
            windowSize[vt1[k]] = windowSize[vt1[k]] + 1;
        }
        for (int k = 1; k < maxLimit; k++)
        {
            windowSize[k] += windowSize[k - 1];
        }
        int k = x;
        while (k--)
        {
            // find array of suffix
            arrayOfSuffix[--windowSize[vt1[vt2[k]]]] = vt2[k];
            // updating values;
        }
        swap(vt1, vt2);
        p = 1;
        vt1[arrayOfSuffix[0]] = 0;
        for (int k = 1; k < x; k++)
        {
            if (vt2[arrayOfSuffix[k - 1]] == vt2[arrayOfSuffix[k]] && vt2[arrayOfSuffix[k - 1] + j] == vt2[arrayOfSuffix[k] + j])
            {
                vt1[arrayOfSuffix[k]] = p - 1;
            }
            else
            {
                vt1[arrayOfSuffix[k]] = p;
                p = p + 1;
            }
        }
    }
    for (int k = 1; k < x; k++)
    {
        sizing[arrayOfSuffix[k]] = k;
    }
    int k = 0;
    int d;
    while (k < x - 1)
    {
        // calculating value of highestprefix;
        for (h &&h--, d = arrayOfSuffix[sizing[k] - 1]; str[k + h] == str[d + h]; h++)
            ;
        hightestPrefix[sizing[k]] = h;
        // calculating value of longest prefix
        k++;
    }
}
int main()
{
    string S;
    cin >> S;
    string combineString;
    combineString = S + S;
    int stringSize = combineString.size();
    vector<int> arrayOfSuffix(stringSize + 1);
    vector<int> highestPrefix(stringSize + 1);

    suffixArray(arrayOfSuffix, highestPrefix, combineString);
    for (int i = 0; i < arrayOfSuffix.size(); i++)
    {
        cout << arrayOfSuffix[i] << " ";
    }
    int i = 0;
    int pos;
    while (i < stringSize)
    {
        if (arrayOfSuffix[i] < S.size())
        {
            pos = arrayOfSuffix[i];
            break;
        }
        i++;
    }
    cout << combineString.substr(pos, S.size());
    return 0;
}