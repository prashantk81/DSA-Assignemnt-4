#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

vector<int> mediumSuffixArray(200010);
vector<int> alpha(200010);
vector<int> mediumLongestCommonPrefix(200010);
vector<int> longestPrefixArray(200010);
int cmpArray[200010];
void highestCommonPrefix(char arrOfChar[], vector<int> &vt2)
{
    int size = strlen(arrOfChar);
    alpha[vt2[0]] = -1;
    int i = 1;
    while (i < size)
    {
        alpha[vt2[i]] = vt2[i - 1];
        i += 1;
    }
    i = 0;
    int flag = 0;

    while (i < size)
    {
        if (alpha[i] == -1)
        {
            mediumLongestCommonPrefix[i] = 0;
            i++;
            continue;
        }
        while (arrOfChar[i + flag] == arrOfChar[alpha[i] + flag])
        {
            flag += 1;
        }
        mediumLongestCommonPrefix[i] = flag;
        flag = (flag - 1) > 0 ? flag - 1 : 0;
        i += 1;
    }
    i = 0;
    while (i < size)
    {
        longestPrefixArray[i] = mediumLongestCommonPrefix[vt2[i]];
        i += 1;
    }
}

void sortingTech(vector<int> &vt1, vector<int> &vt2, int k, int size)
{
    memset(cmpArray, 0, 200010 * sizeof(int));
    int i = 0;
    while (i < size)
    {
        if (i + k < size)
        {
            cmpArray[vt1[i + k]] += 1;
        }
        else
        {
            cmpArray[0] += 1;
        }
        i += 1;
    }

    int sum = 0;
    for (int i = 0; i < max(300, size); i++)
    {
        int temp = cmpArray[i];
        cmpArray[i] = sum;
        sum = sum + temp;
    }
    i = 0;
    while (i < size)
    {
        if (vt2[i] + k < size)
        {
            mediumSuffixArray[cmpArray[vt1[vt2[i] + k]]++] = vt2[i];
        }
        else
        {
            mediumSuffixArray[cmpArray[0]++] = vt2[i];
        }
        i += 1;
    }
    for (int i = 0; i < size; i++)
    {
        vt2[i] = mediumSuffixArray[i];
    }
}

vector<int> suffixArray(char arrOfchar[])
{
    vector<int> vt1(200010);
    vector<int> vt2(200010);
    vector<int> mediatesuffixArr(200010);
    int size = strlen(arrOfchar);
    int i = 0;
    while (i < size)
    {
        vt1[i] = arrOfchar[i];
        vt2[i] = i;
        i += 1;
    }
    int flag;
    for (int i = 1; i < size; i <<= 1)
    {
        sortingTech(vt1, vt2, i, size);
        sortingTech(vt1, vt2, 0, size);
        flag = 0;
        mediatesuffixArr[vt2[0]] = flag;
        int x = 1;
        while (x < size)
        {
            if (vt1[vt2[x]] == vt1[vt2[x - 1]] && vt1[vt2[x] + i] == vt1[vt2[x - 1] + i])
            {
                mediatesuffixArr[vt2[x]] = flag;
            }
            else
            {
                flag += 1;
                mediatesuffixArr[vt2[x]] = flag;
            }
            x++;
        }
        x = 0;
        while (x < size)
        {
            vt1[x] = mediatesuffixArr[x];
            x += 1;
        }
        if (vt1[vt2[size - 1]] == size - 1)
        {
            break;
        }
    }
    highestCommonPrefix(arrOfchar, vt2);
    return vt2;
}
int main()
{
    string S, reversedString;
    cin >> S;
    int size = S.length();
    reversedString = S;
    reverse(reversedString.begin(), reversedString.end());
    S += "$" + reversedString + "#";
    char arrOfchar[200010];
    char finalAns[200010];
    strcpy(arrOfchar, S.c_str());
    int nSize = strlen(arrOfchar);
    vector<int> suffixArr = suffixArray(arrOfchar);
    string inputs = arrOfchar;
    int maxLength = 0;
    int t = 0, i = 1, index = -1;
    string result = "";
    while (i < nSize)
    {
        int first = suffixArr[i];
        int second = suffixArr[i - 1];
        if ((first < size && second > size) || (first > size && second < size))
        {
            result = inputs.substr(suffixArr[i], longestPrefixArray[i]);
            int n = result.size();
            int status = 0;
            int k = 0;
            int nLength = n / 2;
            while (k < nLength)
            {
                if (result[k] == result[n - k - 1])
                {
                    status = 0;
                }
                else
                {
                    status = 1;
                }
                k += 1;
            }
            if (status == 0)
            {
                t = maxLength > longestPrefixArray[i] ? maxLength : longestPrefixArray[i];
                if (t != maxLength)
                {
                    maxLength = t;
                    index = suffixArr[i];
                }
            }
        }
        i += 1;
    }
    memset(finalAns, '\0', sizeof(finalAns));
    strncpy(finalAns, arrOfchar + index, maxLength);
    cout << finalAns << endl;
    return 0;
}