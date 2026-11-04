// BUBBLE SORT
// Sorts the array in ascending order.
// Uses early exit when a pass makes no swaps.

function bubbleSort(values: number[]): void {
    const n = values.length;

    for (let i = 0; i < n - 1; i++) {
        let swapped = false;

        // The last i elements are already sorted.
        for (let j = 0; j < n - i - 1; j++) {
            const left = values[j];
            const right = values[j + 1];

            if (left === undefined || right === undefined) {
                continue;
            }

            if (left > right) {
                values[j] = right;
                values[j + 1] = left;

                swapped = true;
            }
        }

        // No swaps means the array is already sorted.
        if (!swapped) {
            break;
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

    bubbleSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// DEMONSTRATION

console.log("==== BUBBLE SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [5, 3, 8, 4, 2];

console.log("Before sorting:", printArray(values));

bubbleSort(values);

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