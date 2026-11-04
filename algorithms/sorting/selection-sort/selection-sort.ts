// SELECTION SORT
// Sorts the array in ascending order.
// Finds the minimum element in the unsorted portion
// and places it at the beginning of that portion.

function selectionSort(values: number[]): void {
    const n = values.length;

    for (let i = 0; i < n - 1; i++) {
        // Assume the current position contains the minimum.
        let minIndex = i;

        // Find the actual minimum in the remaining portion.
        for (let j = i + 1; j < n; j++) {
            const current = values[j];
            const minimum = values[minIndex];

            if (
                current !== undefined &&
                minimum !== undefined &&
                current < minimum
            ) {
                minIndex = j;
            }
        }

        // Swap only when the minimum is not already in place.
        if (minIndex !== i) {
            const current = values[i];
            const minimum = values[minIndex];

            if (current !== undefined && minimum !== undefined) {
                values[i] = minimum;
                values[minIndex] = current;
            }
        }
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

    selectionSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// DEMONSTRATION

console.log("==== SELECTION SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [5, 3, 8, 4, 2];

console.log("Before sorting:", printArray(values));

selectionSort(values);

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