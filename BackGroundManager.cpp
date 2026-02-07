//==================================================================================
//
// 背景の管理処理 [BackGroundManager.cpp]
// Author : TENMA
//
//==================================================================================
//**********************************************************************************
//*** インクルードファイル ***
//**********************************************************************************
#include "BackGroundManager.h"
#include "mathUtil.h"

using namespace MyMathUtil;

//**********************************************************************************
//*** マクロ定義 ***
//**********************************************************************************
#define WHITE	DEF_COL	// 白	

//**********************************************************************************
//*** グローバル変数 ***
//**********************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = nullptr;		// 背景の頂点バッファ
LPDIRECT3DTEXTURE9 g_apTexBg[MODE_MAX] = {};			// 背景のテクスチャ
MODE g_currentBgType;									// 背景のタイプ
bool g_bUseBackGround = true;							// 背景を使用するか
const char *g_apTexFileNameBg[MODE_MAX] =				// パス
{
	"data/TEXTURE/",
	"data/TEXTURE/",
	"data/TEXTURE/",
};

//==================================================================================
// --- 初期化 ---
//==================================================================================
void InitBackGroundManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_bUseBackGround = true;
	g_currentBgType = MODE_TITLE;

	for (int nCntTex = 0; nCntTex < MODE_MAX; nCntTex++)
	{
		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			g_apTexFileNameBg[nCntTex],
			&g_apTexBg[nCntTex]);
	}

	// 頂点バッファ宣言
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	EndDevice();

	VERTEX_2D* pVtx;

	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	// スクリーン全体に表示
	MyMathUtil::SetFullScreenPolygon(pVtx);

	pVtx[0].pos.z = 1.0f;
	pVtx[1].pos.z = 1.0f;
	pVtx[2].pos.z = 1.0f;
	pVtx[3].pos.z = 1.0f;

	g_pVtxBuffBg->Unlock();
}

//==================================================================================
// --- 終了 ---
//==================================================================================
void UninitBackGroundManager(void)
{
	// 頂点バッファ解放
	RELEASE(g_pVtxBuffBg);

	// テクスチャのバッファ解放
	for (int nCntTex = 0; nCntTex < MODE_MAX; nCntTex++)
	{
		RELEASE(g_apTexBg[nCntTex]);
	}
}

//==================================================================================
// --- 更新 ---
//==================================================================================
void UpdateBackGroundManager(void)
{
	
}

//==================================================================================
// --- 描画 ---
//==================================================================================
void DrawBackGroundManager(void)
{
	if (g_bUseBackGround)
	{
		/*** デバイスの取得 ***/
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ポリゴン描画
		DrawPolygon(pDevice,
			g_pVtxBuffBg,
			g_apTexBg[g_currentBgType],
			sizeof(VERTEX_2D),
			FVF_VERTEX_2D,
			1);

		EndDevice();
	}
}

//==================================================================================
// --- 設定 ---
//==================================================================================
void SetBackGround(MODE bg)
{
	g_currentBgType = bg;
}

//==================================================================================
// --- オンオフ ---
//==================================================================================
void SetEnableBackGround(bool bEnable)
{
	g_bUseBackGround = bEnable;
}