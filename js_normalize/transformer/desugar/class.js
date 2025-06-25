import * as t from "@babel/types";

function handle_ClassDeclaration(path) 
{
    const { id, body, superClass } = path.node;

    const constructorMethod = body.body.find(el => t.isClassMethod(el) && el.kind === "constructor");
    const ctorParams = constructorMethod ? constructorMethod.params : [];
    const ctorBody = constructorMethod ? constructorMethod.body.body : [];

    const ctorFunc = t.functionDeclaration(id, ctorParams, t.blockStatement([
        ...(superClass
            ? [t.expressionStatement(
                t.callExpression(
                    t.memberExpression(superClass, t.identifier("call")),
                    [t.thisExpression(), ...ctorParams.map(p => t.cloneDeep(p))]
                )
            )]
            : []),
        ...ctorBody
    ]));

    const helperStatements = [];

    for (const el of body.body) {
        if (!t.isClassMethod(el)) continue;
        if (el.kind === "constructor") continue;

        const fn = t.functionExpression(null, el.params, el.body, el.generator, el.async);

        const targetObject = el.static
            ? id
            : t.memberExpression(id, t.identifier("prototype"));

        const assignment = t.expressionStatement(
            t.assignmentExpression(
                "=",
                t.memberExpression(targetObject, el.key, el.computed || false),
                fn
            )
        );

        helperStatements.push(assignment);
    }

    path.replaceWithMultiple([ctorFunc, ...helperStatements]);
}

export default {
    ClassDeclaration(path) {
        handle_ClassDeclaration(path);
    }
};