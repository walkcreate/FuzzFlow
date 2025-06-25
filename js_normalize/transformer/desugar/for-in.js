import * as t from "@babel/types";

function handle_ForInStatement(path)
{
    const { left, right, body } = path.node;

    const keysId = path.scope.generateUidIdentifier("forIn_keys");
    const iId = path.scope.generateUidIdentifier("forIn_i");

    // const keys = Object.keys(right);
    const keysInit = t.variableDeclaration("const", [
        t.variableDeclarator(
            keysId,
            t.callExpression(
                t.memberExpression(t.identifier("Object"), t.identifier("keys")),
                [right]
            )
        ),
    ]);

    // keys[i]
    const keyAccessExpr = t.memberExpression(keysId, iId, true);

    let assignStmt;
    if (t.isVariableDeclaration(left)) {
        assignStmt = t.variableDeclaration(left.kind, [
            t.variableDeclarator(left.declarations[0].id, keyAccessExpr),
        ]);
    } else if (t.isPattern(left) || t.isIdentifier(left)) {
        assignStmt = t.expressionStatement(
            t.assignmentExpression("=", left, keyAccessExpr)
        );
    } else {
        throw path.buildCodeFrameError("Unsupported left-hand side in for-in loop.");
    }

    const loop = t.forStatement(
        t.variableDeclaration("let", [
            t.variableDeclarator(iId, t.numericLiteral(0)),
        ]),
        t.binaryExpression(
            "<",
            iId,
            t.memberExpression(keysId, t.identifier("length"))
        ),
        t.updateExpression("++", iId),
        t.blockStatement([
            assignStmt,
            ...(t.isBlockStatement(body) ? body.body : [body]),
        ])
    );

    // replace initial ForInStatement
    path.replaceWithMultiple([keysInit, loop]);
}

export default {
    ForInStatement(path) {
        handle_ForInStatement(path);
    },
};
