//=============================================
//
//攻撃管理クラス[attack_manager.cpp]
//Author Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "colision.h"
#include "player.h"
#include "model_parts.h"
#include "block.h"
#include "field.h"
#include"game.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CAttack_Manager::CAttack_Manager(int nPriority) : CBillboard(nPriority),
m_nLife(INT_ZERO),					//体力
m_nDamage(INT_ZERO),				//ダメージ
m_nNumkill(INT_ZERO)				//キル数
{
}

//=============================================
//デストラクタ
//=============================================
CAttack_Manager::~CAttack_Manager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAttack_Manager::Init()
{
	//親クラスの初期化
	CObject3D::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CAttack_Manager::Uninit()
{
	//親クラスの終了処理
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CAttack_Manager::Update()
{
	//親クラスの更新処理
	CObject3D::Update();

	if (m_nLife > INT_ZERO)
	{//寿命があるなら減らす
		m_nLife--;
	}
}

//=============================================
//描画
//=============================================
void CAttack_Manager::Draw()
{
	//親クラスの描画処理
	CBillboard::Draw();
}

//=============================================
//攻撃当たり判定(エネミー)
//=============================================
bool CAttack_Manager::HitEnemy()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}
		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
		{//エネミーじゃなければ
			//エネミーを探し続ける
			continue;
		}

		//敵との当たり判定
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		//当たり判定確認変数宣言
		CColision::COLISION ColisionCheck;

		for (int nCntParts = 0; nCntParts < pEnemy->GetNumParts(); nCntParts++)
		{
			//パーツのオフセットpos
			D3DXVECTOR3 PartsPos = { pEnemy->m_apModel[nCntParts]->GetMtxWorld()._41
			,pEnemy->m_apModel[nCntParts]->GetMtxWorld()._42
			,pEnemy->m_apModel[nCntParts]->GetMtxWorld()._43 };

			ColisionCheck = CManager::GetInstance()->GetColision()->CheckPolygonModelColisionSphere(Attackpos, Attacksize, PartsPos, pEnemy->m_apModel[nCntParts]->GetMin(), pEnemy->m_apModel[nCntParts]->GetMax());

			if (ColisionCheck != CColision::COLISION::COLISON_NONE)
			{//当たってたら
				if (nCntParts != 1)
				{//頭以外なら
					pEnemy->Damage(m_nDamage);
				}
				else if (nCntParts == 1)
				{//頭なら
					//ダメージ二倍
					pEnemy->Damage(m_nDamage * 2);
				}

				//HIT音を鳴らす
				CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_HIT);

				return true;
			}
		}
	}
	return false;
}

//=============================================
//攻撃当たり判定(プレイヤー)
//=============================================
bool CAttack_Manager::HitPlayer()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();


		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}

		//プレイヤーとの当たり判定
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		CColision::COLISION ColisionCheck;
		for (int nCnt = 0; nCnt < pPlayer->NUM_PARTS; nCnt++)
		{
			//パーツのオフセットpos
			D3DXVECTOR3 PartsPos = { pPlayer->m_apModel[nCnt]->GetMtxWorld()._41
			,pPlayer->m_apModel[nCnt]->GetMtxWorld()._42
			,pPlayer->m_apModel[nCnt]->GetMtxWorld()._43 };

			ColisionCheck = CManager::GetInstance()->GetColision()->CheckPolygonModelColisionSphere(Attackpos, Attacksize, PartsPos, pPlayer->m_apModel[nCnt]->GetMin(), pPlayer->m_apModel[nCnt]->GetMax());

			if (ColisionCheck != CColision::COLISION::COLISON_NONE)
			{//当たってたら
				//ダメージ処理を呼ぶ
				pPlayer->Damage(m_nDamage);
				return true;
			}
		}
	}
}

//=============================================
//攻撃当たり判定(ブロック)
//=============================================
bool CAttack_Manager::HitBlock()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
		{//ブロックじゃなければ
			//ブロックを探し続ける
			continue;
		}

		//ブロックとの当たり判定
		CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

		CColision::COLISION ColisionCheck_X = CManager::GetInstance()->GetColision()->CheckPolygonModelColision_X(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
		CColision::COLISION ColisionCheck_Z = CManager::GetInstance()->GetColision()->CheckPolygonModelColision_Z(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

		if (ColisionCheck_X != CColision::COLISION::COLISON_NONE || ColisionCheck_Z != CColision::COLISION::COLISON_NONE)
		{//当たってたら
			//攻撃の削除
			return true;
		}
	}
	return false;
}

//=============================================
//攻撃当たり判定(床)
//=============================================
bool CAttack_Manager::HitGround()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		//敵との当たり判定
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
		{//床じゃなければ
			//床を探し続ける
			continue;
		}

		//床との当たり判定
		CField* pField = dynamic_cast<CField*>(pObj);

		CColision::COLISION ColisionCheck = CManager::GetInstance()->GetColision()->CheckPolygonFillColision(Attackpos, Attacksize, pField->GetPos(),
		D3DXVECTOR3(-pField->GetSize().x, -pField->GetSize().y, -pField->GetSize().z), 
		D3DXVECTOR3(pField->GetSize().x, pField->GetSize().y, pField->GetSize().z));

		if (ColisionCheck == CColision::COLISION::COLISON_TOP_Y)
		{//当たってたら
			//埋まってる分を足す
			Attackpos.y += pField->GetPos().y - (Attackpos.y - Attacksize.y);

			SetPos(Attackpos);
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
	return false;
}