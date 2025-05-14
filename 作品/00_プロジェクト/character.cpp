//=============================================
//
//キャラクター処理[character.cpp]
//Author Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "player.h"
#include "field.h"
#include "colision.h"
#include "smoke_range.h"

//=============================================
//コンストラクタ
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority),
m_bLanding(false),												//着地しているか
m_move(VEC3_RESET_ZERO),										//移動量
m_nLife(INT_ZERO),												//体力
m_nStateCnt(INT_ZERO),											//ダメージステートを維持するカウント
m_oldpos(VEC3_RESET_ZERO),										//過去の位置
m_State(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL),			 //今の状態
m_PartsCnt(INT_ZERO),											//パーツ数
m_nMotionFrameCnt(INT_ZERO),									//モーションのフレーム数
m_nKeySetCnt(INT_ZERO),											//キーの個数
m_Motion(INT_ZERO),												//モーション情報
m_bLoopFinish(),												//ループが終わったか
m_Speed(),														//スピード
m_Jump(),														//ジャンプ力
m_pGun(),														//銃のポインタ
m_motion_data(),													//モーション設定
m_pMove(),														//移動する処理
m_pGunAttack(),													//銃の攻撃
m_pStan(),														//スタン処理
m_pConfusion(),													//混乱処理
m_pCharacterState(),											//キャラクターのステートパターンポインタ
m_nJumpCnt(INT_ZERO),											//ジャンプ数
m_pShadow(),													//影のポインタ
m_ShadowSize(VEC3_RESET_ZERO)									//影のサイズ
{//イニシャライザーでプライオリティ設定、各メンバ変数初期化
}

//=============================================
//デストラクタ
//=============================================
CCharacter::~CCharacter()
{
	if (m_pMove != nullptr)
	{
		delete m_pMove;
	}
	if (m_pGunAttack != nullptr)
	{
		delete m_pGunAttack;
	}
	if (m_pCharacterState != nullptr)
	{
		delete m_pCharacterState;
	}
	if (m_pStan != nullptr)
	{
		delete m_pStan;
	}
	if (m_pConfusion != nullptr)
	{
		delete m_pConfusion;
	}

	for (int i = INT_ZERO; i < MAX_PARTS; i++)
	{
		if (m_apModel[i] != nullptr)
		{
			m_apModel[i]->Unload();
		}
	}
}

//=============================================
//初期化
//=============================================
HRESULT CCharacter::Init()
{
	if (m_pCharacterState == nullptr)
	{
		m_pCharacterState = new CMoveState;
	}
	if (m_pShadow == nullptr)
	{
		m_pShadow = CShadow::Create({ GetPos().x,SHADOW_POS_Y,GetPos().z }, m_ShadowSize);
	}

	//影のサイズ設定
	m_pShadow->SetSize({ m_ShadowSize });

	//最初どのモーションでもない値を代入
	m_Motion = -1;
	//ループモーション終わってる判定に
	m_bLoopFinish = true;

	//親クラスの初期化
	CObjectX::Init();

	//ワールドマトリックス設定
	ConversionMtxWorld();
    return S_OK;
}

//=============================================
//終了
//=============================================
void CCharacter::Uninit()
{
	if (m_pGun != nullptr)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}

	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}

    CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CCharacter::Update()
{
	for (int nCnt = 0; nCnt < m_PartsCnt; nCnt++)
	{
		m_apModel[nCnt]->SetOldPos({ m_apModel[nCnt]->GetMtxWorld()._41,m_apModel[nCnt]->GetMtxWorld()._42,m_apModel[nCnt]->GetMtxWorld()._43 });
	}

	//重力処理
	Gravity();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	if (m_bLanding)
	{
		//移動量を更新(減速）
		m_move *= FLOAT_ONE - MOVE_FRICTION;
	}

	//過去の位置に今の位置を代入
	m_oldpos = pos;

	//移動量追加
	pos += m_move;

	//座標を更新
	SetPos(pos);

	//影のサイズ設定
	m_pShadow->SetSize(m_ShadowSize);

	//影の位置設定
	m_pShadow->SetPos({ GetPos().x,SHADOW_POS_Y,GetPos().z });

	//最大最小値取得
	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	if (m_bLanding)
	{//着地してるなら
		//ジャンプ数リセット
		m_nJumpCnt = INT_ZERO;
	}

	//ブロックとの接触処理
	HitBlock(m_PartsCnt);

	//床との接触処理
	HitField();
}

//=============================================
//描画
//=============================================
void CCharacter::Draw()
{
	CObjectX::Draw();
}

