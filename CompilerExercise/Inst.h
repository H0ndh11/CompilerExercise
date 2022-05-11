#pragma once
#include "utils.h"

class Inst
{
public:
	Inst(OpCode _opcode, Operator _opr, int _value, int _level, int _numParams, int _index, int _relAddress); 
	~Inst(); 

	// ���߃R�[�h
	OpCode opcode;
	// ���߃R�[�h�����Z�̎�
	Operator opr; 

	// ���e�����̒l�Ȃǂ��i�[����ϐ�
	int value; 

	// �ǂ̐[���̃u���b�N�����邩
	int level;

	// ���̃u���b�N�̃p�����[�^�̐�
	int numParams;

	// jpc �Ȃǂ̖��߂ŃW�����v���� PC �̏ꏊ
	int index;

	// sto �� lod �ő��΃A�h���X���w�肷��
	int relAddress;
};



