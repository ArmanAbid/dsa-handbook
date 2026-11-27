from collections import deque

def breadth_first_search(graph: list[list[int]], start: int) -> list[int]:
    n = len(graph)

    if start < 0 or start >= n:
        raise ValueError("Invalid starting vertex")

    visited = [False] * n
    traversal = []

    queue = deque([start])
    visited[start] = True

    while queue:
        current = queue.popleft()
        traversal.append(current)

        for neighbor in graph[current]:
            if not visited[neighbor]:
                visited[neighbor] = True
                queue.append(neighbor)

    return traversal


def run_test(graph, start, expected, name):
    result = breadth_first_search(graph, start)

    if result == expected:
        print(f"[PASS] {name}")
    else:
        print(f"[FAIL] {name}: expected {expected}, got {result}")


if __name__ == "__main__":
    graph = [
        [1, 2],
        [0, 3, 4],
        [0, 5],
        [1],
        [1],
        [2]
    ]

    run_test(
        graph,
        0,
        [0, 1, 2, 3, 4, 5],
        "Basic BFS"
    )

    run_test(
        graph,
        3,
        [3, 1, 0, 4, 2, 5],
        "Different starting vertex"
    )

    disconnected = [
        [1],
        [0],
        [3],
        [2]
    ]

    run_test(
        disconnected,
        0,
        [0, 1],
        "Disconnected graph"
    )

    run_test(
        [[]],
        0,
        [0],
        "Isolated vertex"
    )