#pragma once
#include <string>
#include "utils.h"

class Source
{
public:

	// プログラムのソースコード
	std::string source;

	// 何番目の文字を処理中かを示す変数
	int index;

	// 今見ている文字
	char ch;

	/**
	* コンストラクタ．
	* @param _source プログラムのソースコード
	*/
	Source(std::string& _source);

	/**
	* source 中の次の文字を読み込む
	* @return 次に読んだ文字
	*/
	char nextChar();

	/**
	* nextChar を読んだ際に，空白文字を読み飛ばすサブルーチン
	*/
	void skipSpaces();

	/**
	* ソース文字列の次のトークンを取り出す
	*
	* @return Token tk を返す
	*  読み込むトークンがないときは
	*     tk.kind = nul,  tk.id = "", tk.value = 0
	*  を返す
	*
	*/
	Token nextToken();

	/**
	* 数値トークンを返す
	* nextTokenで呼び出して使う．
	*
	* @return Token tk を返す
	*	tk.kind = Num, tk.value = 数値, tk.id = ""
	*/
	Token nextNumberToken();

	/**
	* 識別子かキーワードのトークンを読んで返す
	* nextTokenで呼び出して使う．
	*
	* @return Token tk を返す
	*	tk.kind =トークンの種類, tk.value = 0, tk.id = ""
	*/
	Token nextIdentifierOrKeywordToken();


	/**
	* キーワードならば True を返す関数
	* nextIdentifierOToken でつかつ
	*
	* @param str キーワードか調べたい文字列
	* @return もしキーワードなら true を返す．
	*/
	bool isKeyword(std::string& str);

	/**
	* 文字単独でトークンになるかどうかを返す関数
	* トークンになるのは . + - * / \ ( )
	* nextToken で使う
	*
	* @param char 調べたい文字
	* @return もしトークンになるならなら true を返す．
	*/
	bool isSymbolToken(char ch);
};

