#pragma once
#include <vector>
#include <string>
#include "Inst.h"

class VirtualMachine
{
public:
	/**
	* ���z�@�B
	* @papram _code ���s����R�[�h
	*/
	VirtualMachine(std::vector<Inst>& _code); 
	~VirtualMachine(); 


	// ���s���閽�ߗ�
	std::vector<Inst> code; 

	// write / writeln �ŏo�͂���镶����
	std::string output; 

	// �v���O�����J�E���^
	int pc; 

	// �I�y�����h�̃X�^�b�N
	std::vector<int> stack; 

	// ���݂̃X�^�b�N�̃g�b�v
	int top; 
	std::vector<int> display; 


	/**
	* ���z�@�B�����s����Dcode �����s�����D
	*/
	void run(); 

	/**
	* stack ���� pop ����֐�
	* @return ����ꂽ�l
	*/
	int popStack();

	/**
	* stack �� push ����֐�
	* @param �v�b�V������l
	*/
	void pushStack(int value); 

	/**
	* ret �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runRet(Inst inst); 

	/**
	* lit �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runLit(Inst inst); 

	/**
	* ict �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runIct(Inst inst); 

	/**
	* jmp �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runJmp(Inst inst); 

	/**
	* lod �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runLod(Inst inst); 

	/**
	* sto �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runSto(Inst inst); 

	/**
	* cal �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runCal(Inst inst); 

	/**
	* jpc �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runJpc(Inst inst); 

	/**
	* Opr �����s����
	* @papram inst ���ۂɎ��s���閽��
	*/
	void runOpr(Inst inst); 

	/**
	* Opr �� wrt �����s����
	*/
	void runOprWrt(); 

	/**
	* Opr �� wrl �����s����
	*/
	void runOprWrl(); 

	/**
	* Opr �� add �����s����
	*/
	void runOprAdd(); 

	/**
	* Opr �� sub �����s����
	*/
	void runOprSub(); 

	/**
	* Opr �� mul �����s����
	*/
	void runOprMul(); 

	/**
	* Opr �� divi �����s����
	*/
	void runOprDivi(); 
	
	/**
	* Opr �� neg �����s����
	*/
	void runOprNeg(); 
	
	/**
	* Opr �� eq �����s����
	*/
	void runOprEq(); 

	/**
	* Opr �� neq�����s����
	*/
	void runOprNeq(); 

	/**
	* Opr �� lt �����s����
	*/
	void runOprLt(); 

	/**
	* Opr �� gr �����s����
	*/
	void runOprGr(); 

	/**
	* Opr �� lteq �����s����
	*/
	void runOprLteq(); 

	/**
	* Opr �� greq �����s����
	*/
	void runOprGreq(); 

	/**
	* Opr �� odd �����s����
	*/
	void runOprOdd(); 

	/**
	* �R�[�h�̏o��
	*/
	void printCode(); 
};


