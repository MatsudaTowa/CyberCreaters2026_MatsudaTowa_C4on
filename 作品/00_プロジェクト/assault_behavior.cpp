//=============================================
//
//アサルト銃のストラテジーパターン[assault_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "assault_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CAssaultShot::CAssaultShot()
{
}

//=============================================
//デストラクタ
//=============================================
CAssaultShot::~CAssaultShot()
{
}

//=============================================
//コンストラクタ
//=============================================
CAssaultReload::CAssaultReload()
{
}

//=============================================
//デストラクタ
//=============================================
CAssaultReload::~CAssaultReload()
{
}

//=============================================
//アサルトリロード処理
//=============================================
bool CAssaultReload::Reload(CGun* gun)
{
	bool bReload = true; //リロード中かどうか
	int nCnt = GetReloadCnt(); //リロードのカウント取得
	
	++nCnt;

	if (nCnt >= gun->GetReloadFrame())
	{//リロードフレームに到達したら
		//カウントリセット
		nCnt = 0;
		//現在の弾数取得
		int nAmmo = gun->GetAmmo();
		//デフォルトのマガジン弾数代入
		nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
		//弾数設定
		gun->SetAmmo(nAmmo);
		//リロードしていない状態に
		bReload = false;
	}

	//カウント設定
	SetReloadCnt(nCnt);

	//現在のリロード状態を返す
	return bReload;
}
