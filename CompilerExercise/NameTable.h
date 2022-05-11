#pragma once
#include <vector>
#include "utils.h"

class NameTable
{
public:
	NameTable(); 
	~NameTable(); 

	// 定数，変数，関数名を保存するベクタ
	std::vector<TableEntry> table;
	// ブロックの深さに関する情報を保存するスタック
	std::vector<DisplayEntry> display;

	// 現在のアドレス
	int localAddress;

	// 現在の関数があるブロックの深さ
	int level; 

	// 現在見ている関数のアドレス
	int currentFunctionAddress; 

	/**
	* name を持つ定数・変数・関数を探す
	* @param name 探したい名前
	* @return 見つけたときは，その情報を返す
	*/
	TableEntry search(std::string& name); 

	/**
	* 値 value をもった定数 name を追加
	* @param name 追加したい定数名
	* @param value name が持つ値
	*/
	void addConst(std::string& name, int value); 


	/**
	* 変数 name を追加
	* @param name 追加したい変数名
	* @return 追加した変数の相対アドレス
	*/
	int addVar(std::string& name); 

	/**
	* 関数 name を追加
	* @param name 追加したい関数名
	* @param index 追加したい関数名の位置
	* @return 現在管理している関数のアドレス
	*/
	int addFunction(std::string& name, int index); 

	/**
	* 現在管理している関数に変数を追加する
	* @param name 追加したい変数名
	* @return 現在の表のサイズ
	*/
	int addParam(std::string& name); 

	/**
	* 現在管理している関数への関数の追加が終了
	* 各引数の相対アドレスを計算する
	*/
	void endParameters(); 


	/**
	* 現在管理している関数の処理が終了．
	*/
	void endFunction(); 

	/**
	* 現在管理している関数の引数の数
	*/
	int currentFunctionNumParams(); 
};

