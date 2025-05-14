//=============================================
//
//ボスの敵の処理[boss_enemy.cpp]
//Author Matsuda Towa
//
//=============================================
#include "boss_enemy.h"
#include "boss_behavior.h"

//影のサイズ
const D3DXVECTOR3 CBossEnemy::SHADOW_SIZE = { 30.0f, 0.0, 30.0f };

//=============================================
//コンストラクタ
//=============================================
CBossEnemy::CBossEnemy(int nPriority):CEnemy(nPriority),
m_pChase(nullptr),										//追跡処理
m_pWandering(nullptr),									//徘徊処理
m_pConfusion(nullptr),									//混乱処理
m_pTackle(nullptr),										//タックル処理
m_pSearch(nullptr),										//探索処理
m_pRampage(nullptr),									//暴走処理
m_pTackleEffect(nullptr),								//ダッシュエフェクト
m_pTackleCharge(nullptr)								//タックル前のエフェクト
{
	//各行動を作成
	CreateBossStrategy();
}

//=============================================
//デストラクタ
//=============================================
CBossEnemy::~CBossEnemy()
{
	//ステート破棄
	if (m_pBossState != nullptr)
	{
		delete m_pBossState;
	}

	//各行動の破棄
	DeleteBossStrategy();

	//タックルエフェクト破棄
	if (m_pTackleEffect != nullptr)
	{
		m_pTackleEffect->Uninit();
		m_pTackleEffect = nullptr;
	}

	//タックル前のエフェクト破棄
	if (m_pTackleCharge != nullptr)
	{
		m_pTackleCharge->Uninit();
		m_pTackleCharge = nullptr;
	}
}

//=============================================
//ボスの行動作成
//=============================================
void CBossEnemy::CreateBossStrategy()
{
	//ボスの徘徊行動を生成
	if (m_pWandering == nullptr)
	{
		m_pWandering = new CBossWandering;
	}
	//ボスの追跡行動を生成
	if (m_pChase == nullptr)
	{
		m_pChase = new CBossChase;
	}
	//ボスの混乱行動を生成
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CBossConfusion;
	}
	//ボスのスタン行動を生成
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	//ボスの射撃行動を生成
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CBossGunAttack;
	}
	//ボスのタックル行動を生成
	if (m_pTackle == nullptr)
	{
		m_pTackle = new CBossTackle;
	}
	//ボスの暴走行動を作成
	if (m_pRampage == nullptr)
	{
		m_pRampage = new CBossRampage;
	}
	//ボスの捜索行動を作成
	if (m_pSearch == nullptr)
	{
		m_pSearch = new CBossSearch;
	}
}

//=============================================
// 各行動の破棄
//=============================================
void CBossEnemy::DeleteBossStrategy()
{
	//徘徊行動破棄
	if (m_pWandering != nullptr)
	{
		delete m_pWandering;
	}
	//追跡行動破棄
	if (m_pChase != nullptr)
	{
		delete m_pChase;
	}
	//混乱行動破棄
	if (m_pConfusion != nullptr)
	{
		delete m_pConfusion;
	}
	//タックル行動破棄
	if (m_pTackle != nullptr)
	{
		delete m_pTackle;
	}
	//暴走行動破棄
	if (m_pRampage != nullptr)
	{
		delete m_pRampage;
	}
	//探索行動破棄
	if (m_pSearch != nullptr)
	{
		delete m_pSearch;
	}
}

//=============================================
//初期化
//=============================================
HRESULT CBossEnemy::Init()
{
	//ボスのステート生成
	if (m_pBossState == nullptr)
	{
		//最初は徘徊状態
		m_pBossState = new CWanderingState;
	}
	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CMiniGun;

		m_pGun->Init();
	}

	//定数値で決められている初期体力設定
	SetLife(DEFAULT_LIFE);
	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);
	//親クラスの初期化を呼ぶ
	CEnemy::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBossEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CBossEnemy::Update()
{
	//親クラスの更新処理を呼ぶ
	CEnemy::Update();

	ProcessState(); //各ステートの実行処理

	Motion(NUM_PARTS); //モーション処理

	for (int nCnt = INT_ZERO; nCnt < GetNumParts(); ++nCnt)
	{
		if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_X)
		{
			m_HitAxis = X;
			break;
		}
		else if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_Z)
		{
			m_HitAxis = Z;
			break;
		}
		else
		{
			m_HitAxis = NONE;
		}
	}
}

