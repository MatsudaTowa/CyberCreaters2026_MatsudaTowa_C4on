//=============================================
//
//スモーク処理[tactical_somoke.cpp]
//Author Matsuda Towa
//
//=============================================
#include "tactical_smoke.h"
#include "manager.h"

//スモークのサイズ
const D3DXVECTOR3 CTacticalSmoke::SIZE = { 60.0f,60.0f,0.0f };

//=============================================
//コンストラクタ
//=============================================
CTacticalSmoke::CTacticalSmoke(int nPriority):CSmoke(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CTacticalSmoke::~CTacticalSmoke()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTacticalSmoke::Init()
{
	//親クラスの初期化
	CSmoke::Init();

	//サイズ代入
	SetSize(SIZE);

	std::random_device seed;
	std::mt19937 random(seed());

	//それぞれの方向への移動量ランダムで設定
	std::uniform_real_distribution<float> number_x(MOVE_X_MIN, MOVE_X_MAX);
	std::uniform_real_distribution<float> number_y(MOVE_Y_MIN, MOVE_Y_MAX);
	std::uniform_real_distribution<float> number_z(MOVE_Z_MIN, MOVE_Z_MAX);

	D3DXVECTOR3 move = GetMove();
	//移動量代入
	move = { number_x(random) ,number_y(random) ,number_z(random) };

	//移動量設定
	SetMove(move);

	//色設定
	SetColor(COLOR_WHITE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CTacticalSmoke::Uninit()
{
	//親クラスの終了
	CSmoke::Uninit();
}

//=============================================
//更新
//=============================================
void CTacticalSmoke::Update()
{
	//親クラスの更新
	CSmoke::Update();

	D3DXVECTOR3 move = GetMove();
	//移動量代入
	if (move.x > FLOAT_ZERO)
	{
		move.x -= X_DECREASE;
	}
	if (move.x < FLOAT_ZERO)
	{
		move.x += X_DECREASE;
	}

	//移動量設定
	SetMove(move);
}

//=============================================
//描画
//=============================================
void CTacticalSmoke::Draw()
{
	//親クラスの描画
	CSmoke::Draw();
}
