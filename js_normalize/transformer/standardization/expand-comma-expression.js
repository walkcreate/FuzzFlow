import * as t from "@babel/types";

const processedNodes = new WeakSet();

function handle_ExpressionStatement(path) 
{
    if (processedNodes.has(path.node)) 
        return;
    
    const expr = path.node.expression;
    
    if (t.isSequenceExpression(expr)) {
        const stmts = expr.expressions.map(e => {
            const stmt = t.expressionStatement(e);
            processedNodes.add(stmt);
            return stmt;
        });
        processedNodes.add(path.node);
        path.replaceWithMultiple(stmts);
    }
}

function handle_VariableDeclaration(path) 
{
    if (path.parentPath.isForInStatement() || path.parentPath.isForOfStatement()) {
        return;
    }

    if (processedNodes.has(path.node)) 
        return;

    const newStmts = [];

    for (const decl of path.node.declarations) {
        const init = decl.init;

        if (t.isSequenceExpression(init)) {
            const seq = init.expressions;
            for (let i = 0; i < seq.length - 1; i++) {
                const stmt = t.expressionStatement(seq[i]);
                processedNodes.add(stmt);
                newStmts.push(stmt);
            }
            const finalDecl = t.variableDeclaration(path.node.kind, [
                t.variableDeclarator(decl.id, seq[seq.length - 1]),
            ]);
            processedNodes.add(finalDecl);
            newStmts.push(finalDecl);

        } else if (t.isNewExpression(init)) {
            const args = init.arguments;
            const preceding = [];

            for (let i = 0; i < args.length; i++) {
                if (t.isSequenceExpression(args[i])) {
                    const seq = args[i].expressions;
                    for (let j = 0; j < seq.length - 1; j++) {
                        const stmt = t.expressionStatement(seq[j]);
                        processedNodes.add(stmt);
                        preceding.push(stmt);
                    }
                    args[i] = seq[seq.length - 1];
                }
            }

            const newDecl = t.variableDeclaration(path.node.kind, [
                t.variableDeclarator(decl.id, init),
            ]);
            processedNodes.add(newDecl);
            newStmts.push(...preceding, newDecl);

        } else {
            const copy = t.variableDeclaration(path.node.kind, [decl]);
            processedNodes.add(copy);
            newStmts.push(copy);
        }
    }

    if (newStmts.length > 0) {
        processedNodes.add(path.node);
        const stmtParent = path.getStatementParent();
        stmtParent.insertBefore(newStmts);
        path.remove();
    }
}

function handle_ReturnStatement(path) 
{
    if (processedNodes.has(path.node)) 
        return;
    
    const arg = path.node.argument;
    if (arg && t.isSequenceExpression(arg)) {
        const seq = arg.expressions;
        const stmts = seq.slice(0, -1).map(e => {
            const stmt = t.expressionStatement(e);
            processedNodes.add(stmt);
            return stmt;
        });
        const ret = t.returnStatement(seq[seq.length - 1]);
        processedNodes.add(ret);
        stmts.push(ret);
        processedNodes.add(path.node);
        path.replaceWithMultiple(stmts);
    }
}

function handle_AssignmentExpression(path) 
{
    if (processedNodes.has(path.node)) 
        return;

    const right = path.node.right;
    if (t.isSequenceExpression(right)) {
        const seq = right.expressions;
        const exprs = seq.slice(0, -1).map(e => {
            const stmt = t.expressionStatement(e);
            processedNodes.add(stmt);
            return stmt;
        });
        const finalAssign = t.assignmentExpression("=", path.node.left, seq[seq.length - 1]);
        const stmt = t.expressionStatement(finalAssign);
        processedNodes.add(stmt);
        exprs.push(stmt);
        processedNodes.add(path.node);
        path.replaceWithMultiple(exprs);
    }
}

function handle_CallExpression(path) 
{
    if (processedNodes.has(path.node)) 
        return;
    
    const args = path.node.arguments;
    for (let i = 0; i < args.length; i++) {
        const arg = args[i];
        if (t.isSequenceExpression(arg)) {
            const seq = arg.expressions;
            const preceding = seq.slice(0, -1).map(e => {
                const stmt = t.expressionStatement(e);
                processedNodes.add(stmt);
                return stmt;
            });
            args[i] = seq[seq.length - 1];
            path.insertBefore(preceding);
        }
    }
    
    processedNodes.add(path.node);
}

function handle_NewExpression(path) 
{
    if (processedNodes.has(path.node)) 
        return;
    
    const args = path.node.arguments;
    for (let i = 0; i < args.length; i++) {
        const arg = args[i];
        if (t.isSequenceExpression(arg)) {
            const seq = arg.expressions;
            const preceding = seq.slice(0, -1).map(e => {
                const stmt = t.expressionStatement(e);
                processedNodes.add(stmt);
                return stmt;
            });
            args[i] = seq[seq.length - 1];
            path.insertBefore(preceding);
        }
    }

    processedNodes.add(path.node);
}

function handle_ConditionalExpression(path) 
{
    if (processedNodes.has(path.node)) 
        return;
    
    ["test", "consequent", "alternate"].forEach((key) => {
        const sub = path.node[key];
        if (t.isSequenceExpression(sub)) {
            const seq = sub.expressions;
            const pre = seq.slice(0, -1).map(e => {
                const stmt = t.expressionStatement(e);
                processedNodes.add(stmt);
                return stmt;
            });
            path.node[key] = seq[seq.length - 1];
            const stmtPath = path.getStatementParent();
            if (stmtPath) {
                stmtPath.insertBefore(pre);
            }
        }
    });

    processedNodes.add(path.node);
}

export default {
    ExpressionStatement(path) {
        handle_ExpressionStatement(path);
    },

    VariableDeclaration(path) {
        handle_VariableDeclaration(path);
    },

    ReturnStatement(path) {
        handle_ReturnStatement(path);
    },

    AssignmentExpression(path) {
        handle_AssignmentExpression(path);
    },

    CallExpression(path) {
        handle_CallExpression(path);
    },

    NewExpression(path) {
        handle_NewExpression(path);
    },

    ConditionalExpression(path) {
        handle_ConditionalExpression(path);
    },
};
