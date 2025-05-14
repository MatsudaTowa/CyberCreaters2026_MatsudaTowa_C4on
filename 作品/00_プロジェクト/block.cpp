//=============================================
//
//ブロック処理[block.cpp]
//Author Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "player.h"
#include "block_piece.h"
#include "smoke.h"
#include "smoke_range.h"

//モデルパス
const char* CBlock::MODEL_NAME = "data\\MODEL\\Container000.x";

//動く破片のサイズ
const D3DXVECTOR3 CBlock::MOVE_PIECE_SCALE = { 0.3f,0.3f,0.3f };
//滞在する破片のサイズ
const D3DXVECTOR3 CBlock::STACK_PIECE_SCALE = { 0.25f,0.25f,0.25f };

//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlock::Init()
{
	m_nLife = LIFE; //寿命代入
	m_bBreak = true; //デフォルトは壊せる設定に
	//親クラスの初期化処理
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlock::Uninit()
{
	//親クラスの終了処理
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CBlock::Update()
{
	//親クラスの更新処理
	CObjectX::Update();

#ifdef _DEBUG
	//デバッグでブロック一括破壊
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{
		//破片を生成
		CreatePiece();
		//終了処理
		Uninit();
	}
#endif // _DEBUG
}

//=============================================
//ブロックの破片生成
//=============================================
void CBlock::CreatePiece()
{
	//崩れるSEを鳴らす
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BREAK);

	for (int nCnt = INT_ZERO; nCnt < NUM_SMOKE; nCnt++)
	{//任意の数生成
		CSmoke::Create({ GetPos().x,FLOAT_ZERO,GetPos().z }, CSmoke::SMOKE_TYPE_BROKEN);
	}

	for (int nNumCreate = INT_ZERO; nNumCreate < NUM_PIECE; ++nNumCreate)
	{//動かない破片を生成
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_real_distribution<float> rot(PIECE_ROTATION_MIN, PIECE_ROTATION_MAX);
		CBlock_Piece::Create(GetPos(), { rot(random),FLOAT_ZERO,rot(random) }, STACK_PIECE_SCALE, false);
	}
	for (int nNumCreate = INT_ZERO; nNumCreate < NUM_PIECE; ++nNumCreate)
	{//動く破片を生成
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_real_distribution<float> rot(PIECE_ROTATION_MIN, PIECE_ROTATION_MAX);
		CBlock_Piece::Create(GetPos(), { (float)rot(random),FLOAT_ZERO,(float)rot(random) }, MOVE_PIECE_SCALE, true);
	}
}

//=============================================
//描画
//=============================================
void CBlock::Draw()
{
	//親クラスの描画処理
	CObjectX::Draw();

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスのポインタ
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	//親クラスの描画処理
	CObjectX::Draw();

	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================
//ブロック生成
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlock* pBlock = new CBlock;

	//nullならnullを返す
	if (pBlock == nullptr) {return nullptr;}
	
	CModel* pModel = CManager::GetInstance()->GetModel();

	pBlock->m_type = type; //タイプ設定
	pBlock->SetPos(pos); //pos設定
	pBlock->SetRot(rot); //pos設定


	//Xファイル読み込み
	pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pBlock->SetType(OBJECT_TYPE_BLOCK); //タイプ設定

	//初期化処理
	pBlock->Init();
	
	return pBlock;
}