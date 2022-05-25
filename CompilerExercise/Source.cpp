#include "Source.h"


Source::Source(std::string& _source)
	: source(_source), index(0), ch('\0') {
	//���̕����ǂݎ��
	nextChar();
};

//source���̎��̕�����Ԃ��֐�
char Source::nextChar() {
	if (index >= source.size()) {
		ch = '\0';
	}
	else {
		//�C���N�������g�������̂͊֐��ɓn����"��"
		ch = source.at(index++);
	}
	return ch;
}

//ch���X�y�[�X�C���s�Ctab�Ȃ�X�L�b�v
void Source::skipSpaces() {
	while (ch == ' '||ch=='\n'||ch=='	') {
		nextChar();
	}
}

//���̃g�[�N����ǂݏo���������s���֐�
Token Source::nextToken() {
	skipSpaces();//�󔒕������΂�

	//���l�̏ꍇ
	if (isDigit(ch)) {
		//1�����ڂ������Ȃ琔�l�g�[�N���Ȃ̂�nextNumberToken�ɔC����
		return nextNumberToken();
	}

	//���ʎq�̏ꍇ
	if (isIdenfitifierStartChar(ch)) {
		//1�����ڂ����ʎq�Ȃ环�ʎq�g�[�N���Ȃ̂�nextIdentifierOrKeywordToken�ɔC����
		return nextIdentifierOrKeywordToken();
	}

	//�L���̏ꍇ
	if (isSymbolToken(ch)) {
		//�e�L���ɉ����ăg�[�N����Ԃ�
		if (ch == '.') {
			nextChar();
			Token tk = { Period, "", 0 };
			return tk;
		}
		else if (ch == '+') {
			nextChar();
			Token tk = { Plus,"",0 };
			return tk;
		}
		else if (ch == '-') {
			nextChar();
			Token tk = { Minus,"",0 };
			return tk;
		}
		else if (ch == '*') {
			nextChar();
			Token tk = { Mult,"",0 };
			return tk;
		}
		else if (ch == '/') {
			nextChar();
			Token tk = { Div,"",0 };
			return tk;
		}
		else if (ch == '(') {
			nextChar();
			Token tk = { Lparen,"",0 };
			return tk;
		}
		else if (ch == ')') {
			nextChar();
			Token tk = { Rparen,"",0 };
			return tk;
		}
		else if (ch == ';') {
			nextChar();
			Token tk = { Semicolon,"",0 };
			return tk;
		}
	}
	

	//�g�[�N����������Ȃ������ꍇ
	Token tk = {nul, "", 0 };
	return tk; 
}

//���l�g�[�N����ǂݏo���������s���֐�
Token Source::nextNumberToken() {
	//num������
	int num = 0;
	//�������������萔�l��
	while (isDigit(ch)) {
		num = num * 10 + (ch - '0');
		nextChar();
	}
	//token�����ĕԂ�
	Token tk = { Num,"",num };
	return tk;
}

//���ʎq�g�[�N����ǂݏo���������s���֐�
Token Source::nextIdentifierOrKeywordToken() {
	//token�̎��ۂ̕������ۑ�(write��writeln�Ȃ�)
	//���`���Ă������ƁI(�����ɂ͂Ȃ����ǁC�������e�X�g�ʉ߂��Ȃ�����)
	std::string value="";

	//ch�����ʎq�Ɏg������蕶����value�̌��ɒǉ�
	while (isIdentifierChar(ch)){
		value = value + ch;
		nextChar();
	}

	//value���\��ꂾ������
	if (isKeyword(value)) {
		//value��write�Ȃ�Write�g�[�N����Ԃ�
		if (value == "write") {
			Token tk = { Write,"",0 };
			return tk;
		}
		//writeln�Ȃ�WriteLn�g�[�N����Ԃ�
		else if (value == "writeln") {
			Token tk = { WriteLn, "",0 };
			return tk;
		}
		//begin�Ȃ�begin�g�[�N��
		else if (value == "begin") {
			Token tk = { Begin, "", 0 };
			return tk;
		}
		//end�Ȃ�end�g�[�N��
		else if (value == "end") {
			Token tk = { End, "", 0 };
			return tk;
		}
	}


	//����ȊO��Id�Ƃ��ăg�[�N����Ԃ�
	//�����ƈႤ�̂Œ���
	Token tk = { Id, "", 0};
	return tk;
}

//c��1�����Ńg�[�N���ɂȂ�L��( ., +. -, *, /, (, ), ; )�Ȃ�true��Ԃ��֐�
bool Source::isSymbolToken(char c) {
	if (c == '.' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c==';') {
		return true;
	}
	else {
		return false;
	}
}

//str���\���iwrite��writeln, begin, end)�̏ꍇ�Ctrue��Ԃ��֐�
bool Source::isKeyword(std::string& str) {
	if (str == "write" || str == "writeln"|| str == "begin" || str == "end") {
		return true;
	}
	else {
		return false;
	}
}