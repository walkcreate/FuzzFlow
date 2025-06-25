#include "JSEnvironment.h"

namespace FuzzFlow {

///
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/
///
void JSEnvironment::init_built_in_objects()
{
    {
        /// built-in Object
        const string name = "Object";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("assign", 2));
        static_methods.insert(StaticMethod("create", 1));
        static_methods.insert(StaticMethod("defineProperties", 2));
        static_methods.insert(StaticMethod("defineProperty", 3));
        static_methods.insert(StaticMethod("entries", 1));
        static_methods.insert(StaticMethod("freeze", 1));
        static_methods.insert(StaticMethod("fromEntries", 1));
        static_methods.insert(StaticMethod("getOwnPropertyDescriptor", 2));
        static_methods.insert(StaticMethod("getOwnPropertyDescriptors", 1));
        static_methods.insert(StaticMethod("getOwnPropertyNames", 1));
        static_methods.insert(StaticMethod("getOwnPropertySymbols", 1));
        static_methods.insert(StaticMethod("getPrototypeOf", 1));
        static_methods.insert(StaticMethod("groupBy", 2));
        static_methods.insert(StaticMethod("hasOwn", 2));
        static_methods.insert(StaticMethod("is", 2));
        static_methods.insert(StaticMethod("isExtensible", 1));
        static_methods.insert(StaticMethod("isFrozen", 1));
        static_methods.insert(StaticMethod("isSealed", 1));
        static_methods.insert(StaticMethod("keys", 1));
        static_methods.insert(StaticMethod("preventExtensions", 1));
        static_methods.insert(StaticMethod("seal", 1));
        static_methods.insert(StaticMethod("setPrototypeOf", 2));
        static_methods.insert(StaticMethod("values", 1));

        instance_methods.insert(InstanceMethod("hasOwnProperty", 1));
        instance_methods.insert(InstanceMethod("isPrototypeOf", 1));
        instance_methods.insert(InstanceMethod("propertyIsEnumerable", 1));
        instance_methods.insert(InstanceMethod("toLocaleString", 1));
        instance_methods.insert(InstanceMethod("toString", 1));
        instance_methods.insert(InstanceMethod("valueOf", 1));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in Array
        const string name = "Array";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("from", 1));
        static_methods.insert(StaticMethod("fromAsync", 1));
        static_methods.insert(StaticMethod("isArray", 1));
        static_methods.insert(StaticMethod("of", 3));

