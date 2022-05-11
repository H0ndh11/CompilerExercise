#pragma once
#include <vector>
#include "utils.h"

class NameTable
{
public:
	NameTable(); 
	~NameTable(); 

	// �萔�C�ϐ��C�֐�����ۑ�����x�N�^
	std::vector<TableEntry> table;
	// �u���b�N�̐[���Ɋւ������ۑ�����X�^�b�N
	std::vector<DisplayEntry> display;

	// ���݂̃A�h���X
	int localAddress;

	// ���݂̊֐�������u���b�N�̐[��
	int level; 

	// ���݌��Ă���֐��̃A�h���X
	int currentFunctionAddress; 

	/**
	* name �����萔�E�ϐ��E�֐���T��
	* @param name �T���������O
	* @return �������Ƃ��́C���̏���Ԃ�
	*/
	TableEntry search(std::string& name); 

	/**
	* �l value ���������萔 name ��ǉ�
	* @param name �ǉ��������萔��
	* @param value name �����l
	*/
	void addConst(std::string& name, int value); 


	/**
	* �ϐ� name ��ǉ�
	* @param name �ǉ��������ϐ���
	* @return �ǉ������ϐ��̑��΃A�h���X
	*/
	int addVar(std::string& name); 

	/**
	* �֐� name ��ǉ�
	* @param name �ǉ��������֐���
	* @param index �ǉ��������֐����̈ʒu
	* @return ���݊Ǘ����Ă���֐��̃A�h���X
	*/
	int addFunction(std::string& name, int index); 

	/**
	* ���݊Ǘ����Ă���֐��ɕϐ���ǉ�����
	* @param name �ǉ��������ϐ���
	* @return ���݂̕\�̃T�C�Y
	*/
	int addParam(std::string& name); 

	/**
	* ���݊Ǘ����Ă���֐��ւ̊֐��̒ǉ����I��
	* �e�����̑��΃A�h���X���v�Z����
	*/
	void endParameters(); 


	/**
	* ���݊Ǘ����Ă���֐��̏������I���D
	*/
	void endFunction(); 

	/**
	* ���݊Ǘ����Ă���֐��̈����̐�
	*/
	int currentFunctionNumParams(); 
};

