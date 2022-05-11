#pragma once
#include <string>
#include "utils.h"

class Source
{
public:

	// �v���O�����̃\�[�X�R�[�h
	std::string source;

	// ���Ԗڂ̕��������������������ϐ�
	int index;

	// �����Ă��镶��
	char ch;

	/**
	* �R���X�g���N�^�D
	* @param _source �v���O�����̃\�[�X�R�[�h
	*/
	Source(std::string& _source);

	/**
	* source ���̎��̕�����ǂݍ���
	* @return ���ɓǂ񂾕���
	*/
	char nextChar();

	/**
	* nextChar ��ǂ񂾍ۂɁC�󔒕�����ǂݔ�΂��T�u���[�`��
	*/
	void skipSpaces();

	/**
	* �\�[�X������̎��̃g�[�N�������o��
	*
	* @return Token tk ��Ԃ�
	*  �ǂݍ��ރg�[�N�����Ȃ��Ƃ���
	*     tk.kind = nul,  tk.id = "", tk.value = 0
	*  ��Ԃ�
	*
	*/
	Token nextToken();

	/**
	* ���l�g�[�N����Ԃ�
	* nextToken�ŌĂяo���Ďg���D
	*
	* @return Token tk ��Ԃ�
	*	tk.kind = Num, tk.value = ���l, tk.id = ""
	*/
	Token nextNumberToken();

	/**
	* ���ʎq���L�[���[�h�̃g�[�N����ǂ�ŕԂ�
	* nextToken�ŌĂяo���Ďg���D
	*
	* @return Token tk ��Ԃ�
	*	tk.kind =�g�[�N���̎��, tk.value = 0, tk.id = ""
	*/
	Token nextIdentifierOrKeywordToken();


	/**
	* �L�[���[�h�Ȃ�� True ��Ԃ��֐�
	* nextIdentifierOToken �ł���
	*
	* @param str �L�[���[�h�����ׂ���������
	* @return �����L�[���[�h�Ȃ� true ��Ԃ��D
	*/
	bool isKeyword(std::string& str);

	/**
	* �����P�ƂŃg�[�N���ɂȂ邩�ǂ�����Ԃ��֐�
	* �g�[�N���ɂȂ�̂� . + - * / \ ( )
	* nextToken �Ŏg��
	*
	* @param char ���ׂ�������
	* @return �����g�[�N���ɂȂ�Ȃ�Ȃ� true ��Ԃ��D
	*/
	bool isSymbolToken(char ch);
};

