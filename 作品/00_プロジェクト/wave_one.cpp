//=============================================
//
//1ウェーブ処理[wave_one.cpp]
//Author Matsuda Towa
//
//=============================================
#include "wave_one.h"
#include "dash_effect.h"
#include "ult_effect.h"

//エネミーファイル
const std::string CWave_One::WAVE_1_ENEMY_FILE = "data\\FILE\\enemy_000.txt";
//ブロックファイル
const std::string CWave_One::WAVE_1_BLOCK_FILE = "data\\FILE\\block_data000.bin";
//壁ファイル
const std::string CWave_One::WAVE_1_WALL_FILE = "data\\FILE\\wall_000.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_One::CWave_One()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_One::~CWave_One()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_One::Init()
{
	//初期化
	CWave::Init();
	//ブロック読み込み
	CWave::LoadBlock(WAVE_1_BLOCK_FILE);
	//敵読み込み
	CWave::LoadEnemy(&WAVE_1_ENEMY_FILE);
	//壁読み込み
	CWave::LoadWall(&WAVE_1_WALL_FILE);
	//地面生成
	CField::Create(VEC3_RESET_ZERO, CWave::NORMAL_FIELD_SIZE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_One::Uninit()
{
	//終了
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_One::Update()
{
	//更新
	CWave::Update();
}
