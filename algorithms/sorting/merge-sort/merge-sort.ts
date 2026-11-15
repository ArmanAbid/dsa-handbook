// MERGE
// Combines two sorted portions:
// [left, middle) and [middle, right).

function merge(
    values: number[],
    temp: number[],
    left: number,
    middle: number,
    right: number
): void {
    let i = left;
    let j = middle;
    let k = left;

    // Compare elements from both halves.
    while (i < middle && j < right) {
        const leftValue = values[i];
        const rightValue = values[j];

        if (leftValue === undefined || rightValue === undefined) {
            return;
        }

        // Select the left element first when values are equal.
        // This preserves stability.
        if (leftValue <= rightValue) {
            temp[k] = leftValue;
            i++;
        } else {
            temp[k] = rightValue;
            j++;
        }

        k++;
    }

    // Copy remaining elements from the left half.
    while (i < middle) {
        const value = values[i];

        if (value === undefined) {
            return;
        }

        temp[k] = value;

        i++;
        k++;
    }

    // Copy remaining elements from the right half.
    while (j < right) {
        const value = values[j];

        if (value === undefined) {
            return;
        }

        temp[k] = value;

        j++;
        k++;
    }

    // Copy the merged portion back into the original array.
    for (let index = left; index < right; index++) {
        const value = temp[index];

        if (value === undefined) {
            return;
        }

        values[index] = value;
    }
}


// MERGE SORT RECURSIVE HELPER
// Sorts the half-open range [left, right).

function mergeSortRange(
    values: number[],
    temp: number[],
    left: number,
    right: number
): void {
    // A range containing zero or one element is already sorted.
    if (right - left <= 1) {
        return;
    }

    // Divide the range into two halves.
    const middle = left + Math.floor((right - left) / 2);

    // Sort the left half.
    mergeSortRange(values, temp, left, middle);

    // Sort the right half.
    mergeSortRange(values, temp, middle, right);

    // Merge the two sorted halves.
    merge(values, temp, left, middle, right);
}


// MERGE SORT
// Sorts the original array in ascending order.

function mergeSort(values: number[]): void {
    if (values.length <= 1) {
        return;
    }

    // Allocate one temporary array and reuse it for all merges.
    const temp: number[] = new Array<number>(values.length);

    mergeSortRange(
        values,
        temp,
        0,
        values.length
    );
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

    mergeSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// DEMONSTRATION

console.log("==== MERGE SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [8, 3, 5, 4, 7, 6, 1, 2];

console.log("Before sorting:", printArray(values));

mergeSort(values);

console.log("After sorting: ", printArray(values));


// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSort([], [], "Empty array");

testSort([42], [42], "Single element");

testSort(
    [9, 3],
    [3, 9],
    "Two elements"
);

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
    [9, 1, 7, 3, 5],
    [1, 3, 5, 7, 9],
    "Odd-sized array"
);