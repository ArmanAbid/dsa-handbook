interface GraphEdge {
    destination: string;
    weight: number;
}

class Graph {
    private adjacencyList: Map<string, GraphEdge[]>;
    private directed: boolean;
    private edgeCount: number;

    // CREATE: Initialize a directed or undirected graph.
    // false = Undirected, true = Directed.
    constructor(directed: boolean = false) {
        this.adjacencyList = new Map<string, GraphEdge[]>();
        this.directed = directed;
        this.edgeCount = 0;
    }

    // Find an edge inside a vertex's adjacency list.
    private findEdgeIndex(from: string, to: string): number {
        const edges = this.adjacencyList.get(from);

        if (edges === undefined) {
            return -1;
        }

        for (let i = 0; i < edges.length; i++) {
            const edge = edges[i];

            if (edge !== undefined && edge.destination === to) {
                return i;
            }
        }

        return -1;
    }

    // Remove one directed connection from an adjacency list.
    private removeDirectedEdge(from: string, to: string): boolean {
        const edges = this.adjacencyList.get(from);

        if (edges === undefined) {
            return false;
        }

        const index = this.findEdgeIndex(from, to);

        if (index === -1) {
            return false;
        }

        edges.splice(index, 1);
        return true;
    }

    // ADD VERTEX: Add a vertex if it does not exist.
    addVertex(vertex: string): boolean {
        if (this.adjacencyList.has(vertex)) {
            return false;
        }

        this.adjacencyList.set(vertex, []);
        return true;
    }

    // ADD EDGE: Connect two vertices.
    // Missing vertices are created automatically.
    // Default weight is 1.
    addEdge(
        from: string,
        to: string,
        weight: number = 1
    ): boolean {
        this.addVertex(from);
        this.addVertex(to);

        const sourceEdges = this.adjacencyList.get(from);

        if (sourceEdges === undefined) {
            return false;
        }

        const existingIndex = this.findEdgeIndex(from, to);

        // Update an existing edge instead of adding a duplicate.
        if (existingIndex !== -1) {
            const existingEdge = sourceEdges[existingIndex];

            if (existingEdge !== undefined) {
                existingEdge.weight = weight;
            }

            if (!this.directed && from !== to) {
                const reverseEdges = this.adjacencyList.get(to);
                const reverseIndex = this.findEdgeIndex(to, from);

                if (
                    reverseEdges !== undefined &&
                    reverseIndex !== -1
                ) {
                    const reverseEdge = reverseEdges[reverseIndex];

                    if (reverseEdge !== undefined) {
                        reverseEdge.weight = weight;
                    }
                }
            }

            return false;
        }

        sourceEdges.push({
            destination: to,
            weight
        });

        // Store the reverse connection for an undirected graph.
        if (!this.directed && from !== to) {
            const destinationEdges = this.adjacencyList.get(to);

            if (destinationEdges !== undefined) {
                destinationEdges.push({
                    destination: from,
                    weight
                });
            }
        }

        this.edgeCount++;
        return true;
    }

    // REMOVE EDGE: Remove a connection.
    removeEdge(from: string, to: string): boolean {
        if (!this.removeDirectedEdge(from, to)) {
            return false;
        }

        // Remove the reverse connection in an undirected graph.
        if (!this.directed && from !== to) {
            this.removeDirectedEdge(to, from);
        }

        this.edgeCount--;
        return true;
    }

    // REMOVE VERTEX: Remove a vertex and all connected edges.
    removeVertex(vertex: string): boolean {
        const outgoingEdges = this.adjacencyList.get(vertex);

        if (outgoingEdges === undefined) {
            return false;
        }

        // Count outgoing edges, including a possible self-loop.
        let removedEdges = outgoingEdges.length;

        // Remove incoming references from other vertices.
        for (const [source, edges] of this.adjacencyList) {
            if (source === vertex) {
                continue;
            }

            for (let i = edges.length - 1; i >= 0; i--) {
                const edge = edges[i];

                if (
                    edge !== undefined &&
                    edge.destination === vertex
                ) {
                    if (this.directed) {
                        removedEdges++;
                    }

                    edges.splice(i, 1);
                }
            }
        }

        this.adjacencyList.delete(vertex);
        this.edgeCount -= removedEdges;

        return true;
    }

