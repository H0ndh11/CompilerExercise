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
		TableEntry entry = table.at(table.size() - 1 - i);
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

int NameTable::addVar(std::string& name) {
	int relAddress = localAddress++;
	table.push_back(TableEntry{ Var, name, 0, level, relAddress, 0 });
	return relAddress;
}

int NameTable::addFunction(std::string& name, int index) {
	//currentFunctionAddressに記号表における関数の位置を保存する
	currentFunctionAddress = table.size();

	//記号表に関数の情報を追加
	table.push_back(TableEntry{ Func, name, 0, level++, index, 0 });

	//現在のレベルの情報保存
	display.push_back(DisplayEntry{ (int)table.size(), localAddress });

	//新しく追加する関数のlocalAddressを初期化
	localAddress = 2;

	return currentFunctionAddress;
}

int NameTable::addParam(std::string& name) {
	int address = table.size();
	table.push_back(TableEntry{ Param, name, 0, level, 0, 0 });

	//新しく追加した引数を取る関数のnumParamsをインクリメント
	table.at(currentFunctionAddress).numParams++;

	//新しく追加された変数の記号表における位置を返す．
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

