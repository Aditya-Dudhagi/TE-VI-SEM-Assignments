#include <bits/stdc++.h>
using namespace std;

// 1) Food Delivery Order Scheduling (Job Sequencing)

struct Job {
    int profit;
    int deadline;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling(vector<int> &profit, vector<int> &deadline) {

    int n = profit.size();
    vector<Job> jobs(n);

    for (int i = 0; i < n; i++) {
        jobs[i] = {profit[i], deadline[i]};
    }

    sort(jobs.begin(), jobs.end(), cmp);

    int maxDeadline = 0;
    for (auto job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    vector<int> slot(maxDeadline + 1, -1);

    int totalProfit = 0, countJobs = 0;

    for (int i = 0; i < n; i++) {

        for (int j = jobs[i].deadline; j > 0; j--) {

            if (slot[j] == -1) {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                countJobs++;
                break;
            }
        }
    }

    cout << "========== Food Delivery Scheduling ==========\n";
    cout << "Orders Completed: " << countJobs << endl;
    cout << "Total Profit: " << totalProfit << endl;
}


// 2) Railway Track Layout (Prim's Algorithm - MST)

void railwayTrackLayoutPlanning(vector<vector<int>> &graph) {

    int n = graph.size();

    vector<int> key(n, INT_MAX);
    vector<bool> mst(n, false);
    vector<int> parent(n, -1);

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {

        int mini = INT_MAX, u = -1;

        for (int i = 0; i < n; i++) {
            if (!mst[i] && key[i] < mini) {
                mini = key[i];
                u = i;
            }
        }

        mst[u] = true;

        for (int v = 0; v < n; v++) {

            if (graph[u][v] != 0 && !mst[v] &&
                graph[u][v] < key[v]) {

                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int totalCost = 0;

    cout << "\n========== Railway Track Layout (MST) ==========\n";

    for (int i = 1; i < n; i++) {

        cout << parent[i] << " - " << i
             << "  Cost: " << graph[i][parent[i]] << endl;

        totalCost += graph[i][parent[i]];
    }

    cout << "Total Track Length: " << totalCost << endl;
}


// 3) Student Ranking System (Selection Sort)

struct Student {
    string name;
    int marks;
};

void selectionSortStudents(vector<Student> &arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (arr[j].marks > arr[maxIndex]) {
                maxIndex = j;
            }
        }

        swap(arr[i], arr[maxIndex]);
    }
}

void studentRankingSystem() {

    vector<Student> students = {
        {"Amit", 78},
        {"Rahul", 92},
        {"Sneha", 65},
        {"Priya", 85}
    };

    selectionSortStudents(students);

    cout << "\n========== Student Ranking System ==========\n";

    for (int i = 0; i < students.size(); i++) {

        cout << "Rank " << i + 1 << " : "
             << students[i].name << " ("
             << students[i].marks << " marks)\n";
    }
}


// 4) Emergency Vehicle Routing (Dijkstra Algorithm)

#define INF 1e9

void dijkstra(int src,
              vector<vector<pair<int, int>>> &graph,
              int n) {

    vector<int> dist(n, INF);
    dist[src] = 0;

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    pq.push({0, src});

    while (!pq.empty()) {

        int currDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currDist > dist[node])
            continue;

        for (auto edge : graph[node]) {

            int nextNode = edge.first;
            int weight = edge.second;

            if (dist[node] + weight < dist[nextNode]) {

                dist[nextNode] = dist[node] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    cout << "\n========== Emergency Route (Dijkstra) ==========\n";

    for (int i = 0; i < n; i++) {

        cout << "Location " << i
             << " : " << dist[i]
             << " minutes\n";
    }
}


// MAIN FUNCTION

int main() {

    // 1) Food Delivery Scheduling
    vector<int> profit = {100, 19, 27, 25, 15};
    vector<int> deadline = {2, 1, 2, 1, 3};

    jobScheduling(profit, deadline);


    // 2) Railway Planning (Prim's)
    vector<vector<int>> railwayGraph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    railwayTrackLayoutPlanning(railwayGraph);


    // 3) Student Ranking
    studentRankingSystem();


    // 4) Emergency Routing (Dijkstra)
    int n = 5;

    vector<vector<pair<int, int>>> roadGraph(n);

    // Roads (u, v, time)
    roadGraph[0].push_back({1, 5});
    roadGraph[0].push_back({2, 10});

    roadGraph[1].push_back({2, 3});
    roadGraph[1].push_back({3, 7});

    roadGraph[2].push_back({3, 2});
    roadGraph[3].push_back({4, 4});

    int source = 0;  // Emergency Station

    dijkstra(source, roadGraph, n);

    return 0;
}