//=============================================
//モーション用の描画
//=============================================
void CCharacter::MotionDraw()
{
	//デバイスの取得
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX MtxWorld = GetMtxWorld();

	//マトリックスの初期化
	D3DXMatrixIdentity(&MtxWorld);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);

	for (int nCnt = INT_ZERO; nCnt < m_PartsCnt; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//=============================================
//パーツのロード
//=============================================
void CCharacter::Load_Parts(const char* FileName)
{
	//ファイルの読み込み
	std::ifstream File(FileName, std::ios::binary);

	//ファイルが開かなかったら関数を抜ける
	if (!File.is_open())
	{
		return;
	}

	File.read(reinterpret_cast<char*>(&m_motion_data), sizeof(CCharacter::MotionData));

	m_Speed = m_motion_data.speed;
	m_Jump = m_motion_data.jump;
	m_PartsCnt = m_motion_data.parts;

	for (int nCnt = 0; nCnt < m_motion_data.parts; ++nCnt)
	{
		m_apModel[nCnt] = CModel_Parts::Create(VEC3_RESET_ZERO, VEC3_RESET_ZERO, &m_motion_data.path[nCnt][0]);
		m_apModel[nCnt]->m_nIdx = m_motion_data.idx[nCnt];
		m_apModel[nCnt]->m_nIdxModelParent = m_motion_data.parent[nCnt];

		//親を設定
		if (m_apModel[nCnt]->m_nIdxModelParent == -1)
		{
			m_apModel[nCnt]->SetParent(nullptr);
		}
		else
		{
			m_apModel[nCnt]->SetParent(m_apModel[m_apModel[nCnt]->m_nIdxModelParent]);
		}

		m_apModel[nCnt]->SetPos(m_motion_data.parts_pos[nCnt]);
		m_apModel[nCnt]->SetRot(m_motion_data.parts_rot[nCnt]);

		m_apModel[nCnt]->m_Tpos = m_apModel[nCnt]->m_pos;
		m_apModel[nCnt]->m_Trot = m_apModel[nCnt]->m_rot;
	}

	File.close();
}

//=============================================
//モーション処理
//=============================================
void CCharacter::Motion(int NumParts)
{
	D3DXVECTOR3 MovePos[MAX_PARTS];
	D3DXVECTOR3 MoveRot[MAX_PARTS];

	int nNextKey = (m_nKeySetCnt + INT_ONE) % m_motion_data.motion_set[m_Motion].nNumKey;

	for (int nMotionCnt = INT_ZERO; nMotionCnt < m_PartsCnt; nMotionCnt++)
	{
		MovePos[nMotionCnt] = (m_motion_data.motion_set[m_Motion].keySet[nNextKey].key[nMotionCnt].pos - m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].pos) / (float)m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].nFrame;
		MoveRot[nMotionCnt] = (m_motion_data.motion_set[m_Motion].keySet[nNextKey].key[nMotionCnt].rot - m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].key[nMotionCnt].rot) / (float)m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].nFrame;

		m_apModel[nMotionCnt]->m_pos += MovePos[nMotionCnt];
		m_apModel[nMotionCnt]->m_rot += MoveRot[nMotionCnt];
	}

	m_nMotionFrameCnt++;

	if (m_nMotionFrameCnt > m_motion_data.motion_set[m_Motion].keySet[m_nKeySetCnt].nFrame)
	{

		m_nMotionFrameCnt = INT_ZERO;
		m_nKeySetCnt = (m_nKeySetCnt + INT_ONE) % m_motion_data.motion_set[m_Motion].nNumKey;
		if (m_nKeySetCnt == INT_ZERO && m_motion_data.motion_set[m_Motion].nLoop == INT_ZERO)
		{//キーが終わりループモーションじゃなければ
			//モーションをニュートラルに
			SetMotion(INT_ZERO);
			//終わった判定
			m_bLoopFinish = true;
		}	
	}
}

//=====================================
//引数で指定したモーションに切り替える
//=====================================
void CCharacter::SetMotion(int Motion)
{
	if (m_Motion == Motion)
	{//今のモーションと一致していたら
		//この関数を抜ける
		return;
	}

	m_Motion = Motion;

	//フレームリセット
	m_nMotionFrameCnt = INT_ZERO;

	//キーカウントリセット
	m_nKeySetCnt = INT_ZERO;

	if (m_motion_data.motion_set[m_Motion].nLoop == INT_ZERO)
	{
		//終わった判定
		m_bLoopFinish = false;
	}

	for (int nCntParts = INT_ZERO; nCntParts < m_PartsCnt; nCntParts++)
	{
		m_apModel[nCntParts]->m_pos = m_apModel[nCntParts]->m_Tpos;
		m_apModel[nCntParts]->m_rot = m_apModel[nCntParts]->m_Trot;
		m_apModel[nCntParts]->m_rot = m_motion_data.motion_set[Motion].keySet[0].key[nCntParts].rot;
	}
}


//=============================================
//重力処理
//=============================================
void CCharacter::Gravity()
{
    if (m_move.y < GRAVITY_MAX)
    {
        m_move.y -= GRAVITY_MOVE;
    }
}

