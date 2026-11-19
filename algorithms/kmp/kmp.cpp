#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Builds the Longest Proper Prefix which is also a Suffix array.
vector<size_t> buildLPS(const string& pattern) {
    size_t m = pattern.length();

    vector<size_t> lps(m, 0);

    size_t length = 0;
    size_t i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else if (length != 0) {
            length = lps[length - 1];
        }
        else {
            lps[i] = 0;
            i++;
        }
    }

    return lps;
}

// Finds all occurrences of pattern inside text using KMP.
vector<size_t> kmpSearch(
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
    vector<size_t> lps = buildLPS(pattern);

    size_t i = 0; // Text pointer
    size_t j = 0; // Pattern pointer

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            // Entire pattern matched.
            if (j == m) {
                positions.push_back(i - j);

                // Continue searching for overlapping matches.
                j = lps[j - 1];
            }
        }
        else if (j != 0) {
            // Reuse previously matched prefix information.
            j = lps[j - 1];
        }
        else {
            // No prefix information to reuse.
            i++;
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

// Prints a vector of indices.
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
    vector<size_t> result = kmpSearch(text, pattern);

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

// Prints an LPS array.
void printLPS(const vector<size_t>& lps) {
    cout << "[";

    for (size_t i = 0; i < lps.size(); i++) {
        cout << lps[i];

        if (i + 1 < lps.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

int main() {
    cout << "=== KMP STRING MATCHING ===" << endl;

    cout << "\n--- LPS CONSTRUCTION ---" << endl;

    vector<size_t> lps = buildLPS("ABABC");

    cout << "Pattern: ABABC" << endl;
    cout << "LPS: ";
    printLPS(lps);
    cout << endl;

    cout << "\n--- BASIC SEARCH ---" << endl;

    vector<size_t> expected;

    expected.push_back(2);
    runTest(
        "ABABABC",
        "ABABC",
        expected,
        "LPS fallback example"
    );

    expected.clear();
    expected.push_back(10);
    runTest(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        expected,
        "Standard KMP example"
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
    expected.push_back(0);
    expected.push_back(3);
    expected.push_back(6);
    runTest(
        "ABCABCABC",
        "ABC",
        expected,
        "Multiple matches"
    );

    expected.clear();
    expected.push_back(5);
    runTest(
        "AAAAAAAAAB",
        "AAAAB",
        expected,
        "Repeated prefix characters"
    );

    cout << "\n--- EDGE CASES ---" << endl;

    expected.clear();
    runTest(
        "ABCDEF",
        "XYZ",
        expected,
        "No match"
    );

    expected.clear();
    runTest(
        "ABC",
        "ABCDE",
        expected,
        "Pattern longer than text"
    );

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    runTest(
        "ABC",
        "",
        expected,
        "Empty pattern"
    );

    expected.clear();
    expected.push_back(0);
    runTest(
        "",
        "",
        expected,
        "Both empty"
    );

    expected.clear();
    runTest(
        "",
        "A",
        expected,
        "Empty text"
    );

    return 0;
}
