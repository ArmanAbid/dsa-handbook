// INTERPOLATION SEARCH
// Requires ascending sorted input.
// Requires safe integer values and a safe integer range.
// Returns the first occurrence, or -1 if not found.

function interpolationSearch(
    values: readonly number[],
    target: number
): number {
    if (values.length === 0) {
        return -1;
    }

    if (!Number.isSafeInteger(target)) {
        return -1;
    }

    let low = 0;
    let high = values.length - 1;

    let answer = -1;

    while (low <= high) {
        const lowValue = values[low];
        const highValue = values[high];

        if (lowValue === undefined || highValue === undefined) {
            return answer;
        }

        // Ensure the boundary values are safe integers.
        if (
            !Number.isSafeInteger(lowValue) ||
            !Number.isSafeInteger(highValue)
        ) {
            return -1;
        }

        // The target must be within the current range.
        if (target < lowValue || target > highValue) {
            break;
        }

        // Avoid division by zero.
        if (lowValue === highValue) {
            if (lowValue === target) {
                answer = low;
            }

            break;
        }

        const valueDifference = highValue - lowValue;
        const targetDifference = target - lowValue;

        // Avoid unsafe integer arithmetic.
        if (
            !Number.isSafeInteger(valueDifference) ||
            !Number.isSafeInteger(targetDifference)
        ) {
            return -1;
        }

        // Estimate the target's likely position.
        const fraction = targetDifference / valueDifference;

        let position = low + Math.floor(
            fraction * (high - low)
        );

        // Keep the estimated position within the search range.
        position = Math.max(low, Math.min(position, high));

        const currentValue = values[position];

        if (currentValue === undefined) {
            return answer;
        }

        if (currentValue < target) {
            low = position + 1;

        } else {
            if (currentValue === target) {
                answer = position;
            }

            // Continue searching for an earlier occurrence.
            high = position - 1;
        }
    }

    return answer;
}


// Helper function for demonstration.
function testSearch(
    values: readonly number[],
    target: number,
    expected: number,
    description: string
): void {
    const result = interpolationSearch(values, target);

    const status = result === expected ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}


// DEMONSTRATION

console.log("==== INTERPOLATION SEARCH ====");

// UNIFORMLY DISTRIBUTED VALUES
console.log("\n--- UNIFORM DISTRIBUTION ---");

const values: number[] = [
    10, 20, 30, 40, 50, 60, 70, 80, 90, 100
];

console.log("Sorted array:", values);

testSearch(values, 80, 7, "Search for 80");
testSearch(values, 10, 0, "Search for 10");
testSearch(values, 100, 9, "Search for 100");
testSearch(values, 55, -1, "Search for 55");

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSearch([], 10, -1, "Empty array");

testSearch([42], 42, 0, "Single element found");
testSearch([42], 10, -1, "Single element not found");

testSearch(values, 5, -1, "Target smaller than all elements");
testSearch(values, 110, -1, "Target larger than all elements");

// NEGATIVE VALUES
console.log("\n--- NEGATIVE VALUES ---");

const negativeValues: number[] = [-50, -40, -30, -20, -10, 0];

testSearch(negativeValues, -30, 2, "Search for -30");

// DUPLICATES
console.log("\n--- DUPLICATES ---");

const duplicateValues: number[] = [1, 2, 2, 2, 2, 3];

testSearch(
    duplicateValues,
    2,
    1,
    "First occurrence of 2"
);

// ALL ELEMENTS EQUAL
console.log("\n--- ALL ELEMENTS EQUAL ---");

const equalValues: number[] = [5, 5, 5, 5];

testSearch(equalValues, 5, 0, "Search for 5");
testSearch(equalValues, 8, -1, "Search for 8");

// NONUNIFORM DISTRIBUTION
console.log("\n--- NONUNIFORM DISTRIBUTION ---");

const nonuniformValues: number[] = [1, 2, 3, 4, 1000];

testSearch(
    nonuniformValues,
    1000,
    4,
    "Search in nonuniform data"
);

// LARGE INTEGER VALUES
console.log("\n--- LARGE INTEGER VALUES ---");

const largeValues: number[] = [
    -1000000000000000000,
    0,
    1000000000000000000
];

// These values exceed JavaScript's safe integer range.
// The implementation should reject them.
testSearch(
    largeValues,
    1000000000000000000,
    -1,
    "Unsafe integer input rejected"
);