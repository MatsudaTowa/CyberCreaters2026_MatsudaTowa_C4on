//=============================================
//
//ブロックの破片[block_piece.cpp]
//Author Matsuda Towa
//
//=============================================
#include "block_piece.h"

//xファイルパス
const char* CBlock_Piece::MODEL_NAME[CBlock_Piece::PIECE_SHAPE_MAX]
{
	"data\\MODEL\\piece_000.x",
	"data\\MODEL\\piece_001.x",
	"data\\MODEL\\piece_002.x",
};

//=============================================
// コンストラクタ
//=============================================
CBlock_Piece::CBlock_Piece(int nPriority):CObjectX(nPriority),
m_shape()		//ピースの形
{
}

//=============================================
// デストラクタ
//=============================================
CBlock_Piece::~CBlock_Piece()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CBlock_Piece::Init()
{
	//親クラスの初期化処理
	CObjectX::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CBlock_Piece::Uninit()
{
	//親クラスの終了処理
	CObjectX::Uninit();
}

//=============================================
// 更新
//=============================================
void CBlock_Piece::Update()
{
	//親クラスの更新処理
	CObjectX::Update();
}

//=============================================
// 描画
//=============================================
void CBlock_Piece::Draw()
{
	//親クラスの描画処理
	CObjectX::Draw();
}

//=============================================
// 生成
//=============================================
CBlock_Piece* CBlock_Piece::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, bool isMove)
{
	CBlock_Piece* pPiece = nullptr;

	//動くものと動かないもので確保するクラスを変更
	if (isMove)
	{
		pPiece = new CMove_Piece;
	}
	else if (!isMove)
	{
		pPiece = new CStack_Piece;
	}

	//nullならnullを返す
	if (pPiece == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	int nShape = 0;
	//pPiece->m_type = type;
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, CBlock_Piece::PIECE_SHAPE_MAX - 1);
	//ランダムでタイプ指定
	nShape = number(random);

	//元の位置からからどれだけ動かすか
	std::uniform_real_distribution<float> pos_shift_x(SHIFT_X_MIN, SHIFT_X_MAX);
	std::uniform_real_distribution<float> pos_shift_z(SHIFT_Z_MIN, SHIFT_Z_MIN);

	pPiece->m_shape = (CBlock_Piece::PIECE_SHAPE)nShape;
	pPiece->SetPos({ pos .x + pos_shift_x(random),0.2f,pos.z + pos_shift_z(random)}); //pos設定
	pPiece->SetRot(rot); //rot設定
	pPiece->SetScale(scale); //スケール設定
	//pPiece->BindTexture(m_pTextureTemp);

	//Xファイル読み込み
	pPiece->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_shape])).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_shape])).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_shape])).pMesh);

	pPiece->SetType(OBJECT_TYPE_BLOCK_PIECE); //タイプ設定
	pPiece->Init();

	return pPiece;
}

//=============================================
// コンストラクタ
//=============================================
CMove_Piece::CMove_Piece(int nPriority):CBlock_Piece(nPriority),
m_nLife(INT_ZERO),					//寿命
m_move(VEC3_RESET_ZERO)				//移動量
{
}

//=============================================
// デストラクタ
//=============================================
CMove_Piece::~CMove_Piece()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CMove_Piece::Init()
{
	// 親クラスの初期化
	CBlock_Piece::Init();

	//飛ばす方向
	float fVertex;
	//移動量
	float fMove;

	//放射状にランダム
	fVertex = CICRLE_RAND;

	//移動ランダム(最低でもMIN_MOVEは代入されるように設計)
	fMove = (float)(rand() % RAND_RANGE) / MOVE_RANGE + MIN_MOVE;

	//寿命代入
	m_nLife = LIFE;

	//移動量代入
	m_move.x = sinf(fVertex) * fMove;
	m_move.y = fMove;
	m_move.z = cosf(fVertex) * fMove;
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CMove_Piece::Uninit()
{
	// 親クラスの終了
	CBlock_Piece::Uninit();
}

//=============================================
// 更新
//=============================================
void CMove_Piece::Update()
{
	// 親クラスの更新
	CBlock_Piece::Update();

	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動処理
	pos += m_move;
	//位置代入
	SetPos(pos);

	//寿命を減らす
	--m_nLife;
	if (m_nLife <= INT_ZERO)
	{//ライフ切れたら
		m_nLife = INT_ZERO;
		//破棄
		Uninit();
	}
}

//=============================================
// 描画
//=============================================
void CMove_Piece::Draw()
{
	// 親クラスの描画
	CBlock_Piece::Draw();
}

//=============================================
// コンストラクタ
//=============================================
CStack_Piece::CStack_Piece(int nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CStack_Piece::~CStack_Piece()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CStack_Piece::Init()
{
	// 親クラスの初期化
	CBlock_Piece::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CStack_Piece::Uninit()
{
	// 親クラスの終了
	CBlock_Piece::Uninit();
}

//=============================================
// 更新
//=============================================
void CStack_Piece::Update()
{
	// 親クラスの更新
	CBlock_Piece::Update();
}

//=============================================
// 描画
//=============================================
void CStack_Piece::Draw()
{
	// 親クラスの描画
	CBlock_Piece::Draw();
}
