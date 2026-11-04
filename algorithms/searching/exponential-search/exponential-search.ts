// BINARY SEARCH WITHIN A KNOWN RANGE.
// Returns the first occurrence of the target.

function binarySearchFirstOccurrence(
    values: readonly number[],
    target: number,
    start: number,
    end: number
): number {
    let left = start;
    let right = end;
    let answer = -1;

    while (left <= right) {
        const middle = left + Math.floor((right - left) / 2);
        const value = values[middle];

        if (value === undefined) {
            return answer;
        }

        if (value >= target) {
            if (value === target) {
                answer = middle;
            }

            // Continue looking for an earlier occurrence.
            right = middle - 1;

        } else {
            left = middle + 1;
        }
    }

    return answer;
}


// EXPONENTIAL SEARCH
// Requires ascending sorted input.
// Returns the first occurrence, or -1 if not found.

function exponentialSearch(
    values: readonly number[],
    target: number
): number {
    const n = values.length;

    if (n === 0) {
        return -1;
    }

    const first = values[0];

    if (first === undefined) {
        return -1;
    }

    if (first === target) {
        return 0;
    }

    if (first > target) {
        return -1;
    }

    let low = 0;
    let high = 1;

    // Find a range that can contain the target.
    while (high < n) {
        const value = values[high];

        if (value === undefined || value >= target) {
            break;
        }

        low = high;

        // The array length is safely within JavaScript's
        // index range, but cap the boundary to avoid
        // unnecessary growth beyond the array.
        if (high > Math.floor(n / 2)) {
            high = n;
            break;
        }

        high *= 2;
    }

    // The previous boundary is known to be smaller
    // than the target, so search starts after it.
    const left = low + 1;
    const right = Math.min(high, n - 1);

    return binarySearchFirstOccurrence(
        values,
        target,
        left,
        right
    );
}


// Helper function for demonstration.
function testSearch(
    values: readonly number[],
    target: number,
    expected: number,
    description: string
): void {
    const result = exponentialSearch(values, target);

    const status = result === expected ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}


// DEMONSTRATION

console.log("==== EXPONENTIAL SEARCH ====");

const values: number[] = [
    2, 4, 6, 8, 10, 12, 14, 16,
    18, 20, 22, 24, 26, 28, 30
];

// DISPLAY ARRAY
console.log("\nSorted array:", values);

// BASIC SEARCH
console.log("\n--- BASIC SEARCH ---");

testSearch(values, 22, 10, "Search for 22");
testSearch(values, 2, 0, "Search for 2");
testSearch(values, 4, 1, "Search for 4");
testSearch(values, 30, 14, "Search for 30");
testSearch(values, 17, -1, "Search for 17");

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSearch([], 10, -1, "Empty array");

testSearch([42], 42, 0, "Single element found");
testSearch([42], 10, -1, "Single element not found");

testSearch(values, 1, -1, "Target smaller than all elements");
testSearch(values, 50, -1, "Target larger than all elements");

// NEGATIVE VALUES
console.log("\n--- NEGATIVE VALUES ---");

const negativeValues: number[] = [-20, -10, -5, 0, 5];

testSearch(negativeValues, -10, 1, "Search for -10");

// DUPLICATES
console.log("\n--- DUPLICATES ---");

const duplicateValues: number[] = [2, 4, 4, 4, 6, 8];

testSearch(
    duplicateValues,
    4,
    1,
    "First occurrence of 4"
);