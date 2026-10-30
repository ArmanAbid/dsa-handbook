type ArrayElement = number;

// READ

function getAt(
    arr: ArrayElement[],
    index: number
): ArrayElement | undefined {
    if (!Number.isInteger(index) || index < 0 || index >= arr.length) {
        return undefined;
    }

    return arr[index];
}

function getFirst(arr: ArrayElement[]): ArrayElement | undefined {
    if (arr.length === 0) {
        return undefined;
    }

    return arr[0];
}

function getLast(arr: ArrayElement[]): ArrayElement | undefined {
    if (arr.length === 0) {
        return undefined;
    }

    return arr[arr.length - 1];
}

function printArray(arr: ArrayElement[]): void {
    console.log(arr.join(" "));
}

// UPDATE

function setAt(
    arr: ArrayElement[],
    index: number,
    value: ArrayElement
): boolean {
    if (!Number.isInteger(index) || index < 0 || index >= arr.length) {
        return false;
    }

    arr[index] = value;
    return true;
}


// INSERT

function append(arr: ArrayElement[], value: ArrayElement): void {
    arr.push(value);
}

function prepend(arr: ArrayElement[], value: ArrayElement): void {
    arr.unshift(value);
}

// index == arr.length inserts at the end.
function insertAt(
    arr: ArrayElement[],
    index: number,
    value: ArrayElement
): boolean {
    if (!Number.isInteger(index) || index < 0 || index > arr.length) {
        return false;
    }

    arr.splice(index, 0, value);
    return true;
}


// DELETE

function removeAt(
    arr: ArrayElement[],
    index: number
): ArrayElement | undefined {
    if (!Number.isInteger(index) || index < 0 || index >= arr.length) {
        return undefined;
    }

    return arr.splice(index, 1)[0];
}

function popFront(arr: ArrayElement[]): ArrayElement | undefined {
    return arr.shift();
}

function popBack(arr: ArrayElement[]): ArrayElement | undefined {
    return arr.pop();
}

function clearArray(arr: ArrayElement[]): void {
    arr.length = 0;
}


// SIZE AND RESIZING

function sizeOf(arr: ArrayElement[]): number {
    return arr.length;
}

function isEmpty(arr: ArrayElement[]): boolean {
    return arr.length === 0;
}

function resizeArray(
    arr: ArrayElement[],
    newSize: number,
    fillValue: ArrayElement = 0
): boolean {
    if (!Number.isInteger(newSize) || newSize < 0) {
        return false;
    }

    if (newSize < arr.length) {
        arr.length = newSize;
    } else {
        while (arr.length < newSize) {
            arr.push(fillValue);
        }
    }

    return true;
}


// DEMONSTRATION

function main(): void {

    // Create an array using native TypeScript syntax.
    const arr: number[] = [10, 20, 30, 40, 50];

    console.log("Initial array:");
    printArray(arr);

    // READ
    console.log("Element at index 2:", getAt(arr, 2));
    console.log("First element:", getFirst(arr));
    console.log("Last element:", getLast(arr));

    // UPDATE
    setAt(arr, 2, 35);

    // INSERT
    insertAt(arr, 2, 25);
    append(arr, 60);
    prepend(arr, 5);

    console.log("After updates and insertions:");
    printArray(arr);

    // DELETE
    console.log("Removed at index 1:", removeAt(arr, 1));
    console.log("Removed first element:", popFront(arr));
    console.log("Removed last element:", popBack(arr));

    console.log("Current array:");
    printArray(arr);

    // SIZE AND RESIZING
    console.log("Size:", sizeOf(arr));
    console.log("Empty:", isEmpty(arr));

    resizeArray(arr, 6, -1);

    console.log("After resizing:");
    printArray(arr);

    // CLEAR
    clearArray(arr);

    console.log("Size after clearing:", sizeOf(arr));
    console.log("Empty after clearing:", isEmpty(arr));
}

main();
