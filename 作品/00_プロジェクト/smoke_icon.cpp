//=============================================
//
//スモークの表記[smoke_icon.h]
//Author Matsuda Towa
//
//=============================================
#include "smoke_icon.h"
#include "manager.h"

//テクスチャパス
const std::string CSmokeIcon::TEXTURE_NAME = "data\\TEXTURE\\smoke_UI.png";

//=============================================
//コンストラクタ
//=============================================
CSmokeIcon::CSmokeIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CSmokeIcon::~CSmokeIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmokeIcon::Init()
{
	//初期化
	CObject2D::Init();

	//テクスチャ登録
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmokeIcon::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CSmokeIcon::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CSmokeIcon::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CSmokeIcon* CSmokeIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CSmokeIcon* pSmokeIcon = new CSmokeIcon;

	if (pSmokeIcon == nullptr) { return nullptr; }

	pSmokeIcon->SetPos(pos);	//位置設定
	pSmokeIcon->SetSize(size);	//サイズ設定
	pSmokeIcon->SetColor(col);	//カラー設定

	pSmokeIcon->Init();	//初期化設定

	return pSmokeIcon;
}
