// FEASIBILITY CHECK
// Can all packages be shipped within the allowed days
// using the given capacity?

function canShipWithinDays(
    weights: readonly number[],
    days: number,
    capacity: number
): boolean {
    let usedDays = 1;
    let currentLoad = 0;

    for (const weight of weights) {
        if (currentLoad + weight > capacity) {
            // Start a new day.
            usedDays++;
            currentLoad = weight;

        } else {
            currentLoad += weight;
        }

        // No need to continue if the limit is exceeded.
        if (usedDays > days) {
            return false;
        }
    }

    return true;
}

// BINARY SEARCH ON ANSWER
// Returns the minimum capacity required.
// Returns -1 for invalid input.

function minimumShipCapacity(
    weights: readonly number[],
    days: number
): number {
    if (!Number.isSafeInteger(days) || days <= 0) {
        return -1;
    }

    if (weights.length === 0) {
        return 0;
    }

    let low = 0;
    let high = 0;

    // Find the minimum and maximum possible capacities.
    for (const weight of weights) {
        // Package weights must be positive safe integers.
        if (!Number.isSafeInteger(weight) || weight <= 0) {
            return -1;
        }

        low = Math.max(low, weight);

        // Prevent exceeding JavaScript's safe integer range.
        if (weight > Number.MAX_SAFE_INTEGER - high) {
            return -1;
        }

        high += weight;
    }

    // Search for the first feasible capacity.
    while (low < high) {
        const middle = low + Math.floor((high - low) / 2);

        if (canShipWithinDays(weights, days, middle)) {
            // This capacity works.
            // Try to find a smaller one.
            high = middle;

        } else {
            // This capacity is insufficient.
            low = middle + 1;
        }
    }

    return low;
}

// Helper function for demonstration.
function testMinimumCapacity(
    weights: readonly number[],
    days: number,
    expected: number,
    description: string
): void {
    const result = minimumShipCapacity(weights, days);

    const status = result === expected ? "PASSED" : "FAILED";

    console.log(`${description}: ${result} [${status}]`);
}

// DEMONSTRATION

console.log("==== BINARY SEARCH ON ANSWER ====");

const weights: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

// DISPLAY INPUT
console.log("\nWeights:", weights);

// BASIC TESTS
console.log("\n--- BASIC TESTS ---");

testMinimumCapacity(weights, 5, 15, "Ship within 5 days");
testMinimumCapacity(weights, 3, 21, "Ship within 3 days");
testMinimumCapacity(weights, 10, 10, "Ship within 10 days");
testMinimumCapacity(weights, 1, 55, "Ship within 1 day");

// EDGE CASES
console.log("\n--- EDGE CASES ---");

testMinimumCapacity([], 5, 0, "Empty package array");

testMinimumCapacity([7], 2, 7, "Single package");
testMinimumCapacity([7], 1, 7, "Single package, one day");

testMinimumCapacity(
    [5, 5, 5, 5], 2, 10, "Equal package weights"
);

testMinimumCapacity(
    [3, 2, 2, 4, 1, 4], 3, 6, "Another shipping example"
);

// INVALID INPUT
console.log("\n--- INVALID INPUT ---");

testMinimumCapacity(weights, 0, -1, "Zero allowed days");
testMinimumCapacity(weights, -2, -1, "Negative allowed days");

testMinimumCapacity(
    [3, 0, 5], 2, -1, "Zero package weight"
);