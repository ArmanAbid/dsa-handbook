// The result contains two array indices, or null if no pair exists.
type IndexPair = [number, number] | null;


// TWO POINTERS: PAIR SUM
// Requires ascending sorted input.
// Returns the matching indices.
// Returns null when no matching pair exists.

function findPairWithSum(
    values: readonly number[],
    target: number
): IndexPair {
    if (values.length < 2) {
        return null;
    }

    let left = 0;
    let right = values.length - 1;

    while (left < right) {
        const leftValue = values[left];
        const rightValue = values[right];

        if (leftValue === undefined || rightValue === undefined) {
            return null;
        }

        const currentSum = leftValue + rightValue;

        if (currentSum === target) {
            return [left, right];
        }

        if (currentSum < target) {
            // Increase the sum by moving the left pointer.
            left++;
        } else {
            // Decrease the sum by moving the right pointer.
            right--;
        }
    }

    return null;
}


// Helper function for demonstration.
function testPair(
    values: readonly number[],
    target: number,
    expected: IndexPair,
    description: string
): void {
    const result = findPairWithSum(values, target);

    const passed =
        expected === null
            ? result === null
            : result !== null &&
            result[0] === expected[0] &&
            result[1] === expected[1];

    const status = passed ? "PASSED" : "FAILED";

    const display = result === null
        ? "Not found"
        : `(${result[0]}, ${result[1]})`;

    console.log(`${description}: ${display} [${status}]`);
}


// DEMONSTRATION

console.log("==== TWO POINTERS ====");

// BASIC EXAMPLE
console.log("\n--- BASIC PAIR SUM ---");

const values: number[] = [1, 2, 4, 6, 8, 9, 11];

console.log("Sorted array:", values);

testPair(
    values, 10, [0, 5],
    "Find pair with sum 10"
);

testPair(
    values, 13, [1, 6],
    "Find pair with sum 13"
);

testPair(
    values, 21, null,
    "No pair with sum 21"
);


// EDGE CASES
console.log("\n--- EDGE CASES ---");

testPair(
    [], 10, null,
    "Empty array"
);

testPair(
    [5], 10, null,
    "Single element"
);

testPair(
    [3, 7], 10, [0, 1],
    "Two elements"
);

testPair(
    [3, 7], 8, null,
    "Two elements without a pair"
);


// DUPLICATES
console.log("\n--- DUPLICATES ---");

const duplicateValues: number[] = [1, 2, 2, 2, 4];

testPair(
    duplicateValues, 4, [1, 3],
    "Duplicate values"
);

const equalValues: number[] = [5, 5, 5];

testPair(
    equalValues, 10, [0, 2],
    "All elements equal"
);


// NEGATIVE VALUES
console.log("\n--- NEGATIVE VALUES ---");

const negativeValues: number[] = [-8, -3, 0, 4, 9];

testPair(
    negativeValues, 1, [0, 4],
    "Negative and positive pair"
);

testPair(
    negativeValues, -11, [0, 1],
    "Negative pair"
);

testPair(
    negativeValues, 100, null,
    "Target too large"
);