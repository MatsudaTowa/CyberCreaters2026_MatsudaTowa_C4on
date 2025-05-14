//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"
#include "player.h"

//=============================================
//プレイヤーの移動のストラテジー
//=============================================
class CPlayerMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CPlayerMove();
	~CPlayerMove() override;
	void Move(CCharacter* character)override;
};

//=============================================
//プレイヤーの攻撃のストラテジー
//=============================================
class CPlayerAttack : public CGunAttack
{
public:
	CPlayerAttack();
	~CPlayerAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	//射撃時の移動減算の値
	static constexpr float MOVE_SUBTRACTION = 0.85f;
	void ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type);
};

//=============================================
//プレイヤーの回避のストラテジー
//=============================================
class CPlayerAvoidance
{
public:
	CPlayerAvoidance();
	~CPlayerAvoidance();
	void Avoidance(CCharacter* character);
private:
	static constexpr float PLAYER_AVOIDANCE_SPEED = 30.0f; //ブリンクのスピード

};
#endif // !_ENEMY_BEHAVIOR_
