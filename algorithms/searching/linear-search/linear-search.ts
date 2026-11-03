// LINEAR SEARCH
// Returns the index of the first occurrence.
// Returns -1 if the target is not found.

function linearSearch(
    values: readonly number[],
    target: number
): number {
    for (let index = 0; index < values.length; index++) {
        if (values[index] === target) {
            return index;
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
    const result = linearSearch(values, target);

    const status = result === expected ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}

// DEMONSTRATION

console.log("==== LINEAR SEARCH ====");

const values: number[] = [8, 3, 6, 3, 9];

// DISPLAY ARRAY
console.log("\nArray:", values);

// BASIC SEARCH
console.log("\n--- BASIC SEARCH ---");

testSearch(values, 3, 1, "Search for 3");
testSearch(values, 6, 2, "Search for 6");
testSearch(values, 9, 4, "Search for 9");
testSearch(values, 5, -1, "Search for 5");

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSearch([], 10, -1, "Empty array");

testSearch([42], 42, 0, "Single element found");
testSearch([42], 10, -1, "Single element not found");

testSearch([-5, -2, -8], -2, 1, "Negative number");

// DUPLICATE VALUES
console.log("\n--- DUPLICATES ---");

testSearch(values, 3, 1, "First occurrence of 3");