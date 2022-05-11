#pragma once
#include <string>


// 予約語
typedef enum keys {
	Begin, End,
	If, Then,
	While, Do,
	Ret, Func, Param,
	Var, Const, Odd,
	Write, WriteLn,
	end_of_KeyWd, // 予約語

	Plus, Minus,
	Mult, Div,
	Lparen, Rparen,
	Equal, Lss, Gtr,
	NotEq, LssEq, GtrEq,
	Comma, Period, Semicolon,
	Assign,
	end_of_KeySym,

	Id, Num, nul,
	end_of_Token,

	letter, digit, colon, others
} KeyId;

// トークン．
struct Token {
	// トークンの種類
	KeyId kind;
	// 定数，変数，関数のとき，その名前
	std::string id;
	// 数字トークの場合はその値
	int value;
};

// 変数表の各エントリ
struct TableEntry {
	KeyId kind;
	std::string name;
	int value;
	int level;
	int relAdress;
	int numParams;
};

// ブロックの深さを管理するディスプレイ
struct DisplayEntry {
	int address;
	int localAdrdess;
};

// 命令コード
typedef enum codes { lit, opr, lod, sto, cal, ret, ict, jmp, jpc } OpCode;

// opr 命令の時の演算
typedef enum ops {
	neg,
	add,
	sub,
	mul,
	divi,
	odd,
	eq,
	ls,
	gr,
	neq,
	lseq,
	greq,
	wrt,
	wrl,
	nop
} Operator;


/**
* 数値かどうかを判定する
*
* @return その時点で生成されている命令列 code
*/
bool isDigit(char c);

/**
* 識別子の先頭文字になれるかを判定する
*
* @return その時点で生成されている命令列 code
*/
bool isIdenfitifierStartChar(char c);

/**
* 識別子に使える文字かどうかを判定する
*
* @return その時点で生成されている命令列 code
*/
bool isIdentifierChar(char c);

