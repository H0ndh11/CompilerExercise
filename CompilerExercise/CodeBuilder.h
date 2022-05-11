#pragma once
#include <vector>
#include "Inst.h"

class CodeBuilder
{
public:
	CodeBuilder();
	~CodeBuilder();

	std::vector<Inst> code; // 生成する命令の列
	int currentIndex; // コードにおける現在の位置

	/**
	* 生成したコードを出力する
	*
	* @return その時点で生成されている命令列 code
	*/
	std::vector<Inst> getCode();

	/**
	* 命令を code に出力する
	* @param[in] 入力の命令
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emit(Inst inst);

	/**
	* ret 命令．
	* @param level 関数が宣言されているレベル（ブロックの深さ）
	* @param numParams 関数の受け取る引数の数
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitRet(int level, int numParams);

	/**
	* lit 命令
	* @param value value をスタックにプッシュする
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitLit(int value);

	/**
	* jpc 命令
	* @param level スタックのトップが 0 のときのジャンプ先
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitJpc(int level);

	/**
	* jmp 命令
	* @param[in] level ジャンプ先
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitJmp(int index);

	/**
	* ict 命令
	* @param[in] level 増加させる top の個数
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitIct(int localAddress);

	/**
	* sto 命令
	* @param[in] level      今のブロックの深さ
	* @param[in] relAddress ポップした値を格納する先の相対アドレス
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitSto(int level, int relAddress);

	/**
	* lod 命令
	* @param[in] level      今のブロックの深さ
	* @param[in] relAddress 読み込む値のおいてあるアドレス
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitLod(int level, int relAddress);

	/**
	* cal 命令
	* @param[in] level 呼び出し元のレベル
	* @param[in] index 呼び出す関数のおいてあるアドレス
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitCal(int level, int index);

	/**
	* 演算命令 の wrt．スタックのトップの値を出力する．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprWrt();

	/**
	* 演算命令 の wrl．改行を出力する
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprWrtLn();

	/**
	* 演算命令 の neg．スタックのトップの値の符号を反転
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprNeg();

	/**
	* 演算命令 の add．スタックから2つポップして，後にポップした値と先にポップした値を足して，結果をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprAdd();

	/**
	* 演算命令 の sub．スタックから2つポップして，後にポップした値から先にポップした値を引いて，結果をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprSub();

	/**
	* 演算命令 の mul．スタックから2つポップして，後にポップした値と先にポップした値を掛けて，結果をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprMul();

	/**
	* 演算命令 の divi．スタックから2つポップして，後にポップした値から先にポップした値を割って，結果をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprDiv();

	/**
	* 演算命令 の eq．スタックから2つポップして，後にポップした値と先にポップした値が等しければ 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprEq();

	/**
	* 演算命令 の neq．スタックから2つポップして，後にポップした値と先にポップした値が等しくなければ 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprNeq();

	/**
	* 演算命令 の ls．スタックから2つポップして，後にポップした値より先にポップした値が小さければ 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprLs();

	/**
	* 演算命令 の gr．スタックから2つポップして，後にポップした値より先にポップした値が大きければ 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprGr();

	/**
	* 演算命令 の lseq．スタックから2つポップして，後にポップした値より先にポップした値が等しいか小さければ 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprLseq();

	/**
	* 演算命令 の greq．スタックから2つポップして，後にポップした値より先にポップした値が等しいか大きければ 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprGreq();

	/**
	* 演算命令 の odd．スタックから2つポップして，ポップした値が奇数であれば 1 それ以外は 0 をプッシュ．
	* @return 命令を追加したあとのその命令のインデックス
	*/
	int emitOprOdd();

	/**
	* 指定したインデックスの命令のオペランドをあとから書き換える
	* @param jmpInstIndex インデックスを更新する jmp 命令のアドレス
	* @param newIndex 新しいジャンプ先のインデックス
	*/
	void backPatch(int jmpInstIndex, int newIndex);
};
