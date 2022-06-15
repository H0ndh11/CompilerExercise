#include "pch.h"
#include "../CompilerExercise/utils.h"
#include "../CompilerExercise/utils.cpp"
#include "../CompilerExercise/Inst.h"
#include "../CompilerExercise/Inst.cpp"
#include "../CompilerExercise/CodeBuilder.h"
#include "../CompilerExercise/CodeBuilder.cpp"
#include "../CompilerExercise/Source.h"
#include "../CompilerExercise/Source.cpp"
#include "../CompilerExercise/NameTable.h"
#include "../CompilerExercise/NameTable.cpp"
#include "../CompilerExercise/Compiler.h"
#include "../CompilerExercise/Compiler.cpp"
#include "../CompilerExercise/VirtualMachine.h"
#include "../CompilerExercise/VirtualMachine.cpp"

TEST(_1_EmptyProgram, CompileOK) {
	std::string source = ".";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	EXPECT_EQ(vm.output, "");
}
TEST(_1_EmptyProgram, RunRet) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm(code);

	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.stack.at(0), 0);
	EXPECT_EQ(vm.display.at(0), 0);
}


TEST(_2_CompileWrite, Tokenize) {
	std::string source = "write writeln 123.";

	Source tokenizer = Source(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Write);
	EXPECT_EQ(tokenizer.nextToken().kind, WriteLn);
	EXPECT_EQ(tokenizer.nextToken().kind, Num);
	EXPECT_EQ(tokenizer.nextToken().kind, Period);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

TEST(_2_CompileWrite, RunOprWrt) {
	std::vector<Inst> code;

	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 123, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "123");
}

TEST(_2_CompileWrite, RunOprWrtLn) {

	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrl, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "\n");

}

TEST(_2_CompileWrite, ExecWrite) {
	std::string source = "write 123.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "123";
	EXPECT_EQ(vm.output, e_str);
}

TEST(_2_CompileWrite, ExecWriteLn) {
	std::string source = "writeln.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "\n";
	EXPECT_EQ(vm.output, e_str);
}

TEST(_3_ArithmeticCalc, Tokenize) {
	std::string source = "+ - * / ( ) .";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Plus);
	EXPECT_EQ(tokenizer.nextToken().kind, Minus);
	EXPECT_EQ(tokenizer.nextToken().kind, Mult);
	EXPECT_EQ(tokenizer.nextToken().kind, Div);
	EXPECT_EQ(tokenizer.nextToken().kind, Lparen);
	EXPECT_EQ(tokenizer.nextToken().kind, Rparen);
	EXPECT_EQ(tokenizer.nextToken().kind, Period);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

TEST(_3_ArithmeticCalc, RunOprNeg) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 123, 0, 0, 0, 0));
	code.push_back(Inst(opr, neg, 0, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "-123");
}

VirtualMachine threeCompileRun(Operator op)
{
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 10, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 5, 0, 0, 0, 0));
	code.push_back(Inst(opr, op, 0, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	return vm;
}

TEST(_3_ArithmeticCalc, RunOprs) {
	EXPECT_EQ(threeCompileRun(add).output, "15");
	EXPECT_EQ(threeCompileRun(sub).output, "5");
	EXPECT_EQ(threeCompileRun(mul).output, "50");
	EXPECT_EQ(threeCompileRun(divi).output, "2");
}



TEST(_3_ArithmeticCalc, Plus_Times) {
	std::string source = "write 1 + 2 * 3.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "7";
	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_3_ArithmeticCalc, Minus_with_Parenthesis) {
	std::string source = "write - (3 - 5).";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "2";
	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_3_ArithmeticCalc, Div_Unary_Plus) {
	std::string source = "write + 10 / 2.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "5";
	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_3_ArithmeticCalc, Left_Join) {
	std::string source = "write 10 - 5 - 2.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "3";
	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_3_ArithmeticCalc, Unary_Minus_Times) {
	std::string source = "write - 2 * (-3).";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "6";
	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}


TEST(_4_Begin_End, Tokenize) {
	std::string source = "begin end ;";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Begin);
	EXPECT_EQ(tokenizer.nextToken().kind, End);
	EXPECT_EQ(tokenizer.nextToken().kind, Semicolon);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);

}


TEST(_4_Begin_End, Run_Being_End) {
	std::string source = "begin "
		"write 12; "
		"writeln; "
		"  begin "
		"  write 34 "
		"  end;"
		"end.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "12\n34";
	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_5_If_Then, Tokenize_if_then_odd) {
	std::string source = "if then odd";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, If);
	EXPECT_EQ(tokenizer.nextToken().kind, Then);
	EXPECT_EQ(tokenizer.nextToken().kind, Odd);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

TEST(_5_If_Then, Tokenize_comps) {
	std::string source = "< > <= >= <> =";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Lss);
	EXPECT_EQ(tokenizer.nextToken().kind, Gtr);
	EXPECT_EQ(tokenizer.nextToken().kind, LssEq);
	EXPECT_EQ(tokenizer.nextToken().kind, GtrEq);
	EXPECT_EQ(tokenizer.nextToken().kind, NotEq);
	EXPECT_EQ(tokenizer.nextToken().kind, Equal);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

