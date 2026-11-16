#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Interval {
    int start;
    int end;

    Interval(int s, int e) {
        start = s;
        end = e;
    }
};

// Sort by starting point, then by ending point.
bool compareIntervals(const Interval& a, const Interval& b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }

    return a.end < b.end;
}

bool mergeIntervals(
    const vector<Interval>& intervals,
    vector<Interval>& merged
) {
    // Validate intervals before processing.
    for (size_t i = 0; i < intervals.size(); i++) {
        if (intervals[i].start > intervals[i].end) {
            return false;
        }
    }

    if (intervals.empty()) {
        merged.clear();
        return true;
    }

    // Work on a copy so the original input remains unchanged.
    vector<Interval> sorted = intervals;

    sort(
        sorted.begin(),
        sorted.end(),
        compareIntervals
    );

    vector<Interval> result;

    for (size_t i = 0; i < sorted.size(); i++) {
        const Interval& current = sorted[i];

        if (
            result.empty() ||
            current.start > result.back().end
        ) {
            // No overlap: add a new interval.
            result.push_back(current);
        } else {
            // Overlap: extend the previous interval if needed.
            if (current.end > result.back().end) {
                result.back().end = current.end;
            }
        }
    }

    merged = result;
    return true;
}

void printIntervals(const vector<Interval>& intervals) {
    cout << "[";

    for (size_t i = 0; i < intervals.size(); i++) {
        cout << "[" << intervals[i].start
             << ", " << intervals[i].end << "]";

        if (i + 1 < intervals.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

bool intervalsEqual(
    const vector<Interval>& a,
    const vector<Interval>& b
) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++) {
        if (
            a[i].start != b[i].start ||
            a[i].end != b[i].end
        ) {
            return false;
        }
    }

    return true;
}

void testMerge(
    const vector<Interval>& input,
    const vector<Interval>& expected,
    const string& label
) {
    vector<Interval> result;

    bool valid = mergeIntervals(input, result);
    bool passed = valid && intervalsEqual(result, expected);

    cout << label << ": ";
    printIntervals(result);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}

int main() {
    cout << "==== MERGE INTERVALS ====" << endl;

    cout << "\n--- BASIC EXAMPLE ---" << endl;

    vector<Interval> intervals;
    intervals.push_back(Interval(1, 3));
    intervals.push_back(Interval(2, 6));
    intervals.push_back(Interval(8, 10));
    intervals.push_back(Interval(15, 18));

    cout << "Original intervals: ";
    printIntervals(intervals);
    cout << endl;

    vector<Interval> merged;

    bool valid = mergeIntervals(intervals, merged);

    cout << "Merged intervals: ";
    printIntervals(merged);
    cout << (valid ? " [PASSED]" : " [FAILED]") << endl;

    cout << "\n--- TEST CASES ---" << endl;

    vector<Interval> unsorted;
    unsorted.push_back(Interval(8, 10));
    unsorted.push_back(Interval(1, 3));
    unsorted.push_back(Interval(15, 18));
    unsorted.push_back(Interval(2, 6));

    vector<Interval> basicExpected;
    basicExpected.push_back(Interval(1, 6));
    basicExpected.push_back(Interval(8, 10));
    basicExpected.push_back(Interval(15, 18));

    testMerge(
        unsorted,
        basicExpected,
        "Unsorted intervals"
    );

    vector<Interval> touching;
    touching.push_back(Interval(1, 4));
    touching.push_back(Interval(4, 5));

    vector<Interval> touchingExpected;
    touchingExpected.push_back(Interval(1, 5));

    testMerge(
        touching,
        touchingExpected,
        "Touching intervals"
    );

    vector<Interval> separate;
    separate.push_back(Interval(1, 2));
    separate.push_back(Interval(4, 5));
    separate.push_back(Interval(7, 8));

    testMerge(
        separate,
        separate,
        "Non-overlapping intervals"
    );

    vector<Interval> nested;
    nested.push_back(Interval(1, 10));
    nested.push_back(Interval(2, 3));
    nested.push_back(Interval(4, 8));

    vector<Interval> nestedExpected;
    nestedExpected.push_back(Interval(1, 10));

    testMerge(
        nested,
        nestedExpected,
        "Nested intervals"
    );

    vector<Interval> sameStart;
    sameStart.push_back(Interval(1, 4));
    sameStart.push_back(Interval(1, 2));
    sameStart.push_back(Interval(1, 5));

    vector<Interval> sameStartExpected;
    sameStartExpected.push_back(Interval(1, 5));

    testMerge(
        sameStart,
        sameStartExpected,
        "Same starting points"
    );

    vector<Interval> single;
    single.push_back(Interval(5, 7));

    testMerge(
        single,
        single,
        "Single interval"
    );

    vector<Interval> empty;
    testMerge(
        empty,
        empty,
        "Empty input"
    );

    cout << "\n--- INVALID INPUT ---" << endl;

    vector<Interval> invalid;
    invalid.push_back(Interval(1, 3));
    invalid.push_back(Interval(5, 2));

    vector<Interval> output;
    output.push_back(Interval(99, 100));

    vector<Interval> originalOutput = output;

    bool accepted = mergeIntervals(invalid, output);
    bool unchanged = intervalsEqual(output, originalOutput);

    bool passed = !accepted && unchanged;

    cout << "Invalid interval: "
         << (passed ? "Rejected, output unchanged" : "FAILED")
         << (passed ? " [PASSED]" : " [FAILED]")
         << endl;

    return 0;
}