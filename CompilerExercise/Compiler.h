#pragma once

#include <string>
#include <vector>
#include "Inst.h"
#include "CodeBuilder.h"
#include "Source.h"
#include "NameTable.h"

class Compiler
{
public:

	Compiler(std::string& str);
	~Compiler();

	// ソースコードを管理するクラス
	Source source;
	// 現在のトークンを管理するクラス
	Token token;
	// 変数表を管理するクラス
	NameTable nametable;
	// 出力するコードを管理するクラス
	CodeBuilder codebuilder;

	/**
	* コンパイルを実行．コンパイルした後は機械向け語の命令の列を出力する．
	* @return 命令の列
	*/
	std::vector<Inst> compile();

	/**
	* 次のトークンを読む．読んだトークンは token に格納される．
	*/
	void nextToken();

	// 下向き構文解析による構文解析器の構築
	void compileBlock();
	
	void compileConstDecl();
	void compileVarDecl();
	void compileFunctionDecl();

	void compileStatement();
	void compileIdentifier(std::string& name);
	void compileAssign(std::string& name);

	void compileBeginEnd();
	void compileIf();
	void compileWhile();
	void compileWrite();
	void compileWriteLn();

	void compileCondition();

	void compileExpression();
	void compileTerm();
	void compileFactor();

	void compileCall(TableEntry& entry);
	void compileRet();

	/**
	* 次に来るトークンが想定した種類のものであるかどうかをチェックする．
	* @param kind 想定するトークンの種類
	* @return 実際に読んだトークンを返す
	*/
	Token ensureToken(KeyId kind);


};

