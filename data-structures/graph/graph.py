from typing import Dict, List, Tuple

class _Edge:
    def __init__(self, destination: str, weight: int):
        self.destination = destination
        self.weight = weight


class Graph:
    def __init__(self, directed: bool = False):
        self._adjacency: Dict[str, List[_Edge]] = {}
        self._directed = directed
        self._edge_count = 0

    # Find an edge inside a vertex's adjacency list.
    def _find_edge_index(self, source: str, destination: str) -> int:
        edges = self._adjacency.get(source)

        if edges is None:
            return -1

        for index, edge in enumerate(edges):
            if edge.destination == destination:
                return index

        return -1

    # Remove one directed connection from an adjacency list.
    def _remove_directed_edge(
        self,
        source: str,
        destination: str
    ) -> bool:
        edges = self._adjacency.get(source)

        if edges is None:
            return False

        index = self._find_edge_index(source, destination)

        if index == -1:
            return False

        edges.pop(index)
        return True

    # ADD VERTEX: Add a vertex if it does not exist.
    def add_vertex(self, vertex: str) -> bool:
        if vertex in self._adjacency:
            return False

        self._adjacency[vertex] = []
        return True

    # ADD EDGE: Connect two vertices.
    # Missing vertices are created automatically.
    # Default weight is 1.
    def add_edge(
        self,
        source: str,
        destination: str,
        weight: int = 1
    ) -> bool:
        self.add_vertex(source)
        self.add_vertex(destination)

        existing_index = self._find_edge_index(source, destination)

        # Update an existing edge instead of adding a duplicate.
        if existing_index != -1:
            self._adjacency[source][existing_index].weight = weight

            if not self._directed and source != destination:
                reverse_index = self._find_edge_index(
                    destination,
                    source
                )

                if reverse_index != -1:
                    self._adjacency[destination][reverse_index].weight = weight

            return False

        self._adjacency[source].append(_Edge(destination, weight))

        # Store the reverse connection for an undirected graph.
        if not self._directed and source != destination:
            self._adjacency[destination].append(_Edge(source, weight))

        self._edge_count += 1
        return True

    # REMOVE EDGE: Remove a connection.
    def remove_edge(self, source: str, destination: str) -> bool:
        if not self._remove_directed_edge(source, destination):
            return False

        # Remove the reverse connection in an undirected graph.
        if not self._directed and source != destination:
            self._remove_directed_edge(destination, source)

        self._edge_count -= 1
        return True

    # REMOVE VERTEX: Remove a vertex and all connected edges.
    def remove_vertex(self, vertex: str) -> bool:
        if vertex not in self._adjacency:
            return False

        # Count outgoing edges, including a possible self-loop.
        removed_edges = len(self._adjacency[vertex])

        # Remove incoming references from other vertices.
        for source, edges in self._adjacency.items():
            if source == vertex:
                continue

            remaining_edges = [
                edge for edge in edges
                if edge.destination != vertex
            ]

            removed_incoming = len(edges) - len(remaining_edges)

            if self._directed:
                removed_edges += removed_incoming

            self._adjacency[source] = remaining_edges

        del self._adjacency[vertex]
        self._edge_count -= removed_edges

        return True

    # CHECK VERTEX: Check whether a vertex exists.
    def has_vertex(self, vertex: str) -> bool:
        return vertex in self._adjacency

    # CHECK EDGE: Check whether a connection exists.
    def has_edge(self, source: str, destination: str) -> bool:
        return self._find_edge_index(source, destination) != -1

    # GET NEIGHBORS: Return connected vertices and their weights.
    def get_neighbors(self, vertex: str) -> List[Tuple[str, int]]:
        edges = self._adjacency.get(vertex)

        if edges is None:
            return []

        return [
            (edge.destination, edge.weight)
            for edge in edges
        ]

    # GET VERTEX COUNT.
    def vertex_count(self) -> int:
        return len(self._adjacency)

    # GET EDGE COUNT.
    # Undirected edges are counted once.
    def edge_count(self) -> int:
        return self._edge_count

    # CHECK: Check whether the graph is empty.
    def is_empty(self) -> bool:
        return len(self._adjacency) == 0

    # DISPLAY: Show the adjacency list.
    def print_graph(self) -> None:
        graph_type = "Directed" if self._directed else "Undirected"

        print(f"Graph: {graph_type}")

        if not self._adjacency:
            print("Empty")
            return

        for vertex, edges in self._adjacency.items():
            if not edges:
                print(f"{vertex} -> (no edges)")
                continue

            connections = ", ".join(
                f"{edge.destination}({edge.weight})"
                for edge in edges
            )

            print(f"{vertex} -> {connections}")

    # CLEAR: Remove all vertices and edges.
    def clear(self) -> None:
        self._adjacency.clear()
        self._edge_count = 0


# Helper function to display neighbors.
def print_neighbors(graph: Graph, vertex: str) -> None:
    neighbors = graph.get_neighbors(vertex)

    print(f"Neighbors of {vertex}:", end=" ")

    if not neighbors:
        print("None")
        return

    print(", ".join(
        f"{destination}({weight})"
        for destination, weight in neighbors
    ))


# DEMONSTRATION

graph = Graph(directed=False)

print("==== GRAPH ====")

# ADD VERTICES AND EDGES
print("\n--- ADD VERTICES AND EDGES ---")

graph.add_vertex("A")
graph.add_vertex("F")

graph.add_edge("A", "B", 5)
graph.add_edge("A", "C", 3)
graph.add_edge("B", "D", 2)
graph.add_edge("C", "D", 4)

# Default weight is 1.
graph.add_edge("D", "E")

graph.print_graph()

# SEARCH
print("\n--- SEARCH ---")

print("Has vertex A:", graph.has_vertex("A"))
print("Has vertex Z:", graph.has_vertex("Z"))

print("Has edge A-B:", graph.has_edge("A", "B"))
print("Has edge A-D:", graph.has_edge("A", "D"))

# GET NEIGHBORS
print("\n--- GET NEIGHBORS ---")

print_neighbors(graph, "A")
print_neighbors(graph, "F")

# UPDATE EDGE WEIGHT
print("\n--- UPDATE EDGE WEIGHT ---")

graph.add_edge("A", "B", 10)

print("Updated A-B weight to 10.")
print_neighbors(graph, "A")

# REMOVE EDGE
print("\n--- REMOVE EDGE ---")

print("Remove C-D:", graph.remove_edge("C", "D"))

graph.print_graph()

# REMOVE VERTEX
print("\n--- REMOVE VERTEX ---")

print("Remove E:", graph.remove_vertex("E"))

graph.print_graph()

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Vertices:", graph.vertex_count())
print("Edges:", graph.edge_count())
print("Is empty:", graph.is_empty())

# CLEAR
print("\n--- CLEAR ---")

graph.clear()

print("Vertices after clearing:", graph.vertex_count())
print("Edges after clearing:", graph.edge_count())
print("Is empty:", graph.is_empty())

graph.print_graph()

# DIRECTED GRAPH
print("\n==== DIRECTED GRAPH ====")

directed_graph = Graph(directed=True)

directed_graph.add_edge("X", "Y", 10)
directed_graph.add_edge("Y", "Z", 20)

directed_graph.print_graph()

print("Has edge X-Y:", directed_graph.has_edge("X", "Y"))
print("Has edge Y-X:", directed_graph.has_edge("Y", "X"))