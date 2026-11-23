function levenshteinDistance(
    first: string,
    second: string
): number {
    // Use the shorter string as the columns.
    let rows = first;
    let columns = second;

    if (columns.length > rows.length) {
        rows = second;
        columns = first;
    }

    const n = rows.length;
    const m = columns.length;

    // Initial row: converting an empty string into each prefix.
    let previous: number[] = Array.from(
        { length: m + 1 },
        (_, index) => index
    );

    let current: number[] = new Array<number>(m + 1).fill(0);

    for (let i = 1; i <= n; i++) {
        // Initial column: deleting i characters.
        current[0] = i;

        for (let j = 1; j <= m; j++) {

            if (rows.charAt(i - 1) === columns.charAt(j - 1)) {
                // Characters match: no additional edit.
                current[j] = previous[j - 1] as number;

            } else {
                // Three possible operations.
                const deletion = previous[j] as number;
                const insertion = current[j - 1] as number;
                const substitution = previous[j - 1] as number;

                current[j] = 1 + Math.min(
                    deletion,
                    insertion,
                    substitution
                );
            }
        }

        // Move to the next row.
        [previous, current] = [current, previous];
    }

    return previous[m] as number;
}


function runTest(
    first: string,
    second: string,
    expected: number,
    testName: string
): void {
    const result = levenshteinDistance(first, second);

    const passed = result === expected;

    console.log(
        `${testName}: ${result} ` +
        `[${passed ? "PASSED" : "FAILED"}]`
    );

    if (!passed) {
        console.log(`  Expected: ${expected}`);
    }
}


function main(): void {
    console.log("==== LEVENSHTEIN DISTANCE ====");

    console.log("\n--- BASIC EXAMPLES ---");

    runTest("kitten", "sitting", 3, "Kitten to sitting");
    runTest("saturday", "sunday", 3, "Saturday to Sunday");
    runTest("flaw", "lawn", 2, "Flaw to lawn");
    runTest("intention", "execution", 5, "Classic example");

    console.log("\n--- EDIT OPERATIONS ---");

    runTest("cat", "cut", 1, "Substitution");
    runTest("cat", "cart", 1, "Insertion");
    runTest("cart", "cat", 1, "Deletion");

    console.log("\n--- ADDITIONAL CASES ---");

    runTest("Cat", "cat", 1, "Case-sensitive comparison");
    runTest("book", "back", 2, "Multiple substitutions");
    runTest("algorithm", "algorithm", 0, "Identical strings");
    runTest("ab", "ba", 2, "Two substitutions");
    runTest("form", "from", 2, "Transposition is two edits");

    console.log("\n--- EDGE CASES ---");

    runTest("", "", 0, "Both empty");
    runTest("", "abc", 3, "First string empty");
    runTest("abc", "", 3, "Second string empty");
}

main();
