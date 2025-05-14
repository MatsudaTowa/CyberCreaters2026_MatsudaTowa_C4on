//=============================================
//
//ビルボード[billboard.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BILLBOARD_H_ //これが定義されてないとき

#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

//=============================================
//ビルボードクラス
//=============================================
class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority);
	~CBillboard()override;
	void Draw()override;
};
#endif