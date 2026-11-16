export { };


class DifferenceArray {
    private differences: number[];

    constructor(values: readonly number[]) {
        this.differences = new Array<number>(values.length);

        // Validate and construct the difference array.
        for (let i = 0; i < values.length; i++) {
            const current = values[i];

            if (current === undefined || !Number.isSafeInteger(current)) {
                throw new RangeError("All values must be safe integers.");
            }

            if (i === 0) {
                this.differences[i] = current;
                continue;
            }

            const previous = values[i - 1];

            if (previous === undefined) {
                throw new Error("Unexpected missing array value.");
            }

            const difference = current - previous;

            if (!Number.isSafeInteger(difference)) {
                throw new RangeError("Difference exceeds safe integer precision.");
            }

            this.differences[i] = difference;
        }
    }

    // RANGE UPDATE:
    // Add value to every element in inclusive range [left, right].
    // Returns false if the range is invalid.
    rangeAdd(left: number, right: number, value: number): boolean {
        if (
            !Number.isSafeInteger(left) ||
            !Number.isSafeInteger(right) ||
            !Number.isSafeInteger(value) ||
            left < 0 ||
            right < left ||
            right >= this.differences.length
        ) {
            return false;
        }

        const currentStart = this.differences[left];

        if (currentStart === undefined) {
            return false;
        }

        // Calculate both changes before modifying the structure.
        const updatedStart = currentStart + value;

        if (!Number.isSafeInteger(updatedStart)) {
            throw new RangeError("Range update exceeds safe integer precision.");
        }

        let updatedEnd: number | undefined;
        const endIndex = right + 1;

        if (endIndex < this.differences.length) {
            const currentEnd = this.differences[endIndex];

            if (currentEnd === undefined) {
                return false;
            }

            updatedEnd = currentEnd - value;

            if (!Number.isSafeInteger(updatedEnd)) {
                throw new RangeError("Range update exceeds safe integer precision.");
            }
        }

        // Apply the validated changes.
        this.differences[left] = updatedStart;

        if (updatedEnd !== undefined) {
            this.differences[endIndex] = updatedEnd;
        }

        return true;
    }

    // RECONSTRUCT: Build the final array using Prefix Sum.
    buildArray(): number[] {
        const result: number[] = [];

        let current = 0;

        for (const difference of this.differences) {
            current += difference;

            if (!Number.isSafeInteger(current)) {
                throw new RangeError("Reconstructed value exceeds safe integer precision.");
            }

            result.push(current);
        }

        return result;
    }

    // SIZE: Get the number of elements.
    size(): number {
        return this.differences.length;
    }

    // CHECK: Is the structure empty?
    isEmpty(): boolean {
        return this.differences.length === 0;
    }
}


// Test a range update.
function testUpdate(
    values: DifferenceArray,
    left: number,
    right: number,
    delta: number,
    expected: boolean,
    description: string
): void {
    const result = values.rangeAdd(left, right, delta);

    const status = result === expected ? "PASSED" : "FAILED";
    const display = result ? "Updated" : "Rejected";

    console.log(`${description}: ${display} [${status}]`);
}


// Test reconstructed output.
function testArray(
    values: DifferenceArray,
    expected: readonly number[],
    description: string
): void {
    const result = values.buildArray();

    const passed =
        result.length === expected.length &&
        result.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: [${result.join(", ")}] [${status}]`);
}


// Test invalid input.
function testInvalidInput(
    create: () => DifferenceArray,
    description: string
): void {
    try {
        create();

        console.log(`${description}: Not rejected [FAILED]`);

    } catch (error) {
        const passed = error instanceof RangeError;

        console.log(
            `${description}: ${passed ? "Rejected" : "Unexpected error"} ` +
            `[${passed ? "PASSED" : "FAILED"}]`
        );
    }
}


// ========================================
// DEMONSTRATION
// ========================================

console.log("===== DIFFERENCE ARRAY =====");

// BASIC EXAMPLE
console.log("\n--- BUILD DIFFERENCE ARRAY ---");

const initial: number[] = [10, 20, 30, 40, 50];

const values = new DifferenceArray(initial);

console.log("Original array:", initial);
console.log("Size:", values.size());
console.log("Is empty:", values.isEmpty());


// RANGE UPDATES
console.log("\n--- RANGE UPDATES ---");

testUpdate(
    values, 1, 3, 5, true,
    "Add 5 to range [1, 3]"
);

testUpdate(
    values, 0, 2, -3, true,
    "Add -3 to range [0, 2]"
);

testUpdate(
    values, 2, 4, 10, true,
    "Add 10 to range [2, 4]"
);

testArray(
    values,
    [7, 22, 42, 55, 60],
    "Final array after three updates"
);


// EDGE CASES
console.log("\n--- EDGE CASES ---");

const emptyArray = new DifferenceArray([]);

console.log("Empty array size:", emptyArray.size());
console.log("Empty check:", emptyArray.isEmpty());

testUpdate(
    emptyArray, 0, 0, 5, false,
    "Update empty array"
);

const singleArray = new DifferenceArray([10]);

testUpdate(
    singleArray, 0, 0, 5, true,
    "Single-element update"
);

testArray(
    singleArray,
    [15],
    "Single-element result"
);


// FULL ARRAY UPDATE
console.log("\n--- FULL ARRAY UPDATE ---");

const fullArray = new DifferenceArray([1, 2, 3]);

testUpdate(
    fullArray, 0, 2, 10, true,
    "Add 10 to entire array"
);

testArray(
    fullArray,
    [11, 12, 13],
    "Full array result"
);


// OVERLAPPING UPDATES
console.log("\n--- OVERLAPPING UPDATES ---");

const overlapping = new DifferenceArray([0, 0, 0, 0, 0]);

overlapping.rangeAdd(0, 2, 5);
overlapping.rangeAdd(1, 4, 3);

testArray(
    overlapping,
    [5, 8, 8, 3, 3],
    "Overlapping range updates"
);


// INVALID RANGES
console.log("\n--- INVALID RANGES ---");

testUpdate(
    overlapping, -1, 2, 5, false,
    "Negative left index"
);

testUpdate(
    overlapping, 0, 5, 5, false,
    "Right index out of bounds"
);

testUpdate(
    overlapping, 3, 1, 5, false,
    "Left greater than right"
);


// INVALID INTEGER INPUT
console.log("\n--- INVALID INTEGER INPUT ---");

testInvalidInput(
    () => new DifferenceArray([1, 2, Number.MAX_SAFE_INTEGER + 1]),
    "Unsafe integer"
);

testInvalidInput(
    () => new DifferenceArray([
        Number.MIN_SAFE_INTEGER,
        Number.MAX_SAFE_INTEGER
    ]),
    "Unsafe difference"
);