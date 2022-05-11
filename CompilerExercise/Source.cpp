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

Token Source::nextToken() {
	skipSpaces();//�󔒕������΂�

	//���l�g�[�N���̏ꍇ
	if (isDigit(ch)) {
		//1�����ڂ������Ȃ炠�Ƃ�nextNumberToken�ɔC����
		return nextNumberToken();
	}

	//���ʎq�̏ꍇ
	if (isIdenfitifierStartChar(ch)) {
		//1�����ڂ����ʎq�Ȃ炠�Ƃ�nextIdentifierOrKeywordToken�ɔC����
		return nextIdentifierOrKeywordToken();
	}


	//�s���I�h�̏ꍇ
	if (ch == '.') {
		nextChar();
		Token tk = {Period, "", 0 };
		return tk;
	}

	//�g�[�N����������Ȃ������ꍇ
	Token tk = {nul, "", 0 };
	return tk; 
}

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

Token Source::nextIdentifierOrKeywordToken() {
	//token�̎��ۂ̕������ۑ�(write��writeln�Ȃ�)
	//���`���Ă������ƁI(�����ɂ͂Ȃ����ǁC�������e�X�g�ʉ߂��Ȃ�����)
	std::string value="";

	//ch�����ʎq�Ɏg������蕶����value�̌��ɒǉ�
	while (isIdentifierChar(ch)){
		value = value + ch;
		nextChar();
	}

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

	//����ȊO��Id�Ƃ��ăg�[�N����Ԃ�
	//�����ƈႤ�̂Œ���
	Token tk = { Id, "", 0};
	return tk;
}