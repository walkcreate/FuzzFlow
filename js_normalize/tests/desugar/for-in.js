
for (let k in obj) 
    console.log(k);

for (var key in obj) 
    doSomething(key);

// error
//for ({a, b} in obj) {}

// left is identifier, rather than declaration
for (k in obj) { 
    console.log(k); 
}