        instance_methods.insert(InstanceMethod("at", 1));
        instance_methods.insert(InstanceMethod("concat", 2));
        instance_methods.insert(InstanceMethod("copyWithin", 2));
        instance_methods.insert(InstanceMethod("entries", 0));
        instance_methods.insert(InstanceMethod("every", 1));
        instance_methods.insert(InstanceMethod("fill", 3));
        instance_methods.insert(InstanceMethod("fill", 1));
        instance_methods.insert(InstanceMethod("filter", 1));
        instance_methods.insert(InstanceMethod("find", 1));
        instance_methods.insert(InstanceMethod("findIndex", 1));
        instance_methods.insert(InstanceMethod("findLast", 1));
        instance_methods.insert(InstanceMethod("findLastIndex", 1));
        instance_methods.insert(InstanceMethod("flat", 3));
        instance_methods.insert(InstanceMethod("flatMap", 1));
        instance_methods.insert(InstanceMethod("forEach", 1));
        instance_methods.insert(InstanceMethod("includes", 1));
        instance_methods.insert(InstanceMethod("indexOf", 1));
        instance_methods.insert(InstanceMethod("join", 0));
        instance_methods.insert(InstanceMethod("keys", 1));
        instance_methods.insert(InstanceMethod("lastIndexOf", 1));
        instance_methods.insert(InstanceMethod("map", 1));
        instance_methods.insert(InstanceMethod("pop", 0));
        instance_methods.insert(InstanceMethod("push", 1));
        instance_methods.insert(InstanceMethod("reduce", 1));
        instance_methods.insert(InstanceMethod("reduceRight", 1));
        instance_methods.insert(InstanceMethod("reverse", 0));
        instance_methods.insert(InstanceMethod("shift", 0));
        instance_methods.insert(InstanceMethod("slice", 2));
        instance_methods.insert(InstanceMethod("some", 1));
        instance_methods.insert(InstanceMethod("sort", 0));
        instance_methods.insert(InstanceMethod("splice", 1));
        instance_methods.insert(InstanceMethod("toLocaleString", 0));
        instance_methods.insert(InstanceMethod("toReversed", 0));
        instance_methods.insert(InstanceMethod("toSorted", 1));
        instance_methods.insert(InstanceMethod("toSpliced", 1));
        instance_methods.insert(InstanceMethod("toString", 0));
        instance_methods.insert(InstanceMethod("unshift", 1));
        instance_methods.insert(InstanceMethod("values", 0));
        instance_methods.insert(InstanceMethod("with", 2));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in ArrayBuffer
        const string name = "ArrayBuffer";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("isView", 1));

        instance_methods.insert(InstanceMethod("resize", 1));
        instance_methods.insert(InstanceMethod("slice", {0,1,2}));
        instance_methods.insert(InstanceMethod("transfer", {0,1}));
        instance_methods.insert(InstanceMethod("transferToFixedLength", {0,1}));

        //BuiltInObject object(name, constructor, static_methods, instance_methods);
        //this->built_in_objects.push_back(object);
    }

    {
        /// built-in ArrayBuffer
        const string name = "Atomics";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("add", 3));
        static_methods.insert(StaticMethod("and", 3));
        static_methods.insert(StaticMethod("compareExchange", 4));
        static_methods.insert(StaticMethod("exchange", 3));
        static_methods.insert(StaticMethod("isLockFree", 1));
        static_methods.insert(StaticMethod("load", 2));
        static_methods.insert(StaticMethod("notify", 3));
        static_methods.insert(StaticMethod("or", 3));
        static_methods.insert(StaticMethod("pause", {0,1}));
        static_methods.insert(StaticMethod("store", 3));
        static_methods.insert(StaticMethod("sub", 3));
        static_methods.insert(StaticMethod("wait", {3,4}));
        static_methods.insert(StaticMethod("waitAsync", {3,4}));
        static_methods.insert(StaticMethod("xor", 3));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in BigInt
        const string name = "BigInt";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("asIntN", 2));
        static_methods.insert(StaticMethod("asUintN", 2));

        instance_methods.insert(InstanceMethod("toLocaleString", {0,1,2}));
        instance_methods.insert(InstanceMethod("toString", {0,1}));
        instance_methods.insert(InstanceMethod("valueOf", 0));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in Boolean
        const string name = "Boolean";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        instance_methods.insert(InstanceMethod("toString", 0));
        instance_methods.insert(InstanceMethod("valueOf", 0));

        //BuiltInObject object(name, constructor, static_methods, instance_methods);
        //this->built_in_objects.push_back(object);
    }

    {
        /// built-in Date
        const string name = "Date";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("now", 0));
        static_methods.insert(StaticMethod("parse", 1));
        static_methods.insert(StaticMethod("UTC", {1,2,3,4,5,6,7}));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in JSON
        const string name = "JSON";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("isRawJSON", 1));
        static_methods.insert(StaticMethod("parse", {1,2}));
        static_methods.insert(StaticMethod("rawJSON", 1));
        static_methods.insert(StaticMethod("stringify", {1,2,3}));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in Math
        const string name = "Math";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("abs", 1));
        static_methods.insert(StaticMethod("acos", 1));
        static_methods.insert(StaticMethod("acosh", 1));
        static_methods.insert(StaticMethod("asin", 1));
        static_methods.insert(StaticMethod("asinh", 1));
        static_methods.insert(StaticMethod("atan", 1));
        static_methods.insert(StaticMethod("atan2", 1));
        static_methods.insert(StaticMethod("atanh", 1));
        static_methods.insert(StaticMethod("cbrt", 1));
        static_methods.insert(StaticMethod("ceil", 1));
        static_methods.insert(StaticMethod("clz32", 1));
        static_methods.insert(StaticMethod("cos", 1));
        static_methods.insert(StaticMethod("cosh", 1));
        static_methods.insert(StaticMethod("exp", 1));
        static_methods.insert(StaticMethod("expm1", 1));
        static_methods.insert(StaticMethod("f16round", 1));
        static_methods.insert(StaticMethod("floor", 1));
        static_methods.insert(StaticMethod("fround", 1));
        static_methods.insert(StaticMethod("hypot", {0,1,2,3}));
        static_methods.insert(StaticMethod("imul", 2));
        static_methods.insert(StaticMethod("log", 1));
        static_methods.insert(StaticMethod("log10", 1));
        static_methods.insert(StaticMethod("log1p", 1));
        static_methods.insert(StaticMethod("log2", 1));
        static_methods.insert(StaticMethod("max", {0,1,2,3}));
        static_methods.insert(StaticMethod("min", {0,1,2,3}));
        static_methods.insert(StaticMethod("pow", 2));
        static_methods.insert(StaticMethod("random", 0));
        static_methods.insert(StaticMethod("round", 1));
        static_methods.insert(StaticMethod("sign", 1));
        static_methods.insert(StaticMethod("sin", 1));
        static_methods.insert(StaticMethod("sinh", 1));
        static_methods.insert(StaticMethod("sqrt", 1));
        static_methods.insert(StaticMethod("tan", 1));
        static_methods.insert(StaticMethod("tanh", 1));
        static_methods.insert(StaticMethod("trunc", 1));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in Map
        const string name = "Map";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("groupBy", 2));

        //BuiltInObject object(name, constructor, static_methods, instance_methods);
        //this->built_in_objects.push_back(object);
    }

    {
        /// built-in String
        const string name = "String";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("fromCharCode", {0,1,2,3}));
        static_methods.insert(StaticMethod("fromCodePoint", {0,1,2,3}));
        static_methods.insert(StaticMethod("raw", {1,2,3}));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in Symbol
        const string name = "Symbol";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("for", 1));
        static_methods.insert(StaticMethod("keyFor", 1));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }

    {
        /// built-in TypedArray
        const string name = "TypedArray";
        const Constructor constructor(0);
        set<StaticMethod> static_methods;
        set<InstanceMethod> instance_methods;

        static_methods.insert(StaticMethod("from", {2,3}));
        static_methods.insert(StaticMethod("of", {0,1,2,3}));

        BuiltInObject object(name, constructor, static_methods, instance_methods);
        this->built_in_objects.push_back(object);
    }
}

} /// end namespace FuzzFlow