//=============================================
//
//チュートリアル表示「tutorial_UI.cpp」
// Author松田永久
//
//=============================================
#include "tutorial_UI.h"
#include "manager.h"

//キーボードのUIの位置
const D3DXVECTOR3 CTutorial_UI::KEY_UI_POS = { 1050.0f,200.0f,0.0f };
//キーボードのUIのサイズ
const D3DXVECTOR2 CTutorial_UI::KEY_UI_SIZE = { 30.0f, 30.0f };

//リロードの操作説明の位置
const D3DXVECTOR3 CTutorial_UI::RELOAD_TXT_POS = { 1160.0f,200.0f,0.0f };
//リロードの操作説明サイズ
const D3DXVECTOR2 CTutorial_UI::RELOAD_TXT_SIZE = { 100.0f, 50.0f };

//射撃状態説明テキスト位置
const D3DXVECTOR3 CTutorial_UI::SHOT_MODE_TXT_POS = { 1170.0f,300.0f,0.0f };
//射撃状態説明テキストサイズ
const D3DXVECTOR2 CTutorial_UI::SHOT_MODE_TXT_SIZE = { 95.0f, 50.0f };

//発砲方法テキスト位置
const D3DXVECTOR3 CTutorial_UI::SHOT_TXT_POS = { 1170.0f,400.0f,0.0f };
//発砲方法テキストサイズ
const D3DXVECTOR2 CTutorial_UI::SHOT_TXT_SIZE = { 90.0f, 40.0f };

//マウスのUIの位置
const D3DXVECTOR3 CTutorial_UI::MOUSE_SHOT_MODE_UI_POS = { 1050.0f,300.0f,0.0f };
const D3DXVECTOR3 CTutorial_UI::MOUSE_SHOT_UI_POS = { 1050.0f,400.0f,0.0f };

//マウスのUIのサイズ
const D3DXVECTOR2 CTutorial_UI::MOUSE_UI_SIZE = { 30.0f, 30.0f };

//=============================================
//コンストラクタ
//=============================================
CTutorial_UI::CTutorial_UI():
m_pKeyboardReload_UI(),			//キーボードリロードのUI
m_pReloadUI(),					//リロードのUI
m_pMouseshot_UI(),				//マウスの発砲方法のUI
m_pMouseshotmode_UI(),			//マウスの発砲モード切り替え
m_pShotUI(),					//発砲UI
m_pShotModeUI()					//発砲モードUI
{
}

//=============================================
//デストラクタ
//=============================================
CTutorial_UI::~CTutorial_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTutorial_UI::Init()
{
	//UIの生成
	CreateUI();

	return S_OK;
}

//=============================================
//UI生成
//=============================================
void CTutorial_UI::CreateUI()
{
	if (m_pKeyboardReload_UI == nullptr)
	{
		m_pKeyboardReload_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, COLOR_WHITE, CKeyboard_UI::KEY_R);
	}

	if (m_pReloadUI == nullptr)
	{
		m_pReloadUI = CAction_UI::Create(RELOAD_TXT_POS, RELOAD_TXT_SIZE, COLOR_WHITE, CAction_UI::ACTION_RELOAD);
	}

	if (m_pShotModeUI == nullptr)
	{
		m_pShotModeUI = CAction_UI::Create(SHOT_MODE_TXT_POS, SHOT_MODE_TXT_SIZE, COLOR_WHITE, CAction_UI::ACTION_SHOTMODE);
	}

	if (m_pShotUI == nullptr)
	{
		m_pShotUI = CAction_UI::Create(SHOT_TXT_POS, SHOT_TXT_SIZE, COLOR_WHITE, CAction_UI::ACTION_SHOT);
	}

	if (m_pMouseshotmode_UI == nullptr)
	{
		m_pMouseshotmode_UI = CMouse_UI::Create(MOUSE_SHOT_MODE_UI_POS, MOUSE_UI_SIZE, COLOR_WHITE, CMouse_UI::MOUSE_L);
	}

	if (m_pMouseshot_UI == nullptr)
	{
		m_pMouseshot_UI = CMouse_UI::Create(MOUSE_SHOT_UI_POS, KEY_UI_SIZE, COLOR_WHITE, CMouse_UI::MOUSE_R);
	}
}

//=============================================
//終了
//=============================================
void CTutorial_UI::Uninit()
{
	//UIの破棄
	if (m_pKeyboardReload_UI != nullptr)
	{
		m_pKeyboardReload_UI->Uninit();
		m_pKeyboardReload_UI = nullptr;
	}

	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Uninit();
		m_pReloadUI = nullptr;
	}

	if (m_pShotModeUI != nullptr)
	{
		m_pShotModeUI->Uninit();
		m_pShotModeUI = nullptr;
	}

	if (m_pShotUI != nullptr)
	{
		m_pShotUI->Uninit();
		m_pShotUI = nullptr;
	}

	if (m_pMouseshotmode_UI != nullptr)
	{
		m_pMouseshotmode_UI->Uninit();
		m_pMouseshotmode_UI = nullptr;
	}

	if (m_pMouseshot_UI != nullptr)
	{
		m_pMouseshot_UI->Uninit();
		m_pMouseshot_UI = nullptr;
	}
	delete this;
}

//=============================================
//更新
//=============================================
void CTutorial_UI::Update()
{
	if (m_pKeyboardReload_UI != nullptr)
	{
		m_pKeyboardReload_UI->Update();
	}

	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Update();
	}

	if (m_pMouseshotmode_UI != nullptr)
	{
		m_pMouseshotmode_UI->Update();
	}

	if (m_pMouseshot_UI != nullptr)
	{
		m_pMouseshot_UI->Update();
	}
}
