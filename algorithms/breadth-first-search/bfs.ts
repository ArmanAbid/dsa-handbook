function breadthFirstSearch(
    graph: readonly (readonly number[])[],
    start: number
): number[] {
    const n = graph.length;

    if (!Number.isInteger(start) || start < 0 || start >= n) {
        throw new RangeError("Invalid starting vertex");
    }

    const visited: boolean[] = new Array(n).fill(false);
    const traversal: number[] = [];
    const queue: number[] = [];

    let head = 0;

    visited[start] = true;
    queue.push(start);

    while (head < queue.length) {
        const current = queue[head];

        if (current === undefined) {
            break;
        }

        head++;
        traversal.push(current);

        const neighbors = graph[current];

        if (neighbors === undefined) {
            throw new RangeError("Invalid vertex");
        }

        for (const neighbor of neighbors) {
            if (
                !Number.isInteger(neighbor) ||
                neighbor < 0 ||
                neighbor >= n
            ) {
                throw new RangeError("Invalid neighbor vertex");
            }

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    return traversal;
}


function runTest(
    graph: readonly (readonly number[])[],
    start: number,
    expected: number[],
    name: string
): void {
    const result = breadthFirstSearch(graph, start);

    if (JSON.stringify(result) === JSON.stringify(expected)) {
        console.log(`[PASS] ${name}`);
    } else {
        console.log(
            `[FAIL] ${name}: expected ${expected}, got ${result}`
        );
    }
}


const graph: number[][] = [
    [1, 2],
    [0, 3, 4],
    [0, 5],
    [1],
    [1],
    [2]
];

runTest(
    graph,
    0,
    [0, 1, 2, 3, 4, 5],
    "Basic BFS"
);

runTest(
    graph,
    3,
    [3, 1, 0, 4, 2, 5],
    "Different starting vertex"
);

const disconnected: number[][] = [
    [1],
    [0],
    [3],
    [2]
];

runTest(
    disconnected,
    0,
    [0, 1],
    "Disconnected graph"
);

runTest(
    [[]],
    0,
    [0],
    "Isolated vertex"
);
