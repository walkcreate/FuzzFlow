let x = (console.log("a"), console.log("b"), 1 + 2);
let y = (alert("x"), alert("y"), x = 10);
let z = new Foo((init(), 42));

//function foo () {
//    return (cleanup(), x + y + z);
//}

function test() {
    a(), b(), c();
    const x = (foo(), bar());
    
    let y = new Foo(a(), (b(), c()), d());
    
    z = (x(), y());
    
    call((a(), b()), c);
    
    new Bar((d(), e()));
    
    const result = (cond1(), cond2()) ? (a(), b()) : (c(), d());

    if (x(), y()) {
      console.log("yes");
    }

    return (m(), n());
  }
  