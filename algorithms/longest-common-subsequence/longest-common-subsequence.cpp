#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Returns one longest common subsequence.
string longestCommonSubsequence(
    const string& first,
    const string& second
) {
    size_t n = first.length();
    size_t m = second.length();

    // Create an (n + 1) x (m + 1) DP table.
    vector< vector<size_t> > dp(
        n + 1,
        vector<size_t>(m + 1, 0)
    );

    // Fill the DP table.
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {

            if (first[i - 1] == second[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                size_t top = dp[i - 1][j];
                size_t left = dp[i][j - 1];

                dp[i][j] = (top > left) ? top : left;
            }
        }
    }

    // Reconstruct the subsequence.
    string result;

    size_t i = n;
    size_t j = m;

    while (i > 0 && j > 0) {

        if (first[i - 1] == second[j - 1]) {
            result += first[i - 1];

            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Reconstruction happens backwards.
    reverse(result.begin(), result.end());

    return result;
}


void runTest(
    const string& first,
    const string& second,
    const string& expected,
    const string& testName
) {
    string result = longestCommonSubsequence(first, second);

    bool passed = result == expected;

    cout << testName << ": " << result
         << " (length " << result.length() << ")"
         << (passed ? " [PASSED]" : " [FAILED]");

    if (!passed) {
        cout << " Expected: " << expected;
    }

    cout << endl;
}


int main() {
    cout << "=== LONGEST COMMON SUBSEQUENCE ===" << endl;

    cout << "\n--- BASIC EXAMPLES ---" << endl;

    runTest("ABC", "AC", "AC", "Simple example");

    runTest(
        "AGGTAB",
        "GXTXAYB",
        "GTAB",
        "Classic example"
    );

    runTest(
        "ABCDEF",
        "ACE",
        "ACE",
        "Characters with gaps"
    );

    cout << "\n--- ADDITIONAL CASES ---" << endl;

    runTest(
        "ABCD",
        "AEBD",
        "ABD",
        "Different lengths"
    );

    runTest(
        "HELLO",
        "WORLD",
        "L",
        "Single common character"
    );

    runTest(
        "ABC",
        "ABC",
        "ABC",
        "Identical strings"
    );

    runTest(
        "AAAA",
        "AA",
        "AA",
        "Repeated characters"
    );

    runTest(
        "ABC",
        "DEF",
        "",
        "No common characters"
    );

    cout << "\n--- EDGE CASES ---" << endl;

    runTest("", "", "", "Both empty");
    runTest("ABC", "", "", "Second string empty");
    runTest("", "ABC", "", "First string empty");

    return 0;
}
