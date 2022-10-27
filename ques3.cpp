#include <iostream>
using namespace std;
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    int graph[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
    }
    int station[k];
    for (int i = 0; i < k; i++)
    {
        int val;
        cin >> val;
        station[i] = val;
    }

    for (int)
}