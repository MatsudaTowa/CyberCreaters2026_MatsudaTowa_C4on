//=============================================
//
//ボスの敵の処理[boss_enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOSS_ENEMY_H_ //これが定義されてないとき

#define _BOSS_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"
#include "boss_behavior.h"
#include "boss_state.h"
#include"player.h"
#include "dash_effect.h"
#include "tackle_charge.h"

//=============================================
//前方宣言
//=============================================
class CBossChase;
class CBossWandering;
class CBossConfusion;
class CBossTackle;
class CBossSearch;
class CBossRampage;
class CBossState;

//=============================================
//ボスのエネミークラス
//=============================================
class CBossEnemy :public CEnemy
{
public:
	static const int NUM_PARTS = 15; //パーツ数
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //描画順
	static const int PARTS_PARENT[NUM_PARTS]; //パーツ数
	static const int DEFAULT_LIFE = 1500; //ライフ
	static const int LOW_HP = DEFAULT_LIFE / 3; //体力が低い
	static constexpr float FIND_PLAYER_DISTANCE = 300.0f; //この値までだったら追いかける
	static constexpr float LOST_PLAYER_DISTANCE = 100.0f; //この値以上だったら見失う

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_TACKLE,
		MOTION_MAX,
	};

	CBossEnemy(int nPriority = ENEMY_PRIORITY);
	~CBossEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void ChangeState(CBossState* state);

	void TackleAction(); //タックルの実行処理

	void ColisionPlayer(); //プレイヤーとの当たり判定

	void CheckColisionPlayer(CPlayer* pPlayer, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;

	void HitBlock(int NumParts) override; //ブロック当たり判定(複数パーツ用)

	void ColisionReset(); //当たってない判定に

	CBossChase* m_pChase; //追跡処理

	CBossWandering* m_pWandering; //徘徊処理

	CBossConfusion* m_pConfusion; //混乱

	CBossTackle* m_pTackle; //タックル処理

	CBossSearch* m_pSearch; //探索処理

	CBossRampage* m_pRampage; //暴走処理

	CDashEffect* m_pTackleEffect; //ダッシュエフェクト

	CTackleCharge* m_pTackleCharge; //タックルを行う前のエフェクト

	//当たった方向の列挙
	enum COLISION_AXIS
	{
		NONE,
		X,
		Z,
		MAX,
	};

	//当たった方向設定
	inline void SethitAxis(COLISION_AXIS axis)
	{
		m_HitAxis = axis;
	}

	//当たった方向取得
	inline COLISION_AXIS& GetAxis()
	{
		return m_HitAxis;
	}
private:
	static constexpr float CORRECTION_VALUE_Y = 100.0f; //タックルエフェクトを生成する際のYの補正値

	static constexpr float TACKLE_VALUE = 15.0f; //タックル時のスピード加算

	static constexpr float PLAYER_KNOCKBACK_SPEED = 15.0f; //タックルが当たった時にノックバックさせる際のXとZにかけるスピード

	static constexpr float PLAYER_KNOCKBACK_Y = 30.0f; //タックルが当たった時にノックバックさせる際のYに打ち上げる

	static const float DEFAULT_MOVE; //通常時の移動

	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ

	//各行動生成
	void CreateBossStrategy();

	//各行動破棄
	void DeleteBossStrategy();

	//ステートの実行処理
	void ProcessState();

	//デバッグ表示
	void DrawDebug();

	Motion_Type m_Motion; //モーションの種類

	CBossState* m_pBossState; //ボスのステートパターン

	COLISION_AXIS m_HitAxis; //どの方向から当たったか
};

#endif