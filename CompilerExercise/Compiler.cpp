#include <iostream>
#include "Compiler.h"

Compiler::Compiler(std::string& str)
	:source(str)
{
}

Compiler::~Compiler()
{
}
std::vector<Inst> Compiler::compile()
{
	if (source.source != ".") {
		std::cerr << "\•¶ƒGƒ‰[" << std::endl;
	}
	Inst inst(ret, nop, 0, 0, 0, 0, 0);
	std::vector<Inst> code;
	code.push_back(inst);
	return code;
}