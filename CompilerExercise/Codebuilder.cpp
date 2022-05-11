#include "CodeBuilder.h"

CodeBuilder::CodeBuilder()
	:currentIndex(0)
{
}

CodeBuilder::~CodeBuilder()
{
}

//生成したコードを返す
std::vector<Inst> CodeBuilder::getCode() {
	return code;
}

int CodeBuilder::emit(Inst inst) {
	code.push_back(inst);
	return code.size() - 1;
}

int CodeBuilder::emitRet(int level, int numParams) {
	return emit(Inst(ret, nop, 0, level, numParams, 0, 0));
}

int CodeBuilder::emitLit(int value) {
	return emit(Inst(lit, nop, value, 0, 0, 0, 0));
}

int CodeBuilder::emitOprWrt() {
	return emit(Inst(opr, wrt, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprWrtLn() {
	return emit(Inst(opr, wrl, 0, 0, 0, 0, 0));
}