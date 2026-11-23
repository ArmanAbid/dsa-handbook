#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Calculates the minimum number of insertions,
// deletions, and substitutions needed to transform
// first into second.
size_t levenshteinDistance(
    const string& first,
    const string& second
) {
    // Use the shorter string as the columns.
    const string* rows = &first;
    const string* columns = &second;

    if (columns->length() > rows->length()) {
        rows = &second;
        columns = &first;
    }

    size_t n = rows->length();
    size_t m = columns->length();

    // Previous and current DP rows.
    vector<size_t> previous(m + 1, 0);
    vector<size_t> current(m + 1, 0);

    // Base case: transform empty string into a prefix.
    for (size_t j = 0; j <= m; j++) {
        previous[j] = j;
    }

    // Calculate each DP row.
    for (size_t i = 1; i <= n; i++) {
        // Base case: delete i characters to get an empty string.
        current[0] = i;

        for (size_t j = 1; j <= m; j++) {

            if ((*rows)[i - 1] == (*columns)[j - 1]) {
                // Characters match: no additional edit.
                current[j] = previous[j - 1];
            } else {
                // Three possible operations:
                size_t deletion = previous[j];
                size_t insertion = current[j - 1];
                size_t substitution = previous[j - 1];

                size_t minimum = deletion;

                if (insertion < minimum) {
                    minimum = insertion;
                }

                if (substitution < minimum) {
                    minimum = substitution;
                }

                current[j] = minimum + 1;
            }
        }

        // Current row becomes the previous row.
        previous.swap(current);
    }

    return previous[m];
}

// Runs and verifies one test.
void runTest(
    const string& first,
    const string& second,
    size_t expected,
    const string& testName
) {
    size_t result = levenshteinDistance(first, second);

    bool passed = result == expected;

    cout << testName << ": " << result;

    cout << (passed ? " [PASSED]" : " [FAILED]");

    if (!passed) {
        cout << " Expected: " << expected;
    }

    cout << endl;
}

int main() {
    cout << "=== LEVENSHTEIN DISTANCE ===" << endl;

    cout << "\n--- BASIC EXAMPLES ---" << endl;

    runTest(
        "kitten",
        "sitting",
        3,
        "Kitten to sitting"
    );

    runTest(
        "saturday",
        "sunday",
        3,
        "Saturday to Sunday"
    );

    runTest(
        "flaw",
        "lawn",
        2,
        "Flaw to lawn"
    );

    runTest(
        "intention",
        "execution",
        5,
        "Classic example"
    );

    cout << "\n--- EDIT OPERATIONS ---" << endl;

    runTest("cat", "cut", 1, "Substitution");
    runTest("cat", "cart", 1, "Insertion");
    runTest("cart", "cat", 1, "Deletion");

    cout << "\n--- ADDITIONAL CASES ---" << endl;

    runTest("Cat", "cat", 1, "Case-sensitive comparison");
    runTest("book", "back", 2, "Multiple substitutions");
    runTest("algorithm", "algorithm", 0, "Identical strings");
    runTest("ab", "ba", 2, "Two substitutions");
    runTest("form", "from", 2, "Transposition is two edits");

    cout << "\n--- EDGE CASES ---" << endl;

    runTest("", "", 0, "Both empty");
    runTest("", "abc", 3, "First string empty");
    runTest("abc", "", 3, "Second string empty");

    return 0;
}
