interface MaxSubarrayResult {
    sum: number;
    startIndex: number;
    endIndex: number;
}

function maxSubarraySum(
    values: readonly number[]
): MaxSubarrayResult | null {
    if (values.length === 0) {
        return null;
    }

    const first = values[0];

    if (first === undefined || !Number.isSafeInteger(first)) {
        return null;
    }

    let currentSum = first;
    let bestSum = first;

    let currentStart = 0;
    let bestStart = 0;
    let bestEnd = 0;

    for (let i = 1; i < values.length; i++) {
        const value = values[i];

        if (value === undefined || !Number.isSafeInteger(value)) {
            return null;
        }

        const extendedSum = currentSum + value;

        // Reject sums that cannot be represented safely.
        if (!Number.isSafeInteger(extendedSum)) {
            return null;
        }

        // Extend the previous subarray or start a new one.
        if (value > extendedSum) {
            currentSum = value;
            currentStart = i;
        } else {
            currentSum = extendedSum;
        }

        // Update the best result.
        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestStart = currentStart;
            bestEnd = i;
        }
    }

    return {
        sum: bestSum,
        startIndex: bestStart,
        endIndex: bestEnd
    };
}

function testResult(
    values: readonly number[],
    expected: MaxSubarrayResult,
    label: string
): void {
    const result = maxSubarraySum(values);

    const passed =
        result !== null &&
        result.sum === expected.sum &&
        result.startIndex === expected.startIndex &&
        result.endIndex === expected.endIndex;

    console.log(
        `${label}: ${result === null
            ? "No result"
            : JSON.stringify(result)
        } ${passed ? "[PASSED]" : "[FAILED]"}`
    );
}

function main(): void {
    console.log("==== KADANE'S ALGORITHM ====");

    console.log("\n--- BASIC EXAMPLE ---");

    const values = [-2, 1, -3, 4, -1, 2, 1, -5, 4];

    const result = maxSubarraySum(values);

    console.log(`Original array: ${JSON.stringify(values)}`);

    if (result !== null) {
        const subarray = values.slice(
            result.startIndex,
            result.endIndex + 1
        );

        console.log(`Maximum subarray sum: ${result.sum}`);
        console.log(`Start index: ${result.startIndex}`);
        console.log(`End index: ${result.endIndex}`);
        console.log(`Maximum subarray: ${JSON.stringify(subarray)}`);
    }

    console.log("\n--- TEST CASES ---");

    testResult(
        [-8, -3, -6, -2, -5, -4],
        { sum: -2, startIndex: 3, endIndex: 3 },
        "All negative numbers"
    );

    testResult(
        [1, 2, 3, 4],
        { sum: 10, startIndex: 0, endIndex: 3 },
        "All positive numbers"
    );

    testResult(
        [-7],
        { sum: -7, startIndex: 0, endIndex: 0 },
        "Single element"
    );

    testResult(
        [5, -1, 5],
        { sum: 9, startIndex: 0, endIndex: 2 },
        "Positive values with a negative value"
    );

    testResult(
        [1, -1, 1],
        { sum: 1, startIndex: 0, endIndex: 0 },
        "Multiple maximum subarrays"
    );

    console.log("\n--- EDGE CASES ---");

    const emptyResult = maxSubarraySum([]);

    console.log(
        `Empty array: ${emptyResult === null
            ? "Rejected [PASSED]"
            : "[FAILED]"
        }`
    );

    const unsafeResult = maxSubarraySum([
        Number.MAX_SAFE_INTEGER,
        1
    ]);

    console.log(
        `Unsafe integer sum: ${unsafeResult === null
            ? "Rejected [PASSED]"
            : "[FAILED]"
        }`
    );
}

main();