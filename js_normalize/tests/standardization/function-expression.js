const greet = function(name) {
    return "Hello, " + name;
};
  
let square = function(x) {
    return x * x;
};
  
const arrow = (x) => x + 1;

Dog.prototype.speak = function () {
    console.log(this.name + " barks.");
};
