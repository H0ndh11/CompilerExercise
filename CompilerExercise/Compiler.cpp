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
	case Begin:
		nextToken();
		compileBeginEnd();
		break;
	case If:
		nextToken();
		compileIf();
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
	//nextToken();

	
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
	//nextToken();
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

void Compiler::compileBeginEnd() {
	while (true) {
		//statement; �Ƃ����`�̊ԁC�܂�';'���������胋�[�v(�}2.30�Q�l)
		compileStatement();
		if (token.kind == Semicolon) {
			nextToken();
			continue;
		}
		ensureToken(End);
		break;
	}
}

Token Compiler::ensureToken(KeyId kind) {
	Token _token = token;

	//_token.kind��kind����v���Ȃ����ɃG���[
	if (_token.kind != kind) {
		std::cerr << "Syntax error" << kind << "\n";
		exit(1);
	}

	nextToken();
	return _token; //�m�F�����g�[�N����Ԃ�
}

void Compiler::compileIf() {
	compileCondition();
	ensureToken(Then);
	int jpcInst = codebuilder.emitJpc(0);
	compileStatement();
	codebuilder.backPatch(jpcInst, codebuilder.currentIndex);
}

void Compiler::compileCondition() {
	if (token.kind == Odd) {
		nextToken();
		compileExpression();
		codebuilder.emitOprOdd();
	}
	else {
		compileExpression();
		switch (token.kind)
		{
		case Equal:
			nextToken();
			compileExpression();
			codebuilder.emitOprEq();
			break;
		case NotEq:
			nextToken();
			compileExpression();
			codebuilder.emitOprNeq();
			break;
		case Lss:
			nextToken();
			compileExpression();
			codebuilder.emitOprLs();
			break;
		case LssEq:
			nextToken();
			compileExpression();
			codebuilder.emitOprLseq();
			break;
		case Gtr:
			nextToken();
			compileExpression();
			codebuilder.emitOprGr();
			break;
		case GtrEq:
			nextToken();
			compileExpression();
			codebuilder.emitOprGreq();
			break;
		default:
			break;
		}
	}
}