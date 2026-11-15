// BUILD PREFIX SUM
// prefix[i] represents the sum of the first i elements.
// Therefore, prefix[0] is always zero.
//
// Throws RangeError if a value or cumulative sum is unsafe.

function buildPrefixSum(values: readonly number[]): number[] {
    const prefix: number[] = [0];

    for (const value of values) {
        if (!Number.isSafeInteger(value)) {
            throw new RangeError("All values must be safe integers.");
        }

        const previous = prefix[prefix.length - 1];

        if (previous === undefined) {
            throw new Error("Invalid prefix array.");
        }

        const next = previous + value;

        if (!Number.isSafeInteger(next)) {
            throw new RangeError("Prefix sum exceeds safe integer precision.");
        }

        prefix.push(next);
    }

    return prefix;
}


// RANGE SUM QUERY
// Returns the sum of the inclusive range [left, right].
// Returns null for an invalid range or unsafe arithmetic.

function rangeSum(
    prefix: readonly number[],
    left: number,
    right: number
): number | null {
    if (
        !Number.isSafeInteger(left) ||
        !Number.isSafeInteger(right)
    ) {
        return null;
    }

    if (prefix.length === 0 || left < 0 || right < left) {
        return null;
    }

    const n = prefix.length - 1;

    if (right >= n) {
        return null;
    }

    const rangeEnd = prefix[right + 1];
    const rangeStart = prefix[left];

    if (rangeEnd === undefined || rangeStart === undefined) {
        return null;
    }

    const result = rangeEnd - rangeStart;

    if (!Number.isSafeInteger(result)) {
        return null;
    }

    return result;
}


// Test a range sum query.
function testRangeSum(
    prefix: readonly number[],
    left: number,
    right: number,
    expected: number | null,
    description: string
): void {
    const result = rangeSum(prefix, left, right);

    const passed = result === expected;

    const status = passed ? "PASSED" : "FAILED";

    const display = result === null ? "Invalid range" : String(result);

    console.log(`${description}: ${display} [${status}]`);
}


// Test invalid input to the prefix builder.
function testInvalidInput(
    values: readonly number[],
    description: string
): void {
    try {
        buildPrefixSum(values);

        console.log(`${description}: Not rejected [FAILED]`);

    } catch (error) {
        const passed = error instanceof RangeError;

        console.log(
            `${description}: ${passed ? "Rejected" : "Unexpected error"} ` +
            `[${passed ? "PASSED" : "FAILED"}]`
        );
    }
}


// DEMONSTRATION

console.log("==== PREFIX SUM ====");

// BASIC EXAMPLE
console.log("\n--- BUILD PREFIX SUM ---");

const values: number[] = [2, 4, 1, 7, 3, 6];

const prefix = buildPrefixSum(values);

console.log("Original array:", values);
console.log("Prefix array:  ", prefix);


// RANGE SUM QUERIES
console.log("\n--- RANGE SUM QUERIES ---");

testRangeSum(prefix, 1, 4, 15, "Sum from index 1 to 4");
testRangeSum(prefix, 0, 2, 7, "Sum from index 0 to 2");
testRangeSum(prefix, 2, 5, 17, "Sum from index 2 to 5");
testRangeSum(prefix, 0, 5, 23, "Sum of entire array");
testRangeSum(prefix, 3, 3, 7, "Single element range");


// EDGE CASES
console.log("\n--- EDGE CASES ---");

const emptyPrefix = buildPrefixSum([]);

testRangeSum(
    emptyPrefix, 0, 0, null,
    "Empty array"
);

const singlePrefix = buildPrefixSum([42]);

testRangeSum(
    singlePrefix, 0, 0, 42,
    "Single element"
);

testRangeSum(
    prefix, -1, 2, null,
    "Negative left index"
);

testRangeSum(
    prefix, 0, 6, null,
    "Right index out of bounds"
);

testRangeSum(
    prefix, 4, 2, null,
    "Left greater than right"
);


// NEGATIVE VALUES
console.log("\n--- NEGATIVE VALUES ---");

const negativeValues: number[] = [-5, -2, -8, -1, -3];

const negativePrefix = buildPrefixSum(negativeValues);

console.log("Prefix array:", negativePrefix);

testRangeSum(
    negativePrefix, 1, 3, -11,
    "Sum of negative range"
);


// ZERO VALUES
console.log("\n--- ZERO VALUES ---");

const zeroPrefix = buildPrefixSum([0, 0, 0]);

testRangeSum(
    zeroPrefix, 0, 2, 0,
    "All zero values"
);


// INVALID INTEGER INPUT
console.log("\n--- INVALID INTEGER INPUT ---");

testInvalidInput(
    [1.5, 2, 3],
    "Non-integer input"
);

testInvalidInput(
    [1, Number.MAX_SAFE_INTEGER],
    "Unsafe cumulative sum"
);