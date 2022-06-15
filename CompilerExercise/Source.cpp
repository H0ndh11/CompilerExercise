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
			Token tk = { Period, "", 0 };
			return tk;
		}
		else if (ch == '+') {
			nextChar();
			Token tk = { Plus,"",0 };
			return tk;
		}
		else if (ch == '-') {
			nextChar();
			Token tk = { Minus,"",0 };
			return tk;
		}
		else if (ch == '*') {
			nextChar();
			Token tk = { Mult,"",0 };
			return tk;
		}
		else if (ch == '/') {
			nextChar();
			Token tk = { Div,"",0 };
			return tk;
		}
		else if (ch == '(') {
			nextChar();
			Token tk = { Lparen,"",0 };
			return tk;
		}
		else if (ch == ')') {
			nextChar();
			Token tk = { Rparen,"",0 };
			return tk;
		}
		else if (ch == ';') {
			nextChar();
			Token tk = { Semicolon,"",0 };
			return tk;
		}
		else if (ch == '<') {
			nextChar();
			//等号が後ろにある場合，つまり"<="であった場合
			if (ch == '=') {
				nextChar();
				Token tk = { LssEq, "", 0};
				return tk;
			}
			//大なりが後ろにある場合，つまり"<>"であった場合
			else if (ch == '>') {
				nextChar();
				Token tk = { NotEq, "",0 };
				return tk;
			}
			//'<'だけの場合
			else {
				Token tk = { Lss, "", 0 };
				return tk;
			}
		}
		else if (ch == '>') {
			nextChar();
			//等号が後ろにある場合，つまり">="であった場合
			if (ch == '=') {
				nextChar();
				Token tk = { GtrEq, "", 0 };
				return tk;
			}
			//'>'だけの場合
			else {
				Token tk = { Gtr, "", 0 };
				return tk;
			}
		}
		else if (ch == '=') {
			nextChar();
			Token tk = { Equal, "", 0 };
			return tk;
		}
	}
	

	//トークンが見つからなかった場合
	Token tk = {nul, "", 0 };
	return tk; 
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
			Token tk = { Write,"",0 };
			return tk;
		}
		//writelnならWriteLnトークンを返す
		else if (value == "writeln") {
			Token tk = { WriteLn, "",0 };
			return tk;
		}
		//beginならbeginトークン
		else if (value == "begin") {
			Token tk = { Begin, "", 0 };
			return tk;
		}
		//endならendトークン
		else if (value == "end") {
			Token tk = { End, "", 0 };
			return tk;
		}
		//if
		else if (value == "if") {
			Token tk = { If, "", 0 };
			return tk;
		}
		//Then
		else if (value == "then") {
			Token tk = { Then, "", 0 };
			return tk;
		}
		//Odd
		else if (value == "odd") {
			Token tk = { Odd, "", 0 };
			return tk;
		}
	}


	//それ以外はIdとしてトークンを返す
	//資料と違うので注意
	Token tk = { Id, "", 0};
	return tk;
}

//cが1文字でトークンになる記号( ., +. -, *, /, (, ), ; など)ならtrueを返す関数
bool Source::isSymbolToken(char c) {
	if (c == '.' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c ==';' || c=='<' || c == '>' || c == '=') {
		return true;
	}
	else {
		return false;
	}
}

//strが予約語（writeやwriteln, begin, endなど)の場合，trueを返す関数
bool Source::isKeyword(std::string& str) {
	if (str == "write" || str == "writeln"|| str == "begin" || str == "end" || str == "if" || str == "then" || str=="odd") {
		return true;
	}
	else {
		return false;
	}
}