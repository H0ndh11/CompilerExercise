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

	// �\�[�X�R�[�h���Ǘ�����N���X
	Source source;
	// ���݂̃g�[�N�����Ǘ�����N���X
	Token token;
	// �ϐ��\���Ǘ�����N���X
	NameTable nametable;
	// �o�͂���R�[�h���Ǘ�����N���X
	CodeBuilder codebuilder;

	/**
	* �R���p�C�������s�D�R���p�C��������͋@�B������̖��߂̗���o�͂���D
	* @return ���߂̗�
	*/
	std::vector<Inst> compile();

	/**
	* ���̃g�[�N����ǂށD�ǂ񂾃g�[�N���� token �Ɋi�[�����D
	*/
	void nextToken();

	// �������\����͂ɂ��\����͊�̍\�z
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
	* ���ɗ���g�[�N�����z�肵����ނ̂��̂ł��邩�ǂ������`�F�b�N����D
	* @param kind �z�肷��g�[�N���̎��
	* @return ���ۂɓǂ񂾃g�[�N����Ԃ�
	*/
	Token ensureToken(KeyId kind);


};