VirtualMachine genVms(int v1, Operator op, int v2) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, v1, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, v2, 0, 0, 0, 0));
	code.push_back(Inst(opr, op, 0, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	return vm;
}

TEST(_5_If_Then, Check_comp) {
	std::string source = "< > <= >= <> =";
	Source tokenizer(source);

	EXPECT_EQ(genVms(2, eq, 2).output, "1");
	EXPECT_EQ(genVms(2, eq, 3).output, "0");

	EXPECT_EQ(genVms(2, ls, 3).output, "1");
	EXPECT_EQ(genVms(3, ls, 2).output, "0");
	EXPECT_EQ(genVms(2, ls, 2).output, "0");

	EXPECT_EQ(genVms(2, gr, 3).output, "0");
	EXPECT_EQ(genVms(3, gr, 2).output, "1");
	EXPECT_EQ(genVms(2, gr, 2).output, "0");

	EXPECT_EQ(genVms(3, neq, 2).output, "1");
	EXPECT_EQ(genVms(2, neq, 2).output, "0");

	EXPECT_EQ(genVms(3, lseq, 2).output, "0");
	EXPECT_EQ(genVms(2, lseq, 2).output, "1");
	EXPECT_EQ(genVms(2, lseq, 3).output, "1");

	EXPECT_EQ(genVms(3, greq, 2).output, "1");
	EXPECT_EQ(genVms(2, greq, 2).output, "1");
	EXPECT_EQ(genVms(2, greq, 3).output, "0");

}


TEST(_5_If_Then, Check_Odd) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(opr, odd, 0, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 3, 0, 0, 0, 0));
	code.push_back(Inst(opr, odd, 0, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);
	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "01");
}

TEST(_5_If_Then, Run_Jpc) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 0, 0, 0, 0, 0));
	code.push_back(Inst(jpc, nop, 0, 0, 0, 5, 0));
	code.push_back(Inst(lit, nop, 123, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 456, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);
	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "456");

}

std::string fiveCompileRun(std::string& op) {
	std::string source = "begin "
		"if 2 " + op + " 3 then write 1; "
		"if 3 " + op + " 2 then write 2; "
		"if 2 " + op + " 2 then write 3 "
		"end. ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	return vm.output;

}
TEST(_5_If_Then, Run_Code) {

	EXPECT_EQ(fiveCompileRun(std::string("<")), "1");
	EXPECT_EQ(fiveCompileRun(std::string("<=")), "13");
	EXPECT_EQ(fiveCompileRun(std::string(">")), "2");
	EXPECT_EQ(fiveCompileRun(std::string(">=")), "23");
	EXPECT_EQ(fiveCompileRun(std::string("=")), "3");
	EXPECT_EQ(fiveCompileRun(std::string("<>")), "12");
}

TEST(_5_If_Then, Run_Odd) {
	std::string source = "begin "
		"if odd 2 then write 1; "
		"if odd 3 then write 2 "
		"end. ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "2");
}

TEST(_5_If_Then, Run_Sample) {
	std::string source = "begin "
		"if 10 > 5 then begin "
		"    write 123; "
		"    writeln "
		"end; "
		"write 456 "
		"end. ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "123\n456");
}

TEST(_6_Const, Tokenize) {
	std::string source = "const = , ;";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Const);
	EXPECT_EQ(tokenizer.nextToken().kind, Equal);
	EXPECT_EQ(tokenizer.nextToken().kind, Comma);
	EXPECT_EQ(tokenizer.nextToken().kind, Semicolon);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

TEST(_6_Const, Const_reg_and_get) {
	NameTable nametable = NameTable();

	std::string const_a = "a";
	std::string const_b = "b";
	nametable.addConst(const_a, 10);
	nametable.addConst(const_b, 20);

	EXPECT_EQ(nametable.search(const_a).kind, Const);
	EXPECT_EQ(nametable.search(const_a).value, 10);
	EXPECT_EQ(nametable.search(const_b).kind, Const);
	EXPECT_EQ(nametable.search(const_b).value, 20);
}

TEST(_6_Const, RunConst) {
	std::string source = "const a = 3, b= 4; write a * b.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "12";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_6_Const, RunConstMulline) {
	std::string source = "const a = 3; const b= 4; write a * b.";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "12";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_7_Var, Tokenize) {
	std::string source = "var :=";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Var);
	EXPECT_EQ(tokenizer.nextToken().kind, Assign);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}


TEST(_7_Var, Run_Ict_Sto_Lod) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 4, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 10, 0, 0, 0, 0));
	code.push_back(Inst(sto, nop, 0, 0, 0, 0, 2));
	code.push_back(Inst(lit, nop, 20, 0, 0, 0, 0));
	code.push_back(Inst(sto, nop, 0, 0, 0, 0, 3));
	code.push_back(Inst(lod, nop, 0, 0, 0, 0, 2));
	code.push_back(Inst(lod, nop, 0, 0, 0, 0, 3));
	code.push_back(Inst(opr, add, 0, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);
	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "30");
}

