function buildLPS(pattern: string): number[] {
    const m = pattern.length;

    const lps: number[] = new Array<number>(m).fill(0);

    let length = 0;
    let i = 1;

    while (i < m) {
        if (pattern.charAt(i) === pattern.charAt(length)) {
            length++;

            lps[i] = length;
            i++;
        } else if (length !== 0) {
            length = lps[length - 1] ?? 0;
        } else {
            lps[i] = 0;
            i++;
        }
    }

    return lps;
}


function kmpSearch(text: string, pattern: string): number[] {
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

    // Preprocess the pattern.
    const lps = buildLPS(pattern);

    let i = 0; // Text pointer
    let j = 0; // Pattern pointer

    while (i < n) {
        if (text.charAt(i) === pattern.charAt(j)) {
            i++;
            j++;

            // Entire pattern matched.
            if (j === m) {
                positions.push(i - j);

                // Continue searching for overlapping matches.
                j = lps[j - 1] ?? 0;
            }
        } else if (j !== 0) {
            // Reuse previously matched prefix information.
            j = lps[j - 1] ?? 0;
        } else {
            i++;
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
    const result = kmpSearch(text, pattern);

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
    console.log("=== KMP STRING MATCHING ===");

    console.log("\n--- LPS CONSTRUCTION ---");

    console.log("Pattern: ABABC");
    console.log(`LPS: [${buildLPS("ABABC").join(", ")}]`);

    console.log("\n--- BASIC SEARCH ---");

    runTest(
        "ABABABC",
        "ABABC",
        [2],
        "LPS fallback example"
    );

    runTest(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        [10],
        "Standard KMP example"
    );

    runTest(
        "ABABA",
        "ABA",
        [0, 2],
        "Overlapping matches"
    );

    runTest(
        "ABCABCABC",
        "ABC",
        [0, 3, 6],
        "Multiple matches"
    );

    runTest(
        "AAAAAAAAAB",
        "AAAAB",
        [5],
        "Repeated prefix characters"
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
