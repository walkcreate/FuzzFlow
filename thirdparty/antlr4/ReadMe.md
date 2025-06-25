# Build

1. Download JavaScriptLexer.g4 and JavaScriptParser.g4, then modify them for C++ runtime according to the official documentation.

2. Download JavaScriptLexerBase.h/cpp and JavaScriptParserBase.h/cpp.

3. Generate remaining files using antlr-4.9.3 complete jar.
```
export CLASSPATH=".:/path_to/antlr-4.9.3-complete.jar:$CLASSPATH"
alias antlr4='java -Xmx500M -cp "/path_to/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr.v4.Tool'
alias grun='java -Xmx500M -cp "/path_to/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr.v4.gui.TestRig'

antlr4 -Dlanguage=Cpp -visitor JavaScriptLexer.g4
antlr4 -Dlanguage=Cpp -visitor JavaScriptParser.g4
```

Note: antlr-4.9.3-complete.jar runs with Java 8.
C++ runtime should be built from commit-70b2edc.

# Additional Notes

The `antlr4/JavaScriptParser.h` is patched.

The generated JavaScriptParserBaseVisitor.h and JavaScriptParserVisitor.h from antlr-4.9.3 still use `antlrcpp::Any` as visitor return type, while AbstractParseTreeVisitor.h in C++ runtime has been updated to use std::any.

Testing showed that using ANTLR 4.10 to generate files in step 3 causes version mismatch and compilation failures. Consider building a new antlr-4.9.3-complete.jar from commit-70b2edc for compatibility.
