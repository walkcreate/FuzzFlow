import * as t from "@babel/types";

function handle_ForOfStatement(path) 
{
    const { left, right, body } = path.node;
    const arrId = path.scope.generateUidIdentifier("arr");
    const iId = path.scope.generateUidIdentifier("i");

    const arrInit = t.variableDeclaration("const", [
        t.variableDeclarator(arrId, right),
    ]);

    const loopBody = t.cloneNode(body, true);
    const loop = t.forStatement(
        t.variableDeclaration("let", [t.variableDeclarator(iId, t.numericLiteral(0))]),
        t.binaryExpression("<", iId, t.memberExpression(arrId, t.identifier("length"))),
        t.updateExpression("++", iId),
        t.blockStatement([
            t.isVariableDeclaration(left)
                ? t.variableDeclaration(left.kind, [
                    t.variableDeclarator(
                        left.declarations[0].id,
                        t.memberExpression(arrId, iId, true)
                    ),
                ])
                : t.expressionStatement(
                    t.assignmentExpression(
                        "=",
                        left,
                        t.memberExpression(arrId, iId, true)
                    )
                ),
            ...(t.isBlockStatement(loopBody) ? loopBody.body : [loopBody]),
        ])
    );

    path.replaceWithMultiple([arrInit, loop]);
}

export default {
    ForOfStatement(path) {
        handle_ForOfStatement(path);
    }
};
