class Stack {
    private elements: number[];

    constructor() {
        this.elements = [];
    }

    // PUSH: Add an element to the top.
    push(value: number): void {
        this.elements.push(value);
    }

    // POP: Remove and return the top element.
    pop(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        return this.elements.pop();
    }

    // PEEK: Read the top element without removing it.
    peek(): number | undefined {
        if (this.isEmpty()) {
            return undefined;
        }

        return this.elements[this.elements.length - 1];
    }

    // SIZE: Get the number of elements.
    sizeOf(): number {
        return this.elements.length;
    }

    // CHECK: Check whether the stack is empty.
    isEmpty(): boolean {
        return this.elements.length === 0;
    }

    // DISPLAY: Show elements from top to bottom.
    printStack(): void {
        if (this.isEmpty()) {
            console.log("Stack: Top -> Bottom (Empty)");
            return;
        }

        const values = [...this.elements].reverse().join(" -> ");

        console.log(`Stack: Top -> ${values} -> Bottom`);
    }

    // CLEAR: Remove all elements.
    clearStack(): void {
        this.elements.length = 0;
    }
}

// DEMONSTRATION

const stack = new Stack();

console.log("==== STACK ====");

// PUSH
console.log("\n--- PUSH ---");

stack.push(10);
stack.push(20);
stack.push(30);

stack.printStack();

stack.push(40);

console.log("After pushing 40:");
stack.printStack();

// PEEK
console.log("\n--- PEEK ---");

console.log("Top element:", stack.peek());

stack.printStack();

// POP
console.log("\n--- POP ---");

console.log("Removed element:", stack.pop());
stack.printStack();

console.log("Removed element:", stack.pop());
stack.printStack();

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", stack.sizeOf());
console.log("Is empty:", stack.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

stack.clearStack();

stack.printStack();

console.log("Size after clearing:", stack.sizeOf());
console.log("Is empty:", stack.isEmpty());

// EMPTY STACK CHECK
console.log("\n--- EMPTY STACK CHECK ---");

console.log("Pop from empty stack:", stack.pop());
console.log("Peek into empty stack:", stack.peek());