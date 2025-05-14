//=============================================
//
//タイトル処理[title.cpp]
//Author Matsuda Towa
//
//=============================================
#include "title.h"
#include "title_screen.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include"player.h"
#include "field.h"
#include "manager.h"
#include "sound.h"

//ブロックのファイルパス
const std::string CTitle::BLOCK_FILE = "data\\FILE\\block.txt";

//床のサイズ
const D3DXVECTOR3 CTitle::LOGO_POS = { SCREEN_WIDTH * HALF,200.0f,0.0f };

//床のサイズ
const D3DXVECTOR3 CTitle::UI_POS = { SCREEN_WIDTH * HALF, 600.0f, 0.0f };

//床のサイズ
const D3DXVECTOR3 CTitle::FIELD_SIZE = { 1000.0f,0.0f,1000.0f };

//ロゴのサイズ
const D3DXVECTOR2 CTitle::LOGO_SIZE = { 400.0f,200.0f };

//UIのサイズ
const D3DXVECTOR2 CTitle::UI_SIZE = { 200.0f, 50.0f };

//スポーン位置
const D3DXVECTOR3 CTitle::PLAYER_SPAWN = { 0.0f, 0.5f, -300.0f }; 

//=============================================
//コンストラクタ
//=============================================
CTitle::CTitle()
{
}

//=============================================
//デストラクタ
//=============================================
CTitle::~CTitle()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTitle::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
    //地面生成
    CField::Create(VEC3_RESET_ZERO, FIELD_SIZE);

	//プレイヤー生成
	CPlayer::Create();

	//タイトルUI生成
    m_pTitleScreen[0] = CTitle_Screen::Create(LOGO_POS, LOGO_SIZE,CTitle_Screen::TITLE_UI::UI_TITLE_ROGO);

    m_pTitleScreen[1]=CTitle_Screen::Create(UI_POS, UI_SIZE, CTitle_Screen::TITLE_UI::UI_TITLE_PRESS_BUTTON);

    return S_OK;
}

//=============================================
//終了
//=============================================
void CTitle::Uninit()
{
	//サウンドを止める
	CManager::GetInstance()->GetSound()->StopSound();

	//オブジェクトを破棄
    CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CTitle::Update()
{
	//インプット取得
    CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
    CInputPad* pPad = CManager::GetInstance()->GetPad();
    CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

    if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A) || pMouse->GetTrigger(0))
    {
		//チュートリアルに遷移
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TUTORIAL);
    }
}

//=============================================
//描画
//=============================================
void CTitle::Draw()
{
}