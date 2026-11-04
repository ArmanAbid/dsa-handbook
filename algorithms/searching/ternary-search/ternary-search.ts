// DISCRETE TERNARY SEARCH
// Finds the index of the maximum element in a unimodal array.
// Returns -1 if the array is empty.

function ternarySearchMaximum(values: readonly number[]): number {
    if (values.length === 0) {
        return -1;
    }

    let left = 0;
    let right = values.length - 1;

    // Narrow the search interval.
    while (right - left > 2) {
        const third = Math.floor((right - left) / 3);

        const middleOne = left + third;
        const middleTwo = right - third;

        const valueOne = values[middleOne];
        const valueTwo = values[middleTwo];

        if (valueOne === undefined || valueTwo === undefined) {
            return -1;
        }

        if (valueOne < valueTwo) {
            // The maximum must be to the right.
            left = middleOne + 1;
        } else {
            // The maximum must be to the left.
            right = middleTwo - 1;
        }
    }

    // Check the remaining elements.
    let bestIndex = left;

    for (let index = left + 1; index <= right; index++) {
        const currentValue = values[index];
        const bestValue = values[bestIndex];

        if (currentValue !== undefined &&
            bestValue !== undefined &&
            currentValue > bestValue) {
            bestIndex = index;
        }
    }

    return bestIndex;
}


// CONTINUOUS TERNARY SEARCH
// Finds the approximate maximum position of a unimodal function.
// The function is evaluated 100 times.

function ternarySearchContinuousMaximum(
    fn: (x: number) => number,
    start: number,
    end: number
): number {
    let left = Math.min(start, end);
    let right = Math.max(start, end);

    for (let iteration = 0; iteration < 100; iteration++) {
        const third = (right - left) / 3;

        const middleOne = left + third;
        const middleTwo = right - third;

        if (fn(middleOne) < fn(middleTwo)) {
            left = middleOne;
        } else {
            right = middleTwo;
        }
    }

    return left + (right - left) / 2;
}


// Example function:
// f(x) = -(x - 3)^2 + 10
// Maximum is at x = 3, with value 10.

function objectiveFunction(x: number): number {
    const difference = x - 3;

    return -(difference * difference) + 10;
}


// Helper function for discrete search tests.
function testDiscreteSearch(
    values: readonly number[],
    expectedIndex: number,
    description: string
): void {
    const result = ternarySearchMaximum(values);

    const status = result === expectedIndex ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}


// Helper function for continuous search tests.
function testContinuousSearch(
    left: number,
    right: number,
    expected: number,
    description: string
): void {
    const result = ternarySearchContinuousMaximum(
        objectiveFunction,
        left,
        right
    );

    const status =
        Math.abs(result - expected) < 0.0000001
            ? "PASSED"
            : "FAILED";

    console.log(
        `${description}: ${result.toFixed(8)} [${status}]`
    );
}


// DEMONSTRATION

console.log("==== TERNARY SEARCH ====");

// DISCRETE TERNARY SEARCH
console.log("\n--- DISCRETE TERNARY SEARCH ---");

const values: number[] = [1, 3, 8, 12, 14, 11, 7, 4, 2];

console.log("Array:", values);

const peakIndex = ternarySearchMaximum(values);

console.log("Maximum index:", peakIndex);
console.log("Maximum value:", values[peakIndex]);

// DISCRETE EDGE CASES
console.log("\n--- DISCRETE EDGE CASES ---");

testDiscreteSearch(
    [], -1, "Empty array"
);

testDiscreteSearch(
    [42], 0, "Single element"
);

testDiscreteSearch(
    [1, 2, 3, 4, 5], 4, "Increasing array"
);

testDiscreteSearch(
    [5, 4, 3, 2, 1], 0, "Decreasing array"
);

testDiscreteSearch(
    [1, 3, 5, 5, 5, 4, 2], 2, "Maximum plateau"
);

// CONTINUOUS TERNARY SEARCH
console.log("\n--- CONTINUOUS TERNARY SEARCH ---");

testContinuousSearch(
    -10, 10, 3, "Search in [-10, 10]"
);

testContinuousSearch(
    0, 10, 3, "Search in [0, 10]"
);

testContinuousSearch(
    4, 10, 4, "Maximum at left boundary"
);

testContinuousSearch(
    -10, 2, 2, "Maximum at right boundary"
);