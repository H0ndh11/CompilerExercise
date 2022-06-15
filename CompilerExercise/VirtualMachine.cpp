#include "VirtualMachine.h"


VirtualMachine::VirtualMachine(std::vector<Inst>& _code)
	: code(_code), output("")
{
}

VirtualMachine::~VirtualMachine()
{
}


void VirtualMachine::run()
{

	pc = 0;
	stack.push_back(0);
	stack.push_back(0);

	top = stack.size();
	display.push_back(0);

	while (true)
	{
		//codeのpc番目を命令としてinstにいれる
		Inst inst = code.at(pc++);

		//命令種類(inst.opcode)によって分岐
		switch (inst.opcode)
		{
		case ret:
			runRet(inst);
			break;
		case lit:
			runLit(inst);
			break;
		case opr:
			runOpr(inst);
			break;
		case jpc:
			runJpc(inst);
			break;
		default:
			break;

		}

		if (pc == 0) {
			break;
		}
	}
}


void VirtualMachine::runRet(Inst inst)
{
	int result = popStack();
	top = display.at(inst.level);
	display.at(inst.level) = stack.at(top);
	pc = stack.at(top + 1);

	top -= inst.numParams;

	pushStack(result);
}

//lit命令を実行する関数
void VirtualMachine::runLit(Inst inst) {
	//値部分(inst.value)をスタックに積む
	pushStack(inst.value);
}

//wrt命令や演算子などの命令を判別しサブルーチンを呼ぶ関数
void VirtualMachine::runOpr(Inst inst) {
	//具体的な命令内容(inst.opr)によって分岐
	switch (inst.opr) {
	case wrt:
		runOprWrt();
		break;
	case wrl:
		runOprWrl();
		break;
	case neg:
		runOprNeg();
		break;
	case add:
		runOprAdd();
		break;
	case sub:
		runOprSub();
		break;
	case mul:
		runOprMul();
		break;
	case divi:
		runOprDivi();
		break;
	case odd:
		runOprOdd();
		break;
	case eq:
		runOprEq();
		break;
	case neq:
		runOprNeq();
		break;
	case ls:
		runOprLt();
		break;
	case lseq:
		runOprLteq();
		break;
	case gr:
		runOprGr();
		break;
	case greq:
		runOprGreq();
		break;
	default:
		break;
	}
}

//wrt命令を実行する関数
void VirtualMachine::runOprWrt() {
	//スタックのトップにある値をvalueへ
	int value = popStack();
	//valueをstring型にしてから出力内容outputに追加
	output += std::to_string(value);
}

//wrl命令を実行する関数
void VirtualMachine::runOprWrl() {
	//改行を出力結果outputに追加
	output += "\n";
}

//neg命令を実行する関数
void VirtualMachine::runOprNeg() {
	int rhs = popStack();
	pushStack(-rhs);
}

//add命令を実行する関数
void VirtualMachine::runOprAdd() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs + rhs);
}

//sub命令を実行する関数
void VirtualMachine::runOprSub() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs - rhs);
}

//mul命令を実行する関数
void VirtualMachine::runOprMul() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs * rhs);
}

//divi命令を実行する関数
void VirtualMachine::runOprDivi() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(lhs / rhs);
}

//スタックへプッシュ
void VirtualMachine::pushStack(int value) {
	if (stack.size() <= top) {
		stack.push_back(value);
		top++; 
	} else {
	stack.at(top++) = value; 
	}
}

//スタックからポップ
int VirtualMachine::popStack()
{
	return stack.at(--top); 
}

//スタックの戦闘の偶奇判別のodd命令を実行する関数
void VirtualMachine::runOprOdd() {
	int rhs = popStack();
	pushStack(rhs % 2);
}

//スタックから値2つを取り出し，等しいか比較するeq命令の関数
void VirtualMachine::runOprEq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs == lhs);
}

//eq命令の逆
void VirtualMachine::runOprNeq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs != lhs);
}

//2回ポップし，後の方が小さい場合1を返すlss命令を実行する関数
void VirtualMachine::runOprLt() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs > lhs);
}

//2回ポップし，後の方が先の値以下の場合1を返すlsseq命令を実行する関数
void VirtualMachine::runOprLteq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs >= lhs);
}

//2回ポップし，後の方が大きい場合1を返すgtr命令を実行する関数
void VirtualMachine::runOprGr() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs < lhs);
}

//2回ポップし，後の方が先の値以上の場合1を返すgtreq命令を実行する関数
void VirtualMachine::runOprGreq() {
	int rhs = popStack();
	int lhs = popStack();
	pushStack(rhs <= lhs);
}

//if文で用いられるjpc命令を実行する関数
void VirtualMachine::runJpc(Inst inst) {
	int value = popStack();
	if (value == 0) {
		pc = inst.index;
	}
}