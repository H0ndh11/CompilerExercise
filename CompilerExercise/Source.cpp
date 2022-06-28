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
	while (ch == ' '||ch=='\n'||ch=='\t') {
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
			return { Period, "", 0 };
		}
		else if (ch == '+') {
			nextChar();
			return { Plus,"",0 };
		}
		else if (ch == '-') {
			nextChar();
			return { Minus,"",0 };
		}
		else if (ch == '*') {
			nextChar();
			return { Mult,"",0 };
		}
		else if (ch == '/') {
			nextChar();
			return { Div,"",0 };
		}
		else if (ch == '(') {
			nextChar();
			return { Lparen,"",0 };
		}
		else if (ch == ')') {
			nextChar();
			return { Rparen,"",0 };
		}
		else if (ch == ';') {
			nextChar();
			return { Semicolon,"",0 };
		}
		else if (ch == '<') {
			nextChar();
			//���������ɂ���ꍇ�C�܂�"<="�ł������ꍇ
			if (ch == '=') {
				nextChar();
				return { LssEq, "", 0};
			}
			//��Ȃ肪���ɂ���ꍇ�C�܂�"<>"�ł������ꍇ
			else if (ch == '>') {
				nextChar();
				return { NotEq, "",0 };
			}
			//'<'�����̏ꍇ
			else {
				return { Lss, "", 0 };
			}
		}
		else if (ch == '>') {
			nextChar();
			//���������ɂ���ꍇ�C�܂�">="�ł������ꍇ
			if (ch == '=') {
				nextChar();
				return { GtrEq, "", 0 };
			}
			//'>'�����̏ꍇ
			else {
				return { Gtr, "", 0 };
			}
		}
		else if (ch == '=') {
			nextChar();
			return { Equal, "", 0 };
		}
		else if (ch == ',') {
			nextChar();
			return { Comma, "", 0 };
		}
	}

	//:=�̏ꍇ
	if (ch == ':') {
		nextChar();
		if (ch == '=') {
			nextChar();
			return { Assign, "", 0 };
		}
	}
	

	//�g�[�N����������Ȃ������ꍇ
	return {nul, "", 0};
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
			return { Write,"",0 };
		}
		//writeln�Ȃ�WriteLn�g�[�N����Ԃ�
		else if (value == "writeln") {
			return { WriteLn, "",0 };
		}
		//begin�Ȃ�begin�g�[�N��
		else if (value == "begin") {
			return { Begin, "", 0 };
		}
		//end�Ȃ�end�g�[�N��
		else if (value == "end") {
			return { End, "", 0 };
		}
		//if
		else if (value == "if") {
			return { If, "", 0 };
		}
		//then
		else if (value == "then") {
			return { Then, "", 0 };
		}
		//odd
		else if (value == "odd") {
			return { Odd, "", 0 };
		}
		//const
		else if (value == "const") {
			return { Const, "", 0 };
		}
		//var
		else if (value == "var") {
			return { Var, "", 0 };
		}
		//while
		else if (value == "while") {
			return { While, "", 0 };
		}
		//do
		else if (value == "do") {
			return { Do, "", 0 };
		}
	}

	//����ȊO�͕ϐ�(Id)�Ƃ��ăg�[�N����Ԃ�
	//�����ƈႤ�̂Œ���(step5�ȑO)
	return { Id, value, 0};
}

//c��1�����Ńg�[�N���ɂȂ�L��( ., +. -, *, /, (, ), ; �Ȃ�)�Ȃ�true��Ԃ��֐�
bool Source::isSymbolToken(char c) {
	if (c == '.' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c ==';' || c=='<' || c == '>' || c == '='|| c==',') {
		return true;
	}
	else {
		return false;
	}
}

//str���\���iwrite��writeln, begin, end�Ȃ�)�̏ꍇ�Ctrue��Ԃ��֐�
bool Source::isKeyword(std::string& str) {
	if (str == "write" || str == "writeln"|| str == "begin" || str == "end" || str == "if" || str == "then" || str=="odd"|| str=="const" || str=="var" || str== "while" || str =="do") {
		return true;
	}
	else {
		return false;
	}
}