#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool characterFrequency(
    const string& text,
    vector<int>& frequency
) {
    vector<int> counts(26, 0);

    for (size_t i = 0; i < text.size(); i++) {
        char character = text[i];

        // Only lowercase English letters are supported.
        if (character < 'a' || character > 'z') {
            return false;
        }

        int index = character - 'a';
        counts[index]++;
    }

    frequency = counts;
    return true;
}

void printFrequency(const vector<int>& frequency) {
    for (int i = 0; i < 26; i++) {
        if (frequency[i] > 0) {
            cout << static_cast<char>('a' + i)
                 << " -> " << frequency[i] << endl;
        }
    }
}

bool testFrequency(
    const string& text,
    const vector<int>& expected,
    const string& label
) {
    vector<int> result;
    bool valid = characterFrequency(text, result);

    bool passed = valid && result == expected;

    cout << label << ": "
         << (passed ? "[PASSED]" : "[FAILED]")
         << endl;

    return passed;
}

int main() {
    cout << "=== CHARACTER FREQUENCY COUNTING ===" << endl;

    cout << "\n--- BASIC EXAMPLE ---" << endl;

    string text = "banana";
    vector<int> frequency;

    cout << "Input: " << text << endl;

    if (characterFrequency(text, frequency)) {
        cout << "Character frequencies:" << endl;
        printFrequency(frequency);
    }

    cout << "\n--- TEST CASES ---" << endl;

    vector<int> bananaExpected(26, 0);
    bananaExpected[0] = 3;  // a
    bananaExpected[1] = 1;  // b
    bananaExpected[13] = 2; // n

    testFrequency(
        "banana",
        bananaExpected,
        "Repeated characters"
    );

    vector<int> alphabetExpected(26, 1);

    testFrequency(
        "abcdefghijklmnopqrstuvwxyz",
        alphabetExpected,
        "All lowercase letters"
    );

    vector<int> singleExpected(26, 0);
    singleExpected[25] = 1;

    testFrequency(
        "z",
        singleExpected,
        "Single character"
    );

    vector<int> emptyExpected(26, 0);

    testFrequency(
        "",
        emptyExpected,
        "Empty string"
    );

    vector<int> repeatedExpected(26, 0);
    repeatedExpected[2] = 5; // c

    testFrequency(
        "ccccc",
        repeatedExpected,
        "All characters identical"
    );

    cout << "\n--- INVALID INPUT ---" << endl;

    vector<int> invalidResult;
    bool valid = characterFrequency("Banana", invalidResult);

    cout << "Uppercase character: "
         << (!valid ? "Rejected [PASSED]" : "Accepted [FAILED]")
         << endl;

    valid = characterFrequency("hello123", invalidResult);

    cout << "Numeric characters: "
         << (!valid ? "Rejected [PASSED]" : "Accepted [FAILED]")
         << endl;

    return 0;
}