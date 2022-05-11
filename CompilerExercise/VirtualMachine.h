#pragma once
#include <vector>
#include <string>
#include "Inst.h"

class VirtualMachine
{
public:
	/**
	* 仮想機械
	* @papram _code 実行するコード
	*/
	VirtualMachine(std::vector<Inst>& _code); 
	~VirtualMachine(); 


	// 実行する命令列
	std::vector<Inst> code; 

	// write / writeln で出力される文字列
	std::string output; 

	// プログラムカウンタ
	int pc; 

	// オペランドのスタック
	std::vector<int> stack; 

	// 現在のスタックのトップ
	int top; 
	std::vector<int> display; 


	/**
	* 仮想機械を実行する．code が実行される．
	*/
	void run(); 

	/**
	* stack から pop する関数
	* @return 得られた値
	*/
	int popStack();

	/**
	* stack に push する関数
	* @param プッシュする値
	*/
	void pushStack(int value); 

	/**
	* ret を実行する
	* @papram inst 実際に実行する命令
	*/
	void runRet(Inst inst); 

	/**
	* lit を実行する
	* @papram inst 実際に実行する命令
	*/
	void runLit(Inst inst); 

	/**
	* ict を実行する
	* @papram inst 実際に実行する命令
	*/
	void runIct(Inst inst); 

	/**
	* jmp を実行する
	* @papram inst 実際に実行する命令
	*/
	void runJmp(Inst inst); 

	/**
	* lod を実行する
	* @papram inst 実際に実行する命令
	*/
	void runLod(Inst inst); 

	/**
	* sto を実行する
	* @papram inst 実際に実行する命令
	*/
	void runSto(Inst inst); 

	/**
	* cal を実行する
	* @papram inst 実際に実行する命令
	*/
	void runCal(Inst inst); 

	/**
	* jpc を実行する
	* @papram inst 実際に実行する命令
	*/
	void runJpc(Inst inst); 

	/**
	* Opr を実行する
	* @papram inst 実際に実行する命令
	*/
	void runOpr(Inst inst); 

	/**
	* Opr の wrt を実行する
	*/
	void runOprWrt(); 

	/**
	* Opr の wrl を実行する
	*/
	void runOprWrl(); 

	/**
	* Opr の add を実行する
	*/
	void runOprAdd(); 

	/**
	* Opr の sub を実行する
	*/
	void runOprSub(); 

	/**
	* Opr の mul を実行する
	*/
	void runOprMul(); 

	/**
	* Opr の divi を実行する
	*/
	void runOprDivi(); 
	
	/**
	* Opr の neg を実行する
	*/
	void runOprNeg(); 
	
	/**
	* Opr の eq を実行する
	*/
	void runOprEq(); 

	/**
	* Opr の neqを実行する
	*/
	void runOprNeq(); 

	/**
	* Opr の lt を実行する
	*/
	void runOprLt(); 

	/**
	* Opr の gr を実行する
	*/
	void runOprGr(); 

	/**
	* Opr の lteq を実行する
	*/
	void runOprLteq(); 

	/**
	* Opr の greq を実行する
	*/
	void runOprGreq(); 

	/**
	* Opr の odd を実行する
	*/
	void runOprOdd(); 

	/**
	* コードの出力
	*/
	void printCode(); 
};


