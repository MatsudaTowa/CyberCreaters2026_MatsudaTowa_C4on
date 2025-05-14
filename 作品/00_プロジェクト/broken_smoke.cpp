//=============================================
//
//スモーク処理[broken_somoke.cpp]
//Author Matsuda Towa
//
//=============================================
#include "broken_smoke.h"

//スモークのカラー
const D3DXCOLOR CBrokenSmoke::COLOR = { 0.1f,0.1f,0.1f,1.0f };

//スモークのサイズ
const D3DXVECTOR3 CBrokenSmoke::SIZE = { 30.0f,30.0f,0.0f };
//=============================================
//コンストラクタ
//=============================================
CBrokenSmoke::CBrokenSmoke(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBrokenSmoke::~CBrokenSmoke()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBrokenSmoke::Init()
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
	move = { number_x(random),number_y(random),number_z(random)};

	//移動量設定
	SetMove(move);

	//色設定
	SetColor(COLOR);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBrokenSmoke::Uninit()
{
	//親クラスの終了
	CSmoke::Uninit();
}

//=============================================
//更新
//=============================================
void CBrokenSmoke::Update()
{
	//親クラスの更新
	CSmoke::Update();
}

//=============================================
//描画
//=============================================
void CBrokenSmoke::Draw()
{
	//親クラスの描画
	CSmoke::Draw();
}
