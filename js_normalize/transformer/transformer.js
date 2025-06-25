import * as parser from "@babel/parser";
import traverse from "@babel/traverse";
import generate from "@babel/generator";
import prettier from "prettier";

import plugins from "./plugins.js";

export async function transformFile(code) {
    try {
        const ast = parser.parse(code, {
            sourceType: "module",
            plugins: ["jsx"],
        });

        for (const plugin of plugins) {
            traverse.default(ast, plugin);
        }

        const { code: transformed } = generate.default(ast);

        const formatted = await prettier.format(transformed, {
            parser: "babel",
            tabWidth: 4,
            useTabs: false
          });
          
        return formatted;
    } 
    catch (err) {
        console.error("❌ Transform error:", err.message);
        return null;
    }
}
