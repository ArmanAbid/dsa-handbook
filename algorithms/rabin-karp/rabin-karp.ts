const BASE = 256;
const MOD = 1_000_000_007;

function rabinKarpSearch(
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

    // Calculate BASE^(m - 1) modulo MOD.
    let highestPower = 1;

    for (let i = 1; i < m; i++) {
        highestPower = (highestPower * BASE) % MOD;
    }

    let patternHash = 0;
    let windowHash = 0;

    // Calculate initial hashes.
    for (let i = 0; i < m; i++) {
        patternHash = (
            patternHash * BASE + pattern.charCodeAt(i)
        ) % MOD;

        windowHash = (
            windowHash * BASE + text.charCodeAt(i)
        ) % MOD;
    }

    // Slide the window across the text.
    for (let i = 0; i <= n - m; i++) {

        // A matching hash is only a candidate.
        // Verify the actual characters to handle collisions.
        if (patternHash === windowHash) {
            if (text.slice(i, i + m) === pattern) {
                positions.push(i);
            }
        }

        // Update the hash for the next window.
        if (i < n - m) {
            const outgoing = (
                text.charCodeAt(i) * highestPower
            ) % MOD;

            windowHash = (
                windowHash - outgoing + MOD
            ) % MOD;

            windowHash = (
                windowHash * BASE + text.charCodeAt(i + m)
            ) % MOD;
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
    const result = rabinKarpSearch(text, pattern);

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
    console.log("=== RABIN-KARP STRING MATCHING ===");

    console.log("\n--- BASIC SEARCH ---");

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
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        [10],
        "Single match"
    );

    runTest(
        "HELLO WORLD",
        "WORLD",
        [6],
        "Match near end"
    );

    runTest(
        "AAAAA",
        "AA",
        [0, 1, 2, 3],
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
