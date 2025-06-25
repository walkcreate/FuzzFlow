function example() {
    if (true) {
        var x = 1;
        var y;
        function inner() {
            console.log("hi");
        }
    }

    console.log(x, y);
    inner();
}
