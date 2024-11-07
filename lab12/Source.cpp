#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

#define NOMINMAX
#include <Windows.h>

using namespace std;

const unsigned int INF = numeric_limits<unsigned int>::max();

vector<vector<unsigned int>> distances;
vector<vector<pair<int, int>>> adjList;
vector<vector<int>> parent;

bool read(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "�� ������� ������� ����." << endl;
        return false;
    }

    unsigned int N, M;
    file >> N >> M;
    if (N <= 0 || M <= 0) {
        cerr << "����������� ��������� �����. �������� ������� ������ �� �����." << endl;
        return false;
    }

    distances.assign(N, vector<unsigned int>(N, INF));
    parent.assign(N, vector<int>(N, -1));

    adjList.assign(N, vector<pair<int, int>>());

    for (size_t i = 0; i < N; i++) {
        distances[i][i] = 0;
    }

    for (size_t i = 0; i < M; i++) {
        unsigned int v, u, w;
        if (!(file >> v >> u >> w)) {
            cerr << "����� ����� ����������� ��������." << endl;
            return false;
        }
        if (u < 1 || u > N) {
            cerr << "���������� ������� ����� " << (i + 1) << "." << endl;
            return false;
        }
        distances[v - 1][u - 1] = w;
        parent[v - 1][u - 1] = v - 1;
        adjList[v - 1].push_back({ u - 1, w });
    }

    return true;
}

void printShortestPath(int from, int to) {
    vector<int> path;
    for (int v = to; v != -1; v = parent[from][v]) {
        path.push_back(v);
    }

    if (path.back() != from) {
        cout << "���� �� ��������� " << from + 1 << " �� " << to + 1 << " �� ����." << endl;
        return;
    }

    cout << "����: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << (path[i] + 1);
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

void djikstra(int start) {
    unsigned int n = adjList.size();
    vector<unsigned int> dist(n, INF);
    dist[start] = 0;

    vector<bool> visited(n, false);
    visited[start] = true;

    priority_queue<pair<unsigned int, int>, vector<pair<unsigned int, int>>, greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        unsigned int u = pq.top().second;
        unsigned int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adjList[u]) {
            unsigned int v = edge.first;
            unsigned int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[start][v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        distances[start][i] = dist[i];
    }
}

void print() {
    cout << "������� ��������:" << endl;
    unsigned int n = adjList.size();
    for (unsigned int i = 0; i < n; i++) {
        cout << "������� " << i + 1 << ": ";
        for (unsigned int j = 0; j < n; j++) {
            if (distances[i][j] == INF) {
                cout << setw(10) << "INF";
            }
            else {
                cout << setw(10) << distances[i][j];
            }
        }
        cout << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string path;
    cout << "������ ���� �� ����� � ������ �����: ";
    getline(cin, path);

    if (!read(path)) {
        return 1;
    }

    for (unsigned int i = 0; i < adjList.size(); i++) {
        djikstra(i);
    }

    print();

    unsigned int u, v;
    cout << "������ ��������� ������� ��� ������ �����: ";
    cin >> u;
    cout << "������ ������ ������� ��� ������ �����: ";
    cin >> v;

    if (u < 1 || u > adjList.size() || v < 1 || v > adjList.size()) {
        cout << "����� ������� ��� ������ �����." << endl;
        return 3;
    }

    printShortestPath(u - 1, v - 1);

    unsigned int newStart;
    cout << "������ ���� ��������� ������� ��� ������ ����������� ������ �� ��� �����: ";
    cin >> newStart;

    if (newStart < 1 || newStart > adjList.size()) {
        cout << "������ �������!" << endl;
        return 4;
    }

    djikstra(newStart - 1);

    cout << "���������� ����� �� ������� " << newStart << " �� ��� ����� ������:" << endl;
    for (unsigned int i = 0; i < adjList.size(); i++) {
        if (distances[newStart - 1][i] == INF) {
            cout << "������� " << i + 1 << ": ��������� ��������" << endl;
        }
        else {
            cout << "������� " << i + 1 << ": ������� = " << distances[newStart - 1][i] << endl;
        }
    }

    return 0;
}