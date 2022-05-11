#include "NameTable.h"

NameTable::NameTable()
	: localAddress(2), level(0), currentFunctionAddress(0) {
}

NameTable::~NameTable() {
}

TableEntry NameTable::search(std::string& name) {
	return TableEntry{ others, 0, 0, 0, 0, 0 }; 
}

void NameTable::addConst(std::string& name, int value) {
}
