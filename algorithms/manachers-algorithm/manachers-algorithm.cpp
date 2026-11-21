#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ManacherResult {
    vector<int> odd;
    vector<int> even;

    size_t start;
    size_t length;
    string longest;
};

// Calculates odd-length palindrome radii.
vector<int> oddRadii(const string& text) {
    int n = static_cast<int>(text.length());

    vector<int> odd(n, 0);

    int left = 0;
    int right = -1;

    for (int i = 0; i < n; i++) {
        int radius;

        // Reuse information from the current palindrome.
        if (i > right) {
            radius = 1;
        } else {
            int mirror = left + right - i;
            int remaining = right - i + 1;

            radius = odd[mirror] < remaining
                ? odd[mirror]
                : remaining;
        }

        // Expand around the current character.
        while (
            i - radius >= 0 &&
            i + radius < n &&
            text[i - radius] == text[i + radius]
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
vector<int> evenRadii(const string& text) {
    int n = static_cast<int>(text.length());

    vector<int> even(n, 0);

    int left = 0;
    int right = -1;

    for (int i = 0; i < n; i++) {
        int radius;

        // Reuse information from the current palindrome.
        if (i > right) {
            radius = 0;
        } else {
            int mirror = left + right - i + 1;
            int remaining = right - i + 1;

            radius = even[mirror] < remaining
                ? even[mirror]
                : remaining;
        }

        // Expand around the gap before the current character.
        while (
            i - radius - 1 >= 0 &&
            i + radius < n &&
            text[i - radius - 1] == text[i + radius]
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
ManacherResult manacher(const string& text) {
    ManacherResult result;

    result.odd = oddRadii(text);
    result.even = evenRadii(text);

    result.start = 0;
    result.length = 0;
    result.longest = "";

    int n = static_cast<int>(text.length());

    int bestStart = 0;
    int bestLength = 0;

    // Check odd-length palindromes.
    for (int i = 0; i < n; i++) {
        int length = 2 * result.odd[i] - 1;
        int start = i - result.odd[i] + 1;

        if (
            length > bestLength ||
            (length == bestLength && start < bestStart)
        ) {
            bestStart = start;
            bestLength = length;
        }
    }

    // Check even-length palindromes.
    for (int i = 0; i < n; i++) {
        int length = 2 * result.even[i];
        int start = i - result.even[i];

        if (
            length > bestLength ||
            (length == bestLength && start < bestStart)
        ) {
            bestStart = start;
            bestLength = length;
        }
    }

    result.start = static_cast<size_t>(bestStart);
    result.length = static_cast<size_t>(bestLength);
    result.longest = text.substr(result.start, result.length);

    return result;
}

// Compares two integer vectors.
bool areEqual(
    const vector<int>& first,
    const vector<int>& second
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

// Prints a radius array.
void printArray(const vector<int>& values) {
    cout << "[";

    for (size_t i = 0; i < values.size(); i++) {
        cout << values[i];

        if (i + 1 < values.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

// Verifies the radius arrays.
void runRadiusTest(
    const string& text,
    const vector<int>& expectedOdd,
    const vector<int>& expectedEven,
    const string& testName
) {
    vector<int> odd = oddRadii(text);
    vector<int> even = evenRadii(text);

    bool passed =
        areEqual(odd, expectedOdd) &&
        areEqual(even, expectedEven);

    cout << testName << ": ";

    cout << "Odd = ";
    printArray(odd);

    cout << ", Even = ";
    printArray(even);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}

// Verifies the longest palindrome.
void runTest(
    const string& text,
    const string& expectedLongest,
    size_t expectedStart,
    size_t expectedLength,
    const string& testName
) {
    ManacherResult result = manacher(text);

    bool passed =
        result.longest == expectedLongest &&
        result.start == expectedStart &&
        result.length == expectedLength;

    cout << testName << ": ";

    cout << "Longest = \"" << result.longest << "\"";
    cout << ", Start = " << result.start;
    cout << ", Length = " << result.length;

    cout << (passed ? " [PASSED]" : " [FAILED]");

    if (!passed) {
        cout << " Expected: \"" << expectedLongest << "\"";
    }

    cout << endl;
}

int main() {
    cout << "==== MANACHER'S ALGORITHM ====" << endl;

    cout << "\n--- RADIUS ARRAYS ---" << endl;

    vector<int> expectedOdd;
    expectedOdd.push_back(1);
    expectedOdd.push_back(2);
    expectedOdd.push_back(1);
    expectedOdd.push_back(4);
    expectedOdd.push_back(1);
    expectedOdd.push_back(2);
    expectedOdd.push_back(1);

    vector<int> expectedEven(7, 0);

    runRadiusTest(
        "abacaba",
        expectedOdd,
        expectedEven,
        "Odd palindrome radii"
    );

    expectedOdd.clear();
    expectedOdd.push_back(1);
    expectedOdd.push_back(1);
    expectedOdd.push_back(1);
    expectedOdd.push_back(1);

    expectedEven.clear();
    expectedEven.push_back(0);
    expectedEven.push_back(0);
    expectedEven.push_back(2);
    expectedEven.push_back(0);

    runRadiusTest(
        "abba",
        expectedOdd,
        expectedEven,
        "Even palindrome radii"
    );

    cout << "\n--- LONGEST PALINDROMES ---" << endl;

    runTest(
        "babad",
        "bab",
        0,
        3,
        "Odd-length palindrome"
    );

    runTest(
        "cbbd",
        "bb",
        1,
        2,
        "Even-length palindrome"
    );

    runTest(
        "abba",
        "abba",
        0,
        4,
        "Entire string is a palindrome"
    );

    runTest(
        "aaaaa",
        "aaaaa",
        0,
        5,
        "Repeated characters"
    );

    runTest(
        "racecar",
        "racecar",
        0,
        7,
        "Classic palindrome"
    );

    runTest(
        "abc",
        "a",
        0,
        1,
        "No palindrome longer than one"
    );

    runTest(
        "abacdfgdcaba",
        "aba",
        0,
        3,
        "Multiple longest palindromes"
    );

    cout << "\n--- EDGE CASES ---" << endl;

    runTest(
        "",
        "",
        0,
        0,
        "Empty string"
    );

    runTest(
        "x",
        "x",
        0,
        1,
        "Single character"
    );

    runTest(
        "aabbaa",
        "aabbaa",
        0,
        6,
        "Long even palindrome"
    );

    return 0;
}
