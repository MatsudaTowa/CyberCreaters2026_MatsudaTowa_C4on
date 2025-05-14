//=============================================
//
//センタードット[centerdot.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CENTERDOT_H_ //これが定義されてないとき

#define _CENTERDOT_H_

//=============================================
//センタードットクラス
//=============================================
class CCenterDot : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 19; //描画順

	CCenterDot(int nPriority = RETICLE_PRIORITY);
	~CCenterDot()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//センタードット作成
	static CCenterDot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string CENTERDOT_TEXTURE_NAME;	//テクスチャの名前
};

#endif