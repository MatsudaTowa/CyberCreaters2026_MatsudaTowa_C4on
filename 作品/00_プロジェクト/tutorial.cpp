//=============================================
//
//チュートリアル処理[tutorial.cpp]
//Author Matsuda Towa
//
//=============================================
#include "tutorial.h"
#include "tutorial_screen.h"
#include "player.h"

//エネミーファイル
const std::string CTutorial::ENEMY_FILE = "data\\FILE\\enemy_001.txt";
//ブロックファイル
const std::string CTutorial::BLOCK_FILE = "data\\FILE\\block_data_tutorial.bin";
//壁ファイル
const std::string CTutorial::WALL_FILE = "data\\FILE\\wall_002.txt";

//床のサイズ
const D3DXVECTOR3 CTutorial::FIELD_SIZE = { 500.0f, 0.0f, 1000.0f };

//UIの位置
const D3DXVECTOR3 CTutorial::UI_POS = { SCREEN_WIDTH * HALF, 50.0f, 0.0f };

//UIのサイズ
const D3DXVECTOR2 CTutorial::UI_SIZE = { 200.0f, 100.0f };

//=============================================
//コンストラクタ
//=============================================
CTutorial::CTutorial():m_pTutorial_UI()
{
}

//=============================================
//デストラクタ
//=============================================
CTutorial::~CTutorial()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTutorial::Init()
{
	//初期化
	CScene::Init();

	//プレイヤー生成
	CPlayer::Create();

	//ブロック読み込み
	LoadBlock(BLOCK_FILE);
	//敵の読み込み
	LoadEnemy(&ENEMY_FILE);
	//壁の読み込み
	LoadWall(&WALL_FILE);

	//地面生成
	CField::Create(VEC3_RESET_ZERO, FIELD_SIZE);

	//チュートリアルの画像生成
	CTutorial_Screen::Create(UI_POS, UI_SIZE, CTutorial_Screen::TUTORIAL_UI::UI_TUTORIAL_TXT);

	if (m_pTutorial_UI == nullptr)
	{
		m_pTutorial_UI = new CTutorial_UI;
		m_pTutorial_UI->Init();
	}

	return S_OK;
}

//=============================================
//終了
//=============================================
void CTutorial::Uninit()
{
	if (m_pTutorial_UI != nullptr)
	{
		m_pTutorial_UI->Uninit();
		m_pTutorial_UI = nullptr;
	}
	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CTutorial::Update()
{
	if (m_pTutorial_UI != nullptr)
	{
		m_pTutorial_UI->Update();
	}

	if (CEnemy::m_NumEnemy <= INT_ZERO)
	{//敵がいなくなったら再スポーン
		LoadEnemy(&ENEMY_FILE);
	}

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetPad();
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_GAME);
	}
}

//=============================================
//描画
//=============================================
void CTutorial::Draw()
{
}

//=============================================
//ブロック読み込み
//=============================================
void CTutorial::LoadBlock(const std::string& pFileName)
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
//壁読み込み
//=============================================
void CTutorial::LoadWall(const std::string* pFileName)
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
					CWall::Create(m_LoadWall.pos, m_LoadWall.rot, m_LoadWall.size);
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
//敵読み込み
//=============================================
void CTutorial::LoadEnemy(const std::string* pFileName)
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
