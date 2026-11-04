// JUMP SEARCH
// Requires an array sorted in ascending order.
// Returns the first occurrence of the target.
// Returns -1 if the target is not found.

function jumpSearch(values: readonly number[], target: number): number {
    const n = values.length;

    if (n === 0) {
        return -1;
    }

    // Calculate the optimal block size: floor(sqrt(n)).
    const blockSize = Math.max(1, Math.floor(Math.sqrt(n)));

    let start = 0;
    let end = Math.min(blockSize, n);

    // STAGE 1: Find the candidate block.
    while (start < n) {
        const endpoint = values[end - 1];

        if (endpoint === undefined || endpoint >= target) {
            break;
        }

        start = end;

        if (start >= n) {
            return -1;
        }

        end = Math.min(end + blockSize, n);
    }

    // STAGE 2: Linear Search inside the candidate block.
    for (let index = start; index < end; index++) {
        const value = values[index];

        if (value === undefined) {
            return -1;
        }

        if (value === target) {
            return index;
        }

        // The array is sorted, so no later value can match.
        if (value > target) {
            return -1;
        }
    }

    return -1;
}


// Helper function for demonstration.
function testSearch(
    values: readonly number[],
    target: number,
    expected: number,
    description: string
): void {
    const result = jumpSearch(values, target);

    const status = result === expected ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}


// DEMONSTRATION

console.log("==== JUMP SEARCH ====");

const values: number[] = [
    1, 3, 5, 7, 9, 11, 13, 15,
    17, 19, 21, 23, 25, 27, 29
];

// DISPLAY ARRAY
console.log("\nSorted array:", values);

// BASIC SEARCH
console.log("\n--- BASIC SEARCH ---");

testSearch(values, 19, 9, "Search for 19");
testSearch(values, 1, 0, "Search for 1");
testSearch(values, 15, 7, "Search for 15");
testSearch(values, 29, 14, "Search for 29");
testSearch(values, 20, -1, "Search for 20");

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSearch([], 10, -1, "Empty array");

testSearch([42], 42, 0, "Single element found");
testSearch([42], 10, -1, "Single element not found");

testSearch(values, 0, -1, "Target smaller than all elements");
testSearch(values, 40, -1, "Target larger than all elements");

// NEGATIVE VALUES
console.log("\n--- NEGATIVE VALUES ---");

const negativeValues: number[] = [-20, -10, -5, 0, 5];

testSearch(negativeValues, -10, 1, "Search for -10");

// DUPLICATES
console.log("\n--- DUPLICATES ---");

const duplicateValues: number[] = [1, 2, 2, 2, 2, 3];

testSearch(
    duplicateValues,
    2,
    1,
    "First occurrence of 2"
);

const equalValues: number[] = [5, 5, 5, 5];

testSearch(
    equalValues,
    5,
    0,
    "All elements equal"
);