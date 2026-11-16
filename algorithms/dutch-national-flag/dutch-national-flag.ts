function dutchNationalFlag(values: number[]): boolean {
    // Validate before modifying the array.
    for (const value of values) {
        if (value !== 0 && value !== 1 && value !== 2) {
            return false;
        }
    }

    let low = 0;
    let mid = 0;
    let high = values.length;

    while (mid < high) {
        const value = values[mid];

        if (value === undefined) {
            return false;
        }

        if (value === 0) {
            // Move zero to the beginning.
            const temp = values[low];

            if (temp === undefined) {
                return false;
            }

            values[low] = values[mid]!;
            values[mid] = temp;

            low++;
            mid++;
        } else if (value === 1) {
            // One is already in the correct partition.
            mid++;
        } else {
            // Move two to the end.
            high--;

            const temp = values[high];

            if (temp === undefined) {
                return false;
            }

            values[high] = value;
            values[mid] = temp;

            // Do not increment mid.
            // The swapped value is still unprocessed.
        }
    }

    return true;
}

function testSort(
    values: number[],
    expected: number[],
    label: string
): void {
    const valid = dutchNationalFlag(values);

    const passed =
        valid &&
        values.length === expected.length &&
        values.every((value, index) => value === expected[index]);

    console.log(
        `${label}: ${JSON.stringify(values)} ${passed ? "[PASSED]" : "[FAILED]"
        }`
    );
}

function main(): void {
    console.log("==== DUTCH NATIONAL FLAG ====");

    console.log("\n--- BASIC EXAMPLE ---");

    const values = [2, 0, 2, 1, 1, 0];

    console.log(`Original array: ${JSON.stringify(values)}`);

    const valid = dutchNationalFlag(values);

    console.log(
        `Sorted array: ${JSON.stringify(values)} ${valid ? "[PASSED]" : "[FAILED]"
        }`
    );

    console.log("\n--- TEST CASES ---");

    testSort(
        [2, 0, 1, 2, 1, 0],
        [0, 0, 1, 1, 2, 2],
        "Mixed values"
    );

    testSort(
        [0, 1, 2],
        [0, 1, 2],
        "Already sorted"
    );

    testSort(
        [2, 1, 0],
        [0, 1, 2],
        "Reverse order"
    );

    testSort(
        [0, 0, 0],
        [0, 0, 0],
        "All zeros"
    );

    testSort(
        [1, 1, 1],
        [1, 1, 1],
        "All ones"
    );

    testSort(
        [2, 2, 2],
        [2, 2, 2],
        "All twos"
    );

    testSort(
        [2, 2, 1, 0, 1, 0],
        [0, 0, 1, 1, 2, 2],
        "Repeated values"
    );

    testSort(
        [2],
        [2],
        "Single element"
    );

    testSort(
        [],
        [],
        "Empty array"
    );

    console.log("\n--- INVALID INPUT ---");

    const invalid = [2, 0, 3, 1];
    const original = [...invalid];

    const accepted = dutchNationalFlag(invalid);

    const unchanged =
        invalid.every((value, index) => value === original[index]);

    const passed = !accepted && unchanged;

    console.log(
        `Invalid value: ${passed ? "Rejected and unchanged" : "FAILED"
        } ${passed ? "[PASSED]" : "[FAILED]"}`
    );
}

main();