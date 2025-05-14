//=============================================
//
//2ウェーブ処理[wave_two.cpp]
//Author Matsuda Towa
//
//=============================================
#include "wave_two.h"

//敵のファイル
const std::string CWave_Two::WAVE_2_ENEMY_FILE = "data\\FILE\\enemy_001.txt";
//ブロックファイル
const std::string CWave_Two::WAVE_2_BLOCK_FILE = "data\\FILE\\block_data000.bin";
//壁ファイル
const std::string CWave_Two::WAVE_2_WALL_FILE = "data\\FILE\\wall_001.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_Two::CWave_Two()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Two::~CWave_Two()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Two::Init()
{
	//初期化処理
	CWave::Init();

	//壁読み込み
	CWave::LoadBlock(WAVE_2_BLOCK_FILE);
	//敵読み込み
	CWave::LoadEnemy(&WAVE_2_ENEMY_FILE);
	//壁読み込み
	CWave::LoadWall(&WAVE_2_WALL_FILE);
	//地面生成
	CField::Create(VEC3_RESET_ZERO, NORMAL_FIELD_SIZE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Two::Uninit()
{
	//終了
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Two::Update()
{
	//更新
	CWave::Update();
}
