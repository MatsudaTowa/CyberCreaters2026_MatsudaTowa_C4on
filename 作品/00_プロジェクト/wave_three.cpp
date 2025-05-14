//=============================================
//
//3ウェーブ処理[wave_three.cpp]
//Author Matsuda Towa
//
//=============================================
#include "wave_three.h"

//敵のファイル
const std::string CWave_Three::WAVE_3_ENEMY_FILE = "data\\FILE\\enemy_002.txt";
//ブロックファイル
const std::string CWave_Three::WAVE_3_BLOCK_FILE = "data\\FILE\\block_data000.bin";
//壁ファイル
const std::string CWave_Three::WAVE_3_WALL_FILE = "data\\FILE\\wall_002.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_Three::CWave_Three()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Three::~CWave_Three()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Three::Init()
{
	//初期化処理
	CWave::Init();

	//壁読み込み
	CWave::LoadBlock(WAVE_3_BLOCK_FILE);
	//敵読み込み
	CWave::LoadEnemy(&WAVE_3_ENEMY_FILE);
	//壁読み込み
	CWave::LoadWall(&WAVE_3_WALL_FILE);
	//地面生成
	CField::Create(VEC3_RESET_ZERO, NORMAL_FIELD_SIZE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Three::Uninit()
{
	//終了
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Three::Update()
{
	//更新
	CWave::Update();
}
