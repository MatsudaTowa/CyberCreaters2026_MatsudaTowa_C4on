//=============================================
//
//スモークのカメラエフェクト「hit_camera_effect.cpp」
// Author松田永久
//
//=============================================
#include "smoke_camera_effect.h"
#include "manager.h"

//カメラのエフェクトテクスチャ
const std::string CSmokeCameraEffect::TEXTURE_NAME = "data\\TEXTURE\\smoke_camera_effect.png";

//=============================================
//コンストラクタ
//=============================================
CSmokeCameraEffect::CSmokeCameraEffect(int nPriority):CObject2D(nPriority),
m_alpha(FLOAT_ONE)
{
}

//=============================================
//デストラクタ
//=============================================
CSmokeCameraEffect::~CSmokeCameraEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmokeCameraEffect::Init()
{
	CObject2D::Init();

	//位置設定
	SetPos({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f });

	//サイズ取得
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * HALF, SCREEN_HEIGHT * HALF);

	//サイズを代入
	SetSize(size);

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(FLOAT_ONE, FLOAT_ONE, FLOAT_ONE, m_alpha);

	//カラーを代入
	SetColor(col);

	//頂点設定
	SetVtx(FLOAT_ONE);

	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmokeCameraEffect::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CSmokeCameraEffect::Update()
{
	//親クラスの終了
	CObject2D::Update();

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(FLOAT_ONE, FLOAT_ONE, FLOAT_ONE, m_alpha);

	//カラーを代入
	SetColor(col);

	//頂点設定
	SetVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CSmokeCameraEffect::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CSmokeCameraEffect* CSmokeCameraEffect::Create()
{
	CSmokeCameraEffect* pSmokeCameraEffect = new CSmokeCameraEffect;

	if (pSmokeCameraEffect == nullptr) { return nullptr; }

	pSmokeCameraEffect->SetType(OBJECT_TYPE_SMOKE_CAMERA_EFFECT); //タイプ設定

	pSmokeCameraEffect->Init();

	return pSmokeCameraEffect;
}

//=============================================
//アルファ値減算
//=============================================
void CSmokeCameraEffect::SubAlpha()
{
	m_alpha -= FADE_VALUE;
}
