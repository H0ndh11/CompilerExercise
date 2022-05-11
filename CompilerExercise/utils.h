#pragma once
#include <string>


// �\���
typedef enum keys {
	Begin, End,
	If, Then,
	While, Do,
	Ret, Func, Param,
	Var, Const, Odd,
	Write, WriteLn,
	end_of_KeyWd, // �\���

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

// �g�[�N���D
struct Token {
	// �g�[�N���̎��
	KeyId kind;
	// �萔�C�ϐ��C�֐��̂Ƃ��C���̖��O
	std::string id;
	// �����g�[�N�̏ꍇ�͂��̒l
	int value;
};

// �ϐ��\�̊e�G���g��
struct TableEntry {
	KeyId kind;
	std::string name;
	int value;
	int level;
	int relAdress;
	int numParams;
};

// �u���b�N�̐[�����Ǘ�����f�B�X�v���C
struct DisplayEntry {
	int address;
	int localAdrdess;
};

// ���߃R�[�h
typedef enum codes { lit, opr, lod, sto, cal, ret, ict, jmp, jpc } OpCode;

// opr ���߂̎��̉��Z
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
* ���l���ǂ����𔻒肷��
*
* @return ���̎��_�Ő�������Ă��閽�ߗ� code
*/
bool isDigit(char c);

/**
* ���ʎq�̐擪�����ɂȂ�邩�𔻒肷��
*
* @return ���̎��_�Ő�������Ă��閽�ߗ� code
*/
bool isIdenfitifierStartChar(char c);

/**
* ���ʎq�Ɏg���镶�����ǂ����𔻒肷��
*
* @return ���̎��_�Ő�������Ă��閽�ߗ� code
*/
bool isIdentifierChar(char c);

