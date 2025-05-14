//=============================================
//
//スモーク処理[somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //これが定義されてないとき

#define _SMOKE_H_

//=============================================
// スモーククラス
//=============================================
class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //テクスチャの名前
	static const int SMOKE_LIFE = 300; //スモークの持続時間

	static const int SMOKE_PRIORITY = 10; //描画順

	enum SMOKE_TYPE
	{
		SMOKE_TYPE_TACTICAL	= 0,
		SMOKE_TYPE_BROKEN
	};

	CSmoke(int nPriority = SMOKE_PRIORITY);
	~CSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//スモーク作成
	static CSmoke* Create(D3DXVECTOR3 pos, SMOKE_TYPE type);

	//移動量設定
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//移動量取得
	inline D3DXVECTOR3& GetMove()
	{
		return m_move;
	}

private:
	static constexpr float FADE_VALUE = 0.1f;  //アルファ値減衰量

	void Move();

	void FadeOut();

	int m_nLife;
	D3DXVECTOR3 m_move;
};

#endif