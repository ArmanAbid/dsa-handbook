// STABLE COUNTING SORT BY DIGIT
// Sorts values according to one decimal digit.
// The original values and their transformed keys move together.

function countingSortByDigit(
    values: number[],
    keys: number[],
    exponent: number
): void {
    const n = values.length;

    const counts: number[] = new Array<number>(10).fill(0);

    // STEP 1: Count occurrences of each digit.
    for (const key of keys) {
        const digit = Math.floor(key / exponent) % 10;

        const currentCount = counts[digit];

        if (currentCount === undefined) {
            throw new Error("Invalid digit.");
        }

        counts[digit] = currentCount + 1;
    }

    // STEP 2: Calculate cumulative counts.
    for (let i = 1; i < 10; i++) {
        const current = counts[i];
        const previous = counts[i - 1];

        if (current === undefined || previous === undefined) {
            throw new Error("Invalid counting array index.");
        }

        counts[i] = current + previous;
    }

    // STEP 3: Construct output backwards to preserve stability.
    const output: number[] = new Array<number>(n);
    const outputKeys: number[] = new Array<number>(n);

    for (let i = n - 1; i >= 0; i--) {
        const value = values[i];
        const key = keys[i];

        if (value === undefined || key === undefined) {
            throw new Error("Unexpected missing array value.");
        }

        const digit = Math.floor(key / exponent) % 10;

        const count = counts[digit];

        if (count === undefined || count <= 0) {
            throw new Error("Invalid output position.");
        }

        const position = count - 1;

        counts[digit] = position;

        output[position] = value;
        outputKeys[position] = key;
    }

    // Copy the sorted result back.
    for (let i = 0; i < n; i++) {
        const value = output[i];
        const key = outputKeys[i];

        if (value === undefined || key === undefined) {
            throw new Error("Unexpected missing output value.");
        }

        values[i] = value;
        keys[i] = key;
    }
}


// RADIX SORT
// Supports negative and positive safe integers.
// Sorts the original array in ascending order.

function radixSort(values: number[]): void {
    // STEP 1: Validate all values.
    for (const value of values) {
        if (!Number.isSafeInteger(value)) {
            throw new RangeError(
                "Radix Sort requires safe integer values."
            );
        }
    }

    if (values.length <= 1) {
        return;
    }

    // STEP 2: Find minimum and maximum values.
    let minimum = values[0];
    let maximum = values[0];

    if (minimum === undefined || maximum === undefined) {
        return;
    }

    for (const value of values) {
        minimum = Math.min(minimum, value);
        maximum = Math.max(maximum, value);
    }

    // STEP 3: Transform values into non-negative keys.
    const maxKey = maximum - minimum;

    if (!Number.isSafeInteger(maxKey)) {
        throw new RangeError(
            "The transformed value range exceeds safe integer precision."
        );
    }

    const keys: number[] = values.map(
        value => value - minimum
    );

    // STEP 4: Process decimal digits from right to left.
    let exponent = 1;

    while (Math.floor(maxKey / exponent) > 0) {
        countingSortByDigit(
            values,
            keys,
            exponent
        );

        // Avoid overflowing the safe integer range.
        if (exponent > Math.floor(maxKey / 10)) {
            break;
        }

        exponent *= 10;
    }
}


// Helper function for demonstration.
function printArray(values: readonly number[]): string {
    return `[${values.join(", ")}]`;
}


// Test a sorting case.
function testSort(
    input: readonly number[],
    expected: readonly number[],
    description: string
): void {
    const values = [...input];

    radixSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// Test invalid input.
function testInvalidInput(
    input: number[],
    description: string
): void {
    try {
        radixSort(input);

        console.log(`${description}: Did not reject input [FAILED]`);

    } catch (error) {
        const passed = error instanceof RangeError;

        console.log(
            `${description}: ${passed ? "Rejected" : "Unexpected error"} ` +
            `[${passed ? "PASSED" : "FAILED"}]`
        );
    }
}


// DEMONSTRATION

console.log("==== RADIX SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [170, 45, 75, 90, 802, 24, 2, 66];

console.log("Before sorting:", printArray(values));

radixSort(values);

console.log("After sorting: ", printArray(values));


// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSort([], [], "Empty array");

testSort([42], [42], "Single element");

testSort(
    [1, 2, 3, 4, 5],
    [1, 2, 3, 4, 5],
    "Already sorted"
);

testSort(
    [5, 4, 3, 2, 1],
    [1, 2, 3, 4, 5],
    "Reverse sorted"
);

testSort(
    [4, 2, 4, 1, 2],
    [1, 2, 2, 4, 4],
    "Duplicate values"
);

testSort(
    [7, 7, 7, 7],
    [7, 7, 7, 7],
    "All elements equal"
);

testSort(
    [-5, -2, -5, 0, 3, -2],
    [-5, -5, -2, -2, 0, 3],
    "Negative and positive values"
);

testSort(
    [0, -3, 2, -1, 3, -2],
    [-3, -2, -1, 0, 2, 3],
    "Mixed negative and positive values"
);

// DIFFERENT NUMBER OF DIGITS
console.log("\n--- DIFFERENT DIGIT LENGTHS ---");

testSort(
    [1000, 5, 50, 500, 1],
    [1, 5, 50, 500, 1000],
    "Different digit lengths"
);

// SAFE INTEGER LIMITS
console.log("\n--- SAFE INTEGER LIMITS ---");

testSort(
    [
        Number.MIN_SAFE_INTEGER,
        Number.MIN_SAFE_INTEGER + 10,
        Number.MIN_SAFE_INTEGER + 100
    ],
    [
        Number.MIN_SAFE_INTEGER,
        Number.MIN_SAFE_INTEGER + 10,
        Number.MIN_SAFE_INTEGER + 100
    ],
    "Safe integers near minimum"
);

testSort(
    [
        Number.MAX_SAFE_INTEGER,
        Number.MAX_SAFE_INTEGER - 10,
        Number.MAX_SAFE_INTEGER - 100
    ],
    [
        Number.MAX_SAFE_INTEGER - 100,
        Number.MAX_SAFE_INTEGER - 10,
        Number.MAX_SAFE_INTEGER
    ],
    "Safe integers near maximum"
);

// INVALID INPUT
console.log("\n--- INVALID INPUT ---");

testInvalidInput(
    [Number.MAX_SAFE_INTEGER + 1],
    "Unsafe integer"
);

testInvalidInput(
    [-Number.MAX_SAFE_INTEGER, Number.MAX_SAFE_INTEGER],
    "Unsafe transformed range"
);