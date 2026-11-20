#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Builds the Z array for an integer sequence.
vector<size_t> buildZArray(const vector<int>& sequence) {
    size_t n = sequence.size();

    vector<size_t> z(n, 0);

    // Current Z box: [left, right].
    size_t left = 0;
    size_t right = 0;

    for (size_t i = 1; i < n; i++) {

        // Reuse information from the current Z box.
        if (i <= right) {
            size_t mirror = i - left;
            size_t remaining = right - i + 1;

            z[i] = z[mirror] < remaining
                ? z[mirror]
                : remaining;
        }

        // Extend the match beyond the current Z box.
        while (
            i + z[i] < n &&
            sequence[z[i]] == sequence[i + z[i]]
        ) {
            z[i]++;
        }

        // Update the Z box if this match extends farther.
        if (z[i] > 0 && i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }

    return z;
}

// Finds every occurrence of pattern inside text.
vector<size_t> zSearch(
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

    // Build: pattern + separator + text.
    // Character values are 0..255; -1 cannot collide.
    vector<int> combined;

    combined.reserve(m + 1 + n);

    for (size_t i = 0; i < m; i++) {
        combined.push_back(
            static_cast<unsigned char>(pattern[i])
        );
    }

    combined.push_back(-1);

    for (size_t i = 0; i < n; i++) {
        combined.push_back(
            static_cast<unsigned char>(text[i])
        );
    }

    // Calculate the Z array.
    vector<size_t> z = buildZArray(combined);

    // Find positions where the entire pattern matches.
    for (size_t i = m + 1; i < combined.size(); i++) {
        if (z[i] >= m) {
            positions.push_back(i - m - 1);
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

// Runs and verifies one test.
void runTest(
    const string& text,
    const string& pattern,
    const vector<size_t>& expected,
    const string& testName
) {
    vector<size_t> result = zSearch(text, pattern);

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

// Prints a Z array.
void printZArray(const vector<size_t>& z) {
    cout << "[";

    for (size_t i = 0; i < z.size(); i++) {
        cout << z[i];

        if (i + 1 < z.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

int main() {
    cout << "==== Z ALGORITHM ====" << endl;

    cout << "\n--- Z ARRAY CONSTRUCTION ---" << endl;

    vector<int> sample;

    sample.push_back(65); // A
    sample.push_back(66); // B
    sample.push_back(65); // A
    sample.push_back(66); // B
    sample.push_back(65); // A
    sample.push_back(67); // C

    vector<size_t> sampleZ = buildZArray(sample);

    cout << "String: ABABAC" << endl;
    cout << "Z array: ";
    printZArray(sampleZ);
    cout << endl;

    cout << "\n--- BASIC SEARCH ---" << endl;

    vector<size_t> expected;

    expected.push_back(2);
    runTest(
        "ABABABC",
        "ABABC",
        expected,
        "LPS-style prefix reuse example"
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
    expected.push_back(0);
    expected.push_back(3);
    expected.push_back(6);
    runTest(
        "ABCABCABC",
        "ABC",
        expected,
        "Repeated pattern"
    );

    expected.clear();
    expected.push_back(1);
    expected.push_back(4);
    runTest(
        "mississippi",
        "issi",
        expected,
        "Pattern with repeated characters"
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

    return 0;
}
