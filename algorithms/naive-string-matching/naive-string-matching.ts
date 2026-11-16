function naiveStringSearch(
    text: string,
    pattern: string
): number[] {
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

    // Try every possible starting position.
    for (let i = 0; i <= n - m; i++) {
        let j = 0;

        // Compare characters one by one.
        while (
            j < m &&
            text.charAt(i + j) === pattern.charAt(j)
        ) {
            j++;
        }

        // The entire pattern matched.
        if (j === m) {
            positions.push(i);
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
    const result = naiveStringSearch(text, pattern);

    const passed =
        result.length === expected.length &&
        result.every((value, index) => value === expected[index]);

    console.log(
        `${testName}: [${result.join(", ")}] [${passed ? "PASSED" : "FAILED"}]`
    );

    if (!passed) {
        console.log(`  Expected: [${expected.join(", ")}]`);
    }
}


function main(): void {
    console.log("==== NAIVE STRING MATCHING ====");

    console.log("\n--- BASIC SEARCH ---");

    runTest(
        "ABABA",
        "ABA",
        [0, 2],
        "Overlapping matches"
    );

    runTest(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        [10],
        "Single match"
    );

    runTest(
        "ABCDEF",
        "XYZ",
        [],
        "No match"
    );

    runTest(
        "HELLO WORLD",
        "WORLD",
        [6],
        "Match near end"
    );

    console.log("\n--- EDGE CASES ---");

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

    console.log("\n--- REPEATED CHARACTERS ---");

    runTest(
        "AAAAA",
        "AA",
        [0, 1, 2, 3],
        "Repeated overlapping matches"
    );

    runTest(
        "AAAA",
        "AA",
        [0, 1, 2],
        "Consecutive matches"
    );
}


main();