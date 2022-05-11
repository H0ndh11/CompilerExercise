#pragma once
#include <vector>
#include "Inst.h"

class CodeBuilder
{
public:
	CodeBuilder();
	~CodeBuilder();

	std::vector<Inst> code; // �������閽�߂̗�
	int currentIndex; // �R�[�h�ɂ����錻�݂̈ʒu

	/**
	* ���������R�[�h���o�͂���
	*
	* @return ���̎��_�Ő�������Ă��閽�ߗ� code
	*/
	std::vector<Inst> getCode();

	/**
	* ���߂� code �ɏo�͂���
	* @param[in] ���̖͂���
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emit(Inst inst);

	/**
	* ret ���߁D
	* @param level �֐����錾����Ă��郌�x���i�u���b�N�̐[���j
	* @param numParams �֐��̎󂯎������̐�
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitRet(int level, int numParams);

	/**
	* lit ����
	* @param value value ���X�^�b�N�Ƀv�b�V������
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitLit(int value);

	/**
	* jpc ����
	* @param level �X�^�b�N�̃g�b�v�� 0 �̂Ƃ��̃W�����v��
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitJpc(int level);

	/**
	* jmp ����
	* @param[in] level �W�����v��
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitJmp(int index);

	/**
	* ict ����
	* @param[in] level ���������� top �̌�
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitIct(int localAddress);

	/**
	* sto ����
	* @param[in] level      ���̃u���b�N�̐[��
	* @param[in] relAddress �|�b�v�����l���i�[�����̑��΃A�h���X
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitSto(int level, int relAddress);

	/**
	* lod ����
	* @param[in] level      ���̃u���b�N�̐[��
	* @param[in] relAddress �ǂݍ��ޒl�̂����Ă���A�h���X
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitLod(int level, int relAddress);

	/**
	* cal ����
	* @param[in] level �Ăяo�����̃��x��
	* @param[in] index �Ăяo���֐��̂����Ă���A�h���X
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitCal(int level, int index);

	/**
	* ���Z���� �� wrt�D�X�^�b�N�̃g�b�v�̒l���o�͂���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprWrt();

	/**
	* ���Z���� �� wrl�D���s���o�͂���
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprWrtLn();

	/**
	* ���Z���� �� neg�D�X�^�b�N�̃g�b�v�̒l�̕����𔽓]
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprNeg();

	/**
	* ���Z���� �� add�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l�Ɛ�Ƀ|�b�v�����l�𑫂��āC���ʂ��v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprAdd();

	/**
	* ���Z���� �� sub�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l�����Ƀ|�b�v�����l�������āC���ʂ��v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprSub();

	/**
	* ���Z���� �� mul�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l�Ɛ�Ƀ|�b�v�����l���|���āC���ʂ��v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprMul();

	/**
	* ���Z���� �� divi�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l�����Ƀ|�b�v�����l�������āC���ʂ��v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprDiv();

	/**
	* ���Z���� �� eq�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l�Ɛ�Ƀ|�b�v�����l����������� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprEq();

	/**
	* ���Z���� �� neq�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l�Ɛ�Ƀ|�b�v�����l���������Ȃ���� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprNeq();

	/**
	* ���Z���� �� ls�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l����Ƀ|�b�v�����l����������� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprLs();

	/**
	* ���Z���� �� gr�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l����Ƀ|�b�v�����l���傫����� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprGr();

	/**
	* ���Z���� �� lseq�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l����Ƀ|�b�v�����l������������������� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprLseq();

	/**
	* ���Z���� �� greq�D�X�^�b�N����2�|�b�v���āC��Ƀ|�b�v�����l����Ƀ|�b�v�����l�����������傫����� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprGreq();

	/**
	* ���Z���� �� odd�D�X�^�b�N����2�|�b�v���āC�|�b�v�����l����ł���� 1 ����ȊO�� 0 ���v�b�V���D
	* @return ���߂�ǉ��������Ƃ̂��̖��߂̃C���f�b�N�X
	*/
	int emitOprOdd();

	/**
	* �w�肵���C���f�b�N�X�̖��߂̃I�y�����h�����Ƃ��珑��������
	* @param jmpInstIndex �C���f�b�N�X���X�V���� jmp ���߂̃A�h���X
	* @param newIndex �V�����W�����v��̃C���f�b�N�X
	*/
	void backPatch(int jmpInstIndex, int newIndex);
};
