//=============================================
//
//死亡アイコン[death_icon.cpp]
//Author Matsuda Towa
//
//=============================================
#include "death_icon.h"
#include "manager.h"

//テクスチャパス
const std::string CDeathIcon::TEXTURE_NAME = "data\\TEXTURE\\death_icon.png";

//=============================================
//コンストラクタ
//=============================================
CDeathIcon::CDeathIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CDeathIcon::~CDeathIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CDeathIcon::Init()
{
	//初期化
	CObject2D::Init();

	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CDeathIcon::Uninit()
{
	//終了
	CObject2D::Uninit();
}


//=============================================
//更新
//=============================================
void CDeathIcon::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CDeathIcon::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CDeathIcon* CDeathIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CDeathIcon* pDeathIcon = new CDeathIcon;

	if (pDeathIcon == nullptr) { return nullptr; }

	pDeathIcon->SetPos(pos);	//座標代入
	pDeathIcon->SetSize(size);	//サイズ設定
	pDeathIcon->SetColor(col);	//色設定

	pDeathIcon->Init();	//初期化

	return pDeathIcon;
}
