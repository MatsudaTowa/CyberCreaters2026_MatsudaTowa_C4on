//=============================================
//
//敵を妨害するスモーク処理[tactical_somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _TACTICAL_SMOKE_H_ //これが定義されてないとき

#define _TACTICAL_SMOKE_H_

//=============================================
// 敵を妨害するスモーククラス
//=============================================
class CTacticalSmoke : public CSmoke
{
public:
	CTacticalSmoke(int nPriority = SMOKE_PRIORITY);
	~CTacticalSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static constexpr float MOVE_X_MAX = 1.5f; //スモークの移動量の最大値_X
	static constexpr float MOVE_X_MIN = -1.5f; //スモークの移動量の最小値_X

	static constexpr float MOVE_Y_MAX = 0.4f; //スモークの移動量の最大値_Y
	static constexpr float MOVE_Y_MIN = 0.0f; //スモークの移動量の最小値_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //スモークの移動量の最大値_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //スモークの移動量の最小値_Z

	static constexpr float X_DECREASE = 0.01f; //Xの移動量減少定数

	static const D3DXVECTOR3 SIZE; //スモークのサイズ
};

#endif