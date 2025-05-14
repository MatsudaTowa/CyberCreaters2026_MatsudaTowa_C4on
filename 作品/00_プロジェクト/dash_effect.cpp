//=============================================
//
//ダッシュ時にキャラクターの前方に出すエフェクト[dash_effect.cpp]
//Author Matsuda Towa
//
//=============================================
#include "dash_effect.h"
#include "manager.h"

//xファイルのファイルパス
const char* CDashEffect::MODEL_NAME = "data\\MODEL\\dash_effect.x";

//スケール
const D3DXVECTOR3 CDashEffect::SCALE = { 10.0f, 10.0f, 10.0f };

//カラー
const D3DXCOLOR CDashEffect::COLOR = { 1.0f, 1.0f, 1.0f,0.35f };

//=============================================
//コンストラクタ
//=============================================
CDashEffect::CDashEffect(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CDashEffect::~CDashEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CDashEffect::Init()
{
	//描画に必要な情報設定
	SetScale(SCALE);
	SetColor(COLOR);
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CDashEffect::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CDashEffect::Update()
{
	CObjectX::Update();
}

//=============================================
//描画
//=============================================
void CDashEffect::Draw()
{
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CDashEffect* CDashEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CDashEffect* pEffect = new CDashEffect;
	if (pEffect == nullptr) { return nullptr; }

	pEffect->SetPos(pos);	//位置設定

	pEffect->SetRot(rot);	//方向設定

	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	pEffect->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pEffect->SetType(OBJECT_TYPE_DUSH_EFFECT); //タイプ設定

	pEffect->Init();	//初期化設定

	return pEffect;
}
