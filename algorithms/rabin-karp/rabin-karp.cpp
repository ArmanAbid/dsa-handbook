#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long long BASE = 256;
const long long MOD = 1000000007LL;

// Converts a character to an unsigned byte value.
long long charValue(char c) {
    return static_cast<unsigned char>(c);
}

// Finds every occurrence of pattern inside text.
vector<size_t> rabinKarpSearch(
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

    // Calculate BASE^(m - 1) modulo MOD.
    long long highestPower = 1;

    for (size_t i = 1; i < m; i++) {
        highestPower = (highestPower * BASE) % MOD;
    }

    long long patternHash = 0;
    long long windowHash = 0;

    // Calculate the initial pattern and window hashes.
    for (size_t i = 0; i < m; i++) {
        patternHash =
            (patternHash * BASE + charValue(pattern[i])) % MOD;

        windowHash =
            (windowHash * BASE + charValue(text[i])) % MOD;
    }

    // Slide the window across the text.
    for (size_t i = 0; i <= n - m; i++) {

        // A matching hash is only a candidate.
        // Verify the actual characters to handle collisions.
        if (patternHash == windowHash) {
            if (text.compare(i, m, pattern) == 0) {
                positions.push_back(i);
            }
        }

        // Update the hash for the next window.
        if (i < n - m) {
            long long outgoing =
                charValue(text[i]) * highestPower % MOD;

            windowHash = (windowHash - outgoing + MOD) % MOD;

            windowHash =
                (windowHash * BASE + charValue(text[i + m])) % MOD;
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

// Runs and verifies one test.
void runTest(
    const string& text,
    const string& pattern,
    const vector<size_t>& expected,
    const string& testName
) {
    vector<size_t> result = rabinKarpSearch(text, pattern);

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
    cout << "=== RABIN-KARP STRING MATCHING ===" << endl;

    cout << "\n--- BASIC SEARCH ---" << endl;

    vector<size_t> expected;

    expected.push_back(0);
    expected.push_back(2);
    runTest("ABABA", "ABA", expected, "Overlapping matches");

    expected.clear();
    expected.push_back(1);
    expected.push_back(3);
    runTest("BANANA", "ANA", expected, "Multiple matches");

    expected.clear();
    expected.push_back(10);
    runTest(
        "ABABDABACDABABCABAB",
        "ABABCABAB",
        expected,
        "Single match"
    );

    expected.clear();
    expected.push_back(6);
    runTest("HELLO WORLD", "WORLD", expected, "Match near end");

    expected.clear();
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    runTest("AAAAA", "AA", expected, "Repeated overlapping matches");

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
