//=============================================
//
//チュートリアルスクリーン[tutorial_screen.cpp]
//Author Matsuda Towa
//
//=============================================
#include "tutorial_screen.h"
#include "manager.h"

//texパス
const std::string CTutorial_Screen::TXT_TEXTURE_NAME = "data\\TEXTURE\\tutorial.png";
const std::string CTutorial_Screen::BUTTON_A_TEXTURE_NAME = "data\\TEXTURE\\press_enter.png";
const std::string CTutorial_Screen::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\press_enter.png";

//=============================================
//コンストラクタ
//=============================================
CTutorial_Screen::CTutorial_Screen(int nPriority) :CObject2D(nPriority), 
m_UItype(CTutorial_Screen::TUTORIAL_UI::UI_NONE)		//UIのタイプ設定
{
}

//=============================================
//デストラクタ
//=============================================
CTutorial_Screen::~CTutorial_Screen()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTutorial_Screen::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(VEC2_RESET_ONE);

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = COLOR_WHITE;

	//カラーを代入
	SetColor(col);

	//頂点設定
	SetVtx(FLOAT_ONE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTutorial_Screen::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CTutorial_Screen::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	CInputPad* pPad = CManager::GetInstance()->GetPad();

	switch (m_UItype)
	{
	case CTutorial_Screen::TUTORIAL_UI::UI_TUTORIAL_TXT:
		BindTexture(pTexture->GetAddress(pTexture->Regist(&TXT_TEXTURE_NAME)));
		break;
	case CTutorial_Screen::TUTORIAL_UI::UI_TITLE_PRESS_BUTTON:
		if (pPad->GetConnet())
		{//pad接続中
			BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_A_TEXTURE_NAME)));
		}
		else if (!pPad->GetConnet())
		{//pad接続してない
			BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
		}
		break;
	default:
		break;
	}
}

//=============================================
//描画
//=============================================
void CTutorial_Screen::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CTutorial_Screen* CTutorial_Screen::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TUTORIAL_UI type)
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	CTutorial_Screen* pTutorialScreen = new CTutorial_Screen;

	//nullならnullを返す
	if (pTutorialScreen == nullptr) { return nullptr; }

	pTutorialScreen->SetPos(pos); //pos設定

	pTutorialScreen->SetSize(size); //size設定

	pTutorialScreen->m_UItype = type;	//タイプ代入

	CInputPad* pPad = CManager::GetInstance()->GetPad();

	switch (pTutorialScreen->m_UItype)
	{
	case CTutorial_Screen::TUTORIAL_UI::UI_TUTORIAL_TXT:
		pTutorialScreen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TXT_TEXTURE_NAME)));
		break;
	case CTutorial_Screen::TUTORIAL_UI::UI_TITLE_PRESS_BUTTON:
		if (pPad->GetConnet())
		{
			pTutorialScreen->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_A_TEXTURE_NAME)));
		}
		else if (!pPad->GetConnet())
		{
			pTutorialScreen->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
		}
		break;
	default:
		break;
	}

	pTutorialScreen->SetType(OBJECT_TYPE_TITLE); //オブジェクトタイプ設定

	pTutorialScreen->Init();	//初期化

	return pTutorialScreen;
}
