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
	int jmpInst = codebuilder.emitJmp(0);
	//ConstDeclが0回以上ループ
	while (true) {
		if (token.kind == Const) {
			nextToken();
			compileConstDecl();
			continue;
		}
		if (token.kind == Var) {
			nextToken();
			compileVarDecl();
			continue;
		}
		if (token.kind == Func) {
			nextToken();
			compileFunctionDecl();
			continue;
		}
		else {
			break;
		}
	}

	codebuilder.backPatch(jmpInst, codebuilder.currentIndex);

	codebuilder.emitIct(nametable.localAddress);

	//Statementへ
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
	//step5ではこれも忘れずに！（資料に記載なし）
	case If:
		nextToken();
		compileIf();
		break;
	case Id:
		compileAssign(token.id);
		break;
	case While:
		nextToken();
		compileWhile();
		break;
	case Ret:
		nextToken();
		compileRet();
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
	else if (token.kind == Lparen) {
		nextToken();
		compileExpression();
		//この段階でトークンがRparenではなかったらプログラム停止
		if (token.kind != Rparen) {
			exit(1);
		}
		nextToken();
		return;
	}
	else if(token.kind == Id) {
		std::string name = token.id;
		nextToken();
		compileIdentifier(name);
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

void Compiler::compileWhile() {	//compileIfにループ動作を加える
	int startIndex = codebuilder.currentIndex;	//戻ってこれるようにアドレス記録
	compileCondition();
	ensureToken(Do);
	int jpcInst = codebuilder.emitJpc(0);
	compileStatement();
	codebuilder.emitJmp(startIndex);	//topが0ならループ
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

void Compiler::compileConstDecl() {
	while (true) {
		//定数宣言の構文解析
		//x = 10 のようにId, Equal, Numの順
		std::string name = ensureToken(Id).id;
		ensureToken(Equal);
		int value = ensureToken(Num).value;

		//nametableに定数名とその値追加
		nametable.addConst(name, value);
		if (token.kind == Comma) {	//複数の定数宣言に対応
			nextToken();
			continue;
		}
		//最後はセミコロンがくるはず
		ensureToken(Semicolon);
		break;
	}
}

void Compiler::compileIdentifier(std::string& name) {
	TableEntry entry = nametable.search(name);
	switch (entry.kind) {
	case Const:
		//仮想機械のスタックの戦闘に見つけてきた定数の数値を積む命令コードを出力
		codebuilder.emitLit(entry.value);
		break;
	case Var:
		codebuilder.emitLod(entry.level, entry.relAdress);
		break;
	case Param:
		codebuilder.emitLod(entry.level, entry.relAdress);
		break;
	case Func:
		compileCall(entry);
		break;
	default:
		//もしnametable上に存在しなければ
		std::cerr << name << " is not in the name table. \n";
		exit(1);
	}
}

void Compiler::compileAssign(std::string& name) {
	TableEntry entry = nametable.search(name);
	if (entry.kind == nul) {
		std::cerr << "Cannot find the name " << name << "\n";
		exit(1);
	}
	if (entry.kind != Var) {
		std::cerr << "Ihs is not variable \n";
		exit(1);
	}
	nextToken();
	ensureToken(Assign);
	compileExpression();
	codebuilder.emitSto(entry.level, entry.relAdress);
}

void Compiler::compileVarDecl() {
	while (true) {
		std::string name = ensureToken(Id).id;
		nametable.addVar(name);

		if (token.kind == Comma) {	//複数の変数宣言に対応
			nextToken();
			continue;
		}
		//最後はセミコロンがくるはず
		ensureToken(Semicolon);
		break;
	}
}

void Compiler::compileFunctionDecl() {
	std::string functionName = ensureToken(Id).id;
	nametable.addFunction(functionName, codebuilder.currentIndex);
	ensureToken(Lparen);

	while (true)
	{
		if (token.kind == Id) {
			std::string name = token.id;
			nametable.addParam(name);
			nextToken();
			if (token.kind == Comma) {
				nextToken();
				continue;
			}
		}
		ensureToken(Rparen);
		break;
	}

	nametable.endParameters();
	compileBlock();
	nametable.endFunction();
	ensureToken(Semicolon);

}

void Compiler::compileCall(TableEntry& entry) {
	//func(x,y+z,...)における(x,y+z,...)の部分を処理
	ensureToken(Lparen);
	while (true) {
		if (token.kind == Rparen) {
			nextToken();
			break;
		}
		compileExpression();
		if (token.kind == Comma) {
			nextToken();
			continue;
		}
		ensureToken(Rparen);
		break;
	}

	//cal命令の出力
	codebuilder.emitCal(entry.level, entry.relAdress);
}

void Compiler::compileRet() {
	compileExpression();
	codebuilder.emitRet(nametable.level, nametable.currentFunctionNumParams());
}