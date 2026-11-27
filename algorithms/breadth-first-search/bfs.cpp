#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <string>

using namespace std;

vector<int> breadthFirstSearch(
    const vector<vector<int> >& graph,
    int start
) {
    int n = (int)graph.size();

    if (start < 0 || start >= n) {
        throw invalid_argument("Invalid starting vertex");
    }

    vector<bool> visited(n, false);
    vector<int> traversal;
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        traversal.push_back(current);

        for (size_t i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];

            if (neighbor < 0 || neighbor >= n) {
                throw invalid_argument("Invalid neighbor vertex");
            }

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return traversal;
}

void runTest(
    const vector<vector<int> >& graph,
    int start,
    const vector<int>& expected,
    const string& name
) {
    vector<int> result = breadthFirstSearch(graph, start);

    if (result == expected) {
        cout << "[PASS] " << name << endl;
    } else {
        cout << "[FAIL] " << name << endl;

        cout << "Expected: ";
        for (size_t i = 0; i < expected.size(); i++) {
            cout << expected[i] << " ";
        }

        cout << "\nActual:   ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }

        cout << endl;
    }
}

int main() {
    vector<vector<int> > graph(6);

    graph[0].push_back(1);
    graph[0].push_back(2);

    graph[1].push_back(0);
    graph[1].push_back(3);
    graph[1].push_back(4);

    graph[2].push_back(0);
    graph[2].push_back(5);

    graph[3].push_back(1);
    graph[4].push_back(1);
    graph[5].push_back(2);

    vector<int> expected1;

    expected1.push_back(0);
    expected1.push_back(1);
    expected1.push_back(2);
    expected1.push_back(3);
    expected1.push_back(4);
    expected1.push_back(5);

    runTest(graph, 0, expected1, "Basic BFS");

    vector<int> expected2;

    expected2.push_back(3);
    expected2.push_back(1);
    expected2.push_back(0);
    expected2.push_back(4);
    expected2.push_back(2);
    expected2.push_back(5);

    runTest(graph, 3, expected2, "Different starting vertex");

    vector<vector<int> > disconnected(4);

    disconnected[0].push_back(1);
    disconnected[1].push_back(0);
    disconnected[2].push_back(3);
    disconnected[3].push_back(2);

    vector<int> expected3;

    expected3.push_back(0);
    expected3.push_back(1);

    runTest(disconnected, 0, expected3, "Disconnected graph");

    vector<vector<int> > isolated(1);

    vector<int> expected4;

    expected4.push_back(0);

    runTest(isolated, 0, expected4, "Isolated vertex");

    return 0;
}
