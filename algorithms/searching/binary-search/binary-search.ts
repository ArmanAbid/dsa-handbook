// BINARY SEARCH
// Requires an array sorted in ascending order.
// Returns the first occurrence of the target.
// Returns -1 if the target is not found.

function binarySearch(
    values: readonly number[],
    target: number
): number {
    let left = 0;
    let right = values.length;

    // Search using a half-open interval [left, right).
    while (left < right) {
        const middle = left + Math.floor((right - left) / 2);
        const middleValue = values[middle];

        if (middleValue === undefined) {
            return -1;
        }

        if (middleValue < target) {
            // Target can only be in the right half.
            left = middle + 1;
        } else {
            // Keep the middle in the search range.
            // This allows us to find the first occurrence.
            right = middle;
        }
    }

    // Check whether the target exists at the final position.
    if (left < values.length && values[left] === target) {
        return left;
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
    const result = binarySearch(values, target);

    const status = result === expected ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}

// DEMONSTRATION

console.log("==== BINARY SEARCH ====");

const values: number[] = [2, 4, 4, 4, 7, 9, 12, 15];

// DISPLAY ARRAY
console.log("\nSorted array:", values);

// BASIC SEARCH
console.log("\n--- BASIC SEARCH ---");

testSearch(values, 4, 1, "Search for 4");
testSearch(values, 7, 4, "Search for 7");
testSearch(values, 15, 7, "Search for 15");
testSearch(values, 2, 0, "Search for 2");
testSearch(values, 10, -1, "Search for 10");

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSearch([], 10, -1, "Empty array");

testSearch([42], 42, 0, "Single element found");
testSearch([42], 10, -1, "Single element not found");

testSearch(values, 1, -1, "Target smaller than all elements");
testSearch(values, 20, -1, "Target larger than all elements");

const negativeValues: number[] = [-10, -5, -2, 0, 5];

testSearch(negativeValues, -5, 1, "Negative number");

// DUPLICATE VALUES
console.log("\n--- DUPLICATES ---");

testSearch(values, 4, 1, "First occurrence of 4");

const equalValues: number[] = [5, 5, 5, 5];

testSearch(equalValues, 5, 0, "All elements equal");