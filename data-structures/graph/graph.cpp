#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Edge {
    string destination;
    int weight;

    Edge(const string& dest, int w) {
        destination = dest;
        weight = w;
    }
};

class Graph {
private:
    map<string, vector<Edge> > adjacencyList;
    bool directed;
    int edgeCount;

    // Find an edge inside a vertex's adjacency list.
    int findEdgeIndex(
        const string& from,
        const string& to
    ) const {
        map<string, vector<Edge> >::const_iterator it =
            adjacencyList.find(from);

        if (it == adjacencyList.end()) {
            return -1;
        }

        const vector<Edge>& edges = it->second;

        for (unsigned int i = 0; i < edges.size(); i++) {
            if (edges[i].destination == to) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    // Remove one directed connection from an adjacency list.
    bool removeDirectedEdge(
        const string& from,
        const string& to
    ) {
        map<string, vector<Edge> >::iterator it =
            adjacencyList.find(from);

        if (it == adjacencyList.end()) {
            return false;
        }

        vector<Edge>& edges = it->second;
        int index = findEdgeIndex(from, to);

        if (index == -1) {
            return false;
        }

        edges.erase(edges.begin() + index);
        return true;
    }

public:
    // CREATE: Initialize a directed or undirected graph.
    // false = Undirected, true = Directed.
    Graph(bool isDirected = false) {
        directed = isDirected;
        edgeCount = 0;
    }

    // ADD VERTEX: Add a vertex if it does not exist.
    bool addVertex(const string& vertex) {
        if (adjacencyList.find(vertex) != adjacencyList.end()) {
            return false;
        }

        adjacencyList[vertex] = vector<Edge>();
        return true;
    }

    // ADD EDGE: Connect two vertices.
    // Missing vertices are created automatically.
    // Default weight is 1.
    bool addEdge(
        const string& from,
        const string& to,
        int weight = 1
    ) {
        addVertex(from);
        addVertex(to);

        int existingIndex = findEdgeIndex(from, to);

        // Update an existing edge instead of adding a duplicate.
        if (existingIndex != -1) {
            adjacencyList[from][existingIndex].weight = weight;

            if (!directed && from != to) {
                int reverseIndex = findEdgeIndex(to, from);

                if (reverseIndex != -1) {
                    adjacencyList[to][reverseIndex].weight = weight;
                }
            }

            return false;
        }

        adjacencyList[from].push_back(Edge(to, weight));

        // Store the reverse connection for an undirected graph.
        if (!directed && from != to) {
            adjacencyList[to].push_back(Edge(from, weight));
        }

        edgeCount++;
        return true;
    }

    // REMOVE EDGE: Remove a connection.
    bool removeEdge(
        const string& from,
        const string& to
    ) {
        if (!removeDirectedEdge(from, to)) {
            return false;
        }

        // Remove the reverse connection in an undirected graph.
        if (!directed && from != to) {
            removeDirectedEdge(to, from);
        }

        edgeCount--;
        return true;
    }

    // REMOVE VERTEX: Remove a vertex and all connected edges.
    bool removeVertex(const string& vertex) {
        map<string, vector<Edge> >::iterator target =
            adjacencyList.find(vertex);

        if (target == adjacencyList.end()) {
            return false;
        }

        // Count outgoing edges, including a possible self-loop.
        int removedEdges = static_cast<int>(target->second.size());

        // Remove incoming references from other vertices.
        for (
            map<string, vector<Edge> >::iterator it =
                adjacencyList.begin();
            it != adjacencyList.end();
            ++it
        ) {
            if (it->first == vertex) {
                continue;
            }

            vector<Edge>& edges = it->second;

            for (
                int i = static_cast<int>(edges.size()) - 1;
                i >= 0;
                i--
            ) {
                if (edges[i].destination == vertex) {
                    if (directed) {
                        removedEdges++;
                    }

                    edges.erase(edges.begin() + i);
                }
            }
        }

        adjacencyList.erase(target);
        edgeCount -= removedEdges;

        return true;
    }

    // CHECK VERTEX: Check whether a vertex exists.
    bool hasVertex(const string& vertex) const {
        return adjacencyList.find(vertex) != adjacencyList.end();
    }

    // CHECK EDGE: Check whether a connection exists.
    bool hasEdge(
        const string& from,
        const string& to
    ) const {
        return findEdgeIndex(from, to) != -1;
    }

    // GET NEIGHBORS: Return connected vertices and their weights.
    vector<Edge> getNeighbors(const string& vertex) const {
        map<string, vector<Edge> >::const_iterator it =
            adjacencyList.find(vertex);

        if (it == adjacencyList.end()) {
            return vector<Edge>();
        }

        return it->second;
    }

    // GET VERTEX COUNT.
    int vertexCount() const {
        return static_cast<int>(adjacencyList.size());
    }

    // GET EDGE COUNT.
    // Undirected edges are counted once.
    int getEdgeCount() const {
        return edgeCount;
    }

    // CHECK: Check whether the graph is empty.
    bool isEmpty() const {
        return adjacencyList.empty();
    }

    // DISPLAY: Show the adjacency list.
    void printGraph() const {
        cout << "Graph: "
             << (directed ? "Directed" : "Undirected")
             << endl;

        if (adjacencyList.empty()) {
            cout << "Empty" << endl;
            return;
        }

        for (
            map<string, vector<Edge> >::const_iterator it =
                adjacencyList.begin();
            it != adjacencyList.end();
            ++it
        ) {
            cout << it->first << " -> ";

            const vector<Edge>& edges = it->second;

            if (edges.empty()) {
                cout << "(no edges)";
            }

            for (unsigned int i = 0; i < edges.size(); i++) {
                cout << edges[i].destination
                     << "(" << edges[i].weight << ")";

                if (i < edges.size() - 1) {
                    cout << ", ";
                }
            }

            cout << endl;
        }
    }

    // CLEAR: Remove all vertices and edges.
    void clearGraph() {
        adjacencyList.clear();
        edgeCount = 0;
    }
};

// Helper function to display neighbors.
void printNeighbors(
    const Graph& graph,
    const string& vertex
) {
    vector<Edge> neighbors = graph.getNeighbors(vertex);

    cout << "Neighbors of " << vertex << ": ";

    if (neighbors.empty()) {
        cout << "None";
    }

    for (unsigned int i = 0; i < neighbors.size(); i++) {
        cout << neighbors[i].destination
             << "(" << neighbors[i].weight << ")";

        if (i < neighbors.size() - 1) {
            cout << ", ";
        }
    }

    cout << endl;
}

// DEMONSTRATION

int main() {
    Graph graph(false);

    cout << "==== GRAPH ====" << endl;

    // ADD VERTICES AND EDGES
    cout << "\n--- ADD VERTICES AND EDGES ---" << endl;

    graph.addVertex("A");
    graph.addVertex("F");

    graph.addEdge("A", "B", 5);
    graph.addEdge("A", "C", 3);
    graph.addEdge("B", "D", 2);
    graph.addEdge("C", "D", 4);

    // Default weight is 1.
    graph.addEdge("D", "E");

    graph.printGraph();

    // SEARCH
    cout << "\n--- SEARCH ---" << endl;

    cout << "Has vertex A: "
         << (graph.hasVertex("A") ? "Yes" : "No") << endl;

    cout << "Has vertex Z: "
         << (graph.hasVertex("Z") ? "Yes" : "No") << endl;

    cout << "Has edge A-B: "
         << (graph.hasEdge("A", "B") ? "Yes" : "No") << endl;

    cout << "Has edge A-D: "
         << (graph.hasEdge("A", "D") ? "Yes" : "No") << endl;

    // GET NEIGHBORS
    cout << "\n--- GET NEIGHBORS ---" << endl;

    printNeighbors(graph, "A");
    printNeighbors(graph, "F");

    // UPDATE EDGE WEIGHT
    cout << "\n--- UPDATE EDGE WEIGHT ---" << endl;

    graph.addEdge("A", "B", 10);

    cout << "Updated A-B weight to 10." << endl;
    printNeighbors(graph, "A");

    // REMOVE EDGE
    cout << "\n--- REMOVE EDGE ---" << endl;

    cout << "Remove C-D: "
         << (graph.removeEdge("C", "D") ? "Removed" : "Not found")
         << endl;

    graph.printGraph();

    // REMOVE VERTEX
    cout << "\n--- REMOVE VERTEX ---" << endl;

    cout << "Remove E: "
         << (graph.removeVertex("E") ? "Removed" : "Not found")
         << endl;

    graph.printGraph();

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Vertices: " << graph.vertexCount() << endl;
    cout << "Edges: " << graph.getEdgeCount() << endl;
    cout << "Is empty: " << (graph.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    graph.clearGraph();

    cout << "Vertices after clearing: " << graph.vertexCount() << endl;
    cout << "Edges after clearing: " << graph.getEdgeCount() << endl;
    cout << "Is empty: " << (graph.isEmpty() ? "Yes" : "No") << endl;

    graph.printGraph();

    // DIRECTED GRAPH
    cout << "\n==== DIRECTED GRAPH ====" << endl;

    Graph directedGraph(true);

    directedGraph.addEdge("X", "Y", 10);
    directedGraph.addEdge("Y", "Z", 20);

    directedGraph.printGraph();

    cout << "Has edge X-Y: "
         << (directedGraph.hasEdge("X", "Y") ? "Yes" : "No") << endl;

    cout << "Has edge Y-X: "
         << (directedGraph.hasEdge("Y", "X") ? "Yes" : "No") << endl;

    return 0;
}