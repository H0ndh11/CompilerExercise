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
	currentIndex++;
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

int CodeBuilder::emitOprNeg() {
	return emit(Inst(opr, neg, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprAdd() {
	return emit(Inst(opr, add, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprSub() {
	return emit(Inst(opr, sub, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprMul() {
	return emit(Inst(opr, mul, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprDiv() {
	return emit(Inst(opr, divi, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprEq() {
	return emit(Inst(opr, eq, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprNeq() {
	return emit(Inst(opr, neq, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprLs() {
	return emit(Inst(opr, ls, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprGr() {
	return emit(Inst(opr, gr, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprLseq() {
	return emit(Inst(opr, lseq, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprGreq() {
	return emit(Inst(opr, greq, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitOprOdd() {
	return emit(Inst(opr, odd, 0, 0, 0, 0, 0));
}

int CodeBuilder::emitJpc(int index) {
	return emit(Inst(jpc, nop, 0, 0, 0, index, 0));
}

int CodeBuilder::emitJmp(int index) {
	return emit(Inst(jmp, nop, 0, 0, 0, index, 0));
}

void CodeBuilder::backPatch(int jmpInstIndex, int newIndex) {
	//正しいジャンプ先をindexに設定する
	code.at(jmpInstIndex).index = newIndex;
}

int CodeBuilder::emitIct(int localAddress) {
	return emit(Inst(ict, nop, localAddress, 0, 0, 0, 0));
}

int CodeBuilder::emitSto(int level, int relAddress) {
	return emit(Inst(sto, nop, 0, level, 0, 0, relAddress));
}

int CodeBuilder::emitLod(int level, int relAddress) {
	return emit(Inst(lod, nop, 0, level, 0, 0, relAddress));
}
