//=============================================
//
//ヒット時のカメラエフェクト「hit_camera_effect.cpp」
// Author松田永久
//
//=============================================
#include "hit_camera_effect.h"
#include "hit_camera_effect_mild.h"
#include "hit_camera_effect_moderate.h"
#include "hit_camera_effect_severe.h"
#include "manager.h"

//色
const D3DXCOLOR CHitCameraEffect::COLOR = { 0.5f, 0.0f, 0.0f, 0.8f };

//=============================================
//コンストラクタ
//=============================================
CHitCameraEffect::CHitCameraEffect(int nPriority): CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CHitCameraEffect::~CHitCameraEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitCameraEffect::Init()
{
	CObject2D::Init();

	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH*HALF, SCREEN_HEIGHT* HALF);

	//サイズを代入
	SetSize(size);

	//カラーを代入
	SetColor(COLOR);

	//頂点設定
	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CHitCameraEffect::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CHitCameraEffect::Update()
{
	//親クラスの終了
	CObject2D::Update();

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(COLOR.r, COLOR.g, COLOR.b, m_alpha);

	//カラーを代入
	SetColor(col);

	//頂点設定
	SetVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CHitCameraEffect::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CHitCameraEffect* CHitCameraEffect::Create(D3DXVECTOR3 pos, HIT_EFFECT_STAGE stage)
{
	CHitCameraEffect* pHitCameraEffect = nullptr;
	//CObject *pObject = Getobject();

	switch (stage)
	{
	case CHitCameraEffect::MILD:
		pHitCameraEffect = new CHitCameraEffectMild;
		break;
	case CHitCameraEffect::MODERATE:
		pHitCameraEffect = new CHitCameraEffectModerate;
		break;
	case CHitCameraEffect::SEVERE:
		pHitCameraEffect = new CHitCameraEffectSevere;
		break;
	default:
		assert(false);
		break;
	}

	if (pHitCameraEffect == nullptr) {return nullptr;}

	pHitCameraEffect->SetPos(pos); //pos設定

	pHitCameraEffect->m_alpha = COLOR.a;	//アルファ値設定

	pHitCameraEffect->SetType(OBJECT_TYPE_HIT_CAMERA_EFFECT); //タイプ設定

	pHitCameraEffect->Init();

	return pHitCameraEffect;
}

//=============================================
//アルファ値減算
//=============================================
void CHitCameraEffect::SubAlpha()
{
	m_alpha -= SUB_ALPHA;
}
