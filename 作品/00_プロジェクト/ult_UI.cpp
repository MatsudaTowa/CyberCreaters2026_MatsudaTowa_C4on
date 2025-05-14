//=============================================
//
//ult状況表示「ult_UI.cpp」
// Author松田永久
//
//=============================================
#include "ult_UI.h"
#include "ult.h"

//アイコンの位置
const D3DXVECTOR3 CUlt_UI::ICON_POS = { SCREEN_WIDTH * 0.5f,660.0f,0.0f };
//アイコンのサイズ
const D3DXVECTOR2 CUlt_UI::ICON_SIZE = { 70.0f, 70.0f };

//キーボードのUI位置
const D3DXVECTOR3 CUlt_UI::KEY_UI_POS = { SCREEN_WIDTH * 0.5f,700.0f,0.0f};
//キーボードのサイズ
const D3DXVECTOR2 CUlt_UI::KEY_UI_SIZE = { 18.0f, 18.0f };

//=============================================
// コンストラクタ
//=============================================
CUlt_UI::CUlt_UI():
m_PercentPos(VEC3_RESET_ZERO),	//パーセントの位置
m_pKeyboard_UI(),				//キーボードのUI
m_pIcon()						//アイコン
{
}

//=============================================
// デストラクタ
//=============================================
CUlt_UI::~CUlt_UI()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CUlt_UI::Init(CPlayer* player)
{
	//UIの枠生成
	if (m_pIcon == nullptr)
	{
		float Addcolor = (FLOAT_ONE - CUltIcon::START_COLOR.r) / player->m_pUlt->GetCoolTime();

		m_pIcon = CUltIcon::Create(ICON_POS, ICON_SIZE, Addcolor, CUltIcon::ULT_TYPE::ULT_TYPE_MEDIUM);
	}

	if (m_pKeyboard_UI == nullptr)
	{
		m_pKeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, COLOR_WHITE ,CKeyboard_UI::KEY_X);
	}
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CUlt_UI::Uninit()
{
	if (m_pKeyboard_UI != nullptr)
	{
		m_pKeyboard_UI->Uninit();
		m_pKeyboard_UI = nullptr;
	}

	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	delete this;
}

//=============================================
// 更新
//=============================================
void CUlt_UI::Update()
{
	if (m_pKeyboard_UI != nullptr)
	{
		m_pKeyboard_UI->Update();
	}

	if (m_pIcon != nullptr)
	{
		m_pIcon->Update();
	}
}

//=============================================
// UI設定
//=============================================
void CUlt_UI::SetCurrentUlt_UI(CPlayer* player)
{
	//割合を出すためにfloatにキャスト
	int Parcent = ((float)player->m_pUlt->GetCoolTimeCnt() / (float)player->m_pUlt->GetCoolTime()) * 100;
}

//=============================================
// リセット関数(ultが使われたときに呼ばれる)
//=============================================
void CUlt_UI::Reset()
{
	//各クラスのリセット関数を呼ぶだけ
	//アイコンのリセット処理
	m_pIcon->Reset();
}
