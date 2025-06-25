import * as t from "@babel/types";

function handle_VariableDeclaration(path) 
{
    if (!path || !path.node) {
        return;
    }

    const progPath = path.findParent(p => p.isProgram());
    if (progPath) {
        progPath.__varDecls.push(path);
    }
}

function handle_ExpressionStatement(path) 
{
    if (!path || !path.node) {
        return;
    }

    const expr = path.node.expression;
    if (
        t.isAssignmentExpression(expr) &&
        t.isFunctionExpression(expr.right) &&
        expr.right.id === null
    ) {
        const progPath = path.findParent(p => p.isProgram());
        if (progPath) {
            progPath.__assignExprs.push(path);
        }
    }
}

function exit_VariableDeclaration(path) 
{
    for (const p of path.__varDecls) {
        if (!p || !p.node || !t.isVariableDeclaration(p.node)) {
            continue;
        }

        const node = p.node;
        const replacements = [];
        
        for (const decl of node.declarations) {
            const { id, init } = decl;

            if (
                t.isIdentifier(id) &&
                t.isFunctionExpression(init) &&
                init.id === null
            ) {
                const funcDecl = t.functionDeclaration(
                    id,
                    init.params,
                    init.body,
                    init.generator,
                    init.async
                );
                t.inheritsComments(funcDecl, init);
                replacements.push(funcDecl);
            } else {
                replacements.push(t.variableDeclaration(node.kind, [decl]));
            }
        }

        if (replacements.length === 1 && t.isVariableDeclaration(replacements[0])) {
            p.replaceWith(replacements[0]);
        } 
        else {
            p.replaceWithMultiple(replacements);
        }
    }
}

function exit_AssignmentExpression(programPath) 
{
    for (const p of programPath.__assignExprs) {
        if (!p || !p.node) {
            continue;
        }
        
        const expr = p.node.expression;

        if (
            t.isAssignmentExpression(expr) &&
            t.isFunctionExpression(expr.right) &&
            expr.right.id === null
        ) {
            const tempId = p.scope.generateUidIdentifierBasedOnNode(expr.left);
            const funcDecl = t.functionDeclaration(
                tempId,
                expr.right.params,
                expr.right.body,
                expr.right.generator,
                expr.right.async
            );
            t.inheritsComments(funcDecl, expr.right);

            const assignExpr = t.expressionStatement(
                t.assignmentExpression("=", expr.left, tempId)
            );

            p.replaceWithMultiple([funcDecl, assignExpr]);
        }
    }
}

export default {
    Program: {
        enter(path) {
            path.__varDecls = [];
            path.__assignExprs = [];
        },

        exit(path) {
            exit_VariableDeclaration(path);
            exit_AssignmentExpression(path);
        },
    },

    VariableDeclaration(path) {
        handle_VariableDeclaration(path);
    },

    ExpressionStatement(path) {
        handle_ExpressionStatement(path);
    },
};