    // CHECK VERTEX: Check whether a vertex exists.
    hasVertex(vertex: string): boolean {
        return this.adjacencyList.has(vertex);
    }

    // CHECK EDGE: Check whether a connection exists.
    hasEdge(from: string, to: string): boolean {
        return this.findEdgeIndex(from, to) !== -1;
    }

    // GET NEIGHBORS: Return connected vertices and their weights.
    getNeighbors(vertex: string): GraphEdge[] {
        const edges = this.adjacencyList.get(vertex);

        if (edges === undefined) {
            return [];
        }

        // Return copies so callers cannot directly modify graph edges.
        return edges.map(edge => ({
            destination: edge.destination,
            weight: edge.weight
        }));
    }

    // GET VERTEX COUNT.
    vertexCount(): number {
        return this.adjacencyList.size;
    }

    // GET EDGE COUNT.
    // Undirected edges are counted once.
    getEdgeCount(): number {
        return this.edgeCount;
    }

    // CHECK: Check whether the graph is empty.
    isEmpty(): boolean {
        return this.adjacencyList.size === 0;
    }

    // DISPLAY: Show the adjacency list.
    printGraph(): void {
        console.log(
            "Graph:",
            this.directed ? "Directed" : "Undirected"
        );

        if (this.adjacencyList.size === 0) {
            console.log("Empty");
            return;
        }

        for (const [vertex, edges] of this.adjacencyList) {
            if (edges.length === 0) {
                console.log(`${vertex} -> (no edges)`);
                continue;
            }

            const connections = edges
                .map(edge => `${edge.destination}(${edge.weight})`)
                .join(", ");

            console.log(`${vertex} -> ${connections}`);
        }
    }

    // CLEAR: Remove all vertices and edges.
    clearGraph(): void {
        this.adjacencyList.clear();
        this.edgeCount = 0;
    }
}

// Helper function to display neighbors.
function printNeighbors(graph: Graph, vertex: string): void {
    const neighbors = graph.getNeighbors(vertex);

    console.log(`Neighbors of ${vertex}:`);

    if (neighbors.length === 0) {
        console.log("None");
        return;
    }

    console.log(
        neighbors
            .map(edge => `${edge.destination}(${edge.weight})`)
            .join(", ")
    );
}

// DEMONSTRATION

const graph = new Graph(false);

console.log("==== GRAPH ====");

// ADD VERTICES AND EDGES
console.log("\n--- ADD VERTICES AND EDGES ---");

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
console.log("\n--- SEARCH ---");

console.log("Has vertex A:", graph.hasVertex("A"));
console.log("Has vertex Z:", graph.hasVertex("Z"));

console.log("Has edge A-B:", graph.hasEdge("A", "B"));
console.log("Has edge A-D:", graph.hasEdge("A", "D"));

// GET NEIGHBORS
console.log("\n--- GET NEIGHBORS ---");

printNeighbors(graph, "A");
printNeighbors(graph, "F");

// UPDATE EDGE WEIGHT
console.log("\n--- UPDATE EDGE WEIGHT ---");

graph.addEdge("A", "B", 10);

console.log("Updated A-B weight to 10.");
printNeighbors(graph, "A");

// REMOVE EDGE
console.log("\n--- REMOVE EDGE ---");

console.log("Remove C-D:", graph.removeEdge("C", "D"));

graph.printGraph();

// REMOVE VERTEX
console.log("\n--- REMOVE VERTEX ---");

console.log("Remove E:", graph.removeVertex("E"));

graph.printGraph();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Vertices:", graph.vertexCount());
console.log("Edges:", graph.getEdgeCount());
console.log("Is empty:", graph.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

graph.clearGraph();

console.log("Vertices after clearing:", graph.vertexCount());
console.log("Edges after clearing:", graph.getEdgeCount());
console.log("Is empty:", graph.isEmpty());

graph.printGraph();

// DIRECTED GRAPH
console.log("\n==== DIRECTED GRAPH ====");

const directedGraph = new Graph(true);

directedGraph.addEdge("X", "Y", 10);
directedGraph.addEdge("Y", "Z", 20);

directedGraph.printGraph();

console.log("Has edge X-Y:", directedGraph.hasEdge("X", "Y"));
console.log("Has edge Y-X:", directedGraph.hasEdge("Y", "X"));