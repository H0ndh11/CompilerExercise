#include <iostream>
#include "Compiler.h"


//�R���X�g���N�^�Ŏ���token����肷��֐��Ăяo��
//Compiler�N���X�ɂ��Ă�Compiler.h�Q��
Compiler::Compiler(std::string& str)
	:source(str)
{
	nextToken();
}

//����token�����
void Compiler::nextToken() {
	token = source.nextToken();
}

Compiler::~Compiler()
{
}
std::vector<Inst> Compiler::compile()
{
	compileBlock();

	return codebuilder.getCode();
}

void Compiler::compileBlock() {
	compileStatement();
	codebuilder.emitRet(0, 0);
}

void Compiler::compileStatement() {
	switch (token.kind) {
	case Write:
		nextToken();
		compileWrite();
		break;
	case WriteLn:
		nextToken();
		compileWriteLn();
		break;
	default:
		break;
	}
}

void Compiler::compileWrite() {
	if (token.kind != Num) {
		exit(1);//�\���G���[
	}
	codebuilder.emitLit(token.value);
	codebuilder.emitOprWrt();

	nextToken();
}/*if (source.source != ".") {
		std::cerr << "�\���G���[" << std::endl;
	}
	Inst inst(ret, nop, 0, 0, 0, 0, 0);
	std::vector<Inst> code;
	code.push_back(inst);
	return code;
}*/

void Compiler::compileWriteLn() {
	codebuilder.emitOprWrtLn();
	nextToken();
}