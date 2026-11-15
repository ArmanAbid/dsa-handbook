interface WindowResult {
    sum: number;
    startIndex: number;
    endIndex: number;
}


// FIXED-SIZE SLIDING WINDOW
// Finds the maximum sum of a contiguous subarray
// containing exactly k elements.
//
// Returns the maximum sum and its indices.
// Returns null for invalid input or unsafe integer arithmetic.

function maximumSumSubarray(
    values: readonly number[],
    k: number
): WindowResult | null {
    if (!Number.isSafeInteger(k) || k <= 0 || k > values.length) {
        return null;
    }

    // Validate input values.
    for (const value of values) {
        if (!Number.isSafeInteger(value)) {
            return null;
        }
    }

    // STEP 1: Calculate the first window sum.
    let currentSum = 0;

    for (let i = 0; i < k; i++) {
        const value = values[i];

        if (value === undefined) {
            return null;
        }

        currentSum += value;

        if (!Number.isSafeInteger(currentSum)) {
            return null;
        }
    }

    // Initialize the best result using the first actual window.
    let bestSum = currentSum;
    let bestStart = 0;
    let bestEnd = k - 1;

    // STEP 2: Slide the window.
    for (let endIndex = k; endIndex < values.length; endIndex++) {
        const outgoing = values[endIndex - k];
        const incoming = values[endIndex];

        if (outgoing === undefined || incoming === undefined) {
            return null;
        }

        // Remove the element leaving the window.
        currentSum -= outgoing;

        if (!Number.isSafeInteger(currentSum)) {
            return null;
        }

        // Add the element entering the window.
        currentSum += incoming;

        if (!Number.isSafeInteger(currentSum)) {
            return null;
        }

        // Update only when a strictly better sum is found.
        // This preserves the first window when sums are equal.
        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestStart = endIndex - k + 1;
            bestEnd = endIndex;
        }
    }

    return {
        sum: bestSum,
        startIndex: bestStart,
        endIndex: bestEnd
    };
}


// Helper function for testing.
function testMaximumSum(
    values: readonly number[],
    k: number,
    expected: WindowResult | null,
    description: string
): void {
    const result = maximumSumSubarray(values, k);

    const passed =
        expected === null
            ? result === null
            : result !== null &&
            result.sum === expected.sum &&
            result.startIndex === expected.startIndex &&
            result.endIndex === expected.endIndex;

    const status = passed ? "PASSED" : "FAILED";

    const display = result === null
        ? "No valid window"
        : `Sum = ${result.sum}, Indices = (${result.startIndex}, ${result.endIndex})`;

    console.log(`${description}: ${display} [${status}]`);
}


// DEMONSTRATION

console.log("==== SLIDING WINDOW ====");

// BASIC EXAMPLE
console.log("\n--- MAXIMUM SUM SUBARRAY ---");

const values: number[] = [2, 1, 5, 1, 3, 2];

console.log("Array:", values);
console.log("Window size: 3");

testMaximumSum(
    values, 3,
    { sum: 9, startIndex: 2, endIndex: 4 },
    "Maximum sum"
);


// EDGE CASES
console.log("\n--- EDGE CASES ---");

testMaximumSum(
    [], 2, null,
    "Empty array"
);

testMaximumSum(
    [7], 1,
    { sum: 7, startIndex: 0, endIndex: 0 },
    "Single element"
);

testMaximumSum(
    [7], 2, null,
    "Window larger than array"
);

testMaximumSum(
    values, 0, null,
    "Zero window size"
);

testMaximumSum(
    values, -2, null,
    "Negative window size"
);

testMaximumSum(
    values, 6,
    { sum: 14, startIndex: 0, endIndex: 5 },
    "Window equals array size"
);


// NEGATIVE VALUES
console.log("\n--- NEGATIVE VALUES ---");

const negativeValues: number[] = [-5, -2, -8, -1, -3];

testMaximumSum(
    negativeValues, 2,
    { sum: -4, startIndex: 3, endIndex: 4 },
    "All negative values"
);


// DUPLICATE MAXIMUM WINDOWS
console.log("\n--- EQUAL MAXIMUM WINDOWS ---");

const equalValues: number[] = [4, 4, 4, 4];

testMaximumSum(
    equalValues, 2,
    { sum: 8, startIndex: 0, endIndex: 1 },
    "First window among equal maximum sums"
);


// MAXIMUM AT DIFFERENT POSITIONS
console.log("\n--- MAXIMUM WINDOW POSITIONS ---");

testMaximumSum(
    [10, 2, 3, 1], 2,
    { sum: 12, startIndex: 0, endIndex: 1 },
    "Maximum at first window"
);

testMaximumSum(
    [1, 2, 3, 10], 2,
    { sum: 13, startIndex: 2, endIndex: 3 },
    "Maximum at last window"
);


// INVALID INTEGER INPUT
console.log("\n--- INVALID INTEGER INPUT ---");

testMaximumSum(
    [1, Number.MAX_SAFE_INTEGER, 2], 2, null,
    "Unsafe intermediate sum"
);

testMaximumSum(
    [1.5, 2, 3], 2, null,
    "Non-integer input"
);