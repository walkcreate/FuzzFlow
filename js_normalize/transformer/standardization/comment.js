
function handle_program(path)
{
    path.traverse({
        enter(innerPath) {
            if (innerPath.node.leadingComments) {
                delete innerPath.node.leadingComments;
            }
            if (innerPath.node.trailingComments) {
                delete innerPath.node.trailingComments;
            }
            if (innerPath.node.innerComments) {
                delete innerPath.node.innerComments;
            }
        }
    });
}

export default {
    Program: {
        enter(path) {
            handle_program(path)
        }
    }
};
