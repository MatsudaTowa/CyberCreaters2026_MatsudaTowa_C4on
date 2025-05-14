//=============================================
//
//スコア処理「score.cpp」
// Author松田永久
//
//=============================================
#include "score.h"
#include "manager.h"

//座標
const D3DXVECTOR3 CScore::NUM_POS = { 750.0f, 55.0f, 0.0f };
//サイズ
const D3DXVECTOR2 CScore::NUM_SIZE = { 20.0f, 30.0f };

//=============================================
//コンストラクタ
//=============================================
CScore::CScore():
m_nScore(INT_ZERO),			//スコアの値
m_pos(VEC3_RESET_ZERO),		//位置
m_size(VEC2_RESET_ZERO)		//サイズ
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		m_pNumber[nCnt] = nullptr;
	}
}

//=============================================
//デストラクタ
//=============================================
CScore::~CScore()
{
}

//=============================================
//初期化
//=============================================
HRESULT CScore::Init()
{
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_pos, m_size);
			//座標をずらす
			m_pos.x -= m_DigitShift;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CScore::Uninit()
{
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}
}

//=============================================
//更新
//=============================================
void CScore::Update()
{
	SetScore(m_nScore);
}

//=============================================
//描画
//=============================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//=============================================
//スコア書き出し
//=============================================
void CScore::ExportScore(const std::string& FileName)
{
	std::ofstream File(FileName,std::ios::binary);

	if (!File.is_open())
	{
		return;
	}

	File.write(reinterpret_cast<const char*>(&m_nScore), sizeof(int));
	File.close();
}

//=============================================
//スコアリセット
//=============================================
void CScore::Reset()
{
	m_nScore = INT_ZERO;
}

//=============================================
//スコア設定
//=============================================
void CScore::SetScore(int nScore)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = INT_ONE;
	int nCnt;
	for (nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = m_nScore / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= INT_ZERO; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, COLOR_WHITE);
	}
}

