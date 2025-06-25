
java -Xmx500M -cp "/path_to/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr4.v4.Tool -Dlanguage=Cpp -visitor JavaScriptLexer.g4

java -Xmx500M -cp "/path_to/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr4.v4.Tool -Dlanguage=Cpp -visitor JavaScriptParser.g4

