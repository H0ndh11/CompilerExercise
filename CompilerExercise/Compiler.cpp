#include <iostream>
#include "Compiler.h"


//コンストラクタで次のtokenを入手する関数呼び出し
//CompilerクラスについてはCompiler.h参照
Compiler::Compiler(std::string& str)
	:source(str)
{
	nextToken();
}

//次のtokenを入手
void Compiler::nextToken() {
	token = source.nextToken();
}

Compiler::~Compiler()
{
}
std::vector<Inst> Compiler::compile()
{
	compileBlock();

	return codebuilder.getCode();
}

void Compiler::compileBlock() {
	compileStatement();
	codebuilder.emitRet(0, 0);
}

void Compiler::compileStatement() {
	switch (token.kind) {
	case Write:
		nextToken();
		compileWrite();
		break;
	case WriteLn:
		nextToken();
		compileWriteLn();
		break;
	default:
		break;
	}
}

void Compiler::compileWrite() {
	if (token.kind != Num) {
		exit(1);//構文エラー
	}
	codebuilder.emitLit(token.value);
	codebuilder.emitOprWrt();

	nextToken();
}/*if (source.source != ".") {
		std::cerr << "構文エラー" << std::endl;
	}
	Inst inst(ret, nop, 0, 0, 0, 0, 0);
	std::vector<Inst> code;
	code.push_back(inst);
	return code;
}*/

void Compiler::compileWriteLn() {
	codebuilder.emitOprWrtLn();
	nextToken();
}