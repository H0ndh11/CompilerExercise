#pragma once
#include "utils.h"

class Inst
{
public:
	Inst(OpCode _opcode, Operator _opr, int _value, int _level, int _numParams, int _index, int _relAddress); 
	~Inst(); 

	// 命令コード
	OpCode opcode;
	// 命令コードが演算の時
	Operator opr; 

	// リテラルの値などを格納する変数
	int value; 

	// どの深さのブロックを見るか
	int level;

	// そのブロックのパラメータの数
	int numParams;

	// jpc などの命令でジャンプする PC の場所
	int index;

	// sto や lod で相対アドレスを指定する
	int relAddress;
};



