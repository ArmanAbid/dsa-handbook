#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Finds every occurrence of pattern inside text.
vector<size_t> naiveStringSearch(
    const string& text,
    const string& pattern
) {
    vector<size_t> positions;

    size_t n = text.length();
    size_t m = pattern.length();

    // An empty pattern matches every boundary position.
    if (m == 0) {
        for (size_t i = 0; i <= n; i++) {
            positions.push_back(i);
        }
        return positions;
    }

    // Pattern cannot fit inside the text.
    if (m > n) {
        return positions;
    }

    // Try every possible starting position.
    for (size_t i = 0; i <= n - m; i++) {
        size_t j = 0;

        // Compare characters one by one.
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }

        // Entire pattern matched.
        if (j == m) {
            positions.push_back(i);
        }
    }

    return positions;
}

// Compares two result vectors.
bool areEqual(
    const vector<size_t>& first,
    const vector<size_t>& second
) {
    if (first.size() != second.size()) {
        return false;
    }

    for (size_t i = 0; i < first.size(); i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

// Prints matching indices.
void printPositions(const vector<size_t>& positions) {
    cout << "[";

    for (size_t i = 0; i < positions.size(); i++) {
        cout << positions[i];

        if (i + 1 < positions.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

// Runs and verifies one test case.
void runTest(
    const string& text,
    const string& pattern,
    const vector<size_t>& expected,
    const string& testName
) {
    vector<size_t> result = naiveStringSearch(text, pattern);

    bool passed = areEqual(result, expected);

    cout << testName << ": ";
    printPositions(result);

    cout << (passed ? " [PASSED]" : " [FAILED]");

    if (!passed) {
        cout << " Expected: ";
        printPositions(expected);
    }

    cout << endl;
}

int main() {
    cout << "==== NAIVE STRING MATCHING ====" << endl;

    cout << "\n--- BASIC SEARCH ---" << endl;

    vector<size_t> expected;

    expected.push_back(0);
    expected.push_back(2);
    runTest("ABABA", "ABA", expected, "Overlapping matches");

    expected.clear();
    expected.push_back(10);
    runTest(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        expected,
        "Single match"
    );

    expected.clear();
    runTest("ABCDEF", "XYZ", expected, "No match");

    expected.clear();
    expected.push_back(6);
    runTest("HELLO WORLD", "WORLD", expected, "Match near end");

    cout << "\n--- EDGE CASES ---" << endl;

    expected.clear();
    runTest("ABC", "ABCDE", expected, "Pattern longer than text");

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    runTest("ABC", "", expected, "Empty pattern");

    expected.clear();
    expected.push_back(0);
    runTest("", "", expected, "Both empty");

    expected.clear();
    runTest("", "A", expected, "Empty text");

    cout << "\n--- REPEATED CHARACTERS ---" << endl;

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    runTest("AAAAA", "AA", expected, "Repeated overlapping matches");

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    runTest("AAAA", "AA", expected, "Consecutive matches");

    return 0;
}
