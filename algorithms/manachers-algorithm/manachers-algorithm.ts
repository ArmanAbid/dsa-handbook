interface ManacherResult {
    odd: number[];
    even: number[];
    start: number;
    length: number;
    longest: string;
}

// Calculates odd-length palindrome radii.
function oddRadii(text: string): number[] {
    const n = text.length;
    const odd: number[] = new Array<number>(n).fill(0);

    let left = 0;
    let right = -1;

    for (let i = 0; i < n; i++) {
        let radius: number;

        // Reuse information from the current palindrome.
        if (i > right) {
            radius = 1;
        } else {
            const mirror = left + right - i;
            const remaining = right - i + 1;

            radius = Math.min(
                odd[mirror] ?? 0,
                remaining
            );
        }

        // Expand around the current character.
        while (
            i - radius >= 0 &&
            i + radius < n &&
            text.charAt(i - radius) === text.charAt(i + radius)
        ) {
            radius++;
        }

        odd[i] = radius;

        // Update the rightmost palindrome.
        if (i + radius - 1 > right) {
            left = i - radius + 1;
            right = i + radius - 1;
        }
    }

    return odd;
}


// Calculates even-length palindrome radii.
function evenRadii(text: string): number[] {
    const n = text.length;
    const even: number[] = new Array<number>(n).fill(0);

    let left = 0;
    let right = -1;

    for (let i = 0; i < n; i++) {
        let radius: number;

        // Reuse information from the current palindrome.
        if (i > right) {
            radius = 0;
        } else {
            const mirror = left + right - i + 1;
            const remaining = right - i + 1;

            radius = Math.min(
                even[mirror] ?? 0,
                remaining
            );
        }

        // Expand around the gap before the current character.
        while (
            i - radius - 1 >= 0 &&
            i + radius < n &&
            text.charAt(i - radius - 1) === text.charAt(i + radius)
        ) {
            radius++;
        }

        even[i] = radius;

        // Update the rightmost palindrome.
        if (i + radius - 1 > right) {
            left = i - radius;
            right = i + radius - 1;
        }
    }

    return even;
}


// Calculates both radius arrays and finds the longest palindrome.
function manacher(text: string): ManacherResult {
    const odd = oddRadii(text);
    const even = evenRadii(text);

    let bestStart = 0;
    let bestLength = 0;

    // Check odd-length palindromes.
    for (let i = 0; i < text.length; i++) {
        const length = 2 * (odd[i] ?? 0) - 1;
        const start = i - (odd[i] ?? 0) + 1;

        if (
            length > bestLength ||
            (length === bestLength && start < bestStart)
        ) {
            bestStart = start;
            bestLength = length;
        }
    }

    // Check even-length palindromes.
    for (let i = 0; i < text.length; i++) {
        const length = 2 * (even[i] ?? 0);
        const start = i - (even[i] ?? 0);

        if (
            length > bestLength ||
            (length === bestLength && start < bestStart)
        ) {
            bestStart = start;
            bestLength = length;
        }
    }

    return {
        odd,
        even,
        start: bestStart,
        length: bestLength,
        longest: text.substring(bestStart, bestStart + bestLength)
    };
}


// Verifies both radius arrays.
function runRadiusTest(
    text: string,
    expectedOdd: number[],
    expectedEven: number[],
    testName: string
): void {
    const odd = oddRadii(text);
    const even = evenRadii(text);

    const passed =
        odd.length === expectedOdd.length &&
        even.length === expectedEven.length &&
        odd.every((value, index) => value === expectedOdd[index]) &&
        even.every((value, index) => value === expectedEven[index]);

    console.log(
        `${testName}: Odd = [${odd.join(", ")}], ` +
        `Even = [${even.join(", ")}] ` +
        `[${passed ? "PASSED" : "FAILED"}]`
    );
}


// Verifies the longest palindrome.
function runTest(
    text: string,
    expectedLongest: string,
    expectedStart: number,
    expectedLength: number,
    testName: string
): void {
    const result = manacher(text);

    const passed =
        result.longest === expectedLongest &&
        result.start === expectedStart &&
        result.length === expectedLength;

    console.log(
        `${testName}: Longest = "${result.longest}", ` +
        `Start = ${result.start}, Length = ${result.length} ` +
        `[${passed ? "PASSED" : "FAILED"}]`
    );

    if (!passed) {
        console.log(`  Expected: "${expectedLongest}" at ${expectedStart}`);
    }
}


function main(): void {
    console.log("==== MANACHER'S ALGORITHM ====");

    console.log("\n--- RADIUS ARRAYS ---");

    runRadiusTest(
        "abacaba",
        [1, 2, 1, 4, 1, 2, 1],
        [0, 0, 0, 0, 0, 0, 0],
        "Odd palindrome radii"
    );

    runRadiusTest(
        "abba",
        [1, 1, 1, 1],
        [0, 0, 2, 0],
        "Even palindrome radii"
    );

    console.log("\n--- LONGEST PALINDROMES ---");

    runTest("babad", "bab", 0, 3, "Odd-length palindrome");
    runTest("cbbd", "bb", 1, 2, "Even-length palindrome");
    runTest("abba", "abba", 0, 4, "Entire string is a palindrome");
    runTest("aaaaa", "aaaaa", 0, 5, "Repeated characters");
    runTest("racecar", "racecar", 0, 7, "Classic palindrome");
    runTest("abc", "a", 0, 1, "No palindrome longer than one");

    runTest(
        "abacdfgdcaba",
        "aba",
        0,
        3,
        "Multiple longest palindromes"
    );

    console.log("\n--- EDGE CASES ---");

    runTest("", "", 0, 0, "Empty string");
    runTest("x", "x", 0, 1, "Single character");
    runTest("aabbaa", "aabbaa", 0, 6, "Long even palindrome");
}


main();
