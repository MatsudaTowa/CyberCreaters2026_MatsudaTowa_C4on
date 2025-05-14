//=============================================
//
//タイトル処理[title.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_H_ //これが定義されてないとき

#define _TITLE_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include "block.h"
#include "title_screen.h"

//=============================================
//タイトルクラス
//=============================================
class CTitle :public CScene
{
public:
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	static const std::string BLOCK_FILE;	//エネミーのファイル

	//読み込むときに必要なブロックの構造体
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	static const D3DXVECTOR3 LOGO_POS; //ロゴの位置
	static const D3DXVECTOR3 UI_POS; //UIの位置

	static const D3DXVECTOR3 FIELD_SIZE; //床のサイズ
	static const D3DXVECTOR2 LOGO_SIZE; //ロゴのサイズ
	static const D3DXVECTOR2 UI_SIZE; //UIサイズ

	static const D3DXVECTOR3 PLAYER_SPAWN; //スポーン位置

	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報

	//プレイヤー
	CPlayer*m_pPlayer;

	CTitle_Screen*m_pTitleScreen[2];
};
#endif