TEST(_7_Var, Run_Code) {
	std::string source = "var x, y ; "
		"begin "
		"  x := 10; "
		"  write x * 2 "
		" end. ";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "20";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_8_While, Tokenize) {
	std::string source = "while do";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, While);
	EXPECT_EQ(tokenizer.nextToken().kind, Do);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

TEST(_8_While, Run_Jmp) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(jmp, nop, 0, 0, 0, 4, 0));
	code.push_back(Inst(lit, nop, 123, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(lit, nop, 456, 0, 0, 0, 0));
	code.push_back(Inst(opr, wrt, 0, 0, 0, 0, 0));
	code.push_back(Inst(ret, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);
	vm.run();

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, "456");

}

TEST(_8_While, Run_Code) {
	std::string source = "var i; "
		" begin "
		"   i := 5; "
		"   while i > 0 do "
		"   begin "
		"     write i; "
		"     writeln; "
		"     i := i - 1 "
		"   end "
		" end. ";
	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);

	vm.run();

	std::string e_str = "5\n4\n3\n2\n1\n";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);

}

TEST(_8_While, CalcFibonacci) {
	std::string source = "const n = 10; "
		"  var x0, x1, i, tmp; "
		"  begin "
		"    i := n; "
		"    x0 := 0; "
		"    x1 := 1; "
		"    while i > 0 do begin "
		"      tmp := x0 + x1; "
		"      x0 := x1; "
		"      x1 := tmp; "
		"      i := i - 1 "
		"    end; "
		"    write x1; "
		"    writeln "
		"  end.`; ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);
	vm.run();


	std::string e_str = "89\n";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_9_Function, Tokenize) {
	std::string source = "function return";
	Source tokenizer(source);

	EXPECT_EQ(tokenizer.nextToken().kind, Func);
	EXPECT_EQ(tokenizer.nextToken().kind, Ret);
	EXPECT_EQ(tokenizer.nextToken().kind, nul);
}

TEST(_9_Function, Run_Cal) {
	std::vector<Inst> code;
	code.push_back(Inst(ict, nop, 2, 0, 0, 0, 0));
	code.push_back(Inst(cal, nop, 0, 0, 0, 2, 0));
	code.push_back(Inst(jmp, nop, 0, 0, 0, 0, 0));

	VirtualMachine vm = VirtualMachine(code);
	vm.run();

	EXPECT_EQ(vm.pc, 0);

	int i;
	i = vm.stack.back();
	EXPECT_EQ(i, 2);
	vm.stack.pop_back();
	i = vm.stack.back();
	EXPECT_EQ(i, -1);
	vm.stack.pop_back();
	i = vm.stack.back();
	EXPECT_EQ(i, 0);
	vm.stack.pop_back();
	i = vm.stack.back();
	EXPECT_EQ(i, 0);
}

TEST(_9_Function, Test_Code1) {
	std::string source = "function f(x) "
		"  var y; "
		"  begin "
		"    y := x * 2; "
		"    return y "
		"  end; "
		"  write f(10).";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);
	vm.run();


	std::string e_str = "20";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_9_Function, Test_Rec) {
	std::string source = " function fact(n) "
		"   begin "
		"     if n = 0 then return 1; "
		"     return n * fact(n - 1) "
		"   end; "
		" write fact(5). ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);
	vm.run();


	std::string e_str = "120";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_9_Function, Test_Shadowing) {

	std::string source = "    var x;          "
		"    function f1(y)  "
		"    begin           "
		"      x := y + 1;   "
		"      return x      "
		"    end;            "
		"    function f2(y)  "
		"    var x;          "
		"    begin           "
		"      x := y + 1;   "
		"      return x      "
		"    end;            "
		"    begin           "
		"      write f1(10); "
		"      writeln;      "
		"      write f2(20); "
		"      writeln;      "
		"      write x;      "
		"      writeln       "
		"    end.            ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);
	vm.run();


	std::string e_str = "11\n21\n11\n";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}

TEST(_9_Function, Multiply_Function) {

	std::string source = "  "
		"function multiply(x, y) "
		"  var a, b, c; "
		"  begin "
		"    a := x; "
		"    b := y; "
		"    c := 0; "
		"    while b > 0 do "
		"      begin "
		"        if odd b then c := c + a; "
		"        a := 2 * a; "
		"        b := b /2 "
		"      end; "
		"    return c "
		"  end; "
		"       "
		"  const m = 7, n = 85; "
		"  var x, y; "
		"        "
		"  begin "
		"    x := m; "
		"    y := n; "
		"    write multiply(x, y); "
		"    writeln "
		"  end. "
		"    ";

	Compiler c = Compiler(source);
	std::vector<Inst> code = c.compile();
	VirtualMachine vm = VirtualMachine(code);
	vm.run();


	std::string e_str = "595\n";

	EXPECT_EQ(vm.pc, 0);
	EXPECT_EQ(vm.output, e_str);
}
