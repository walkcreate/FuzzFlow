let counter = 0;

function generateUniqueName(base = "arrowFn") {
    return `_${base}_${counter++}`;
}

function getInsertionScope(path) {
    return path.findParent(p => p.isBlockStatement() || p.isProgram());
}

function isConvertibleToDeclaration(path) {
    const parentPath = path.parentPath;
    return (
        parentPath.isVariableDeclarator() &&
        parentPath.node.id.type === "Identifier" &&
        parentPath.parentPath.isVariableDeclaration()
    );
}

function createFunctionDeclaration(name, params, body, isAsync = false) {
    return {
        type: "FunctionDeclaration",
        id: { type: "Identifier", name },
        params,
        body,
        generator: false,
        async: isAsync,
    };
}

function handle_ArrowFunctionExpression(path) 
{
    const { node, scope, parentPath } = path;
    const body = node.body.type === "BlockStatement"
        ? node.body
        : {
            type: "BlockStatement",
            body: [{ type: "ReturnStatement", argument: node.body }],
        };
    const params = node.params;

    // Case: export default () => {}
    if (parentPath.isExportDefaultDeclaration()) {
        const uniqueName = generateUniqueName("exported");
        const decl = createFunctionDeclaration(uniqueName, params, body, node.async);
        const program = path.findParent(p => p.isProgram());
        program.unshiftContainer("body", decl);

        parentPath.replaceWith({
            type: "ExportDefaultDeclaration",
            declaration: { type: "Identifier", name: uniqueName }
        });
        return;
    }

    // Case: variable assignment
    if (isConvertibleToDeclaration(path)) {
        const varId = parentPath.node.id;
        const name = varId.name;

        if (!scope.hasBinding(name, true)) {
            const funcDecl = createFunctionDeclaration(name, params, body, node.async);
            parentPath.parentPath.replaceWith(funcDecl);
            return;
        }
    }

    // Default fallback — create standalone function and replace with reference
    const uniqueName = generateUniqueName("fn");
    const decl = createFunctionDeclaration(uniqueName, params, body, node.async);
    const insertionScope = getInsertionScope(path);
    insertionScope.unshiftContainer("body", decl);
    const idRef = { type: "Identifier", name: uniqueName };

    // Context-sensitive replacements
    if (parentPath.isObjectProperty() && parentPath.node.value === node) {
        parentPath.node.value = idRef;
    } else if (parentPath.isCallExpression() && parentPath.node.callee === node) {
        parentPath.node.callee = idRef;
    } else if (parentPath.isReturnStatement()) {
        path.replaceWith(idRef);
    } else if (parentPath.isArrayExpression()) {
        path.replaceWith(idRef);
    } else if (parentPath.isConditionalExpression()) {
        if (parentPath.node.consequent === node) {
            parentPath.node.consequent = idRef;
        } else if (parentPath.node.alternate === node) {
            parentPath.node.alternate = idRef;
        }
    } else if (parentPath.isClassProperty() && parentPath.node.value === node) {
        parentPath.node.value = idRef;
    } else {
        path.replaceWith(idRef);
    }
}

export default {
    ArrowFunctionExpression(path) {
        handle_ArrowFunctionExpression(path);
    }
};
