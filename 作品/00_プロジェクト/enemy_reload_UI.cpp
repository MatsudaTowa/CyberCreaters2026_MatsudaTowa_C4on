//=============================================
//
//敵のリロード中のUI[enemy_reload_UI.cpp]
//Author Matsuda Towa
//
//=============================================
#include "enemy_reload_UI.h"
#include "manager.h"

//テクスチャパス
const std::string CEnemy_Reload_UI::TEXTURE_NAME = "data\\TEXTURE\\magazine.png";

//=============================================
//コンストラクタ
//=============================================
CEnemy_Reload_UI::CEnemy_Reload_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy_Reload_UI::~CEnemy_Reload_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_Reload_UI::Init()
{
	//親クラスの初期化
	CBillboard::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy_Reload_UI::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy_Reload_UI::Update()
{
	//親クラスの更新
	CBillboard::Update();
}

//=============================================
//描画
//=============================================
void CEnemy_Reload_UI::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CEnemy_Reload_UI* CEnemy_Reload_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy_Reload_UI* pEnemyReloadUI = new CEnemy_Reload_UI;
	if(pEnemyReloadUI == nullptr) { return nullptr;}

	pEnemyReloadUI->SetPos(pos);	//位置設定
	pEnemyReloadUI->SetSize(size);	//サイズ設定

	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	pEnemyReloadUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pEnemyReloadUI->Init();	//初期化設定
	return pEnemyReloadUI;
}
