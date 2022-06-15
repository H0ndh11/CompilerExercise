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
	case Begin:
		nextToken();
		compileBeginEnd();
		break;
	case If:
		nextToken();
		compileIf();
		break;
	default:
		break;
	}
}

void Compiler::compileWrite() {
	//if (token.kind != Num) {
	//	exit(1);//構文エラー
	//}
	//codebuilder.emitLit(token.value);


	compileExpression();
	codebuilder.emitOprWrt();
	//nextToken();

	
	/*if (source.source != ".") {
		std::cerr << "構文エラー" << std::endl;
	}
	Inst inst(ret, nop, 0, 0, 0, 0, 0);
	std::vector<Inst> code;
	code.push_back(inst);
	return code;
	}*/
}

void Compiler::compileWriteLn() {
	codebuilder.emitOprWrtLn();
	//nextToken();
}

void Compiler::compileExpression() {
	//最初に出てくる項が負の数かどうか
	bool shouldEmitNeg = false;

	//+と-の場合の処理
	switch (token.kind) {
	case Plus:
		nextToken();
		break;
	case Minus:
		shouldEmitNeg = true;
		nextToken();
		break;
	default:
		break;
	}

	compileTerm();
	//負の数であった場合
	if (shouldEmitNeg) {
		codebuilder.emitOprNeg();
	}

	//トークンがPlus，Minusの場合
	while (true) {
		if (token.kind == Plus) {
			nextToken();
			compileTerm();
			codebuilder.emitOprAdd();
			continue;
		}
		else if (token.kind == Minus) {
			nextToken();
			compileTerm();
			codebuilder.emitOprSub();
			continue;
		}
		//PlusでもMinusでもなければ抜け出す
		break;
	}
}

void Compiler::compileTerm() {
	compileFactor();

	//トークンがMult，Divの場合
	while (true) {
		if (token.kind == Mult) {
			nextToken();
			compileFactor();
			codebuilder.emitOprMul();
			continue;
		}
		else if (token.kind == Div) {
			nextToken();
			compileFactor();
			codebuilder.emitOprDiv();
			continue;
		}
		break;
	}
}

void Compiler::compileFactor() {
	if (token.kind == Num) {
		codebuilder.emitLit(token.value);
		nextToken();
		return;
	}
	if (token.kind == Lparen) {
		nextToken();
		compileExpression();
		//この段階でトークンがRparenではなかったらプログラム停止
		if (token.kind != Rparen) {
			exit(1);
		}
		nextToken();
		return;
	}
	//数値が(expression)以外なら文法エラー
	std::cerr << "Syntax error\n";
	exit(1);
}

void Compiler::compileBeginEnd() {
	while (true) {
		//statement; という形の間，つまり';'が続く限りループ(図2.30参考)
		compileStatement();
		if (token.kind == Semicolon) {
			nextToken();
			continue;
		}
		ensureToken(End);
		break;
	}
}

Token Compiler::ensureToken(KeyId kind) {
	Token _token = token;

	//_token.kindとkindが一致しない時にエラー
	if (_token.kind != kind) {
		std::cerr << "Syntax error" << kind << "\n";
		exit(1);
	}

	nextToken();
	return _token; //確認したトークンを返す
}

void Compiler::compileIf() {
	compileCondition();
	ensureToken(Then);
	int jpcInst = codebuilder.emitJpc(0);
	compileStatement();
	codebuilder.backPatch(jpcInst, codebuilder.currentIndex);
}

void Compiler::compileCondition() {
	if (token.kind == Odd) {
		nextToken();
		compileExpression();
		codebuilder.emitOprOdd();
	}
	else {
		compileExpression();
		switch (token.kind)
		{
		case Equal:
			nextToken();
			compileExpression();
			codebuilder.emitOprEq();
			break;
		case NotEq:
			nextToken();
			compileExpression();
			codebuilder.emitOprNeq();
			break;
		case Lss:
			nextToken();
			compileExpression();
			codebuilder.emitOprLs();
			break;
		case LssEq:
			nextToken();
			compileExpression();
			codebuilder.emitOprLseq();
			break;
		case Gtr:
			nextToken();
			compileExpression();
			codebuilder.emitOprGr();
			break;
		case GtrEq:
			nextToken();
			compileExpression();
			codebuilder.emitOprGreq();
			break;
		default:
			break;
		}
	}
}