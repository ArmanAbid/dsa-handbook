#include <iostream>
#include <map>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> componentSize;
    int componentCount;

    // CHECK: Validate an element index.
    bool isValid(int element) const {
        return element >= 0 &&
               element < static_cast<int>(parent.size());
    }

public:
    // CREATE: Initialize n separate elements.
    explicit DisjointSet(int n) {
        if (n < 0) {
            n = 0;
        }

        parent.resize(n);
        componentSize.resize(n);

        componentCount = n;

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            componentSize[i] = 1;
        }
    }

    // FIND: Get the representative of an element.
    // Uses path compression.
    int find(int element) {
        if (!isValid(element)) {
            return -1;
        }

        if (parent[element] != element) {
            parent[element] = find(parent[element]);
        }

        return parent[element];
    }

    // UNION: Merge the components of two elements.
    // Uses union by size.
    bool unionSets(int first, int second) {
        int rootFirst = find(first);
        int rootSecond = find(second);

        if (rootFirst == -1 || rootSecond == -1) {
            return false;
        }

        // Already in the same component.
        if (rootFirst == rootSecond) {
            return false;
        }

        // Attach the smaller component beneath the larger one.
        if (componentSize[rootFirst] < componentSize[rootSecond]) {
            int temp = rootFirst;
            rootFirst = rootSecond;
            rootSecond = temp;
        }

        parent[rootSecond] = rootFirst;

        componentSize[rootFirst] += componentSize[rootSecond];

        componentCount--;

        return true;
    }

    // CONNECTED: Check whether two elements belong to the same set.
    bool connected(int first, int second) {
        int rootFirst = find(first);
        int rootSecond = find(second);

        if (rootFirst == -1 || rootSecond == -1) {
            return false;
        }

        return rootFirst == rootSecond;
    }

    // GET COMPONENT SIZE: Return the size of an element's component.
    int getComponentSize(int element) {
        int representative = find(element);

        if (representative == -1) {
            return 0;
        }

        return componentSize[representative];
    }

    // GET COMPONENT COUNT: Number of separate components.
    int getComponentCount() const {
        return componentCount;
    }

    // SIZE: Get the total number of elements.
    int size() const {
        return static_cast<int>(parent.size());
    }

    // CHECK: Check whether the DSU contains no elements.
    bool isEmpty() const {
        return parent.empty();
    }

    // DISPLAY: Show all components.
    void printComponents() {
        map<int, vector<int> > groups;

        for (int i = 0; i < size(); i++) {
            int representative = find(i);
            groups[representative].push_back(i);
        }

        cout << "Components: ";

        if (groups.empty()) {
            cout << "Empty" << endl;
            return;
        }

        for (
            map<int, vector<int> >::const_iterator it =
                groups.begin();
            it != groups.end();
            ++it
        ) {
            cout << "{ ";

            for (
                unsigned int i = 0;
                i < it->second.size();
                i++
            ) {
                cout << it->second[i];

                if (i < it->second.size() - 1) {
                    cout << ", ";
                }
            }

            cout << " } ";
        }

        cout << endl;
    }

    // RESET: Restore every element as its own component.
    void reset() {
        for (int i = 0; i < size(); i++) {
            parent[i] = i;
            componentSize[i] = 1;
        }

        componentCount = size();
    }
};

// DEMONSTRATION

int main() {
    DisjointSet dsu(7);

    cout << "==== DISJOINT SET UNION ====" << endl;

    // INITIAL STATE
    cout << "\n--- INITIAL STATE ---" << endl;

    dsu.printComponents();

    cout << "Elements: " << dsu.size() << endl;
    cout << "Components: " << dsu.getComponentCount() << endl;

    // UNION
    cout << "\n--- UNION ---" << endl;

    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);
    dsu.unionSets(5, 6);

    dsu.printComponents();

    cout << "Components: " << dsu.getComponentCount() << endl;

    // UNION ALREADY CONNECTED ELEMENTS
    cout << "\n--- DUPLICATE UNION ---" << endl;

    cout << "Union 0 and 2: "
         << (dsu.unionSets(0, 2) ? "Merged" : "Already connected")
         << endl;

    cout << "Components: " << dsu.getComponentCount() << endl;

    // FIND
    cout << "\n--- FIND ---" << endl;

    cout << "Representative of 0: " << dsu.find(0) << endl;
    cout << "Representative of 2: " << dsu.find(2) << endl;
    cout << "Representative of 4: " << dsu.find(4) << endl;

    // CONNECTED
    cout << "\n--- CONNECTED ---" << endl;

    cout << "Are 0 and 2 connected: "
         << (dsu.connected(0, 2) ? "Yes" : "No") << endl;

    cout << "Are 0 and 4 connected: "
         << (dsu.connected(0, 4) ? "Yes" : "No") << endl;

    // UNION COMPONENTS
    cout << "\n--- MERGE COMPONENTS ---" << endl;

    dsu.unionSets(2, 4);

    dsu.printComponents();

    cout << "Components: " << dsu.getComponentCount() << endl;

    // COMPONENT SIZE
    cout << "\n--- COMPONENT SIZE ---" << endl;

    cout << "Component size of 0: "
         << dsu.getComponentSize(0) << endl;

    cout << "Component size of 3: "
         << dsu.getComponentSize(3) << endl;

    cout << "Component size of 5: "
         << dsu.getComponentSize(5) << endl;

    // INVALID ELEMENT
    cout << "\n--- INVALID ELEMENT ---" << endl;

    cout << "Find 10: " << dsu.find(10) << endl;
    cout << "Get size of 10: " << dsu.getComponentSize(10) << endl;

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Total elements: " << dsu.size() << endl;
    cout << "Is empty: " << (dsu.isEmpty() ? "Yes" : "No") << endl;

    // RESET
    cout << "\n--- RESET ---" << endl;

    dsu.reset();

    dsu.printComponents();

    cout << "Components after reset: "
         << dsu.getComponentCount() << endl;

    cout << "Are 0 and 1 connected: "
         << (dsu.connected(0, 1) ? "Yes" : "No") << endl;

    // EMPTY DSU
    cout << "\n--- EMPTY DSU ---" << endl;

    DisjointSet emptySet(0);

    cout << "Is empty: "
         << (emptySet.isEmpty() ? "Yes" : "No") << endl;

    cout << "Components: " << emptySet.getComponentCount() << endl;

    return 0;
}