//=============================================
//ジャンプ処理
//=============================================
void CCharacter::Jump()
{
	m_move.y = m_Jump; //ジャンプ力代入
	m_bLanding = false; //空中状態
}

//=============================================
//ブロックとの接触判定(複数パーツ用)
//=============================================
void CCharacter::HitBlock(int NumParts)
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < NumParts; ++nPartsCnt)
	{
		D3DXVECTOR3 pos = {m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43};
		D3DXVECTOR3 oldpos = m_apModel[nPartsCnt]->GetOldPos();
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
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

			//ブロックを探す
			if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{//ブロックじゃなければ
				//ブロックを探し続ける
				continue;
			}

			//安全にダウンキャスト
			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

			//ブロックとの当たり判定
			ColisionBlock_X(nPartsCnt, pos, oldpos, Minpos, Maxpos, pBlock);
			ColisionBlock_Z(nPartsCnt, pos, oldpos, Minpos, Maxpos, pBlock);
			ColisionBlock_Y(nPartsCnt, pos, oldpos, Minpos, Maxpos, pBlock);

			if (m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_X
				|| m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_Z)
			{
				break;
			}
		}
	}
}

//=============================================
//ブロックとの接触判定_X
//=============================================
void CCharacter::ColisionBlock_X(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	//当たり判定チェック
	CColision::COLISION Colision = CManager::GetInstance()->GetColision()->CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	CModel_Parts::ColisionBlockInfo Info = m_apModel[PartsIdx]->GetColisionBlockInfo();

	if (Colision == CColision::COLISION::COLISON_X)
	{//x方向に当たってたら

		SetPos({m_oldpos.x,GetPos().y,GetPos().z});

		//X軸に当たった
		Info.bColision_X = true;

		//当たったブロックの情報を渡す
		Info.pBlock = pBlock;
	}
	else if (Colision == CColision::COLISION::COLISON_NONE)
	{
		//X軸に当たってない
		Info.bColision_X = false;
	}

	m_apModel[PartsIdx]->SetColisionBlockInfo(Info);
}

//=============================================
//ブロックとの接触判定_Y
//=============================================
void CCharacter::ColisionBlock_Y(int PartsIdx, D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	CColision::COLISION Colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	CModel_Parts::ColisionBlockInfo Info = m_apModel[PartsIdx]->GetColisionBlockInfo();

	if (Colision == CColision::COLISION::COLISON_UNDER_Y)
	{//y(下)方向に当たってたら
		CharacterPos.y = CharacterOldPos.y;

		//Y軸に当たった
		Info.bColision_Y = true;
	}

	if (Colision == CColision::COLISION::COLISON_TOP_Y)
	{//y(上)方向に当たってたら
		CharacterPos.y = CharacterOldPos.y;
		m_move.y = FLOAT_ZERO;
		m_bLanding = true; //着地

		//Y軸に当たった
		Info.bColision_Y = true;
	}

	if (Colision == CColision::COLISION::COLISON_NONE)
	{
		//Y軸に当たってない
		Info.bColision_Y = false;
	}
	m_apModel[PartsIdx]->SetColisionBlockInfo(Info);
}

//=============================================
//ブロックとの接触判定_Z
//=============================================
void CCharacter::ColisionBlock_Z(int PartsIdx, D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock)
{
	CColision::COLISION Colision = CManager::GetInstance()->GetColision()->CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
	CModel_Parts::ColisionBlockInfo Info = m_apModel[PartsIdx]->GetColisionBlockInfo();

	if (Colision == CColision::COLISION::COLISON_Z)
	{//z方向に当たってたら
		SetPos({GetPos().x,GetPos().y,m_oldpos.z});

		//Z軸に当たった
		Info.bColision_Z = true;

		//当たったブロックの情報を渡す
		Info.pBlock = pBlock;
		
	}
	else if (Colision == CColision::COLISION::COLISON_NONE)
	{
		//Z軸に当たってない
		Info.bColision_Z = false;
	}
	m_apModel[PartsIdx]->SetColisionBlockInfo(Info);
}

