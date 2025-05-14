//=============================================
//
//ウェーブごとの結果[wave_result.cpp]
//Author Matsuda Towa
//
//=============================================
#include "wave_result.h"
#include "manager.h"
#include "game.h"

//=============================================
//コンストラクタ
//=============================================
CWave_Result::CWave_Result():
m_pScreen(),	//スクリーン
m_nScore()		//スコア
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Result::~CWave_Result()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Result::Init()
{
	m_pScreen = nullptr;

	if (m_pScreen == nullptr)
	{
		m_pScreen = CWave_Result_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * HALF, SCREEN_HEIGHT * HALF, 0.0f));
	}

	LoadScore(m_ResultFile);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Result::Uninit()
{
	if (m_pScreen != nullptr)
	{
		m_pScreen->Uninit();
		m_pScreen = nullptr;
	}
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Result::Update()
{
	if (m_pScreen != nullptr)
	{
		m_pScreen->Update();
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetInstance()->GetMouse()->GetTrigger(0))
	{
		if (m_next != WAVE::NONE)
		{
			CGame::SetWave(m_next);
		}
		else
		{
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
		}
	}
	CWave::Update();
}

//=============================================
//次のウェーブ設定
//=============================================
void CWave_Result::SetNextWave(CWave::WAVE wave)
{
	m_next = wave;
}

//=============================================
//スコアロード
//=============================================
void CWave_Result::LoadScore(const std::string& pFileName)
{
	//ファイルの読み込み
	std::ifstream File(pFileName, std::ios::binary);

	//ファイルが開かなかったら関数を抜ける
	if (!File.is_open())
	{
		return;
	}

	File.read(reinterpret_cast<char*>(&m_nScore), sizeof(int));

	m_pScore->AddScore(m_nScore);
}
