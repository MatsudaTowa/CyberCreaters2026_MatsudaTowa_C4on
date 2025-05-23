//=============================================
//
//ボスのステートパターン[boss_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_

#include "character_state.h"
#include "boss_enemy.h"

//=============================================
//前方宣言
//=============================================
class CBossEnemy;

//=============================================
//ボスのステートクラス TODO:キャラクターのステートを継承して
//=============================================
class CBossState
{
public:
	CBossState();
	virtual ~CBossState();
	virtual void Start(CBossEnemy* boss);
	virtual void End(CBossEnemy* boss);
	virtual void Chase(CBossEnemy* boss);
	virtual void Stan(CBossEnemy* boss);
	virtual void Wandering(CBossEnemy* boss);
	virtual void Confusion(CBossEnemy* boss);
	virtual void Tackle(CBossEnemy* boss);
	virtual void Search(CBossEnemy* boss);
	virtual void Rampage(CBossEnemy* boss);
	virtual void DrawDebug();
};

//=============================================
//エネミーの追跡状態
//=============================================
class CChaseState : public CBossState
{
public:
	CChaseState();
	~CChaseState() override;
	virtual void Chase(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	static const int PLAY_TACKLE_FLAME = 300; //タックルを実行するまでのフレーム
	int m_PlayTackleCnt; //タックルまでの計測用
};

//=============================================
//エネミーのスタン状態
//=============================================
class CBossStanState :public CBossState
{
public:
	void Start(CBossEnemy* boss) override;
	void End(CBossEnemy* boss) override;
	virtual void Stan(CBossEnemy* boss);
	virtual void DrawDebug()override;
private:
	static const int STAN_FRAME = 180; //スタン時間
	int m_StanCnt; //スタン計測カウント
};

//=============================================
//エネミーの徘徊状態
//=============================================
class CWanderingState : public CBossState
{
public:
	CWanderingState();
	~CWanderingState() override;
	virtual void Wandering(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	static const int TRANSITION_FRAME = 60;
	int m_TransitionCnt;		//ステートが移り変わる猶予カウント
	bool m_bDamage;				//ダメージ食らったか
	D3DXVECTOR3 m_TargetRot;	//目的の方向
};

//=============================================
//エネミーの混乱状態
//=============================================
class CConfusionBossState : public CBossState
{
public:
	CConfusionBossState();
	~CConfusionBossState() override;
	void Start(CBossEnemy* boss) override;
	virtual void Confusion(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	static constexpr float CORRECTION_VALUE = 70.0f; //リアクションのUIを生成する際のYの補正値
	static const D3DXVECTOR3 SIZE; //リアクションのUIのサイズ

	float m_StartRot;
	bool m_isRight; //見渡す(true:右 false:左)
	CEnemy_Reaction_UI* m_pReaction;
};

//=============================================
//エネミーのタックル状態
//=============================================
class CTackleState : public CBossState
{
public:
	CTackleState();
	~CTackleState() override;
	void Start(CBossEnemy* boss) override;
	void End(CBossEnemy* boss) override;
	virtual void Tackle(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};

//=============================================
//エネミーのプレイヤーを探す状態
//=============================================
class CSearchState : public CBossState
{
public:
	void Start(CBossEnemy* boss) override;
	virtual void Search(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
private:
	D3DXVECTOR3 m_TargetPos;
};

//=============================================
//エネミーの暴走状態
//=============================================
class CRampageState : public CBossState
{
public:
	void Start(CBossEnemy* boss) override;
	void End(CBossEnemy* boss) override;
	virtual void Rampage(CBossEnemy* boss)override;
	virtual void DrawDebug()override;
};
#endif