#include <iostream>
#include <vector>
using namespace std;

class priorityQueue
{
public:
    vector<vector<int>> minHeap;
    int heapSize;
    priorityQueue()
    {
        heapSize = 0;
    }
    void heapify(int index)
    {
        int leftNode, rightNode, smallest;
        leftNode = 2 * index + 1;
        rightNode = leftNode + 1;
        smallest = index;
        if (true && leftNode < heapSize && minHeap[leftNode][0] < minHeap[smallest][0])
        {
            smallest = leftNode;
        }
        if (true && rightNode < heapSize && minHeap[rightNode][0] < minHeap[smallest][0])
        {
            smallest = rightNode;
        }
        if (smallest == index)
        {
        }
        else
        {
            int distance, parentNode;
            distance = minHeap[smallest][0];
            parentNode = minHeap[smallest][1];
            minHeap[smallest][0] = minHeap[index][0];
            minHeap[smallest][1] = minHeap[index][1];
            minHeap[index][0] = distance;
            minHeap[index][1] = parentNode;
            heapify(smallest);
        }
    }
    void deleteRoot()
    {
        if (heapSize == 0)
        {
            return;
        }
        else
        {
            minHeap[0] = minHeap[heapSize - 1];
            heapSize -= 1;
            minHeap.pop_back();
            heapify(0);
        }
    }
    void insertion(vector<int> node)
    {
        if (heapSize == 0)
        {
            minHeap.push_back(node);
            heapSize += 1;
        }
        else
        {
            minHeap.push_back(node);
            heapSize += 1;
            int i = heapSize / 2 - 1;
            while (i >= 0)
            {
                heapify(i);
                i--;
            }
        }
    }
};

void findShortestPath(vector<vector<int>> arrOfWeights[], vector<int> &stations, vector<int> &nearestDis, int N)
{

    priorityQueue *myHeap = new priorityQueue();

    int i = 0;
    for (i = 0; i < stations.size(); i++)
    {
        nearestDis[stations[i]] = 0;
    }
    vector<int> node;
    i = 0;
    for (i = 0; i < stations.size(); i++)
    {
        node.clear();
        node.push_back(0);
        node.push_back(stations[i]);
        myHeap->insertion(node);
    }
    while (myHeap->heapSize != 0)
    {
        vector<int> minimumElement = myHeap->minHeap[0];
        myHeap->deleteRoot();
        int minDistance, parentNode;
        minDistance = minimumElement[0];
        parentNode = minimumElement[1];
        for (auto adjNode : arrOfWeights[parentNode])
        {
            int childNode, weight;
            childNode = adjNode[0];
            weight = adjNode[1];
            int value = minDistance + weight;
            if (value < nearestDis[childNode])
            {
                nearestDis[childNode] = value;
                node.clear();
                node.push_back(nearestDis[childNode]);
                node.push_back(childNode);
                myHeap->insertion(node);
            }
        }
    }
}

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    int u, v, w;
    int i = 0;
    vector<vector<int>> arrOfWeights[N + 1];
    for (i = 0; i < M; i++)
    {
        cin >> u >> v >> w;
        vector<int> vt1;
        vt1.push_back(v);
        vt1.push_back(w);
        arrOfWeights[u].push_back(vt1);
        vector<int> vt2;
        vt2.push_back(u);
        vt2.push_back(w);
        arrOfWeights[v].push_back(vt2);
    }
    vector<int> stations;
    i = 0;
    int policeSt;
    for (i = 0; i < K; i++)
    {
        cin >> policeSt;
        stations.push_back(policeSt);
    }
    i = 0;
    if (N == K)
    {
        for (i = 0; i < N; i++)
        {
            cout << 0 << " ";
        }
        return 0;
    }
    vector<int> nearestDis(N + 1, 1e9);
    findShortestPath(arrOfWeights, stations, nearestDis, N);
    i = 0;
    for (i = 0; i <= N; i++)
    {
        if (nearestDis[i] == 1e9)
        {
            nearestDis[i] = -1;
        }
    }
    i = 1;
    for (i = 1; i <= N; i++)
    {
        cout << nearestDis[i] << " ";
    }
    return 0;
}