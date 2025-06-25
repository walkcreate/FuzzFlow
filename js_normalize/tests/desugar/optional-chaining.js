let obj = { a: null, f: () => ({ g: { h: 42 } }) };

obj.a?.b;

let x = obj.a?.b?.c;

x = obj?.a;

const y = obj.a?.();

function test() {
  return obj.a?.b?.c;
}

let z = obj.f?.().g?.h;
