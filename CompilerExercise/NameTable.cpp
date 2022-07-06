#include "NameTable.h"

NameTable::NameTable()
	: localAddress(2), level(0), currentFunctionAddress(0) {
}

NameTable::~NameTable() {
}

TableEntry NameTable::search(std::string& name) {
	//table�𖖔����猟�����Ă���
	//����entry�ɑ΂���entry.name��name����v���Ă����炻��entry��Ԃ�
	for (size_t i = 0; i < table.size(); i++) {
		TableEntry entry = table.at(table.size() - 1 - i);
		if (entry.name == name) {
			return entry;
		}
	}
	//������Ȃ������ꍇ��kind��nul�Ƃ��ĕԂ�
	return TableEntry{ nul, 0, 0, 0, 0, 0 }; 
}

//name�ɒ萔���Cvalue�ɒl������
void NameTable::addConst(std::string& name, int value) {
	//push_back()�֐���p���āCtable��tableentry�^�̒l��ǉ�����D
	//���ʂ������ƈႤ�̂Œ���
	table.push_back(TableEntry{ Const, name, value, 0, 0, 0 });
}

int NameTable::addVar(std::string& name) {
	int relAddress = localAddress++;
	table.push_back(TableEntry{ Var, name, 0, level, relAddress, 0 });
	return relAddress;
}

int NameTable::addFunction(std::string& name, int index) {
	//currentFunctionAddress�ɋL���\�ɂ�����֐��̈ʒu��ۑ�����
	currentFunctionAddress = table.size();

	//�L���\�Ɋ֐��̏���ǉ�
	table.push_back(TableEntry{ Func, name, 0, level++, index, 0 });

	//���݂̃��x���̏��ۑ�
	display.push_back(DisplayEntry{ (int)table.size(), localAddress });

	//�V�����ǉ�����֐���localAddress��������
	localAddress = 2;

	return currentFunctionAddress;
}

int NameTable::addParam(std::string& name) {
	int address = table.size();
	table.push_back(TableEntry{ Param, name, 0, level, 0, 0 });

	//�V�����ǉ��������������֐���numParams���C���N�������g
	table.at(currentFunctionAddress).numParams++;

	//�V�����ǉ����ꂽ�ϐ��̋L���\�ɂ�����ʒu��Ԃ��D
	return address;
}

void NameTable::endParameters() {
	int numParams = table.at(currentFunctionAddress).numParams;
	for (size_t i = 1; i <= numParams; i++) {
		table.at(currentFunctionAddress + i).relAdress = i - 1 - numParams;
	}
}

void NameTable::endFunction() {
	DisplayEntry de = display.back();
	display.pop_back();
	table.resize(de.address);
	localAddress = de.localAdrdess;
	level--;
}

int NameTable::currentFunctionNumParams() {
	return table.at(currentFunctionAddress).numParams;
}

