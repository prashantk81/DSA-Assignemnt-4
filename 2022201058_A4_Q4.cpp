#include <iostream>
using namespace std;

class Election
{
public:
    int *SizeOfParties, *Parent;
    int MaxSize = 1;
    int TotalParties;
    Election(int n)
    {
        TotalParties = n;
        SizeOfParties = new int[n + 1];
        Parent = new int[n + 1];
        int i = 0;
        while (i <= n)
        {
            Parent[i] = i;
            SizeOfParties[i] = 1;
            i++;
        }
    }

    int FindParent(int a)
    {
        return a == Parent[a] ? a : Parent[a] = FindParent(Parent[a]);
    }
    void findParties(int a, int b)
    {
        int ParentOfa = FindParent(a);
        int ParentOfb = FindParent(b);
        if (ParentOfa != ParentOfb)
        {
            if (SizeOfParties[a] >= SizeOfParties[b])
            {
                Parent[b] = a;
                SizeOfParties[ParentOfa] += SizeOfParties[ParentOfb];
                if (MaxSize < SizeOfParties[ParentOfa])
                {
                    MaxSize = SizeOfParties[ParentOfa];
                }
            }
            else
            {

                Parent[a] = b;
                SizeOfParties[ParentOfb] += SizeOfParties[ParentOfa];
                if (MaxSize < SizeOfParties[ParentOfb])
                {
                    MaxSize = SizeOfParties[ParentOfb];
                }
            }
            TotalParties -= 1;
        }
        else
        {
            return;
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Election AG(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        AG.findParties(a, b);
        cout << AG.TotalParties << " " << AG.MaxSize << endl;
    }
}
