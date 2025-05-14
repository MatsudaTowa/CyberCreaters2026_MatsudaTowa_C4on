//=============================================
//
//スモークグレネード処理[somoke_grenade.cpp]
//Author Matsuda Towa
//
//=============================================
#include "smoke_grenade.h"
#include "manager.h"
#include "smoke_range.h"
#include "field.h"

//モデルパス
const char* CSmokeGrenade::MODEL_NAME = "data\\MODEL\\jett.x";

//=============================================
//コンストラクタ
//=============================================
CSmokeGrenade::CSmokeGrenade(int nPriority) :CObjectX(nPriority),
m_move(VEC3_RESET_ZERO),		//移動量
m_oldpos(VEC3_RESET_ZERO),		//過去の位置
m_bBoot(false)					//炸裂したか
{
}

//=============================================
//デストラクタ
//=============================================
CSmokeGrenade::~CSmokeGrenade()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmokeGrenade::Init()
{
	//親クラスの初期化
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmokeGrenade::Uninit()
{
	//親クラスの終了
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CSmokeGrenade::Update()
{
	//親クラスの更新
	CObjectX::Update();

	D3DXVECTOR3 pos = GetPos();

	m_oldpos = pos;

	//移動量代入
	pos += m_move;

	//位置設定
	SetPos(pos);

	//床との判定
	HitField();

	if (m_bBoot)
	{//炸裂したら
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SMOKE);

		for (int nCnt = INT_ZERO; nCnt < CREATE_SMOKE_NUM; nCnt++)
		{
			CSmoke::Create(GetPos(),CSmoke::SMOKE_TYPE_TACTICAL);
		}
		CSmokeRange::Create(GetPos(), VEC3_RESET_ZERO);
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CSmokeGrenade::Draw()
{
	//親クラスの描画
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CSmokeGrenade* CSmokeGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	CSmokeGrenade* pSmokeGrenade = new CSmokeGrenade;

	if (pSmokeGrenade == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	pSmokeGrenade->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pSmokeGrenade->SetPos(pos);		//位置代入
	pSmokeGrenade->m_move = move;	//移動量設定
	pSmokeGrenade->SetRot(rot);		//方向設定
	pSmokeGrenade->Init();			//初期化処理
	pSmokeGrenade->SetType(OBJECT_TYPE_SMOKE_GRENADE);	//タイプ設定

	return pSmokeGrenade;
}

//=============================================
//床との判定
//=============================================
void CSmokeGrenade::HitField()
{
	D3DXVECTOR3 pos = GetPos();

	//サイズ取得
	D3DXVECTOR3 min = GetMinPos();
	D3DXVECTOR3 max = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
		{//床じゃなければ
			//床を探し続ける
			continue;
		}

		CField* pField = dynamic_cast<CField*>(pObj);

		//床のみだけローカルで
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, pos, min, max, pField->GetPos(), pField->GetSize());

		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{//y(上)方向に当たってたら
			pos.y = m_oldpos.y;
			m_move = VEC3_RESET_ZERO;
			m_bBoot = true;
		}

		if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x
			&& pos.x < pField->GetPos().x - pField->GetSize().x)
		{
			pos.x = m_oldpos.x;
			m_move = VEC3_RESET_ZERO;
			m_bBoot = true;
		}

		if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x
			&& pos.x > pField->GetPos().x + pField->GetSize().x)
		{
			pos.x = m_oldpos.x;
			m_move = VEC3_RESET_ZERO;
			m_bBoot = true;
		}

		if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z
			&& pos.z < pField->GetPos().z - pField->GetSize().z)
		{
			pos.z = m_oldpos.z;
			m_move = VEC3_RESET_ZERO;
			m_bBoot = true;
		}

		if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z
			&& pos.z > pField->GetPos().z + pField->GetSize().z)
		{
			pos.z = m_oldpos.z;
			m_move = VEC3_RESET_ZERO;
			m_bBoot = true;
		}
		
	}
	SetPos(pos);

}
