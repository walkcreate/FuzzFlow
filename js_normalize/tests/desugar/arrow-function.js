const add = (a, b) => a + b;

const obj = {
  greet: (name) => "Hi, " + name
};

setTimeout(() => {
  console.log("done");
}, 1000);

let multiply = (a, b) => a * b;

(() => {
  console.log("IIFE");
})();

// arrow function in class
class A {
    f = () => console.log("hello");
}

// export default
export default (x) => x + 1;

// conditional expr
const fn = flag ? () => 1 : () => 2;