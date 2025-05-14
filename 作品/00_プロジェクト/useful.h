//=============================================
//
//実用的な処理をまとめたもの[useful.h]
//Author Matsuda Towa
//
//============================================= 

//２重インクルード防止
#ifndef _USEFUL_H_ //これが定義されてないとき
#define _USEFUL_H_

#include "main.h"

//0初期化用
#define INT_ZERO (0)
#define FLOAT_ZERO (0.0f)
#define INT_ONE (1)
#define FLOAT_ONE (1.0f)

//半分
#define HALF	(0.5f)

//カラー初期化
#define COLOR_NONE (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))
#define COLOR_BLACK (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define COLOR_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define COLOR_RED (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define COLOR_GREEN (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define COLOR_BLUE (D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))
#define COLOR_YELLOW (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))

//頂点3D初期化
#define VEC3_RESET_ZERO (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define VEC3_RESET_ONE (D3DXVECTOR3(1.0f,1.0f,1.0f))

//頂点2D初期化
#define VEC2_RESET_ZERO (D3DXVECTOR2(0.0f,0.0f))
#define VEC2_RESET_ONE (D3DXVECTOR2(1.0f,1.0f))

//半円
#define HALF_PI	(D3DX_PI * HALF)
//1/4円
#define QRTR_PI	(D3DX_PI * (HALF * HALF))

//文字数最大数
#define MAX_TXT (256)

//放射状にランダム
#define CICRLE_RAND  ((float)(rand() % 629 - 314) / 100.0f)

#endif