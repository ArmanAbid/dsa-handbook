interface Interval {
    start: number;
    end: number;
}

function mergeIntervals(
    intervals: readonly Interval[]
): Interval[] | null {
    // Validate intervals before processing.
    for (const interval of intervals) {
        if (
            !Number.isSafeInteger(interval.start) ||
            !Number.isSafeInteger(interval.end) ||
            interval.start > interval.end
        ) {
            return null;
        }
    }

    // Copy the input so we do not modify the original array.
    const sorted = intervals.map(interval => ({
        start: interval.start,
        end: interval.end
    }));

    // Sort by starting point, then ending point.
    sorted.sort((a, b) => {
        return (a.start - b.start) || (a.end - b.end);
    });

    const merged: Interval[] = [];

    for (const current of sorted) {
        const previous = merged[merged.length - 1];

        if (
            previous === undefined ||
            current.start > previous.end
        ) {
            // No overlap: add a new interval.
            merged.push({
                start: current.start,
                end: current.end
            });
        } else {
            // Overlap: extend the previous interval.
            if (current.end > previous.end) {
                previous.end = current.end;
            }
        }
    }

    return merged;
}

function testMerge(
    intervals: readonly Interval[],
    expected: readonly Interval[],
    label: string
): void {
    const result = mergeIntervals(intervals);

    const passed =
        result !== null &&
        result.length === expected.length &&
        result.every((interval, index) => {
            const expectedInterval = expected[index];

            return (
                expectedInterval !== undefined &&
                interval.start === expectedInterval.start &&
                interval.end === expectedInterval.end
            );
        });

    console.log(
        `${label}: ${result === null
            ? "Invalid input"
            : JSON.stringify(result)
        } ${passed ? "[PASSED]" : "[FAILED]"}`
    );
}

function main(): void {
    console.log("=== MERGE INTERVALS ===");

    console.log("\n--- BASIC EXAMPLE ---");

    const intervals: Interval[] = [
        { start: 1, end: 3 },
        { start: 2, end: 6 },
        { start: 8, end: 10 },
        { start: 15, end: 18 }
    ];

    console.log(`Original intervals: ${JSON.stringify(intervals)}`);

    const merged = mergeIntervals(intervals);

    console.log(`Merged intervals: ${JSON.stringify(merged)}`);

    console.log("\n--- TEST CASES ---");

    testMerge(
        [
            { start: 8, end: 10 },
            { start: 1, end: 3 },
            { start: 15, end: 18 },
            { start: 2, end: 6 }
        ],
        [
            { start: 1, end: 6 },
            { start: 8, end: 10 },
            { start: 15, end: 18 }
        ],
        "Unsorted intervals"
    );

    testMerge(
        [
            { start: 1, end: 4 },
            { start: 4, end: 5 }
        ],
        [
            { start: 1, end: 5 }
        ],
        "Touching intervals"
    );

    testMerge(
        [
            { start: 1, end: 2 },
            { start: 4, end: 5 },
            { start: 7, end: 8 }
        ],
        [
            { start: 1, end: 2 },
            { start: 4, end: 5 },
            { start: 7, end: 8 }
        ],
        "Non-overlapping intervals"
    );

    testMerge(
        [
            { start: 1, end: 10 },
            { start: 2, end: 3 },
            { start: 4, end: 8 }
        ],
        [
            { start: 1, end: 10 }
        ],
        "Nested intervals"
    );

    testMerge(
        [
            { start: 1, end: 4 },
            { start: 1, end: 2 },
            { start: 1, end: 5 }
        ],
        [
            { start: 1, end: 5 }
        ],
        "Same starting points"
    );

    testMerge(
        [{ start: 5, end: 7 }],
        [{ start: 5, end: 7 }],
        "Single interval"
    );

    testMerge(
        [],
        [],
        "Empty input"
    );

    console.log("\n--- INVALID INPUT ---");

    const invalid: Interval[] = [
        { start: 1, end: 3 },
        { start: 5, end: 2 }
    ];

    const invalidResult = mergeIntervals(invalid);

    console.log(
        `Invalid interval: ${invalidResult === null ? "Rejected" : "Accepted"
        } ${invalidResult === null ? "[PASSED]" : "[FAILED]"
        }`
    );

    console.log("\n--- SAFE INTEGER VALIDATION ---");

    const unsafe: Interval[] = [
        { start: Number.MAX_SAFE_INTEGER + 1, end: Number.MAX_SAFE_INTEGER + 2 }
    ];

    const unsafeResult = mergeIntervals(unsafe);

    console.log(
        `Unsafe integer: ${unsafeResult === null ? "Rejected" : "Accepted"
        } ${unsafeResult === null ? "[PASSED]" : "[FAILED]"
        }`
    );
}

main();