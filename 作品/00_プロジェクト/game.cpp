//=============================================
//
//ゲーム[game.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"
#include "dash_effect.h"
#include "player.h"

//プレイヤー
CPlayer*CGame::m_pPlayer = nullptr;

//ウェーブ
CWave*CGame::m_pWave = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//コンストラクタ
//=============================================
CGame::CGame():
m_nResultDelay(INT_ZERO),	//リザルトの遷移ディレイ
m_next_wave()				//次のウェーブ格納変数
{
	//読み込むブロックの情報初期化
	m_LoadBlock.pos = VEC3_RESET_ZERO;
	m_LoadBlock.rot = VEC3_RESET_ZERO;
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	if (m_pWave == nullptr)
	{
		m_pWave = new CWave;
		m_pWave->Init();
	}

	//プレイヤー生成
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	CManager::GetInstance()->GetSound()->StopSound();
	m_GameState = GAME_STATE_NORMAL;

	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		m_pWave = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	if (CEnemy::m_NumEnemy <= INT_ZERO)
	{//敵がいなくなったらウェーブ遷移
		switch (CWave::GetCurrentWave())
		{
		case CWave::WAVE::ONE:
			m_next_wave = CWave::WAVE::TWO;
			break;
		case CWave::WAVE::TWO:
			m_next_wave = CWave::WAVE::THREE;
			break;
		case CWave::WAVE::THREE:
			m_next_wave = CWave::WAVE::BOSS;
			break;
		case CWave::WAVE::BOSS:
			m_next_wave = CWave::WAVE::NONE;
			break;
		case CWave::WAVE::NONE:
			break;
		default:
			break;
		}

		if (CWave::GetCurrentWave() != CWave::WAVE::RESULT)
		{
			m_nResultDelay++;
			if (m_nResultDelay > DELAY_FLAME)
			{
				m_nResultDelay = INT_ZERO;

				//死んだ数分だけスコアマイナス
				ApplyDeathPenalty();

				//現在のスコアを書き出し
				m_pWave->WaveResult(CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1]);
				SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
			}
		}
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Update();
	}
	
#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_TAB))
	{
		m_next_wave = CWave::WAVE::BOSS;

		SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
	}

	if (pKeyboard->GetTrigger(DIK_F7))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TEST);
	}
#endif // _DEBUG
}

//=============================================
//死んだ数だけスコアマイナス
//=============================================
void CGame::ApplyDeathPenalty()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();
			
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなかったら
			//プレイヤーを探し続ける
			continue;
		}

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		for (int nCnt = 0; nCnt < pPlayer->GetDeathCnt(); nCnt++)
		{
			CScore* pScore = CWave::GetScore();

			if (pScore->m_nScore > INT_ZERO)
			{
				pScore->AddScore(DEATH_PENALTY);

				if (pScore->m_nScore <= INT_ZERO)
				{//0を下回ったら
					//スコア0に
					pScore->m_nScore = INT_ZERO;
				}
			}
		}
	}
}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//プレイヤー取得
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//=============================================
//ウェーブ取得
//=============================================
CWave* CGame::GetWave()
{
	return m_pWave;
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave);
	}
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave, CWave::WAVE next_wave,const char* ResultFile)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave, next_wave, ResultFile);
	}
}

//=============================================
//ゲームの状態取得
//=============================================
CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}