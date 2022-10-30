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

            arrayOfSuffix[--windowSize[vt1[vt2[k]]]] = vt2[k];
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
        for (h &&h--, d = arrayOfSuffix[sizing[k] - 1]; str[k + h] == str[d + h]; h++)
            ;
        hightestPrefix[sizing[k]] = h;
        k++;
    }
}
int longestSubstring(vector<int> &highestPrefix, string S, int k)
{
    int maximumValue;
    maximumValue = -1;
    int stringSize = S.size();
    int cmpValue = stringSize - k + 1;
    for (int i = 1; i <= cmpValue; i++)
    {
        int temp = stringSize + 1;
        for (int j = i + 1; j <= i + k - 1; j++)
        {
            temp = min(temp, highestPrefix[j]);
        }
        maximumValue = max(maximumValue, temp);
    }
    if (maximumValue > 0)
    {
        return maximumValue;
    }
    return -1;
}

int main()
{
    int k;
    string S;
    cin >> k;
    cin >> S;
    int stringSize = S.size();
    if (k == 1)
    {
        cout << stringSize;
        return 0;
    }
    vector<int> arrayOfSuffix(stringSize + 1);
    vector<int> highestPrefix(stringSize + 1);

    suffixArray(arrayOfSuffix, highestPrefix, S);
    cout << longestSubstring(highestPrefix, S, k) << " ";
    return 0;
}