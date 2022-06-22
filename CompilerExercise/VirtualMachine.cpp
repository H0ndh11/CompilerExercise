#include "VirtualMachine.h"


VirtualMachine::VirtualMachine(std::vector<Inst>& _code)
	: code(_code), output("")
{
}

VirtualMachine::~VirtualMachine()
{
}


void VirtualMachine::run()
{

	pc = 0;
	stack.push_back(0);
	stack.push_back(0);

	top = stack.size();
	display.push_back(0);

	while (true)
	{
		//code��pc�Ԗڂ𖽗߂Ƃ���inst�ɂ����
		Inst inst = code.at(pc++);

		//���ߎ��(inst.opcode)�ɂ���ĕ���
		switch (inst.opcode)
		{
		case ret:
			runRet(inst);
			break;
		case lit:
			runLit(inst);
			break;
		case opr:
			runOpr(inst);
			break;
		case jpc:
			runJpc(inst);
			break;
		default:
			break;

		}

		if (pc == 0) {
			break;
		}
	}
}


void VirtualMachine::runRet(Inst inst)
{
	int result = popStack();
	top = display.at(inst.level);
	display.at(inst.level) = stack.at(top);
	pc = stack.at(top + 1);

	top -= inst.numParams;

	pushStack(result);
}

//lit���߂����s����֐�
void VirtualMachine::runLit(Inst inst) {
	//�l����(inst.value)���X�^�b�N�ɐς�
	pushStack(inst.value);
}

//wrt���߂≉�Z�q�Ȃǂ̖��߂𔻕ʂ��T�u���[�`�����ĂԊ֐�
void VirtualMachine::runOpr(Inst inst) {
	//��̓I�Ȗ��ߓ��e(inst.opr)�ɂ���ĕ���
	switch (inst.opr) {
	case wrt:
		runOprWrt();
		break;
	case wrl:
		runOprWrl();
		break;
	case neg:
		runOprNeg();
		break;
	case add:
		runOprAdd();
		break;
	case sub:
		runOprSub();
		break;
	case mul:
		runOprMul();
		break;
	case divi:
		runOprDivi();
		break;
	case odd:
		runOprOdd();
		break;
	case eq:
		runOprEq();
		break;
	case neq:
		runOprNeq();
		break;
	case ls:
		runOprLt();
		break;
	case lseq:
		runOprLteq();
		break;
	case gr:
		runOprGr();
		break;
	case greq:
		runOprGreq();
		break;
	default:
		break;
	}
}

//wrt���߂����s����֐�
void VirtualMachine::runOprWrt() {
	//�X�^�b�N�̃g�b�v�ɂ���l��value��
	int value = popStack();
	//value��string�^�ɂ��Ă���o�͓��eoutput�ɒǉ�
	output += std::to_string(value);
}

//wrl���߂����s����֐�
void VirtualMachine::runOprWrl() {
	//���s���o�͌���output�ɒǉ�
	output += "\n";
}

//neg���߂����s����֐�
void VirtualMachine::runOprNeg() {
	int rhs = popStack();
	pushStack(-rhs);
}

//add���߂����s����֐�
void VirtualMachine::runOprAdd() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs + rhs);
}

//sub���߂����s����֐�
void VirtualMachine::runOprSub() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs - rhs);
}

//mul���߂����s����֐�
void VirtualMachine::runOprMul() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs * rhs);
}

//divi���߂����s����֐�
void VirtualMachine::runOprDivi() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs / rhs);
}

//�X�^�b�N�փv�b�V��
void VirtualMachine::pushStack(int value) {
	if (stack.size() <= top) {
		stack.push_back(value);
		top++; 
	} else {
	stack.at(top++) = value; 
	}
}

//�X�^�b�N����|�b�v
int VirtualMachine::popStack()
{
	return stack.at(--top); 
}

//�X�^�b�N�̐퓬�̋��ʂ�odd���߂����s����֐�
void VirtualMachine::runOprOdd() {
	int rhs = popStack();
	pushStack(rhs % 2);
}

//�X�^�b�N����l2�����o���C����������r����eq���߂̊֐�
void VirtualMachine::runOprEq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs == lhs);
}

//eq���߂̋t
void VirtualMachine::runOprNeq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs != lhs);
}

//2��|�b�v���C��̕����������ꍇ1��Ԃ�lss���߂����s����֐�
void VirtualMachine::runOprLt() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs > lhs);
}

//2��|�b�v���C��̕�����̒l�ȉ��̏ꍇ1��Ԃ�lsseq���߂����s����֐�
void VirtualMachine::runOprLteq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs >= lhs);
}

//2��|�b�v���C��̕����傫���ꍇ1��Ԃ�gtr���߂����s����֐�
void VirtualMachine::runOprGr() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs < lhs);
}

//2��|�b�v���C��̕�����̒l�ȏ�̏ꍇ1��Ԃ�gtreq���߂����s����֐�
void VirtualMachine::runOprGreq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs <= lhs);
}

//if���ŗp������jpc���߂����s����֐�
void VirtualMachine::runJpc(Inst inst) {
	int value = popStack();
	if (value == 0) {
		pc = inst.index;
	}
}