//=============================================
//
//プレイヤー[player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _player_H_ //これが定義されてないとき

#define _player_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
#include "reticle.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"
#include "player_behavior.h"
#include "enemy.h"
#include "hit_camera_effect.h"
#include "gun_icon.h"
#include "player_state.h"
#include "ult.h"
#include "smoke_UI.h"
#include "gauge.h"
#include "blink_UI.h"

//=============================================
// 前方宣言
//=============================================
class CPlayerState;
class CPlayerAvoidance;
class CAmmo_UI;
class CUlt_UI;
class CUlt;
class CSmoke_UI;
class CBlink_UI;

//=============================================
//プレイヤークラス
//=============================================
class CPlayer:public CCharacter
{
public:
	static const int NUM_PARTS = 15; //パーツ数
	static const int MAX_KEY = 20; //キー最大数
	static const int PLAYER_LIFE = 150; //体力
	static const int PLAYER_STAMINA = 100; //スタミナ
	static const int AVOIDANCE_COST = 30; //回避アクションのスタミナコスト
	static const int PLAYER_PRIORITY = 8; //描画順

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void CanDetectEnemyCollision();
	void Draw();

	//プレイヤー作成
	static CPlayer* Create();

	void Damage(int nDamage); //当たり判定

	void ResetRot(); //方向のリセット

	void ColisionEnemy(); //敵との当たり判定

	void ChangeDamageState(); //TODOキャラクターにまとめろ

	void CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos);

	void Input(); //プレイヤー入力処理

	void ChangePlayerState(CPlayerState* state); //プレイヤーのステート切り替え

	//死んだ回数設定
	inline void SetDeathCnt(int DeathCnt)
	{
		m_DeathCnt = DeathCnt;
	}

	//スタミナ設定
	inline void SetStamina(int Stamina)
	{
		m_Stamina = Stamina;
	}

	//スモークが使えるかを設定
	inline void SetIsSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	//吹っ飛ばされているか設定
	inline void SetBlown(bool isBlown)
	{
		m_isBlown = isBlown;
	}

	//ブリンクの使える回数設定
	inline void SetBlinkCnt(int BlinkCnt)
	{
		m_BlinkCnt = BlinkCnt;
	}

	//エネミーとの当たり判定設定
	inline void SetEnemyColision(bool isColision)
	{
		m_isEnemyColision = isColision;
	}

	//死んだ回数取得
	inline int& GetDeathCnt()
	{
		return m_DeathCnt;
	}

	//スタミナ取得
	inline int& GetStamina()
	{
		return m_Stamina;
	}

	//ブリンクが使える回数取得
	inline int& GetBlinkCnt()
	{
		return m_BlinkCnt;
	}

	//スモークが使えるか取得
	inline bool& GetIsSmoke()
	{
		return m_isSmoke;
	}

	//吹っ飛ばされているか取得
	inline bool& GetBlown()
	{
		return m_isBlown;
	}

	//エネミーとの当たり判定取得
	inline bool& GetEnemyColision()
	{
		return m_isEnemyColision;
	}

	CReticle* m_Raticle;	//レティクルポインタ

	CUlt* m_pUlt;			//ウルトポインタ

	CPlayerState* m_pPlayerState;	//プレイヤーの状態

	CPlayerAvoidance* m_pAvoidance;	//回避行動
private:

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //スポーン位置
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //スポーン方向

	static const int IGNORE_COLLISION_FRAME = 150; //当たり判定無視フレーム
	static const int SMOKE_RECAST_FRAME = 900; //スモーク復活フレーム
	static const int DEFAULT_AR_RELOAD_FRAME = 90; //デフォルトのアサルトのリロードフレーム数
	static const int STAN_FRAME = 120; //スタンフレーム数
	static const int DEFAULT_AR_DAMAGE = 10; //デフォルトのアサルトのダメージ
	static const int STAMINA_RECOVERY = 1; //スタミナ回復数値
	static const int STAMINA_RECOVERY_FRAME = 5; //スタミナがSTAMINA_RECOVERY分回復するまでのフレーム数
	static const int DAMAGE_FRAME = 30; //ダメージフレーム

	static constexpr float DEADZONE_Y = -100.0f; //これを過ぎたらプレイヤー破棄
	static constexpr float RETICLE_CORRECTION_VALUE = 16.0f; //レティクルのY座標補正
	static constexpr float SMOKE_CORRECTION_VALUE = 50.0f; //スモークを射出する際の補正値
	static constexpr float SMOKE_SHOT_SPEED = 20.0f; //スモークを射出するスピード

	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ
	static const D3DXVECTOR3 STAMINA_GAUGE_SIZE; //スタミナのサイズ
	static const D3DXVECTOR3 GUN_UI_POS;//銃のUIの位置
	static const D3DXVECTOR2 GUN_UI_SIZE;//銃のUIのサイズ

	void SetUI(); //UI設定
	void ReSpawn(); //リスポーン

	CAmmo_UI* m_pAmmoUI;	//残弾UI

	CLife_UI* m_pLifeUI;	//体力UI

	CUlt_UI* m_pUltUI;		//ウルトUI

	CSmoke_UI* m_pSmokeUI;	//スモークUI

	CBlink_UI* m_pBlinkUI;	//ブリンクUI

	CGunIcon* m_pGunIcon;	//銃のアイコン

	CHitCameraEffect* m_pHitCameraEffect;	//ヒット時のカメラエフェクト

	void DebugPos();	//デバッグ時位置情報表示

	int m_IgnoreColisionCnt;	//敵との当たり判定無効カウント

	int m_SmokeRecastCnt;		//スモークのクールタイムカウント

	int m_DeathCnt; //死亡数

	int m_Stamina; //スタミナ

	int m_BlinkCnt; //ブリンク回数

	int m_StaminaRecoveryCnt; //スタミナ回復カウント

	bool m_isEnemyColision; //エネミーとの判定をとるか

	bool m_isRelorad; //リロードするかどうか

	bool m_isSmoke; //スモークを使ったか

	bool m_isBlown; //ふっとばされてるか
};
#endif