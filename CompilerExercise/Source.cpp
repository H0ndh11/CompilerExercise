#include "Source.h"


Source::Source(std::string& _source)
	: source(_source), index(0), ch('\0') {
	//次の文字読み取り
	nextChar();
};

//source内の次の文字を返す関数
char Source::nextChar() {
	if (index >= source.size()) {
		ch = '\0';
	}
	else {
		//インクリメントがされるのは関数に渡した"後"
		ch = source.at(index++);
	}
	return ch;
}

//chがスペース，改行，tabならスキップ
void Source::skipSpaces() {
	while (ch == ' '||ch=='\n'||ch=='\t') {
		nextChar();
	}
}

//次のトークンを読み出す処理を行う関数
Token Source::nextToken() {
	skipSpaces();//空白文字を飛ばす

	//数値の場合
	if (isDigit(ch)) {
		//1文字目が数字なら数値トークンなのでnextNumberTokenに任せる
		return nextNumberToken();
	}

	//識別子の場合
	if (isIdenfitifierStartChar(ch)) {
		//1文字目が識別子なら識別子トークンなのでnextIdentifierOrKeywordTokenに任せる
		return nextIdentifierOrKeywordToken();
	}

	//記号の場合
	if (isSymbolToken(ch)) {
		//各記号に応じてトークンを返す
		if (ch == '.') {
			nextChar();
			return { Period, "", 0 };
		}
		else if (ch == '+') {
			nextChar();
			return { Plus,"",0 };
		}
		else if (ch == '-') {
			nextChar();
			return { Minus,"",0 };
		}
		else if (ch == '*') {
			nextChar();
			return { Mult,"",0 };
		}
		else if (ch == '/') {
			nextChar();
			return { Div,"",0 };
		}
		else if (ch == '(') {
			nextChar();
			return { Lparen,"",0 };
		}
		else if (ch == ')') {
			nextChar();
			return { Rparen,"",0 };
		}
		else if (ch == ';') {
			nextChar();
			return { Semicolon,"",0 };
		}
		else if (ch == '<') {
			nextChar();
			//等号が後ろにある場合，つまり"<="であった場合
			if (ch == '=') {
				nextChar();
				return { LssEq, "", 0};
			}
			//大なりが後ろにある場合，つまり"<>"であった場合
			else if (ch == '>') {
				nextChar();
				return { NotEq, "",0 };
			}
			//'<'だけの場合
			else {
				return { Lss, "", 0 };
			}
		}
		else if (ch == '>') {
			nextChar();
			//等号が後ろにある場合，つまり">="であった場合
			if (ch == '=') {
				nextChar();
				return { GtrEq, "", 0 };
			}
			//'>'だけの場合
			else {
				return { Gtr, "", 0 };
			}
		}
		else if (ch == '=') {
			nextChar();
			return { Equal, "", 0 };
		}
		else if (ch == ',') {
			nextChar();
			return { Comma, "", 0 };
		}
	}

	//:=の場合
	if (ch == ':') {
		nextChar();
		if (ch == '=') {
			nextChar();
			return { Assign, "", 0 };
		}
	}
	

	//トークンが見つからなかった場合
	return {nul, "", 0};
}

//数値トークンを読み出す処理を行う関数
Token Source::nextNumberToken() {
	//num初期化
	int num = 0;
	//数字が続く限り数値化
	while (isDigit(ch)) {
		num = num * 10 + (ch - '0');
		nextChar();
	}
	//token化して返す
	Token tk = { Num,"",num };
	return tk;
}

//識別子トークンを読み出す処理を行う関数
Token Source::nextIdentifierOrKeywordToken() {
	//tokenの実際の文字列を保存(writeやwritelnなど)
	//空定義しておくこと！(資料にはないけど，正しくテスト通過しないため)
	std::string value="";

	//chが識別子に使える限り文字列valueの後ろに追加
	while (isIdentifierChar(ch)){
		value = value + ch;
		nextChar();
	}

	//valueが予約語だったら
	if (isKeyword(value)) {
		//valueがwriteならWriteトークンを返す
		if (value == "write") {
			return { Write,"",0 };
		}
		//writelnならWriteLnトークンを返す
		else if (value == "writeln") {
			return { WriteLn, "",0 };
		}
		//beginならbeginトークン
		else if (value == "begin") {
			return { Begin, "", 0 };
		}
		//endならendトークン
		else if (value == "end") {
			return { End, "", 0 };
		}
		//if
		else if (value == "if") {
			return { If, "", 0 };
		}
		//then
		else if (value == "then") {
			return { Then, "", 0 };
		}
		//odd
		else if (value == "odd") {
			return { Odd, "", 0 };
		}
		//const
		else if (value == "const") {
			return { Const, "", 0 };
		}
		//var
		else if (value == "var") {
			return { Var, "", 0 };
		}
		//while
		else if (value == "while") {
			return { While, "", 0 };
		}
		//do
		else if (value == "do") {
			return { Do, "", 0 };
		}
	}

	//それ以外は変数(Id)としてトークンを返す
	//資料と違うので注意(step5以前)
	return { Id, value, 0};
}

//cが1文字でトークンになる記号( ., +. -, *, /, (, ), ; など)ならtrueを返す関数
bool Source::isSymbolToken(char c) {
	if (c == '.' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c ==';' || c=='<' || c == '>' || c == '='|| c==',') {
		return true;
	}
	else {
		return false;
	}
}

//strが予約語（writeやwriteln, begin, endなど)の場合，trueを返す関数
bool Source::isKeyword(std::string& str) {
	if (str == "write" || str == "writeln"|| str == "begin" || str == "end" || str == "if" || str == "then" || str=="odd"|| str=="const" || str=="var" || str== "while" || str =="do") {
		return true;
	}
	else {
		return false;
	}
}