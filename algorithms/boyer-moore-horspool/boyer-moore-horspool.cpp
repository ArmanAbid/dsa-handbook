#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Builds the shift table for all possible byte values.
vector<size_t> buildShiftTable(const string& pattern) {
    size_t m = pattern.length();

    // Default shift: the entire pattern length.
    vector<size_t> shift(256, m);

    // Exclude the last character from preprocessing.
    for (size_t i = 0; i + 1 < m; i++) {
        unsigned char c =
            static_cast<unsigned char>(pattern[i]);

        shift[c] = m - 1 - i;
    }

    return shift;
}

// Finds every occurrence of pattern inside text.
vector<size_t> boyerMooreHorspoolSearch(
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

    // Preprocess the pattern.
    vector<size_t> shift = buildShiftTable(pattern);

    size_t start = 0;

    while (start <= n - m) {
        size_t j = m;

        // Compare from right to left.
        while (
            j > 0 &&
            pattern[j - 1] == text[start + j - 1]
        ) {
            j--;
        }

        // Entire pattern matched.
        if (j == 0) {
            positions.push_back(start);
        }

        // Shift using the last character of the text window.
        unsigned char lastChar =
            static_cast<unsigned char>(text[start + m - 1]);

        start += shift[lastChar];
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

// Runs and verifies a test.
void runTest(
    const string& text,
    const string& pattern,
    const vector<size_t>& expected,
    const string& testName
) {
    vector<size_t> result =
        boyerMooreHorspoolSearch(text, pattern);

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

// Prints a shift table for the provided pattern.
void printShiftTable(const string& pattern) {
    vector<size_t> shift = buildShiftTable(pattern);

    cout << "Pattern: " << pattern << endl;
    cout << "Character shifts:" << endl;

    for (size_t i = 0; i + 1 < pattern.length(); i++) {
        unsigned char c =
            static_cast<unsigned char>(pattern[i]);

        // Print a character only at its rightmost occurrence
        // before the final pattern position.
        bool isLastOccurrence = true;

        for (size_t j = i + 1; j + 1 < pattern.length(); j++) {
            if (pattern[j] == pattern[i]) {
                isLastOccurrence = false;
                break;
            }
        }

        if (isLastOccurrence) {
            cout << pattern[i] << " -> " << shift[c] << endl;
        }
    }
}

int main() {
    cout << "==== BOYER-MOORE-HORSPOOL ====" << endl;

    cout << "\n--- SHIFT TABLE ---" << endl;

    printShiftTable("ABC");

    cout << "\n--- BASIC SEARCH ---" << endl;

    vector<size_t> expected;

    expected.push_back(4);
    runTest(
        "ABAAABCD",
        "ABC",
        expected,
        "Shift-based search"
    );

    expected.clear();
    expected.push_back(17);
    runTest(
        "HERE IS A SIMPLE EXAMPLE",
        "EXAMPLE",
        expected,
        "Classic example"
    );

    expected.clear();
    expected.push_back(0);
    expected.push_back(2);
    runTest(
        "ABABA",
        "ABA",
        expected,
        "Overlapping matches"
    );

    expected.clear();
    expected.push_back(1);
    expected.push_back(3);
    runTest(
        "BANANA",
        "ANA",
        expected,
        "Multiple matches"
    );

    expected.clear();
    expected.push_back(1);
    expected.push_back(4);
    runTest(
        "mississippi",
        "issi",
        expected,
        "Repeated characters"
    );

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    runTest(
        "AAAAA",
        "AAA",
        expected,
        "Repeated overlapping matches"
    );

    cout << "\n--- EDGE CASES ---" << endl;

    expected.clear();
    runTest("ABCDEF", "XYZ", expected, "No match");

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

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    runTest("aaaa", "a", expected, "Single-character pattern");

    return 0;
}