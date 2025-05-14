//=============================================
//
//テストシーン[test.cpp]
//Author Matsuda Towa
//
//=============================================
#include "test.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//読み込むブロック情報のファイル
const std::string CTest::BLOCK_FILE = "data\\FILE\\block_data_tutorial.bin";

//=============================================
// コンストラクタ
//=============================================
CTest::CTest()
{
}

//=============================================
// デストラクタ
//=============================================
CTest::~CTest()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CTest::Init()
{
	//ブロック生成
	LoadBlock(CTest::BLOCK_FILE);

	CField::Create(VEC3_RESET_ZERO, { 1000.0f,0.0f,1000.0f });

	//プレイヤー生成
	CPlayer::Create();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CTest::Uninit()
{
	CObject::ReleaseAll();
}

//=============================================
// 更新
//=============================================
void CTest::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	//if (m_bEdit == false)
	//{

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
// 描画
//=============================================
void CTest::Draw()
{
}

//=============================================
// ブロック読み込み
//=============================================
void CTest::LoadBlock(const std::string& pFileName)
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
