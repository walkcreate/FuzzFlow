import * as t from "@babel/types";

function handle_VariableDeclaration(path) 
{
    const newDeclarations = [];

    function processPattern(pattern, source) {
        if (!source) {
            throw new Error("Destructuring pattern must have a source expression");
        }

        if (t.isObjectPattern(pattern)) {
            for (const prop of pattern.properties) {
                if (t.isRestElement(prop)) {
                    // Rest properties in destructuring are non-trivial and may need helper functions
                    console.warn("RestElement in object pattern not supported yet.");
                    continue;
                }

                const key = prop.key;
                const computed = prop.computed || false;
                const value = prop.value;

                const access = t.memberExpression(source, key, computed);

                if (t.isAssignmentPattern(value)) {
                    newDeclarations.push(
                        t.variableDeclarator(
                            value.left,
                            t.conditionalExpression(
                                t.binaryExpression("===",
                                    t.memberExpression(source, key, computed),
                                    t.identifier("undefined")
                                ),
                                value.right,
                                access
                            )
                        )
                    );
                } else if (t.isObjectPattern(value) || t.isArrayPattern(value)) {
                    const tempId = path.scope.generateUidIdentifierBasedOnNode(key);
                    newDeclarations.push(t.variableDeclarator(tempId, access));
                    processPattern(value, tempId);
                } else {
                    newDeclarations.push(t.variableDeclarator(value, access));
                }
            }

        } else if (t.isArrayPattern(pattern)) {
            pattern.elements.forEach((elem, index) => {
                if (!elem) return;

                const access = t.memberExpression(source, t.numericLiteral(index), true);

                if (t.isAssignmentPattern(elem)) {
                    newDeclarations.push(
                        t.variableDeclarator(
                            elem.left,
                            t.conditionalExpression(
                                t.binaryExpression("===",
                                    access,
                                    t.identifier("undefined")
                                ),
                                elem.right,
                                access
                            )
                        )
                    );
                } else if (t.isRestElement(elem)) {
                    console.warn("RestElement in array pattern not supported yet.");
                } else if (t.isArrayPattern(elem) || t.isObjectPattern(elem)) {
                    const tempId = path.scope.generateUidIdentifier("elem");
                    newDeclarations.push(t.variableDeclarator(tempId, access));
                    processPattern(elem, tempId);
                } else {
                    newDeclarations.push(t.variableDeclarator(elem, access));
                }
            });
        }
    }

    let changed = false;

    for (const decl of path.node.declarations) {
        const id = decl.id;
        const init = decl.init;

        // skip declaration without init, e.g., `const [a];`
        if (!init || (!t.isObjectPattern(id) && !t.isArrayPattern(id))) {
            newDeclarations.push(decl);
            continue;
        }

        processPattern(id, init);
        changed = true;
    }

    if (changed) {
        path.replaceWith(t.variableDeclaration(path.node.kind, newDeclarations));
    }
}

export default {
    VariableDeclaration(path) {
        handle_VariableDeclaration(path)
    }
};