//=============================================
//床との接触判定
//=============================================
void CCharacter::HitField()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
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

		//床との当たり判定
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pField->GetPos(), pField->GetSize());

		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{//y(上)方向に当たってたら
			CharacterPos.y = m_oldpos.y;
			m_move.y = FLOAT_ZERO;
			m_bLanding = true; //着地
		}
		else
		{
			m_bLanding = false; //着地
		}

		if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x + COLLISION_SLACK
			&& CharacterPos.x <= pField->GetPos().x - pField->GetSize().x + COLLISION_SLACK)
		{
			CharacterPos.x = m_oldpos.x;
			m_move.x = FLOAT_ZERO;
		}

		if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x - COLLISION_SLACK
			&& CharacterPos.x >= pField->GetPos().x + pField->GetSize().x - COLLISION_SLACK)
		{
			CharacterPos.x = m_oldpos.x;
			m_move.x = FLOAT_ZERO;
		}

		if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z + COLLISION_SLACK
			&& CharacterPos.z <= pField->GetPos().z - pField->GetSize().z + COLLISION_SLACK)
		{
			CharacterPos.z = m_oldpos.z;
			m_move.x = FLOAT_ZERO;
		}

		if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z - COLLISION_SLACK
			&& CharacterPos.z >= pField->GetPos().z + pField->GetSize().z - COLLISION_SLACK)
		{
			CharacterPos.z = m_oldpos.z;
			m_move.x = FLOAT_ZERO;
		}
		SetPos(CharacterPos);
	}
}

//=============================================
//レイがスモークと当たるかチェック
//=============================================
CCharacter::RayHitInfo CCharacter::PerformRaycast_Smoke(D3DXVECTOR3 vector, CCharacter* character)
{
	RayHitInfo Info; //ヒット情報を返す変数

	//初期化
	Info.distance = -1.0f; //絶対値で返るので当たらなかった時用に-を代入
	Info.hit = false; //当たっていない状態に

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CSmokeRange::SMOKE_RANGE_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_SMOKE_RANGE)
		{//スモークじゃなければ
			//スモークを探し続ける
			continue;
		}

		CSmokeRange* pSmoke = dynamic_cast<CSmokeRange*>(pObj);
		//レイを原点からの差分から飛ばす(yはエネミーから飛ばす際の高さ調整)
		D3DXVECTOR3 StartRay = { character->GetPos().x - pSmoke->GetPos().x,character->GetPos().y + RAY_CORRECTION_VALUE,character->GetPos().z - pSmoke->GetPos().z };

		D3DXIntersect(pSmoke->GetpMesh(), &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);

		if (Info.hit)
		{
			// 障害物が間にある場合
			return Info;
		}
	}
	// 障害物がなく、プレイヤーまでレイが到達する場合
	return Info;
}

//=============================================
//レイがブロックと当たるかチェック
//=============================================
CCharacter::RayHitInfo CCharacter::PerformRaycast_Block(D3DXVECTOR3 vector, CCharacter* character)
{
	RayHitInfo Info; //ヒット情報を返す変数
	
	//初期化
	Info.distance = -1.0f; //絶対値で返るので当たらなかった時用に-を代入
	Info.hit = false; //当たっていない状態に

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
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

		CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

		//レイを原点からの差分から飛ばす
		D3DXVECTOR3 StartRay = { character->GetPos().x - pBlock->GetPos().x,character->GetPos().y + RAY_CORRECTION_VALUE,character->GetPos().z - pBlock->GetPos().z };
		D3DXIntersect(pBlock->GetpMesh(), &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
		if (Info.hit)
		{
			return Info;
		}
	}
	return Info;
}

//=============================================
//ワールドマトリックスの変換
//=============================================
void CCharacter::ConversionMtxWorld()
{
	//デバイスの取得
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX MtxWorld = GetMtxWorld();

	//マトリックスの初期化
	D3DXMatrixIdentity(&MtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);

	for (int nCnt = INT_ZERO; nCnt < m_PartsCnt; nCnt++)
	{
		m_apModel[nCnt]->ConversionMtxWorld();
	}
}

//=============================================
//壁との接触判定_X
//=============================================
void CCharacter::ColisionWall_X(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall)
{
	//当たり判定チェック
	CColision::COLISION Checkcolision_X = CManager::GetInstance()->GetColision()->CheckColision_X(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pWall->GetPos(), pWall->GetSize());
	if (Checkcolision_X == CColision::COLISION::COLISON_X)
	{//x方向に当たってたら
		CharacterPos.x = m_oldpos.x;
		m_move.x = FLOAT_ZERO;
	}
}

//=============================================
//壁との接触判定_Z
//=============================================
void CCharacter::ColisionWall_Z(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall)
{
	//当たり判定チェック
	CColision::COLISION Checkcolision_Z = CManager::GetInstance()->GetColision()->CheckColision_Z(m_oldpos, CharacterPos, CharacterMin, CharacterMax, pWall->GetPos(), pWall->GetSize());
	if (Checkcolision_Z == CColision::COLISION::COLISON_Z)
	{//z方向に当たってたら
		CharacterPos.z = m_oldpos.z;
		m_move.z = FLOAT_ZERO;
	}
}

//=============================================
//キャラクターのステート変更
//=============================================
void CCharacter::ChangeState(CCharacterState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pCharacterState != nullptr)
	{
		delete m_pCharacterState;
		m_pCharacterState = state;
		m_pCharacterState->Start(this);
	}
}
