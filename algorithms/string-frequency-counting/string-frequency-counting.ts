function characterFrequency(text: string): number[] | null {
    const frequency: number[] = new Array(26).fill(0);

    for (const character of text) {
        const code = character.charCodeAt(0);

        // Only lowercase English letters are supported.
        if (code < 97 || code > 122) {
            return null;
        }

        const index = code - 97;

        const currentCount = frequency[index];

        if (currentCount === undefined) {
            return null;
        }

        frequency[index] = currentCount + 1;
    }

    return frequency;
}

function printFrequency(frequency: number[]): void {
    for (let i = 0; i < 26; i++) {
        const count = frequency[i];

        if (count !== undefined && count > 0) {
            const character = String.fromCharCode(97 + i);
            console.log(`${character} -> ${count}`);
        }
    }
}

function testFrequency(
    text: string,
    expected: number[],
    label: string
): void {
    const result = characterFrequency(text);

    const passed =
        result !== null &&
        result.length === expected.length &&
        result.every((count, index) => count === expected[index]);

    console.log(
        `${label}: ${passed ? "[PASSED]" : "[FAILED]"}`
    );
}

function main(): void {
    console.log("==== CHARACTER FREQUENCY COUNTING ====");

    console.log("\n--- BASIC EXAMPLE ---");

    const text = "banana";

    console.log(`Input: ${text}`);

    const frequency = characterFrequency(text);

    if (frequency !== null) {
        console.log("Character frequencies:");
        printFrequency(frequency);
    }

    console.log("\n--- TEST CASES ---");

    const bananaExpected = new Array<number>(26).fill(0);
    bananaExpected[0] = 3;
    bananaExpected[1] = 1;
    bananaExpected[13] = 2;

    testFrequency(
        "banana",
        bananaExpected,
        "Repeated characters"
    );

    testFrequency(
        "abcdefghijklmnopqrstuvwxyz",
        new Array<number>(26).fill(1),
        "All lowercase letters"
    );

    const singleExpected = new Array<number>(26).fill(0);
    singleExpected[25] = 1;

    testFrequency(
        "z",
        singleExpected,
        "Single character"
    );

    testFrequency(
        "",
        new Array<number>(26).fill(0),
        "Empty string"
    );

    const repeatedExpected = new Array<number>(26).fill(0);
    repeatedExpected[2] = 5;

    testFrequency(
        "ccccc",
        repeatedExpected,
        "All characters identical"
    );

    console.log("\n--- INVALID INPUT ---");

    const uppercaseResult = characterFrequency("Banana");

    console.log(
        `Uppercase character: ${uppercaseResult === null
            ? "Rejected [PASSED]"
            : "Accepted [FAILED]"
        }`
    );

    const numericResult = characterFrequency("hello123");

    console.log(
        `Numeric characters: ${numericResult === null
            ? "Rejected [PASSED]"
            : "Accepted [FAILED]"
        }`
    );
}

main();