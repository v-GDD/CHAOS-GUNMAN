//================================================================================================================
//
// DirectXの計算関連ヘッダファイル [mathUtil.h]
// Author : TENMA
//
//================================================================================================================
#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_

//**********************************************************************************
//*** インクルードファイル ***
//**********************************************************************************
#include "main.h"

// modeldata.hが存在する場合
#if __has_include("modeldata.h")
#include "modeldata.h"
#define MODELDATA_DEFINED
#endif

//**********************************************************************************
//*** マクロ定義 ***
//**********************************************************************************
#define RECT_NULL				(RECT{0, 0, 0, 0})				// RECT初期化
#define INT_VECTOR3_NULL		(INT_VECTOR3{ 0, 0, 0 })		// INT_VECTOR3初期化
#define INT_VECTOR2_NULL		(INT_VECTOR2{ 0, 0 })			// INT_VECTOR2初期化
#define D3DCOLOR_NULL			(D3DCOLOR_RGBA(255, 255, 255, 255)) // D3DCOLOR_NULL
#define INT_INFINITY			(0x7FFFFFFF)					// int型の最大(signed intの最大値)
#define VECNULL					D3DXVECTOR3(0.0f,0.0f,0.0f)		// 省略版vectorNull
#define VEC_X(x)				D3DXVECTOR3(x, 0.0f, 0.0f)		// Xのみ変更
#define VEC_Y(y)				D3DXVECTOR3(0.0f, y, 0.0f)		// Yのみ変更
#define VEC_Z(z)				D3DXVECTOR3(0.0f, 0.0f, z)		// Zのみ変更
#define InitRot(x, y, z)		RepairedRot(D3DXVECTOR3(x, y, z))	// 修正済み角度
#define DEF_COL					D3DXCOLOR_NULL					// デフォルトカラー

namespace MyMathUtil
{
	//**********************************************************************************
	//*** int型Vector3構造体 ***
	//**********************************************************************************
	typedef struct
	{
		int x;		// x
		int y;		// y
		int z;		// z
	}INT_VECTOR3;

	//**********************************************************************************
	//*** int型Vector2構造体 ***
	//**********************************************************************************
	typedef struct
	{
		int x;		// x
		int y;		// y
	}INT_VECTOR2;

	//**********************************************************************************
	//*** プロトタイプ宣言 ***
	//**********************************************************************************

	//----------------------------------------------------------------------------------
	/*** 当たり判定、角度関連 ***/
	bool CollisionBox(RECT rect, D3DXVECTOR3 pos);
	bool CollisionBoxZ(D3DXVECTOR4 rect, D3DXVECTOR3 pos);
	void RepairFloat(float* fRepairTarget, int nCnt = 3);
	float RepairRot(float fRot);
	void RepairRot(float* pOut, const float* fAngle);
	void RepairRot(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn);
	float InverseRot(float fRot);
	D3DXVECTOR3 InverseRot(D3DXVECTOR3 fRot);
	D3DXVECTOR3 RepairedRot(const D3DXVECTOR3 pIn);
	D3DXVECTOR3 DegreeToRadian(D3DXVECTOR3 degree);
	D3DXVECTOR3 RadianToDegree(D3DXVECTOR3 radian);
	//----------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	/*** D3DXVECTOR3の位置関連 ***/
	D3DXVECTOR3 GetPTPLerp(D3DXVECTOR3 Start, D3DXVECTOR3 End, float s);
	void HomingPosToPos(D3DXVECTOR3 posTarget, D3DXVECTOR3* posMover, float fSpeed);
	float GetPosToPos(D3DXVECTOR3 posTarget, D3DXVECTOR3 posMover);
	D3DXVECTOR3 GetPosBetweenPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
	float GetPTPLength(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
	//----------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	/*** D3DXCOLOR関連 ***/
	D3DXCOLOR GetColLerp(D3DXCOLOR Start, D3DXCOLOR End, float s);
	//----------------------------------------------------------------------------------
	
	//----------------------------------------------------------------------------------
	/*** ランダムな値取得関連 ***/
	D3DXVECTOR3 GetRandomVector3(int mx, int my, int mz);
	D3DXCOLOR GetRandomColor(bool bUseAlphaRand);
	//----------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	/*** 頂点情報関連 ***/
	void RollPolygon(VERTEX_2D* pVtx, D3DXVECTOR3 pos, float fWidth, float fHeight, float fRot, int nSpeed);
	void SetFullScreenPolygon(VERTEX_2D* pVtx);
	//----------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	/*** 変換関連 ***/
	D3DXVECTOR3 INTToFloat(INT_VECTOR3 nVector3);
	D3DXVECTOR2 INTToFloat(INT_VECTOR2 nVector2);
	//----------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	/*** 描画関連 ***/
	void DrawPolygon(LPDIRECT3DDEVICE9 pDevice,
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff,
		LPDIRECT3DTEXTURE9 pTexture,
		UINT VertexFormatSize,
		DWORD FVF,
		int nNumPolygon,
		UINT OffSet = 0);

	void DrawPolygonTextureArray(LPDIRECT3DDEVICE9 pDevice,
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff,
		LPDIRECT3DTEXTURE9* pTexture,
		UINT nNumTexture,
		int* pArrayTexNo,
		UINT VertexFormatSize,
		DWORD FVF,
		int nNumPolygon,
		UINT OffSet = 0);

	void DrawPolygonTextureFromIndex(LPDIRECT3DDEVICE9 pDevice,
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff,
		int nIdxTexture,
		UINT VertexFormatSize,
		DWORD FVF,
		int nNumPolygon,
		UINT OffSet = 0);

	void Draw3DModelFromXFile(LPDIRECT3DDEVICE9 pDevice,
		D3DXMATERIAL *pMat,
		DWORD dwNumMat,
		LPDIRECT3DTEXTURE9 *ppTexture,
		LPD3DXMESH pMesh);

#ifdef MODELDATA_DEFINED
	void Draw3DModelFromModelData(LPDIRECT3DDEVICE9 pDevice,
		LPMODELDATA pModelData);
#endif

	void CalcWorldMatrix(LPDIRECT3DDEVICE9 pDevice,
		D3DXMATRIX* mtxWorld,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		bool bSetTransform);

	void CalcWorldMatrixFromParent(LPDIRECT3DDEVICE9 pDevice,
		D3DXMATRIX* mtxWorld,
		D3DXMATRIX* mtxParent,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		bool bSetTransform);

	void CreateShadowMatrix(LPDIRECT3DDEVICE9 pDevice, D3DXMATRIX* pIn, D3DXMATRIX* pOut);
	void SetEnableZFunction(LPDIRECT3DDEVICE9 pDevice, bool bEnable);
	//----------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	/*** システム関連 ***/
	HRESULT CheckIndex(int TargetIndexMax, int Index, int TargetIndexMin = 0);
	bool CheckPath(_In_ const char* pFileName);
	void UniteChar(char* pOut, const char* fmt, ...);
	int GenerateMessageBox(_In_ UINT nType, _In_ const char* pCaption, _In_ const char* fmt, ...);
	//----------------------------------------------------------------------------------
}
#endif
