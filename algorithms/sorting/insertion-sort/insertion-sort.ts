// INSERTION SORT
// Sorts the array in ascending order.
// Builds a sorted portion by inserting each new element
// into its correct position.

function insertionSort(values: number[]): void {
    const n = values.length;

    for (let i = 1; i < n; i++) {
        // Store the current element.
        const key = values[i];

        if (key === undefined) {
            continue;
        }

        // Start comparing with the element immediately to the left.
        let j = i;

        // Shift elements greater than key one position to the right.
        while (j > 0) {
            const previous = values[j - 1];

            if (previous === undefined || previous <= key) {
                break;
            }

            values[j] = previous;
            j--;
        }

        // Insert key into its correct position.
        values[j] = key;
    }
}


// Helper function for demonstration.
function printArray(values: readonly number[]): string {
    return `[${values.join(", ")}]`;
}


// Test a sorting case.
function testSort(
    input: readonly number[],
    expected: readonly number[],
    description: string
): void {
    const values = [...input];

    insertionSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// DEMONSTRATION

console.log("==== INSERTION SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [5, 3, 8, 4, 2];

console.log("Before sorting:", printArray(values));

insertionSort(values);

console.log("After sorting: ", printArray(values));

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSort([], [], "Empty array");

testSort([42], [42], "Single element");

testSort(
    [1, 2, 3, 4, 5],
    [1, 2, 3, 4, 5],
    "Already sorted"
);

testSort(
    [5, 4, 3, 2, 1],
    [1, 2, 3, 4, 5],
    "Reverse sorted"
);

testSort(
    [4, 2, 4, 1, 2],
    [1, 2, 2, 4, 4],
    "Duplicate values"
);

testSort(
    [7, 7, 7, 7],
    [7, 7, 7, 7],
    "All elements equal"
);

testSort(
    [-5, 3, -10, 0, 8],
    [-10, -5, 0, 3, 8],
    "Negative and positive values"
);

testSort(
    [1, 2, 4, 3, 5],
    [1, 2, 3, 4, 5],
    "Nearly sorted"
);