//=============================================
//ステートの実行処理
//=============================================
void CBossEnemy::ProcessState()
{
	//現在のステートの徘徊の処理を呼ぶ
	m_pBossState->Wandering(this);

	//現在のステートの追跡の処理を呼ぶ
	m_pBossState->Chase(this);

	//現在のステートのスタンの処理を呼ぶ
	m_pBossState->Stan(this);

	//現在のステートの混乱の処理を呼ぶ
	m_pBossState->Confusion(this);

	//現在のステートのタックルの処理を呼ぶ
	m_pBossState->Tackle(this);

	//現在のステートの探索の処理を呼ぶ
	m_pBossState->Search(this);

	//現在のステートの暴走の処理を呼ぶ
	m_pBossState->Rampage(this);
}

//=============================================
//描画
//=============================================
void CBossEnemy::Draw()
{
	//デバッグ表示
	DrawDebug();
	//親クラスの描画処理を呼ぶ
	CEnemy::Draw();
}

//=============================================
//ボスの状態切り替え
//=============================================
void CBossEnemy::ChangeState(CBossState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pBossState != nullptr)
	{
		//破棄漏れをなくすために破棄する関数を実行
		m_pBossState->End(this);
		delete m_pBossState;
		m_pBossState = state;
		//最初の一回だけ呼びたい関数を実行
		m_pBossState->Start(this);
	}
}

//=============================================
//タックルの処理
//=============================================
void CBossEnemy::TackleAction()
{
	SetMotion(CBossEnemy::MOTION_TACKLE);

	if (m_pTackleEffect == nullptr)
	{
		float fAngle = atan2f(sinf(GetRot().y), cosf(GetRot().y));

		//ダッシュエフェクト生成
		m_pTackleEffect = CDashEffect::Create({m_apModel[3]->GetMtxWorld()._41,m_apModel[3]->GetMtxWorld()._42 - CORRECTION_VALUE_Y,m_apModel[3]->GetMtxWorld()._43 }
		, { FLOAT_ZERO,fAngle,FLOAT_ZERO });
	}

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//移動量加算
	move.x += sinf(GetRot().y) *  GetSpeed() * -TACKLE_VALUE;
	move.z += cosf(GetRot().y) *  GetSpeed() * -TACKLE_VALUE;

	//移動量代入
	SetMove(move);

	if ( m_pTackleEffect != nullptr)
	{//エフェクトがあったら
	 //エフェクトを動かす
		 m_pTackleEffect->SetPos({ m_apModel[3]->GetMtxWorld()._41,m_apModel[3]->GetMtxWorld()._42 - CORRECTION_VALUE_Y,m_apModel[3]->GetMtxWorld()._43 });
	}

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf( GetRot().y + D3DX_PI), INT_ZERO, cosf( GetRot().y + D3DX_PI) };

	//プレイヤーとの判定チェック
	 ColisionPlayer();
}

//=============================================
//プレイヤーとの当たり判定
//=============================================
void CBossEnemy::ColisionPlayer()
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		//位置取得
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		//最小値取得
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		//最大値取得
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();

		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; ++nCnt)
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

			//プレイヤーを探す
			if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{//プレイヤーじゃなければ
				//プレイヤーを探し続ける
				continue;
			}

			//安全にダウンキャスト
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

			if (pPlayer->GetEnemyColision())
			{//プレイヤーがエネミーと当たる状態のとき
				CheckColisionPlayer(pPlayer, nPartsCnt, pos, Minpos, Maxpos);
			}
		}
	}
}

