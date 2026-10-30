type StringResult = string | undefined;


// READ

function getAt(text: string, index: number): StringResult {
    if (!Number.isInteger(index) || index < 0 || index >= text.length) {
        return undefined;
    }

    return text[index];
}

function getFirst(text: string): StringResult {
    if (text.length === 0) {
        return undefined;
    }

    return text[0];
}

function getLast(text: string): StringResult {
    if (text.length === 0) {
        return undefined;
    }

    return text[text.length - 1];
}

function printString(text: string): void {
    console.log(text);
}


// UPDATE

function setAt(
    text: string,
    index: number,
    newChar: string
): StringResult {
    if (
        !Number.isInteger(index) ||
        index < 0 ||
        index >= text.length ||
        newChar.length !== 1
    ) {
        return undefined;
    }

    return text.slice(0, index) + newChar + text.slice(index + 1);
}


// INSERT

function appendText(text: string, value: string): string {
    return text + value;
}

function prependText(text: string, value: string): string {
    return value + text;
}

// index == text.length inserts at the end.
function insertAt(
    text: string,
    index: number,
    value: string
): StringResult {
    if (
        !Number.isInteger(index) ||
        index < 0 ||
        index > text.length
    ) {
        return undefined;
    }

    return text.slice(0, index) + value + text.slice(index);
}


// DELETE

function removeAt(text: string, index: number): StringResult {
    if (
        !Number.isInteger(index) ||
        index < 0 ||
        index >= text.length
    ) {
        return undefined;
    }

    return text.slice(0, index) + text.slice(index + 1);
}

function removeFirst(text: string): StringResult {
    if (text.length === 0) {
        return undefined;
    }

    return text.slice(1);
}

function removeLast(text: string): StringResult {
    if (text.length === 0) {
        return undefined;
    }

    return text.slice(0, -1);
}

function clearString(text: string): string {
    return "";
}


// SIZE AND BASIC PROPERTIES

function sizeOf(text: string): number {
    return text.length;
}

function isEmpty(text: string): boolean {
    return text.length === 0;
}


// OTHER BASIC STRING OPERATIONS

// Extract the range [start, end).
// Start is included; end is excluded.
function substringRange(
    text: string,
    start: number,
    end: number
): StringResult {
    if (
        !Number.isInteger(start) ||
        !Number.isInteger(end) ||
        start < 0 ||
        end < start ||
        end > text.length
    ) {
        return undefined;
    }

    return text.slice(start, end);
}

function concatenate(first: string, second: string): string {
    return first + second;
}

function stringsEqual(first: string, second: string): boolean {
    return first === second;
}


// DEMONSTRATION

function main(): void {

    // Initialize a string using native TypeScript syntax.
    let text: string = "Hello";

    console.log("==== TYPESCRIPT STRING ====");

    console.log("Original:", text);

    // READ
    console.log("Character at index 1:", getAt(text, 1));
    console.log("First character:", getFirst(text));
    console.log("Last character:", getLast(text));

    // UPDATE
    const updatedText = setAt(text, 0, "Y");

    if (updatedText !== undefined) {
        text = updatedText;
    }

    console.log("After updating:", text);

    // INSERT
    const insertedText = insertAt(text, 5, "!");

    if (insertedText !== undefined) {
        text = insertedText;
    }

    text = appendText(text, " World");
    text = prependText(text, "Hi, ");

    console.log("After inserting:", text);

    // DELETE
    const withoutCharacter = removeAt(text, 2);

    if (withoutCharacter !== undefined) {
        text = withoutCharacter;
    }

    const withoutFirst = removeFirst(text);

    if (withoutFirst !== undefined) {
        text = withoutFirst;
    }

    const withoutLast = removeLast(text);

    if (withoutLast !== undefined) {
        text = withoutLast;
    }

    console.log("After deleting:", text);

    // SIZE AND PROPERTIES
    console.log("Length:", sizeOf(text));
    console.log("Empty:", isEmpty(text));

    // SUBSTRING
    console.log("Substring [0, 2):", substringRange(text, 0, 2));

    // CONCATENATION
    const combined = concatenate(text, "!!!");

    console.log("Concatenated:", combined);

    // COMPARISON
    console.log("Strings equal:", stringsEqual(text, combined));

    // CLEAR
    text = clearString(text);

    console.log('After clearing:', `"${text}"`);
    console.log("Empty after clearing:", isEmpty(text));
}

main();
