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
        for (int i = 0; i <= n; i++)
        {
            Parent[i] = i;
            SizeOfParties[i] = 1;
        }
    }

    int FindParent(int a)
    {
        if (a == Parent[a])
        {
            return a;
        }
        else
        {
            return Parent[a] = FindParent(Parent[a]);
        }
    }
    void findParties(int a, int b)
    {
        int ParentOfa = FindParent(a);
        int ParentOfb = FindParent(b);
        if (ParentOfa == ParentOfb)
        {
            return;
        }
        else
        {
            if (SizeOfParties[a] < SizeOfParties[b])
            {
                Parent[a] = b;
                SizeOfParties[ParentOfb] += SizeOfParties[ParentOfa];
                MaxSize = max(MaxSize, SizeOfParties[ParentOfb]);
            }
            else
            {
                Parent[b] = a;
                SizeOfParties[ParentOfa] += SizeOfParties[ParentOfb];
                MaxSize = max(MaxSize, SizeOfParties[ParentOfa]);
            }
            TotalParties -= 1;
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
