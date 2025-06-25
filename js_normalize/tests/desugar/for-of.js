function testBasic() {
    const list = [10, 20, 30];
    for (const item of list) {
        console.log(item);
    }
}

function testAssignment() {
    let val;
    for (val of [1, 2, 3]) {
        console.log(val);
    }
}

function testDestructuringArray() {
    const pairs = [[1, 2], [3, 4]];
    for (const [a, b] of pairs) {
        console.log(a + b);
    }
}

function testDestructuringObject() {
    const objects = [{ x: 1, y: 2 }, { x: 3, y: 4 }];
    for (const { x, y } of objects) {
        console.log(x * y);
    }
}

function testWithContinueAndBreak() {
    for (const x of [5, 6, 7, 8]) {
        if (x === 6) continue;
        if (x === 8) break;
        console.log(x);
    }
}
