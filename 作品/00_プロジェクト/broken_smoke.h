//=============================================
//
//ブロックから生成するスモーク処理[broken_somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _BROKEN_SMOKE_H_ //これが定義されてないとき

#define _BROKEN_SMOKE_H_

//=============================================
//ブロックから生成するスモーククラス
//=============================================
class CBrokenSmoke : public CSmoke
{
public:
	CBrokenSmoke(int nPriority = SMOKE_PRIORITY);
	~CBrokenSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static constexpr float MOVE_X_MAX = 0.3f; //スモークの移動量の最大値_X
	static constexpr float MOVE_X_MIN = -0.3f; //スモークの移動量の最小値_X

	static constexpr float MOVE_Y_MAX = 0.7f; //スモークの移動量の最大値_Y
	static constexpr float MOVE_Y_MIN = 0.1f; //スモークの移動量の最小値_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //スモークの移動量の最大値_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //スモークの移動量の最小値_Z

	static const D3DXVECTOR3 SIZE; //スモークのサイズ

	static const D3DXCOLOR COLOR;
};

#endif