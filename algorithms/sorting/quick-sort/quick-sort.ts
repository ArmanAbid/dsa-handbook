// QUICK SORT RANGE
// Uses three-way partitioning:
//
// [left, less - 1]       Values smaller than pivot.
// [less, greater]        Values equal to pivot.
// [greater + 1, right]   Values greater than pivot.
//
// Recursively sorts the smaller partition and iteratively
// processes the larger partition to limit stack usage.

function quickSortRange(
    values: number[],
    initialLeft: number,
    initialRight: number
): void {
    let left = initialLeft;
    let right = initialRight;

    while (left < right) {
        // Choose the middle-position element as the pivot.
        const middle = left + Math.floor((right - left) / 2);
        const pivot = values[middle];

        if (pivot === undefined) {
            return;
        }

        let less = left;
        let current = left;
        let greater = right;

        // THREE-WAY PARTITIONING
        while (current <= greater) {
            const currentValue = values[current];

            if (currentValue === undefined) {
                return;
            }

            if (currentValue < pivot) {
                // Move smaller element into the left region.
                const lessValue = values[less];

                if (lessValue === undefined) {
                    return;
                }

                values[less] = currentValue;
                values[current] = lessValue;

                less++;
                current++;

            } else if (currentValue > pivot) {
                // Move greater element into the right region.
                const greaterValue = values[greater];

                if (greaterValue === undefined) {
                    return;
                }

                values[current] = greaterValue;
                values[greater] = currentValue;

                greater--;

                // Do not increment current.
                // The incoming element still needs examination.

            } else {
                // Equal element belongs to the middle region.
                current++;
            }
        }

        // Calculate the sizes of the unsorted portions.
        const leftSize = less - left;
        const rightSize = right - greater;

        // Recursively sort the smaller portion.
        // Process the larger portion using the loop.
        if (leftSize < rightSize) {
            quickSortRange(
                values,
                left,
                less - 1
            );

            left = greater + 1;

        } else {
            quickSortRange(
                values,
                greater + 1,
                right
            );

            right = less - 1;
        }
    }
}


// QUICK SORT
// Sorts the original array in ascending order.

function quickSort(values: number[]): void {
    if (values.length <= 1) {
        return;
    }

    quickSortRange(
        values,
        0,
        values.length - 1
    );
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

    quickSort(values);

    const passed =
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    const status = passed ? "PASSED" : "FAILED";

    console.log(`${description}: ${printArray(values)} [${status}]`);
}


// DEMONSTRATION

console.log("==== QUICK SORT ====");

// BASIC EXAMPLE
console.log("\n--- BASIC SORTING ---");

const values: number[] = [8, 3, 5, 4, 7, 6, 1, 2];

console.log("Before sorting:", printArray(values));

quickSort(values);

console.log("After sorting: ", printArray(values));


// EDGE CASES
console.log("\n--- EDGE CASES ---");

testSort([], [], "Empty array");

testSort([42], [42], "Single element");

testSort(
    [9, 3],
    [3, 9],
    "Two elements"
);

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
    [7, 7, 7, 7, 7],
    [7, 7, 7, 7, 7],
    "All elements equal"
);

testSort(
    [-5, 3, -10, 0, 8],
    [-10, -5, 0, 3, 8],
    "Negative and positive values"
);

testSort(
    [9, 1, 7, 3, 5],
    [1, 3, 5, 7, 9],
    "Odd-sized array"
);