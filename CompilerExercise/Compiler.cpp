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
	//ConstDecl��0��ȏニ�[�v
	while (true) {
		if (token.kind == Const) {
			nextToken();
			compileConstDecl();
			continue;
		}
		if (token.kind == Var) {
			nextToken();
			compileVarDecl();
			continue;
		}
		else {
			break;
		}
	}
	codebuilder.emitIct(nametable.localAddress);

	//Statement��
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
	//step5�ł͂�����Y�ꂸ�ɁI�i�����ɋL�ڂȂ��j
	case If:
		nextToken();
		compileIf();
		break;
	case Id:
		compileAssign(token.id);
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
	else if (token.kind == Lparen) {
		nextToken();
		compileExpression();
		//���̒i�K�Ńg�[�N����Rparen�ł͂Ȃ�������v���O������~
		if (token.kind != Rparen) {
			exit(1);
		}
		nextToken();
		return;
	}
	else if(token.kind == Id) {
		std::string name = token.id;
		nextToken();
		compileIdentifier(name);
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

void Compiler::compileConstDecl() {
	while (true) {
		//�萔�錾�̍\�����
		//x = 10 �̂悤��Id, Equal, Num�̏�
		std::string name = ensureToken(Id).id;
		ensureToken(Equal);
		int value = ensureToken(Num).value;

		//nametable�ɒ萔���Ƃ��̒l�ǉ�
		nametable.addConst(name, value);
		if (token.kind == Comma) {	//�����̒萔�錾�ɑΉ�
			nextToken();
			continue;
		}
		//�Ō�̓Z�~�R����������͂�
		ensureToken(Semicolon);
		break;
	}
}

void Compiler::compileIdentifier(std::string& name) {
	TableEntry entry = nametable.search(name);
	switch (entry.kind) {
	case Const:
		//���z�@�B�̃X�^�b�N�̐퓬�Ɍ����Ă����萔�̐��l��ςޖ��߃R�[�h���o��
		codebuilder.emitLit(entry.value);
		break;
	case Var:
		codebuilder.emitLod(entry.level, entry.relAdress);
		break;
	default:
		//����nametable��ɑ��݂��Ȃ����
		std::cerr << name << " is not in the name table. \n";
		exit(1);
	}
}

void Compiler::compileAssign(std::string& name) {
	TableEntry entry = nametable.search(name);
	if (entry.kind == nul) {
		std::cerr << "Cannot find the name " << name << "\n";
		exit(1);
	}
	if (entry.kind != Var) {
		std::cerr << "Ihs is not variable \n";
		exit(1);
	}
	nextToken();
	ensureToken(Assign);
	compileExpression();
	codebuilder.emitSto(entry.level, entry.relAdress);
}

void Compiler::compileVarDecl() {
	while (true) {
		std::string name = ensureToken(Id).id;
		nametable.addVar(name);

		if (token.kind == Comma) {	//�����̕ϐ��錾�ɑΉ�
			nextToken();
			continue;
		}
		//�Ō�̓Z�~�R����������͂�
		ensureToken(Semicolon);
		break;
	}
}