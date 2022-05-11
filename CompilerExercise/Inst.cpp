#include "Inst.h"



Inst::Inst(OpCode _opcode, Operator _opr, int _value, int _level, int _numParams, int _index, int _relAddress): 
	opcode(_opcode), opr(_opr), value(_value), level(_level), numParams(_numParams), index(_index), relAddress(_relAddress)
{
}

Inst::~Inst()
{
}
