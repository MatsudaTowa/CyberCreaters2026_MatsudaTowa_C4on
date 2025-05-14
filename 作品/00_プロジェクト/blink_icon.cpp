//=============================================
//
//ブリンクの表記[blink_icon.cpp]
//Author Matsuda Towa
//
//=============================================
#include "blink_icon.h"
#include "manager.h"

//テクスチャパス
const std::string CBlinkIcon::TEXTURE_NAME = "data\\TEXTURE\\blink.png";

//=============================================
//コンストラクタ
//=============================================
CBlinkIcon::CBlinkIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlinkIcon::~CBlinkIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlinkIcon::Init()
{
	//初期化
	CObject2D::Init();

	//テクスチャ情報取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//テクスチャ登録
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//頂点生成
	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlinkIcon::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CBlinkIcon::Update()
{
	//更新
	CObject2D::Update();

	//頂点生成
	SetVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CBlinkIcon::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CBlinkIcon* CBlinkIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBlinkIcon* pBlinkIcon = new CBlinkIcon;

	if (pBlinkIcon == nullptr) { return nullptr; }

	pBlinkIcon->SetPos(pos);	//座標設定
	pBlinkIcon->SetSize(size);	//サイズ設定
	pBlinkIcon->SetColor(col);	//色設定

	//初期化処理
	pBlinkIcon->Init();

	return pBlinkIcon;
}
