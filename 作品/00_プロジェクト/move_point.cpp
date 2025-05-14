//=============================================
// 
//敵が徘徊する際に向かうポイント[move_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "move_point.h"
#include "manager.h"

//何番目の地点か
int CMovePoint::m_NumPoint = 0;

//=============================================
//コンストラクタ
//=============================================
CMovePoint::CMovePoint(int nPriority):CBillboard(nPriority)
{
	++m_NumPoint;
}

//=============================================
//デストラクタ
//=============================================
CMovePoint::~CMovePoint()
{
	--m_NumPoint;
}

//=============================================
//初期化
//=============================================
HRESULT CMovePoint::Init()
{
	SetSize(D3DXVECTOR3(POINT_SIZE,POINT_SIZE,FLOAT_ZERO));
	//親クラスの初期化
	CObject3D::Init();
	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CMovePoint::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CMovePoint::Update()
{
	//親クラスの更新処理
	CObject3D::Update();
}

//=============================================
//描画
//=============================================
void CMovePoint::Draw()
{
#ifdef _DEBUG
	CBillboard::Draw();
#endif // _DEBUG
}

//=============================================
//生成
//=============================================
CMovePoint* CMovePoint::Create(D3DXVECTOR3 pos)
{
	CMovePoint* pMovePoint = new CMovePoint;
	if(pMovePoint == nullptr){ return nullptr; }

	//位置の設定
	pMovePoint->SetPos(pos);

	pMovePoint->Init();

	return pMovePoint;
}
