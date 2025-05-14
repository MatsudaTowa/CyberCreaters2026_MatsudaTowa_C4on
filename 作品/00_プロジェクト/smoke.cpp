//=============================================
//
//スモーク処理[somoke.cpp]
//Author Matsuda Towa
//
//=============================================
#include "smoke.h"
#include "smoke_range.h"
#include "manager.h"
#include "tactical_smoke.h"
#include "broken_smoke.h"

//テクスチャパス
const std::string CSmoke::SMOKE_TEXTURE_NAME = "data\\TEXTURE\\effect002.tga";

//=============================================
//コンストラクタ
//=============================================
CSmoke::CSmoke(int nPriority) : CBillboard(nPriority),
m_nLife(INT_ZERO),			//体力
m_move(VEC3_RESET_ZERO)		//移動量
{
}

//=============================================
//デストラクタ
//=============================================
CSmoke::~CSmoke()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmoke::Init()
{
	//親クラスの初期化
	CObject3D::Init();

	//ライフ設定
	m_nLife = SMOKE_LIFE; 

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmoke::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CSmoke::Update()
{
	//親クラスのアップデート
	CObject3D::Update();

	//移動処理
	Move();

	if (m_nLife > INT_ZERO)
	{//ライフが残っていれば
		//ライフを1減らす
		--m_nLife;
	}
	else
	{//ライフがなければ
		//フェードアウト
		FadeOut();
	}
}

//=============================================
//移動処理
//=============================================
void CSmoke::Move()
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//移動量代入
	pos += m_move;

	//位置設定
	SetPos(pos);

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//フェードアウト
//=============================================
void CSmoke::FadeOut()
{
	//色取得
	D3DXCOLOR color = GetColor();

	if (color.a > FLOAT_ZERO)
	{//透明度が0より高かったら
		//減算
		color.a -= FADE_VALUE;
		//色代入
		SetColor(color);
	}
	else
	{//見えなくなったら
		//SEを止めて
		CManager::GetInstance()->GetSound()->StopSound(CSound::SOUND_LABEL_SE_SMOKE);
		//終了
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CSmoke::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ビルボードの描画処理
	CBillboard::Draw();

	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	//親クラスの描画処理
	CBillboard::Draw();

	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	//zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//生成
//=============================================
CSmoke* CSmoke::Create(D3DXVECTOR3 pos, SMOKE_TYPE type)
{
	CSmoke* pSmoke = nullptr;

	switch (type)
	{
	case CSmoke::SMOKE_TYPE_TACTICAL:
		pSmoke = new CTacticalSmoke;
		break;
	case CSmoke::SMOKE_TYPE_BROKEN:
		pSmoke = new CBrokenSmoke;
		break;
	default:
		assert(false);
		break;
	}

	if(pSmoke == nullptr) {return nullptr;}

	pSmoke->SetPos(pos);
	pSmoke->Init();
	pSmoke->SetType(OBJECT_TYPE_SMOKE);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	pSmoke->BindTexture(pTexture->GetAddress(pTexture->Regist(&SMOKE_TEXTURE_NAME)));

	return pSmoke;
}
