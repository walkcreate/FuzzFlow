import comment from "./standardization/comment.js";
import hoisting from "./standardization/hoisting.js";
import expandComma from "./standardization/expand-comma-expression.js";
import functionExpression from "./standardization/function-expression.js";

import optionalChaining from "./desugar/optional-chaining.js";
import firstDefinedOperator from "./desugar/first-defined-operator.js";
import destructuring from "./desugar/destructuring.js";
import forOf from "./desugar/for-of.js";
import forIn from "./desugar/for-in.js";
import classTransform from "./desugar/class.js";
import arrowFunction from "./desugar/arrow-function.js";

const plugins = [
    comment,
    hoisting,
    expandComma,
    destructuring,
    
    arrowFunction,
    functionExpression,
    optionalChaining,
    firstDefinedOperator,
    
    forOf,
    forIn,
    classTransform,
];

export default plugins;
