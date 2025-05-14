//=============================================
//
//スモークのカメラエフェクト「hit_camera_effect.h」
// Author松田永久
//
//=============================================
#ifndef _SMOKE_CAMERA_EFFECT_H_ //これが定義されてないとき
#define _SMOKE_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//スモークのカメラエフェクトクラス
//=============================================
class CSmokeCameraEffect :public CObject2D
{
public:
	static const int PRIORITY = 28; //描画順

	CSmokeCameraEffect(int nPriority = PRIORITY);
	~CSmokeCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CSmokeCameraEffect* Create();

	void SubAlpha();

	inline float& GetAlpha()
	{
		return m_alpha;
	}
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	static constexpr float FADE_VALUE = 0.01f;  //アルファ値減衰量

	float m_alpha; //アルファ値
};

#endif // _HIT_CAMERA_EFFECT_H_