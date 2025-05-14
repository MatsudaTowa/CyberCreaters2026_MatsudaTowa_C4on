//=============================================
//
//敵の処理[enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //これが定義されてないとき

#define _ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "enemy_behavior.h"
#include "enemy_state.h"

//=============================================
// 前方宣言
//=============================================
class CEnemyState;

//=============================================
//エネミークラス
//=============================================
class CEnemy :public CCharacter
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //描画順
	static const int DEFAULT_LIFE = 5; //ライフ

	//エネミーの列挙定義
	enum ENEMY_TYPE
	{
		ENEMY_TYPE_NORMAL = 0,
		ENEMY_TYPE_BOSS,
		ENEMY_TYPE_MAX,
	};

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX,
	};

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void ChangeDamageState();
	void Draw() override;

	//エネミー作成
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const ENEMY_TYPE& type);

	void Damage(int nDamage); //当たり判定

	virtual void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage); //ウルトの判定

	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);

	static int m_NumEnemy; //エネミーの総数
	ENEMY_TYPE m_Type; //エネミーの種類
	int m_nCombatChangeCnt; //戦闘状態切り替えカウント

private:
	//void ColisionUlt(D3DXVECTOR3& enemyPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall);

	//プレイヤーの移動関連
	static constexpr float DEFAULT_MOVE = 1.0f; //通常時の移動
	static constexpr float DAMPING_COEFFICIENT = 0.3f; //移動抵抗
	static constexpr float DEFAULT_JUMP = 25.0f; //通常時のジャンプ力
	static constexpr float ULT_KNOCKBACK_SPEED = 10.0f; //ULTが当たった時にノックバックさせる際のXとZにかけるスピード
	static constexpr float ULT_KNOCKBACK_Y = 40.0f; //ULTが当たった時にノックバックさせる際のYに打ち上げる
	static constexpr float DEADZONE_Y = -100.0f; //これを過ぎたらエネミー破棄
	static const int STENCIL_FLAME = 300; //ステンシルテスト有効
	static const int STAN_FRAME = 300; //スタン時間
	static const int DEFAULT_SCORE = 300; //デフォルトのスコア
	static const int BOSS_SCORE = 1000; //ボスを倒したら入るスコア


	void ReSpawn(); //リスポーン

	Motion_Type m_Motion; //モーションの種類
	bool m_isStencil; //ステンシルテストを有効にするか
	int m_StencilCnt; //ステンシルテスト有効カウント
};

#endif