//=============================================
//
//銃のストラテジーパターン[gun_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "gun_behavior.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CShot::CShot()
{
}

//=============================================
//デストラクタ
//=============================================
CShot::~CShot()
{
}

//=============================================
//弾発射処理
//=============================================
void CShot::Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* gun)
{
	//現在の弾数取得
	int nAmmo = gun->GetAmmo();
	if (nAmmo > INT_ZERO)
	{//マガジン内に弾があれば
		//弾を生成
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			VEC3_RESET_ZERO, D3DXVECTOR3(size.x, size.y, FLOAT_ZERO), LIFE, nDamage, Allegiance, type);

		//マズルフラッシュを生成
		CMuzzleFlash::Create(pos);

		//弾数を減らす
		--nAmmo;
	}
	gun->SetAmmo(nAmmo);
}

//=============================================
//コンストラクタ
//=============================================
CReload::CReload():m_nReloadCnt(INT_ZERO)
{
}

//=============================================
//デストラクタ
//=============================================
CReload::~CReload()
{
}
