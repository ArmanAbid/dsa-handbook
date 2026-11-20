function buildZArray(sequence: number[]): number[] {
    const n = sequence.length;

    const z: number[] = new Array<number>(n).fill(0);

    let left = 0;
    let right = 0;

    for (let i = 1; i < n; i++) {

        // Reuse information from the current Z box.
        if (i <= right) {
            const mirror = i - left;
            const remaining = right - i + 1;

            z[i] = Math.min(
                z[mirror] ?? 0,
                remaining
            );
        }

        // Extend the match beyond the current Z box.
        while (i + (z[i] ?? 0) < n) {
            const offset = z[i] ?? 0;

            if (
                sequence[offset] !== sequence[i + offset]
            ) {
                break;
            }

            z[i] = offset + 1;
        }

        // Update the Z box if this match extends farther.
        const currentZ = z[i] ?? 0;

        if (
            currentZ > 0 &&
            i + currentZ - 1 > right
        ) {
            left = i;
            right = i + currentZ - 1;
        }
    }

    return z;
}


function zSearch(text: string, pattern: string): number[] {
    const positions: number[] = [];

    const n = text.length;
    const m = pattern.length;

    // An empty pattern matches every boundary position.
    if (m === 0) {
        for (let i = 0; i <= n; i++) {
            positions.push(i);
        }

        return positions;
    }

    // Pattern cannot fit inside the text.
    if (m > n) {
        return positions;
    }

    // Build: pattern + separator + text.
    // -1 cannot collide with UTF-16 character values.
    const combined: number[] = [];

    for (let i = 0; i < m; i++) {
        combined.push(pattern.charCodeAt(i));
    }

    combined.push(-1);

    for (let i = 0; i < n; i++) {
        combined.push(text.charCodeAt(i));
    }

    // Calculate the Z array.
    const z = buildZArray(combined);

    // Find positions where the entire pattern matches.
    for (let i = m + 1; i < combined.length; i++) {
        if ((z[i] ?? 0) >= m) {
            positions.push(i - m - 1);
        }
    }

    return positions;
}


function runTest(
    text: string,
    pattern: string,
    expected: number[],
    testName: string
): void {
    const result = zSearch(text, pattern);

    const passed =
        result.length === expected.length &&
        result.every(
            (value, index) => value === expected[index]
        );

    console.log(
        `${testName}: [${result.join(", ")}] ` +
        `[${passed ? "PASSED" : "FAILED"}]`
    );

    if (!passed) {
        console.log(`  Expected: [${expected.join(", ")}]`);
    }
}


function main(): void {
    console.log("==== Z ALGORITHM ====");

    console.log("\n--- Z ARRAY CONSTRUCTION ---");

    console.log("String: ABABAC");

    const sample = [65, 66, 65, 66, 65, 67];

    console.log(`Z array: [${buildZArray(sample).join(", ")}]`);

    console.log("\n--- BASIC SEARCH ---");

    runTest(
        "ABABABC",
        "ABABC",
        [2],
        "LPS-style prefix reuse example"
    );

    runTest(
        "ABABA",
        "ABA",
        [0, 2],
        "Overlapping matches"
    );

    runTest(
        "BANANA",
        "ANA",
        [1, 3],
        "Multiple matches"
    );

    runTest(
        "ABCABCABC",
        "ABC",
        [0, 3, 6],
        "Repeated pattern"
    );

    runTest(
        "mississippi",
        "issi",
        [1, 4],
        "Pattern with repeated characters"
    );

    runTest(
        "AAAAA",
        "AAA",
        [0, 1, 2],
        "Repeated overlapping matches"
    );

    console.log("\n--- EDGE CASES ---");

    runTest(
        "ABCDEF",
        "XYZ",
        [],
        "No match"
    );

    runTest(
        "ABC",
        "ABCDE",
        [],
        "Pattern longer than text"
    );

    runTest(
        "ABC",
        "",
        [0, 1, 2, 3],
        "Empty pattern"
    );

    runTest(
        "",
        "",
        [0],
        "Both empty"
    );

    runTest(
        "",
        "A",
        [],
        "Empty text"
    );
}


main();
