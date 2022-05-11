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

void VirtualMachine::pushStack(int value) {
	if (stack.size() <= top) {
		stack.push_back(value);
		top++; 
	} else {
	stack.at(top++) = value; 
	}
}

int VirtualMachine::popStack()
{
	return stack.at(--top); 
}


