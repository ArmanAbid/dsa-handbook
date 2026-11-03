class DisjointSet {
    private parent: number[];
    private componentSize: number[];
    private componentCount: number;

    constructor(n: number) {
        if (!Number.isInteger(n) || n < 0) {
            throw new RangeError(
                "Number of elements must be a non-negative integer."
            );
        }

        this.parent = [];
        this.componentSize = [];
        this.componentCount = n;

        for (let i = 0; i < n; i++) {
            this.parent.push(i);
            this.componentSize.push(1);
        }
    }

    // Check whether an element index is valid.
    private isValid(element: number): boolean {
        return (
            Number.isInteger(element) &&
            element >= 0 &&
            element < this.parent.length
        );
    }

    // FIND: Get the representative of an element.
    // Uses path compression.
    find(element: number): number {
        if (!this.isValid(element)) {
            return -1;
        }

        const parent = this.parent[element];

        if (parent === undefined) {
            return -1;
        }

        if (parent !== element) {
            const representative = this.find(parent);

            if (representative === -1) {
                return -1;
            }

            this.parent[element] = representative;
        }

        return this.parent[element] ?? -1;
    }

    // UNION: Merge the components of two elements.
    // Uses union by size.
    unionSets(first: number, second: number): boolean {
        let rootFirst = this.find(first);
        let rootSecond = this.find(second);

        if (rootFirst === -1 || rootSecond === -1) {
            return false;
        }

        // Already in the same component.
        if (rootFirst === rootSecond) {
            return false;
        }

        // Get the sizes of both components.
        const firstSize = this.componentSize[rootFirst];
        const secondSize = this.componentSize[rootSecond];

        if (firstSize === undefined || secondSize === undefined) {
            return false;
        }

        // Attach the smaller component beneath the larger one.
        if (firstSize < secondSize) {
            const temp = rootFirst;
            rootFirst = rootSecond;
            rootSecond = temp;
        }

        this.parent[rootSecond] = rootFirst;

        const largerSize = this.componentSize[rootFirst] ?? 0;
        const smallerSize = this.componentSize[rootSecond] ?? 0;

        this.componentSize[rootFirst] = largerSize + smallerSize;

        this.componentCount--;

        return true;
    }

    // CONNECTED: Check whether two elements belong to the same set.
    connected(first: number, second: number): boolean {
        const rootFirst = this.find(first);
        const rootSecond = this.find(second);

        if (rootFirst === -1 || rootSecond === -1) {
            return false;
        }

        return rootFirst === rootSecond;
    }

    // GET COMPONENT SIZE: Return the size of an element's component.
    getComponentSize(element: number): number {
        const representative = this.find(element);

        if (representative === -1) {
            return 0;
        }

        return this.componentSize[representative] ?? 0;
    }

    // GET COMPONENT COUNT: Number of separate components.
    getComponentCount(): number {
        return this.componentCount;
    }

    // SIZE: Get the total number of elements.
    size(): number {
        return this.parent.length;
    }

    // CHECK: Check whether the DSU contains no elements.
    isEmpty(): boolean {
        return this.parent.length === 0;
    }

    // DISPLAY: Show all components.
    printComponents(): void {
        const groups = new Map<number, number[]>();

        for (let i = 0; i < this.size(); i++) {
            const representative = this.find(i);

            if (representative === -1) {
                continue;
            }

            let members = groups.get(representative);

            if (members === undefined) {
                members = [];
                groups.set(representative, members);
            }

            members.push(i);
        }

        if (groups.size === 0) {
            console.log("Components: Empty");
            return;
        }

        const formatted: string[] = [];

        for (const members of groups.values()) {
            formatted.push(`{ ${members.join(", ")} }`);
        }

        console.log("Components:", formatted.join(" "));
    }

    // RESET: Restore every element as its own component.
    reset(): void {
        for (let i = 0; i < this.size(); i++) {
            this.parent[i] = i;
            this.componentSize[i] = 1;
        }

        this.componentCount = this.size();
    }
}

// DEMONSTRATION

const dsu = new DisjointSet(7);

console.log("==== DISJOINT SET UNION ====");

// INITIAL STATE
console.log("\n--- INITIAL STATE ---");

dsu.printComponents();

console.log("Elements:", dsu.size());
console.log("Components:", dsu.getComponentCount());

// UNION
console.log("\n--- UNION ---");

dsu.unionSets(0, 1);
dsu.unionSets(1, 2);
dsu.unionSets(3, 4);
dsu.unionSets(5, 6);

dsu.printComponents();

console.log("Components:", dsu.getComponentCount());

// UNION ALREADY CONNECTED ELEMENTS
console.log("\n--- DUPLICATE UNION ---");

console.log("Union 0 and 2:", dsu.unionSets(0, 2));

console.log("Components:", dsu.getComponentCount());

// FIND
console.log("\n--- FIND ---");

console.log("Representative of 0:", dsu.find(0));
console.log("Representative of 2:", dsu.find(2));
console.log("Representative of 4:", dsu.find(4));

// CONNECTED
console.log("\n--- CONNECTED ---");

console.log("Are 0 and 2 connected:", dsu.connected(0, 2));
console.log("Are 0 and 4 connected:", dsu.connected(0, 4));

// UNION COMPONENTS
console.log("\n--- MERGE COMPONENTS ---");

dsu.unionSets(2, 4);

dsu.printComponents();

console.log("Components:", dsu.getComponentCount());

// COMPONENT SIZE
console.log("\n--- COMPONENT SIZE ---");

console.log("Component size of 0:", dsu.getComponentSize(0));
console.log("Component size of 3:", dsu.getComponentSize(3));
console.log("Component size of 5:", dsu.getComponentSize(5));

// INVALID ELEMENT
console.log("\n--- INVALID ELEMENT ---");

console.log("Find 10:", dsu.find(10));
console.log("Get size of 10:", dsu.getComponentSize(10));

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Total elements:", dsu.size());
console.log("Is empty:", dsu.isEmpty());

// RESET
console.log("\n--- RESET ---");

dsu.reset();

dsu.printComponents();

console.log("Components after reset:", dsu.getComponentCount());
console.log("Are 0 and 1 connected:", dsu.connected(0, 1));

// EMPTY DSU
console.log("\n--- EMPTY DSU ---");

const emptySet = new DisjointSet(0);

console.log("Is empty:", emptySet.isEmpty());
console.log("Components:", emptySet.getComponentCount());