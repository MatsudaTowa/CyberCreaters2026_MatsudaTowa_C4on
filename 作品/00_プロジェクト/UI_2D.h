//=============================================
//
//2DUIの表記[UI_2D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _UI_2D_H_ //これが定義されてないとき

#define _UI_2D_H_
#include "main.h"
#include "object2D.h"

//2DUIの表記クラス
class CUI_2D : public CObject2D
{
public:
	static const int PRIORITY = 20;  //描画順

	CUI_2D(int nPriority = PRIORITY);
	~CUI_2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	bool m_isDraw;
};
#endif