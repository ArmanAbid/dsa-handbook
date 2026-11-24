function longestCommonSubsequence(
    first: string,
    second: string
): string {
    const n = first.length;
    const m = second.length;

    // Create an (n + 1) x (m + 1) DP table.
    const dp: number[][] = Array.from(
        { length: n + 1 },
        () => new Array<number>(m + 1).fill(0)
    );

    // Fill the DP table.
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= m; j++) {

            if (first.charAt(i - 1) === second.charAt(j - 1)) {
                dp[i]![j] = dp[i - 1]![j - 1]! + 1;

            } else {
                dp[i]![j] = Math.max(
                    dp[i - 1]![j]!,
                    dp[i]![j - 1]!
                );
            }
        }
    }

    // Reconstruct the subsequence.
    const result: string[] = [];

    let i = n;
    let j = m;

    while (i > 0 && j > 0) {

        if (first.charAt(i - 1) === second.charAt(j - 1)) {
            result.push(first.charAt(i - 1));

            i--;
            j--;

        } else if (dp[i - 1]![j]! >= dp[i]![j - 1]!) {
            i--;

        } else {
            j--;
        }
    }

    // Reconstruction happens backwards.
    result.reverse();

    return result.join("");
}


function runTest(
    first: string,
    second: string,
    expected: string,
    testName: string
): void {
    const result = longestCommonSubsequence(first, second);

    const passed = result === expected;

    console.log(
        `${testName}: ${result} ` +
        `(length ${result.length}) ` +
        `[${passed ? "PASSED" : "FAILED"}]`
    );

    if (!passed) {
        console.log(`  Expected: ${expected}`);
    }
}


function main(): void {
    console.log("==== LONGEST COMMON SUBSEQUENCE ====");

    console.log("\n--- BASIC EXAMPLES ---");

    runTest("ABC", "AC", "AC", "Simple example");

    runTest(
        "AGGTAB",
        "GXTXAYB",
        "GTAB",
        "Classic example"
    );

    runTest(
        "ABCDEF",
        "ACE",
        "ACE",
        "Characters with gaps"
    );

    console.log("\n--- ADDITIONAL CASES ---");

    runTest("ABCD", "AEBD", "ABD", "Different lengths");
    runTest("HELLO", "WORLD", "L", "Single common character");
    runTest("ABC", "ABC", "ABC", "Identical strings");
    runTest("AAAA", "AA", "AA", "Repeated characters");
    runTest("ABC", "DEF", "", "No common characters");

    console.log("\n--- EDGE CASES ---");

    runTest("", "", "", "Both empty");
    runTest("ABC", "", "", "Second string empty");
    runTest("", "ABC", "", "First string empty");
}


main();
