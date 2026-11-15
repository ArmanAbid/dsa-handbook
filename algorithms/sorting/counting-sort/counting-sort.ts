// COUNTING SORT
// Supports negative and positive integers.
// Sorts the original array in ascending order.
// Uses cumulative counts to preserve stability.

function countingSort(values: number[]): void {
    if (values.length <= 1) {
        if (
            values.length === 1 &&
            !Number.isSafeInteger(values[0])
        ) {
            throw new RangeError("Values must be safe integers.");
        }

        return;
    }

    // STEP 1: Find minimum and maximum values.
    let minimum = values[0];
    let maximum = values[0];

    if (minimum === undefined || maximum === undefined) {
        return;
    }

    for (const value of values) {
        if (!Number.isSafeInteger(value)) {
            throw new RangeError("Values must be safe integers.");
        }

        minimum = Math.min(minimum, value);
        maximum = Math.max(maximum, value);
    }

    // Calculate the number of possible integer values.
    const valueRange = maximum - minimum + 1;

    if (!Number.isSafeInteger(valueRange)) {
        throw new RangeError("The value range is too large.");
    }

    // STEP 2: Create the counting array.
    // This requires a manageable value range.
    const counts: number[] = new Array<number>(valueRange).fill(0);

    // Count the occurrences of each value.
    for (const value of values) {
        const index = value - minimum;
        const currentCount = counts[index];

        if (currentCount === undefined) {
            throw new Error("Invalid counting array index.");
        }

        counts[index] = currentCount + 1;
    }

    // STEP 3: Calculate cumulative counts.
    for (let i = 1; i < valueRange; i++) {
        const current = counts[i];
        const previous = counts[i - 1];

        if (current === undefined || previous === undefined) {
            throw new Error("Invalid counting array index.");
        }

        counts[i] = current + previous;
    }

    // STEP 4: Construct the output array.
    const output: number[] = new Array<number>(values.length);

    // Traverse backwards to preserve stability.
    for (let i = values.length - 1; i >= 0; i--) {
        const value = values[i];

        if (value === undefined) {
            throw new Error("Unexpected missing array value.");
        }

        const index = value - minimum;
        const position = counts[index];

        if (position === undefined || position <= 0) {
            throw new Error("Invalid output position.");
        }

        const outputIndex = position - 1;

        output[outputIndex] = value;
        counts[index] = outputIndex;
    }

    // Copy the sorted output back into the original array.
    for (let i = 0; i < values.length; i++) {
        const value = output[i];

        if (value === undefined) {
            throw new Error("Unexpected missing output value.");
        }

        values[i] = value;
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

    countingSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// DEMONSTRATION

console.log("==== COUNTING SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [4, 2, 2, 8, 3, 3, 1];

console.log("Before sorting:", printArray(values));

countingSort(values);

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
    [-5, -2, -5, 0, 3, -2],
    [-5, -5, -2, -2, 0, 3],
    "Negative and positive values"
);

testSort(
    [0, -3, 2, -1, 3, -2],
    [-3, -2, -1, 0, 2, 3],
    "Mixed negative and positive values"
);