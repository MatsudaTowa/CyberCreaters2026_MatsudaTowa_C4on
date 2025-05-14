//=============================================
//
//ブリンクの数字の背景[blink_back_UI.cpp]
//Author Matsuda Towa
//
//=============================================
#include "blink_back_UI.h"
#include "manager.h"

//テクスチャパス
const std::string CBlinkBackUI::TEXTURE_NAME = "data\\TEXTURE\\blink_back.png";

//=============================================
//コンストラクタ
//=============================================
CBlinkBackUI::CBlinkBackUI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlinkBackUI::~CBlinkBackUI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlinkBackUI::Init()
{
	//親クラスの初期化
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
void CBlinkBackUI::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CBlinkBackUI::Update()
{
	//親クラスの更新
	CObject2D::Update();

	//頂点生成
	SetVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CBlinkBackUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CBlinkBackUI* CBlinkBackUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBlinkBackUI* pBlinkBackUI = new CBlinkBackUI;

	if (pBlinkBackUI == nullptr) { return nullptr; }

	pBlinkBackUI->SetPos(pos);		//位置設定
	pBlinkBackUI->SetSize(size);	//サイズ設定
	pBlinkBackUI->SetColor(col);	//カラー設定

	//初期化
	pBlinkBackUI->Init();

	return pBlinkBackUI;
}
