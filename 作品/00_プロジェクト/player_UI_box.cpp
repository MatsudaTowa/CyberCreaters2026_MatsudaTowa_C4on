//=============================================
//
//プレイヤーのUIの枠[player_UI_box.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_UI_box.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CPlayerUIBox::CPlayerUIBox(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerUIBox::~CPlayerUIBox()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayerUIBox::Init()
{
	//親クラスの初期化
	CObject2D::Init();

	SetVtx(FLOAT_ONE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayerUIBox::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayerUIBox::Update()
{
	//親クラスの更新
	CObject2D::Update();

	SetVtx(FLOAT_ONE);

}

//=============================================
//描画
//=============================================
void CPlayerUIBox::Draw()
{
	//親クラスの描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CPlayerUIBox* CPlayerUIBox::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, BOX_TYPE type)
{
	CPlayerUIBox*pUIBox = nullptr;

	switch (type)
	{
	case CPlayerUIBox::BOX_TYPE_LIFE:
		pUIBox = new CLifeUIBox;
		break;
	case CPlayerUIBox::BOX_TYPE_AMMO:
		pUIBox = new CAmmoUIBox;
		break;
	case CPlayerUIBox::BOX_TYPE_SCORE:
		pUIBox = new CScoreUIBox;
		break;
	default:
		break;
	}
	
	if(pUIBox == nullptr) {return nullptr;}

	//座標代入
	pUIBox->SetPos(pos);

	//サイズ代入
	pUIBox->SetSize(size);

	//色代入
	pUIBox->SetColor(col);

	pUIBox->SetType(OBJECT_TYPE_UI_BOX);

	pUIBox->Init();

	return pUIBox;
}

//texパス
const std::string CLifeUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box_000.png";

//=============================================
//コンストラクタ
//=============================================
CLifeUIBox::CLifeUIBox(int nPriority):CPlayerUIBox(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CLifeUIBox::~CLifeUIBox()
{
}

//=============================================
//初期化
//=============================================
HRESULT CLifeUIBox::Init()
{
	//テクスチャ代入
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	//初期化
	CPlayerUIBox::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CLifeUIBox::Uninit()
{
	//終了
	CPlayerUIBox::Uninit();
}

//=============================================
//更新
//=============================================
void CLifeUIBox::Update()
{
	//更新
	CPlayerUIBox::Update();
}

//=============================================
//描画
//=============================================
void CLifeUIBox::Draw()
{
	//描画
	CPlayerUIBox::Draw();
}


//texパス
const std::string CAmmoUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box_001.png";

//=============================================
//コンストラクタ
//=============================================
CAmmoUIBox::CAmmoUIBox(int nPriority) :CPlayerUIBox(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CAmmoUIBox::~CAmmoUIBox()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAmmoUIBox::Init()
{
	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	//初期化
	CPlayerUIBox::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CAmmoUIBox::Uninit()
{
	//終了
	CPlayerUIBox::Uninit();
}

//=============================================
//更新
//=============================================
void CAmmoUIBox::Update()
{
	//更新
	CPlayerUIBox::Update();
}

//=============================================
//描画
//=============================================
void CAmmoUIBox::Draw()
{
	//描画
	CPlayerUIBox::Draw();
}

//texパス
const std::string CScoreUIBox::TEXTURE_NAME = "data\\TEXTURE\\UI_box_002.png";

//=============================================
//コンストラクタ
//=============================================
CScoreUIBox::CScoreUIBox(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CScoreUIBox::~CScoreUIBox()
{
}

//=============================================
//初期化
//=============================================
HRESULT CScoreUIBox::Init()
{
	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	
	//初期化
	CPlayerUIBox::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CScoreUIBox::Uninit()
{
	//終了
	CPlayerUIBox::Uninit();
}

//=============================================
//更新
//=============================================
void CScoreUIBox::Update()
{
	//更新
	CPlayerUIBox::Update();
}

//=============================================
//描画
//=============================================
void CScoreUIBox::Draw()
{
	//描画
	CPlayerUIBox::Draw();
}
