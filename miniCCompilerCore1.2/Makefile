.PHONY:clean

OBJ=main.o token.o \
	analysisTable.o \
	analysisTableItem.o \
	code.o \
	codeList.o \
	codeOptimization.o \
	fileOperation.o \
	first.o \
	follow.o \
	fourElementType.o \
	fourElementTypeItem.o \
	functionDefinition.o \
	grammarAnalysis.o \
	grammar.o \
	grammarTreeTmp.o \
	lexicalAnalysisAnimation.o \
	lexicalAnalysis.o \
	LL_1_Analysis.o \
	LL_1_AnalysisItem.o \
	node.o \
	objectCodeGeneration.o \
	objectCodeGeneration_Linux.o \
	objectCodeGeneration_x86.o \
	parameterList.o \
	production.o \
	semanticAnalysis.o \
	tree.o \
	variableDefinition.o \
	variableList.o

main:$(OBJ)
	g++ -Wall -g $^ -o $@ -std=c++11

main.o: main.cpp
	g++ -Wall -c $^ -o $@ -std=c++11


analysisTable.o: analysisTable.cpp
	g++ -Wall -c $^ -o $@ -std=c++11


analysisTableItem.o: analysisTableItem.cpp
	g++ -Wall -c $^ -o $@ -std=c++11


code.o: code.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

codeList.o: codeList.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

codeOptimization.o: codeOptimization.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

fileOperation.o: fileOperation.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

first.o: first.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

follow.o: follow.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

fourElementType.o: fourElementType.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

fourElementTypeItem.o: fourElementTypeItem.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

functionDefinition.o: functionDefinition.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

grammarAnalysis.o: grammarAnalysis.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

grammar.o: grammar.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

grammarTreeTmp.o: grammarTreeTmp.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

lexicalAnalysisAnimation.o: lexicalAnalysisAnimation.cpp
	g++ -c $^ -o $@ -std=c++11

lexicalAnalysis.o: lexicalAnalysis.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

LL_1_Analysis.o: LL_1_Analysis.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

LL_1_AnalysisItem.o: LL_1_AnalysisItem.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

node.o: node.cpp
	g++ -c $^ -o $@ -std=c++11

objectCodeGeneration.o: objectCodeGeneration.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

objectCodeGeneration_Linux.o: objectCodeGeneration_Linux.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

objectCodeGeneration_x86.o: objectCodeGeneration_x86.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

parameterList.o: parameterList.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

production.o: production.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

semanticAnalysis.o: semanticAnalysis.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

token.o: token.cpp
	g++ -c $^ -o $@ -std=c++11

tree.o: tree.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

variableDefinition.o: variableDefinition.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

variableList.cpp.o: variableList.cpp.cpp
	g++ -Wall -c $^ -o $@ -std=c++11

clean:
	rm -f *.o main
