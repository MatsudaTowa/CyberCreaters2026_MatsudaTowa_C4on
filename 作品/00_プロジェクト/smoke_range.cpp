//=============================================
//
//スモーク範囲処理[somoke_range.cpp]
//Author Matsuda Towa
//
//=============================================
#include "smoke_range.h"
#include "manager.h"

//モデルパス
const char* CSmokeRange::MODEL_NAME = "data\\MODEL\\colision.x";

//=============================================
//コンストラクタ
//=============================================
CSmokeRange::CSmokeRange(int nPriority):CObjectX(nPriority),
m_nLife(INT_ZERO)			//寿命
{
}

//=============================================
//デストラクタ
//=============================================
CSmokeRange::~CSmokeRange()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmokeRange::Init()
{
	//親クラスの初期化
	CObjectX::Init();
	m_nLife = CSmoke::SMOKE_LIFE;	//寿命代入
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmokeRange::Uninit()
{
	//親クラスの終了
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CSmokeRange::Update()
{
	//親クラスの更新
	CObjectX::Update();

	//寿命減算
	--m_nLife;
	
	if(m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CSmokeRange::Draw()
{
#ifdef _DEBUG
	//CObjectX::Draw();

#endif // _DEBUG

}

//=============================================
//生成
//=============================================
CSmokeRange* CSmokeRange::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSmokeRange* pSmokeRange = new CSmokeRange;

	if (pSmokeRange == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	pSmokeRange->SetPos(pos);	//位置設定
	pSmokeRange->SetRot(rot);	//方向設定
	//Xファイル読み込み
	pSmokeRange->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);
	pSmokeRange->SetType(OBJECT_TYPE_SMOKE_RANGE);	//オブジェクトタイプ設定
	pSmokeRange->Init();	//初期化処理

	return pSmokeRange;
}
