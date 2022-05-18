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
	//if (token.kind != Num) {
	//	exit(1);//�\���G���[
	//}
	//codebuilder.emitLit(token.value);


	compileExpression();
	codebuilder.emitOprWrt();
	nextToken();

	
	/*if (source.source != ".") {
		std::cerr << "�\���G���[" << std::endl;
	}
	Inst inst(ret, nop, 0, 0, 0, 0, 0);
	std::vector<Inst> code;
	code.push_back(inst);
	return code;
	}*/
}

void Compiler::compileWriteLn() {
	codebuilder.emitOprWrtLn();
	nextToken();
}

void Compiler::compileExpression() {
	//�ŏ��ɏo�Ă��鍀�����̐����ǂ���
	bool shouldEmitNeg = false;

	//+��-�̏ꍇ�̏���
	switch (token.kind) {
	case Plus:
		nextToken();
		break;
	case Minus:
		shouldEmitNeg = true;
		nextToken();
		break;
	default:
		break;
	}

	compileTerm();
	//���̐��ł������ꍇ
	if (shouldEmitNeg) {
		codebuilder.emitOprNeg();
	}

	//�g�[�N����Plus�CMinus�̏ꍇ
	while (true) {
		if (token.kind == Plus) {
			nextToken();
			compileTerm();
			codebuilder.emitOprAdd();
			continue;
		}
		else if (token.kind == Minus) {
			nextToken();
			compileTerm();
			codebuilder.emitOprSub();
			continue;
		}
		//Plus�ł�Minus�ł��Ȃ���Δ����o��
		break;
	}
}

void Compiler::compileTerm() {
	compileFactor();

	//�g�[�N����Mult�CDiv�̏ꍇ
	while (true) {
		if (token.kind == Mult) {
			nextToken();
			compileFactor();
			codebuilder.emitOprMul();
			continue;
		}
		else if (token.kind == Div) {
			nextToken();
			compileFactor();
			codebuilder.emitOprDiv();
			continue;
		}
		break;
	}
}

void Compiler::compileFactor() {
	if (token.kind == Num) {
		codebuilder.emitLit(token.value);
		nextToken();
		return;
	}
	if (token.kind == Lparen) {
		nextToken();
		compileExpression();
		//���̒i�K�Ńg�[�N����Rparen�ł͂Ȃ�������v���O������~
		if (token.kind != Rparen) {
			exit(1);
		}
		nextToken();
		return;
	}
	//���l��(expression)�ȊO�Ȃ當�@�G���[
	std::cerr << "Syntax error\n";
	exit(1);
}