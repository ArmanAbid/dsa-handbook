function buildShiftTable(pattern: string): Map<string, number> {
    const m = pattern.length;

    const shift = new Map<string, number>();

    // Exclude the final character.
    for (let i = 0; i < m - 1; i++) {
        shift.set(
            pattern.charAt(i),
            m - 1 - i
        );
    }

    return shift;
}


function boyerMooreHorspoolSearch(
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

    // Preprocess the pattern.
    const shift = buildShiftTable(pattern);

    let start = 0;

    while (start <= n - m) {
        let j = m - 1;

        // Compare from right to left.
        while (
            j >= 0 &&
            pattern.charAt(j) === text.charAt(start + j)
        ) {
            j--;
        }

        // Entire pattern matched.
        if (j < 0) {
            positions.push(start);
        }

        // Shift using the last character of the text window.
        const lastChar = text.charAt(start + m - 1);

        start += shift.get(lastChar) ?? m;
    }

    return positions;
}


function runTest(
    text: string,
    pattern: string,
    expected: number[],
    testName: string
): void {
    const result = boyerMooreHorspoolSearch(text, pattern);

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
    console.log("==== BOYER-MOORE-HORSPOOL ====");

    console.log("\n--- SHIFT TABLE ---");

    console.log("Pattern: ABC");
    console.log(
        `Character shifts: ${JSON.stringify(
            Object.fromEntries(buildShiftTable("ABC"))
        )}`
    );

    console.log("\n--- BASIC SEARCH ---");

    runTest(
        "ABAAABCD",
        "ABC",
        [4],
        "Shift-based search"
    );

    runTest(
        "HERE IS A SIMPLE EXAMPLE",
        "EXAMPLE",
        [17],
        "Classic example"
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
        "mississippi",
        "issi",
        [1, 4],
        "Repeated characters"
    );

    runTest(
        "AAAAA",
        "AAA",
        [0, 1, 2],
        "Repeated overlapping matches"
    );

    console.log("\n--- EDGE CASES ---");

    runTest("ABCDEF", "XYZ", [], "No match");
    runTest("ABC", "ABCDE", [], "Pattern longer than text");
    runTest("ABC", "", [0, 1, 2, 3], "Empty pattern");
    runTest("", "", [0], "Both empty");
    runTest("", "A", [], "Empty text");
    runTest("aaaa", "a", [0, 1, 2, 3], "Single-character pattern");
}


main();

export { };
