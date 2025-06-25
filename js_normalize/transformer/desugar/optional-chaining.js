import * as t from "@babel/types";

function isOptional(node) {
    return t.isOptionalMemberExpression(node) || t.isOptionalCallExpression(node);
}

function unwrapChain(node) {
    const chain = [];
    while (isOptional(node)) {
        chain.unshift(node);
        node = t.isOptionalMemberExpression(node) ? node.object : node.callee;
    }
    chain.unshift(node);
    return chain;
}

function transformOptionalChain(path, getExpression) {
    const expr = getExpression(path);
    if (!isOptional(expr)) return;

    const chain = unwrapChain(expr);
    const { scope } = path;

    const declarations = [];
    const ids = [];

    let currentExpr = chain[0];
    let currentId = scope.generateUidIdentifier("temp0");
    declarations.push(t.variableDeclaration("let", [
        t.variableDeclarator(currentId, currentExpr)
    ]));
    ids.push(currentId);

    for (let i = 1; i < chain.length; i++) {
        const node = chain[i];
        const prevId = ids[ids.length - 1];
        const newId = scope.generateUidIdentifier(`temp${i}`);
        ids.push(newId);

        let access;
        if (t.isOptionalMemberExpression(node)) {
            access = t.memberExpression(prevId, node.property, node.computed);
        } else if (t.isOptionalCallExpression(node)) {
            access = t.callExpression(prevId, node.arguments);
        }

        const nullCheck = t.binaryExpression("==", prevId, t.nullLiteral());

        declarations.push(t.variableDeclaration("let", [
            t.variableDeclarator(
                newId,
                t.conditionalExpression(nullCheck, t.identifier("undefined"), access)
            )
        ]));
    }

    const final = ids[ids.length - 1];

    // Replace depending on context
    if (path.isExpressionStatement()) {
        path.replaceWithMultiple([
            ...declarations,
            t.expressionStatement(final),
        ]);
    } else if (path.isVariableDeclarator()) {
        path.get("init").replaceWith(final);
        path.parentPath.insertBefore(declarations); // Insert before the VariableDeclaration
    } else if (path.isAssignmentExpression()) {
        path.get("right").replaceWith(final);
        path.insertBefore(declarations);
    } else if (path.isReturnStatement()) {
        path.get("argument").replaceWith(final);
        path.insertBefore(declarations);
    } else if (path.isCallExpression()) {
        const parentPath = path.findParent(p => p.isExpressionStatement());
        if (parentPath) {
            parentPath.insertBefore(declarations);
        } else {
            path.replaceWithMultiple([
                ...declarations,
                final,
            ]);
        }
        path.replaceWith(final);
    } else {
        // fallback for other expression contexts
        path.replaceWithMultiple([
            ...declarations,
            final,
        ]);
    }
}

export default {
    ExpressionStatement(path) {
        transformOptionalChain(path, p => p.node.expression);
    },
    VariableDeclarator(path) {
        transformOptionalChain(path, p => p.node.init);
    },
    AssignmentExpression(path) {
        transformOptionalChain(path, p => p.node.right);
    },
    ReturnStatement(path) {
        transformOptionalChain(path, p => p.node.argument);
    },
    CallExpression(path) {
        transformOptionalChain(path, p => p.node);
    }
};
