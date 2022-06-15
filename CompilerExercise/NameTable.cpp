#include "NameTable.h"

NameTable::NameTable()
	: localAddress(2), level(0), currentFunctionAddress(0) {
}

NameTable::~NameTable() {
}

TableEntry NameTable::search(std::string& name) {
	//tableを末尾から検索していく
	//もしentryに対してentry.nameとnameが一致していたらそのentryを返す
	for (size_t i = 0; i < table.size(); i++) {
		TableEntry entry = table.at(i);
		if (entry.name == name) {
			return entry;
		}
	}
	//見つからなかった場合はkindをnulとして返す
	return TableEntry{ nul, 0, 0, 0, 0, 0 }; 
}

//nameに定数名，valueに値が入る
void NameTable::addConst(std::string& name, int value) {
	//push_back()関数を用いて，tableにtableentry型の値を追加する．
	//括弧が資料と違うので注意
	table.push_back(TableEntry{ Const, name, value, 0, 0, 0 });
}
