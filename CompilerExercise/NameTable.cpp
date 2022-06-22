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