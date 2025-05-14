//=============================================
//
//スモーク状況表示「smoke_UI_manager.cpp」
// Author松田永久
//
//=============================================
#include "smoke_UI_manager.h"

//UIの背景の位置
const D3DXVECTOR3 CSmoke_UI_Manager::BOX_POS = { 1150.0f, 565.0f, 0.0f };
//UIの背景のサイズ
const D3DXVECTOR2 CSmoke_UI_Manager::BOX_SIZE = { 50.0f, 50.0f };

//スモークのアイコンの位置
const D3DXVECTOR3 CSmoke_UI_Manager::ICON_POS = { 1150.0f,565.0f,0.0f };
//スモークのアイコンのサイズ
const D3DXVECTOR2 CSmoke_UI_Manager::ICON_SIZE = { 40.0f, 40.0f };

//数字の位置
const D3DXVECTOR3 CSmoke_UI_Manager::NUMBER_POS = { 1000.0f, 565.0f, 0.0f };
//数字のサイズ
const D3DXVECTOR2 CSmoke_UI_Manager::NUMBER_SIZE = { 20.0f, 30.0f };

//キーボードのUIの位置
const D3DXVECTOR3 CSmoke_UI_Manager::KEY_UI_POS = { 1150.0f,600.0f,0.0f };
//キーボードのUIのサイズ
const D3DXVECTOR2 CSmoke_UI_Manager::KEY_UI_SIZE = { 18.0f, 18.0f };

//=============================================
//コンストラクタ
//=============================================
CSmoke_UI_Manager::CSmoke_UI_Manager():
m_SmokePos(VEC3_RESET_ZERO),	//スモークの位置初期化
m_NumSmoke(INT_ZERO),			//スモークの数初期化
m_pCurrentSmoke(),				//現在のスモークの数のポインタ初期化
m_pUIBox(),						//UIの枠初期化
m_pIcon(),						//アイコンの初期化
m_pkeyboard_UI()				//キーボードの初期化
{
}

//=============================================
//デストラクタ
//=============================================
CSmoke_UI_Manager::~CSmoke_UI_Manager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmoke_UI_Manager::Init(CPlayer* player)
{
	m_SmokePos = NUMBER_POS;

	//UIの枠生成
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, COLOR_WHITE, CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//UIの枠生成
	if (m_pIcon == nullptr)
	{
		m_pIcon = CSmokeIcon::Create(ICON_POS, ICON_SIZE, COLOR_WHITE);
	}

	//キーボードUIの枠生成
	if (m_pkeyboard_UI == nullptr)
	{
		m_pkeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, COLOR_WHITE, CKeyboard_UI::KEY_Q);
	}

	//数字生成
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentSmoke[nCnt] == nullptr)
		{
			m_pCurrentSmoke[nCnt] = CNumber_2D::Create(m_SmokePos, NUMBER_SIZE);
			//座標をずらす
			m_SmokePos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmoke_UI_Manager::Uninit()
{
	//UIの枠破棄
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	//キーボードUIのアイコン破棄
	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	//UIのアイコン破棄
	if (m_pkeyboard_UI != nullptr)
	{
		m_pkeyboard_UI->Uninit();
		m_pkeyboard_UI = nullptr;
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//数字破棄
		if (m_pCurrentSmoke[nCnt] != nullptr)
		{
			m_pCurrentSmoke[nCnt]->Uninit();
			m_pCurrentSmoke[nCnt] = nullptr;
		}
	}

	delete this;
}

//=============================================
//更新
//=============================================
void CSmoke_UI_Manager::Update()
{
}

//=============================================
//現在のUIの設定
//=============================================
void CSmoke_UI_Manager::SetCurrentSmoke_UI(CPlayer* player)
{
	if (player->GetSmoke())
	{//スモークを使っていたら
		m_pIcon->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	}
	else if (!player->GetSmoke())
	{//スモークを使っていなかったら
		m_pIcon->SetColor(COLOR_WHITE);
	}
}

//=============================================
//数字設定
//=============================================
void CSmoke_UI_Manager::SetNumber(int nParcent)
{
}

//=============================================
//初期状態に
//=============================================
void CSmoke_UI_Manager::Reset()
{
}
