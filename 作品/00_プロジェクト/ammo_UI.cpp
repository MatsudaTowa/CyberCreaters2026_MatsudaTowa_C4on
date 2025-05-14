//=============================================
//
//残弾数表示「ammo_UI.cpp」
// Author松田永久
//
//=============================================
#include "ammo_UI.h"
#include "manager.h"

//UIの背景の位置
const D3DXVECTOR3 CAmmo_UI::BOX_POS = { 1070.0f, 665.0f, 0.0f };
//UIの背景のサイズ
const D3DXVECTOR2 CAmmo_UI::BOX_SIZE = { 180.0f, 50.0f };

//弾数の表示位置
const D3DXVECTOR3 CAmmo_UI::CURRENT_AMMO_POS = { 1000.0f, 665.0f, 0.0f };
//弾数の表示サイズ
const D3DXVECTOR2 CAmmo_UI::CURRENT_AMMO_SIZE = { 20.0f, 30.0f };

//マガジンサイズの位置
const D3DXVECTOR3 CAmmo_UI::DEFAULT_AMMO_POS = { 1065.0f, 670.0f, 0.0f };
//マガジンサイズのサイズ
const D3DXVECTOR2 CAmmo_UI::DEFAULT_AMMO_SIZE = { 10.0f, 20.0f };

//=============================================
//コンストラクタ
//=============================================
CAmmo_UI::CAmmo_UI():
m_nDefaultAmmo(FLOAT_ZERO),			//通常の弾数
m_CurrentAmmoPos(VEC3_RESET_ZERO),	//現在の弾数表示位置
m_DefaultAmmoPos(VEC3_RESET_ZERO),	//一マガジンごとの弾数表示位置
m_pCurrentAmmo(),					//現在の弾数の数字ポインタ
m_pDefaultAmmo(),					//一マガジンごとの弾数の数字ポインタ
m_pUIBox()							//UIの背景ポインタ
{
}

//=============================================
//デストラクタ
//=============================================
CAmmo_UI::~CAmmo_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAmmo_UI::Init()
{
	//初期位置代入
	m_CurrentAmmoPos = CURRENT_AMMO_POS;
	m_DefaultAmmoPos = DEFAULT_AMMO_POS;

	//UIの枠生成
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, COLOR_WHITE,CPlayerUIBox::BOX_TYPE::BOX_TYPE_AMMO);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentAmmo[nCnt] == nullptr)
		{
			m_pCurrentAmmo[nCnt] = CNumber_2D::Create(m_CurrentAmmoPos, CURRENT_AMMO_SIZE);
			//座標をずらす
			m_CurrentAmmoPos.x -= CURRENT_AMMO_DIGIT_SHIFT;
		}

		if (m_pDefaultAmmo[nCnt] == nullptr)
		{
			m_pDefaultAmmo[nCnt] = CNumber_2D::Create(m_DefaultAmmoPos, DEFAULT_AMMO_SIZE);
			//座標をずらす
			m_DefaultAmmoPos.x -= DEFAULT_AMMO_DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CAmmo_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//現在の弾数の数字ポインタ破棄
		if (m_pCurrentAmmo[nCnt] != nullptr)
		{
			m_pCurrentAmmo[nCnt]->Uninit();
			m_pCurrentAmmo[nCnt] = nullptr;
		}

		//一マガジンごとの弾数の数字ポインタ破棄
		if (m_pDefaultAmmo[nCnt] != nullptr)
		{
			m_pDefaultAmmo[nCnt]->Uninit();
			m_pDefaultAmmo[nCnt] = nullptr;
		}
	}

	//UIの背景ポインタ破棄
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	delete this;
}

//=============================================
//更新
//=============================================
void CAmmo_UI::Update()
{
}

//=============================================
//UIに設定
//=============================================
void CAmmo_UI::SetCurrentAmmo_UI(int nAmmo)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nAmmo / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		if (nAmmo < m_nDefaultAmmo * 0.3f)
		{//弾数少なくなったら赤色に
			m_pCurrentAmmo[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(COLOR_RED));
		}
		else
		{
			m_pCurrentAmmo[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(COLOR_WHITE));
		}
	}
}

//=============================================
//UIに設定
//=============================================
void CAmmo_UI::SetDefaultAmmo_UI(int nAmmo)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//デフォルト弾数代入
	m_nDefaultAmmo = nAmmo;

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nAmmo / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pDefaultAmmo[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
