class Animal {
    constructor(name) {
        this.name = name;
    }

    speak() {
        console.log(this.name + " makes a noise.");
    }

    static category() {
        return "creature";
    }

    [Symbol.toStringTag]() {
        return "AnimalInstance";
    }
}

class Dog extends Animal {
    constructor(name, breed) {
        super(name);
        this.breed = breed;
    }

    speak() {
        console.log(this.name + " barks.");
    }

    static isDog(obj) {
        return obj instanceof Dog;
    }

    get description() {
        return this.name + " is a " + this.breed;
    }

    set nickname(n) {
        this.nick = n;
    }
}
