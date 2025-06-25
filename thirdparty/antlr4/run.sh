
java -Xmx500M -cp "/media/Store/bin/antlr/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr4.v4.Tool -Dlanguage=Cpp -visitor JavaScriptLexer.g4

java -Xmx500M -cp "/media/Store/bin/antlr/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr4.v4.Tool -Dlanguage=Cpp -visitor JavaScriptParser.g4



java -Xmx500M -cp "/media/Store1/Tools/antlr4/antlr-4.10-complete.jar:$CLASSPATH" org.antlr4.v4.Tool -Dlanguage=Cpp -visitor JavaScriptLexer.g4

java -Xmx500M -cp "/media/Store1/Tools/antlr4/antlr-4.10-complete.jar:$CLASSPATH" org.antlr4.v4.Tool -Dlanguage=Cpp -visitor JavaScriptParser.g4

export CLASSPATH="/media/Store1/Tools/antlr4/antlr-4.10-complete.jar:$CLASSPATH"

alias antlr4='java -Xmx500M -cp "/media/Store1/Tools/antlr4/antlr-4.10-complete.jar:$CLASSPATH" org.antlr.v4.Tool'

alias grun='java -Xmx500M -cp "/media/Store1/Tools/antlr4/antlr-4.10-complete.jar:$CLASSPATH" org.antlr.v4.gui.TestRig'


export CLASSPATH="/media/Store1/Tools/antlr4/antlr-4.10.1-complete.jar:$CLASSPATH"

alias antlr4='java -Xmx500M -cp "/media/Store1/Tools/antlr4/antlr-4.10.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool'

alias grun='java -Xmx500M -cp "/media/Store1/Tools/antlr4/antlr-4.10.1-complete.jar:$CLASSPATH" org.antlr.v4.gui.TestRig'

antlr4 -Dlanguage=Cpp -visitor JavaScriptLexer.g4
antlr4 -Dlanguage=Cpp -visitor JavaScriptParser.g4