//=============================================
//プレイヤーとの当たり判定チェック
//=============================================
void CBossEnemy::CheckColisionPlayer(CPlayer* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < pPlayer->GetNumParts(); ++nPartsCnt)
	{//パーツ数回す
		//プレイヤーのワールドマトリックスの位置情報取得
		D3DXVECTOR3 playerpos = { pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._41,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._42,
			pPlayer->m_apModel[nPartsCnt]->GetMtxWorld()._43 };

		//最小値取得
		D3DXVECTOR3 PlayerMinpos = pPlayer->m_apModel[nPartsCnt]->GetMin();

		//最大値取得
		D3DXVECTOR3 PlayerMaxpos = pPlayer->m_apModel[nPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			playerpos, PlayerMinpos, PlayerMaxpos);

		if (colision == CColision::COLISION::COLISON_Z || colision == CColision::COLISION::COLISON_X)
		{//当たっていたら
			//プレイヤーを吹っ飛ばす
			D3DXVECTOR3 Playermove = D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * PLAYER_KNOCKBACK_SPEED,
				PLAYER_KNOCKBACK_Y, cosf(GetRot().y + D3DX_PI) * PLAYER_KNOCKBACK_SPEED);

			//移動量を設定
			pPlayer->SetMove(Playermove);
			//プレイヤーのステートを吹っ飛ばし状態に
			pPlayer->ChangePlayerState(new CBlownState);
			//ダメージを与える
			pPlayer->Damage(m_pTackle->TACKLE_DAMAGE);
		}
	}
}
//=============================================
//ウルトヒット処理
//=============================================
void CBossEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	ChangeState(new CBossStanState);
	//親クラスのヒット処理
	CEnemy::MediumUltHit(UltPos, nDamage);
}

//=============================================
//ブロックとの判定
//=============================================
void CBossEnemy::HitBlock(int NumParts)
{
	CCharacter::HitBlock(NumParts);

	for (int nPartsCnt = INT_ZERO; nPartsCnt < NumParts; ++nPartsCnt)
	{//パーツ数回す
		//自分のワールドマトリックスの位置情報取得
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		//過去の位置取得
		D3DXVECTOR3 oldpos = m_apModel[nPartsCnt]->GetOldPos();
		//最小値取得
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		//最大値取得
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();

		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; ++nCnt)
		{
			if (m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_X
				|| m_apModel[nPartsCnt]->GetColisionBlockInfo().bColision_Z)
			{
				break;
			}
		}
	}
}

//=============================================
//当たってない判定に
//=============================================
void CBossEnemy::ColisionReset()
{
	for (int nCntParts = INT_ZERO; nCntParts < GetNumParts(); ++nCntParts)
	{//パーツ数回す
		//当たっていない状態に
		m_apModel[nCntParts]->GetColisionBlockInfo().bColision_X = false;
		m_apModel[nCntParts]->GetColisionBlockInfo().bColision_Z = false;
	}
}

//=============================================
//ボスのデバッグ表示
//=============================================
void CBossEnemy::DrawDebug()
{
#ifdef _DEBUG
	m_pWandering->DrawDebug();
	m_pBossState->DrawDebug();
	m_pChase->DrawDebug();
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	for (int nCnt = 0; nCnt < GetNumParts(); ++nCnt)
	{
		if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_X)
		{
			sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d move:%.1f,%.1f,%.1f rot:%.1f,%.1f,%.1f 当たり判定:X", GetLife(), GetMove().x, GetMove().y, GetMove().z, GetRot().x, GetRot().y, GetRot().z);
		}
		else if (m_apModel[nCnt]->GetColisionBlockInfo().bColision_Z)
		{
			sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d move:%.1f,%.1f,%.1f rot:%.1f,%.1f,%.1f 当たり判定:Z", GetLife(), GetMove().x, GetMove().y, GetMove().z, GetRot().x, GetRot().y, GetRot().z);
		}
		else
		{
			sprintf(&aStr[0], "\n\n\n\n\n\nHP:%d move:%.1f,%.1f,%.1f rot:%.1f,%.1f,%.1f 当たり判定:当たってない", GetLife(), GetMove().x, GetMove().y, GetMove().z, GetRot().x, GetRot().y, GetRot().z);
		}
	}

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
