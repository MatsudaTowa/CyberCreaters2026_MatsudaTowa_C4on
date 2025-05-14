//=============================================
//
//ウェーブ処理[wave.h]
//Author Matsuda Towa
//
//=============================================
#include "wave.h"
#include "manager.h"
#include "wave_one.h"
#include "wave_two.h"
#include "wave_three.h"
#include "wave_boss.h"
#include "wave_result.h"
#include "game_score.h"
#include "wave_score.h"
#include"player.h"
#include "wall.h"
#include "move_point.h"
#include "mask.h"
#include "gauge.h"

//通常の床のサイズ
const D3DXVECTOR3 CWave::NORMAL_FIELD_SIZE = { 500.0f, 0.0f, 1000.0f };

//boss戦の床のサイズ
const D3DXVECTOR3 CWave::BOSS_FIELD_SIZE = { 900.0f, 0.0f, 900.0f };

//現在のウェーブ
CWave::WAVE CWave::m_CurrentWave = WAVE::NONE;
//次のウェーブ
CWave::WAVE CWave::m_next = WAVE::NONE;
//リザルトのファイル
const char* CWave::m_ResultFile = nullptr;
//スコア
CScore* CWave::m_pScore = nullptr;

//=============================================
//コンストラクタ
//=============================================
CWave::CWave()
{
}

//=============================================
//デストラクタ
//=============================================
CWave::~CWave()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave::Init()
{
	CMask::Create();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave::Uninit()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CWave::Update()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}
}

//=============================================
//ウェーブ設定
//=============================================
CWave* CWave::Create(WAVE wave)
{
	// インスタンス生成
	CWave* pWave = new CWave;

	// 条件分岐
	switch (wave)
	{
	case WAVE::ONE: // ウェーブ1
		delete pWave;
		pWave = new CWave_One;
		break;

	case WAVE::TWO: //ウェーブ2
		delete pWave;
		pWave = new CWave_Two;
		break;

	case WAVE::THREE: // ウェーブ3

		delete pWave;
		pWave = new CWave_Three;
		break;
	case WAVE::BOSS: //ウェーブboss

		delete pWave;
		pWave = new CWave_Boss;
		break;
	case WAVE::RESULT: //ウェーブリザルト

		delete pWave;
		pWave = new CWave_Result;
		break;
	default:
		break;
	}

	//スコア初期化
	if (m_pScore == nullptr)
	{
		if (wave != WAVE::RESULT)
		{
			m_pScore = new CGameScore;
			//プレイヤー生成
			CPlayer::Create();
		}
		else if (wave == WAVE::RESULT)
		{
			m_pScore = new CWaveScore;
		}
		m_pScore->Init();
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//今のシーンの初期化
	pWave->Init();

	return pWave;
}

//=============================================
//ウェーブ設定
//=============================================
CWave* CWave::Create(WAVE wave, WAVE next_wave,const char* ResultFile)
{
	// インスタンス生成
	CWave* pWave = nullptr;

	m_next = next_wave;

	m_ResultFile = ResultFile;

	// 条件分岐
	switch (wave)
	{
	case WAVE::RESULT: //ウェーブリザルト

		delete pWave;
		pWave = new CWave_Result;
		break;
	default:
		break;
	}

	//スコア初期化
	if (m_pScore == nullptr)
	{
		if (wave != WAVE::RESULT)
		{
			m_pScore = new CGameScore;
			//プレイヤー生成
			CPlayer::Create();
		}
		else if (wave == WAVE::RESULT)
		{
			m_pScore = new CWaveScore;
		}
		m_pScore->Init();
	}

	if (pWave != nullptr)
	{
		pWave->m_CurrentWave = wave;
	}
	//今のシーンの初期化
	pWave->Init();

	return pWave;
}

//=============================================
//現在のウェーブを取得
//=============================================
CWave::WAVE CWave::GetCurrentWave()
{
	return m_CurrentWave;
}

//=============================================
//スコア取得
//=============================================
CScore* CWave::GetScore()
{
	return m_pScore;
}

//=============================================
//ブロックをロード
//=============================================
void CWave::LoadBlock(const std::string& pFileName)
{
	//ファイルの読み込み
	std::ifstream File(pFileName, std::ios::binary);

	//ファイルが開かなかったら関数を抜ける
	if (!File.is_open())
	{
		return;
	}

	//生成するブロック数読み込み用
	int NumBlock = 0;

	File.read(reinterpret_cast<char*>(&NumBlock), sizeof(int));

	if (NumBlock > 0)
	{
		//生成するブロックの情報を持つ変数
		std::vector<LOAD_BLOCK> info(NumBlock);

		//ファイルから読み込んだデータを格納
		File.read(reinterpret_cast<char*>(info.data()), sizeof(LOAD_BLOCK) * NumBlock);

		//イテレータで回して生成
		for (auto& itr : info)
		{
			CBlock::Create(itr.type, itr.pos, itr.rot);
		}
	}

	File.close();
}

//=============================================
//壁をロード
//=============================================
void CWave::LoadWall(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
	int nNumWall; //壁の数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_WALL"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumWall);
		}
		if (!strcmp(aDataSearch, "WALLSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_WALLSET"))
				{
					//ブロック生成
					CWall::Create(m_LoadWall.pos, m_LoadWall.rot,m_LoadWall.size);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.pos.x,
						&m_LoadWall.pos.y,
						&m_LoadWall.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.rot.x,
						&m_LoadWall.rot.y,
						&m_LoadWall.rot.z);
				}
				else if (!strcmp(aDataSearch, "SIZE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadWall.size.x,
						&m_LoadWall.size.y,
						&m_LoadWall.size.z);
				}
			}
		}
	}
}

//=============================================
//エネミーをロード
//=============================================
void CWave::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[TXT_MAX];
	char aEqual[TXT_MAX]; //[＝]読み込み用
	int nNumEnemy; //エネミーの数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//エネミー生成
					CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}


