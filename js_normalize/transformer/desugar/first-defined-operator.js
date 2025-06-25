import * as t from "@babel/types";

///
/// first-defined operator: ??
///

export default {
    LogicalExpression(path) {
        if (path.node.operator !== "??") return;

        const { left, right } = path.node;
        path.replaceWith(
            t.conditionalExpression(
                t.binaryExpression("!=", left, t.nullLiteral()),
                left,
                right
            )
        );
    }
};
