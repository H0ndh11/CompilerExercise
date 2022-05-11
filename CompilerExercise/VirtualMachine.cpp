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
		Inst inst = code.at(pc++);
		switch (inst.opcode)
		{
		case ret:
			runRet(inst);
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


