import * as t from "@babel/types";

function isFunctionDeclaration(path) 
{
    return (
        t.isFunctionDeclaration(path.node) &&
        path.parentPath &&
        (path.parentPath.isProgram() || path.parentPath.isBlockStatement())
    );
}

function hoistFunctionDeclarations(bodyPaths) 
{
    const functionDecls = [];
    const others = [];

    for (const path of bodyPaths) {
        if (isFunctionDeclaration(path)) {
            functionDecls.push(path.node);
            path.remove();
        } else {
            others.push(path);
        }
    }

    return [...functionDecls, ...others.map(p => p.node)];
}

function hoistVarDeclarations(path) 
{
    const body = path.get("body").body;
    const hoistedVars = [];
    const keepInPlace = [];

    path.traverse({
        VariableDeclaration(innerPath) {
            if (!t.isVariableDeclaration(innerPath.node, { kind: "var" })) return;

            const declarators = innerPath.node.declarations;
            const toHoist = [];
            const initAssignments = [];

            for (const decl of declarators) {
                if (t.isIdentifier(decl.id)) {
                    toHoist.push(t.variableDeclarator(decl.id, null));
                    if (decl.init) {
                        initAssignments.push(
                            t.expressionStatement(
                                t.assignmentExpression("=", decl.id, decl.init)
                            )
                        );
                    }
                }
                // to extend: destruct
            }

            if (toHoist.length > 0) {
                hoistedVars.push(...toHoist);
            }

            if (initAssignments.length > 0) {
                innerPath.replaceWithMultiple(initAssignments);
            } else {
                innerPath.remove();
            }
        },
    });

    if (hoistedVars.length > 0) {
        path.get("body").unshiftContainer(
            "body",
            t.variableDeclaration("var", hoistedVars)
        );
    }
}

function processScope(path) 
{
    const bodyPath = path.get("body");

    if (!bodyPath || !bodyPath.node || bodyPath.node.type !== "BlockStatement") 
        return;

    const bodyPaths = bodyPath.get("body");

    const newBody = hoistFunctionDeclarations(bodyPaths);

    path.get("body").set("body", newBody);

    hoistVarDeclarations(path);
}

export default {
    Program(path) {
        processScope(path);
    },
    FunctionDeclaration(path) {
        processScope(path);
    },
    FunctionExpression(path) {
        processScope(path);
    },
    ArrowFunctionExpression(path) {
        if (t.isBlockStatement(path.node.body)) {
            processScope(path.get("body"));
        }
    },
};
