//=============================================
//
//弾[bullet.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //これが定義されてないとき

#define _BULLET_H_

//=============================================
//弾クラス
//=============================================
class CBullet : public CAttack_Manager
{
public:
	static const int BULLET_PRIORITY = 10; //描画順

	//敵か自分かの判断する列挙
	enum BULLET_ALLEGIANCE
	{
		BULLET_ALLEGIANCE_PLAYER = 0,
		BULLET_ALLEGIANCE_ENEMY,
		BULLET_ALLEGIANCE_MAX,
	};

	//弾の種類
	enum BULLET_TYPE
	{
		BULLET_TYPE_NORMAL = 0,
		BULLET_TYPE_MAX,
	};

	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void OnActive();

	void SetHitMaker();

	//弾作成
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot,
	D3DXVECTOR3 size,int nLife,int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type);

	//移動量設定
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//タイプ設定
	inline void SetBulletType(BULLET_TYPE type)
	{
		m_type = type;
	}

	//敵か自分かの設定
	inline void SetBulletAllegiance(BULLET_ALLEGIANCE Allegiance)
	{
		m_Allegiance = Allegiance;
	}

	inline D3DXVECTOR3 GetMove()
	{
		return m_move;
	}

	inline BULLET_ALLEGIANCE GetBulletAllegiance()
	{
		return m_Allegiance;
	}
private:
	static const std::string BULLET_TEXTURE_NAME;	//テクスチャの名前

	bool PenetrationBlock();
	BULLET_ALLEGIANCE m_Allegiance; //敵か自分かを判断する列挙型変数
	BULLET_TYPE m_type; //弾の種類
	D3DXVECTOR3 m_move; //移動量
};

#endif