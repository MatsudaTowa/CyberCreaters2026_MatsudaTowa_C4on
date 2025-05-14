//=============================================
//
//ブロックの破片[block_piece.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BLOCK_PIECE_H_ //これが定義されてないとき

#define _BLOCK_PIECE_H_
#include "main.h"
#include "objectX.h"
#include "manager.h"

//=============================================
//ブロックの破片クラス
//=============================================
class CBlock_Piece : public CObjectX
{
public:
	static const int BLOCK_PRIORITY = 10; //描画順

	enum PIECE_SHAPE
	{
		PIECE_SHAPE_0 = 0,
		PIECE_SHAPE_1,
		PIECE_SHAPE_2,
		PIECE_SHAPE_MAX,
	};

	static const char* MODEL_NAME[PIECE_SHAPE_MAX];	//モデルの名前

	CBlock_Piece(int nPriority = BLOCK_PRIORITY);
	~CBlock_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CBlock_Piece* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 scale,bool isMove);
private:
	static constexpr float SHIFT_X_MAX = 50.0f;
	static constexpr float SHIFT_X_MIN = -50.0f;

	static constexpr float SHIFT_Z_MAX = 50.0f;
	static constexpr float SHIFT_Z_MIN = -50.0f;
	PIECE_SHAPE m_shape;
};

//=============================================
//ブロックの動かす破片クラス
//=============================================
class CMove_Piece :public CBlock_Piece
{
public:
	CMove_Piece(int nPriority = BLOCK_PRIORITY);
	~CMove_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static const int LIFE = 120;				//寿命
	static const int RAND_RANGE = 101;			//ランダムの算出範囲
	static constexpr float MIN_MOVE = 5.0f;		//移動量の最低値
	static constexpr float MOVE_RANGE = 10.0f;	//移動量の算出範囲
	D3DXVECTOR3 m_move;
	int m_nLife;
};

//=============================================
//ブロックの動かさない破片クラス
//=============================================
class CStack_Piece :public CBlock_Piece
{
public:
	CStack_Piece(int nPriority = BLOCK_PRIORITY);
	~CStack_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif