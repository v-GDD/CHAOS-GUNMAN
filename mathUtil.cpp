//================================================================================================================
//
// DirectXの計算関連cppファイル [mathUtil.cpp]
// Author : TENMA
//
//================================================================================================================
//**********************************************************************************
//*** インクルードファイル ***
//**********************************************************************************
#include "mathUtil.h"
#include "Texture.h"

//**********************************************************************************
//*** グローバル変数 ***
//**********************************************************************************

//================================================
// --- 対象の位置の範囲確認処理 ---
//================================================
bool MyMathUtil::CollisionBox(RECT rect, D3DXVECTOR3 pos)
{
	/*** 対象の位置が指定された四角形の範囲内か確認 ***/
	if (pos.x >= rect.left
		&& pos.x <= rect.right
		&& pos.y >= rect.top
		&& pos.y <= rect.bottom)
	{
		return true;
	}

	return false;
}

//================================================
// --- 対象の位置の範囲確認処理(XZ平面) ---
//================================================
bool MyMathUtil::CollisionBoxZ(D3DXVECTOR4 rect, D3DXVECTOR3 pos)
{
	/*** 対象の位置が指定された四角形の範囲内か確認 ***/
	if (pos.x >= rect.x
		&& pos.x <= rect.y
		&& pos.z >= rect.z
		&& pos.z <= rect.w)
	{
		return true;
	}

	return false;
}

//================================================
// --- 列挙型の範囲確認処理 ---
//================================================
HRESULT MyMathUtil::CheckIndex(int TargetIndexMax, int Index, int TargetIndexMin)
{
	if (Index < TargetIndexMin || Index >= TargetIndexMax)
	{
		return E_FAIL;
	}

	return S_OK;
}

//==================================================================
// --- 対象から対象へホーミングする処理 ---
//==================================================================
void MyMathUtil::HomingPosToPos(D3DXVECTOR3 posTarget, D3DXVECTOR3 *posMover, float fSpeed)
{
	float fAngle = 0.0f;
	
	fAngle = atan2f(posTarget.x - posMover->x, posTarget.z - posMover->z);

	posMover->x += sinf(fAngle) * fSpeed;
	posMover->z += cosf(fAngle) * fSpeed;
}

//==================================================================
// --- 対象から対象への角度を求める処理 ---
//==================================================================
float MyMathUtil::GetPosToPos(D3DXVECTOR3 posTarget, D3DXVECTOR3 posMover)
{
	float fAngle = 0.0f;

	fAngle = atan2f(posTarget.x - posMover.x, posTarget.z - posMover.z);

	/** 角度の修正! **/
	if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}
	else if (fAngle >= D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}

	return fAngle;
}

//==================================================================
// --- 角度を修正する処理 ---
//==================================================================
float MyMathUtil::RepairRot(float fRot)
{
	if (fRot <= -D3DX_PI || fRot > D3DX_PI)
	{
		if (fRot > D3DX_PI)
		{
			fRot -= D3DX_PI * 2.0f;
		}
		else if (fRot <= -D3DX_PI)
		{
			fRot += D3DX_PI * 2.0f;
		}

		return fRot;
	}
	else
	{
		return fRot;
	}
}

//==================================================================
// --- 角度を修正する処理(ポインタ処理) ---
//==================================================================
void MyMathUtil::RepairRot(float *pOut, const float *fAngle)
{
	float fOut = *fAngle;

	if (fOut > D3DX_PI)
	{
		fOut -= D3DX_PI * 2.0f;
	}
	else if (fOut <= -D3DX_PI)
	{
		fOut += D3DX_PI * 2.0f;
	}

	*pOut = fOut;
}

//==================================================================
// --- 角度を修正する処理(ポインタ処理) ---
//==================================================================
void MyMathUtil::RepairRot(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn)
{
	D3DXVECTOR3 out = *pIn;

	if (out.x > D3DX_PI)
	{
		out.x -= D3DX_PI * 2.0f;
	}
	else if (out.x <= -D3DX_PI)
	{
		out.x += D3DX_PI * 2.0f;
	}

	if (out.y > D3DX_PI)
	{
		out.y -= D3DX_PI * 2.0f;
	}
	else if (out.y <= -D3DX_PI)
	{
		out.y += D3DX_PI * 2.0f;
	}

	if (out.z > D3DX_PI)
	{
		out.z -= D3DX_PI * 2.0f;
	}
	else if (out.z <= -D3DX_PI)
	{
		out.z += D3DX_PI * 2.0f;
	}

	*pOut = out;
}

//==================================================================
// --- 角度を反転する処理 ---
//==================================================================
float MyMathUtil::InverseRot(float fRot)
{
	float fRotInverse = fRot;

	fRotInverse += D3DX_PI;
	if (fRotInverse > D3DX_PI)
	{
		fRotInverse -= D3DX_PI * 2.0f;
	}
	else if (fRotInverse <= -D3DX_PI)
	{
		fRotInverse += D3DX_PI * 2.0f;
	}

	return fRotInverse;
}

//==================================================================
// --- ベクトルを反転する処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::InverseRot(D3DXVECTOR3 fRot)
{
	return VECNULL;
}

//==================================================================
// --- 角度を修正する処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::RepairedRot(const D3DXVECTOR3 pIn)
{
	D3DXVECTOR3 out = pIn;

	if (out.x > D3DX_PI)
	{
		out.x -= D3DX_PI * 2.0f;
	}
	else if (out.x <= -D3DX_PI)
	{
		out.x += D3DX_PI * 2.0f;
	}

	if (out.y > D3DX_PI)
	{
		out.y -= D3DX_PI * 2.0f;
	}
	else if (out.y <= -D3DX_PI)
	{
		out.y += D3DX_PI * 2.0f;
	}

	if (out.z > D3DX_PI)
	{
		out.z -= D3DX_PI * 2.0f;
	}
	else if (out.z <= -D3DX_PI)
	{
		out.z += D3DX_PI * 2.0f;
	}

	return out;
}

//==================================================================
// --- 位置と位置の間の座標を求める処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::GetPosBetweenPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 posResult = D3DXVECTOR3_NULL;

	/*** X座標を比較し大きい方から差分を求める ***/
	if (pos1.x >= pos2.x)
	{
		posResult.x = (pos1.x + pos2.x) * 0.5f;
	}
	else
	{
		posResult.x = (pos2.x + pos1.x) * 0.5f;
	}

	/*** Y座標を比較し大きい方から差分を求める ***/
	if (pos1.y >= pos2.y)
	{
		posResult.y = (pos1.y + pos2.y) * 0.5f;
	}
	else
	{
		posResult.y = (pos2.y + pos1.y) * 0.5f;
	}

	/*** Z座標を比較し大きい方から差分を求める ***/
	if (pos1.z >= pos2.z)
	{
		posResult.z = (pos1.z + pos2.z) * 0.5f;
	}
	else
	{
		posResult.z = (pos2.z + pos1.z) * 0.5f;
	}

	/*** 結果 ***/
	return posResult;
}

//==================================================================
// --- ランダムな色を求める処理 ---
//==================================================================
D3DXCOLOR MyMathUtil::GetRandomColor(bool bUseAlphaRand)
{
	D3DXCOLOR col;

	col.r = (float)((rand() % 100) * 0.01f);
	col.g = (float)((rand() % 100) * 0.01f);
	col.b = (float)((rand() % 100) * 0.01f);

	if (bUseAlphaRand)
	{
		col.a = (float)((rand() % 100) * 0.01f);
	}
	else
	{
		col.a = 1.0f;
	}

	return col;
}

//==================================================================
// --- 2点間の距離を求める処理 ---
//==================================================================
float MyMathUtil::GetPTPLength(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	float fLength = 0.0f;

	if (pos1.x >= pos2.x
		&& pos1.y >= pos2.y)
	{
		fLength = sqrtf(powf((pos1.x - pos2.x), 2) + powf((pos1.y - pos2.y), 2));
	}
	else if (pos1.x >= pos2.x
		&& pos1.y <= pos2.y)
	{
		fLength = sqrtf(powf((pos1.x - pos2.x), 2) + powf((pos2.y - pos1.y), 2));
	}
	else if (pos1.x <= pos2.x
		&& pos1.y >= pos2.y)
	{
		fLength = sqrtf(powf((pos2.x - pos1.x), 2) + powf((pos1.y - pos2.y), 2));
	}
	else
	{
		fLength = sqrtf(powf((pos2.x - pos1.x), 2) + powf((pos2.y - pos1.y), 2));
	}

	return fLength;
}

//==================================================================
// --- ポリゴンを回転させる処理 ---
//==================================================================
void MyMathUtil::RollPolygon(VERTEX_2D* pVtx, D3DXVECTOR3 pos, float fWidth, float fHeight, float fRot, int nSpeed)
{
	float fLength = sqrtf(powf(fWidth, 2.0f) + powf(fHeight, 2.0f));
	float fAngle = atan2f(fWidth, fHeight);

	/*** 頂点バッファのポインタがNULLの場合、処理を行わずにスキップ ***/
	if (pVtx == NULL)
	{
		return;
	}

	pVtx[0].pos.x = pos.x + sinf(D3DX_PI + fAngle + fRot) * fLength;
	pVtx[0].pos.y = pos.y + cosf(D3DX_PI + fAngle + fRot) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(D3DX_PI - fAngle + fRot) * fLength;
	pVtx[1].pos.y = pos.y + cosf(D3DX_PI - fAngle + fRot) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(fRot - fAngle) * fLength;
	pVtx[2].pos.y = pos.y + cosf(fRot - fAngle) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(fRot + fAngle) * fLength;
	pVtx[3].pos.y = pos.y + cosf(fRot + fAngle) * fLength;
	pVtx[3].pos.z = 0.0f;
}

//==================================================================
// --- ポリゴンを画面全体に描画する処理 ---
//==================================================================
void MyMathUtil::SetFullScreenPolygon(VERTEX_2D* pVtx)
{
	/*** 頂点バッファのポインタがNULLの場合、処理を行わずにスキップ ***/
	if (pVtx == NULL)
	{
		return;
	}

	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	/*** 座標変換用係数の設定 ***/
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	/*** 頂点カラー設定 ***/
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	/*** テクスチャ座標の設定 ***/
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//==================================================================
// --- 360°をD3DXVECTOR3のRadianに変換する処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::DegreeToRadian(D3DXVECTOR3 degree)
{
	D3DXVECTOR3 radian;
	
	radian.x = D3DXToRadian(degree.x);
	/** 角度の修正! **/
	if (radian.x < -D3DX_PI)
	{
		radian.x += D3DX_PI * 2.0f;
	}
	else if (radian.x >= D3DX_PI)
	{
		radian.x -= D3DX_PI * 2.0f;
	}

	radian.y = D3DXToRadian(degree.y);
	/** 角度の修正! **/
	if (radian.y < -D3DX_PI)
	{
		radian.y += D3DX_PI * 2.0f;
	}
	else if (radian.y >= D3DX_PI)
	{
		radian.y -= D3DX_PI * 2.0f;
	}

	radian.z = D3DXToRadian(degree.z);
	/** 角度の修正! **/
	if (radian.z < -D3DX_PI)
	{
		radian.z += D3DX_PI * 2.0f;
	}
	else if (radian.z >= D3DX_PI)
	{
		radian.z -= D3DX_PI * 2.0f;
	}

	return radian;
}

//==================================================================
// --- RadianをD3DXVECTOR3のDegreeに変換する処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::RadianToDegree(D3DXVECTOR3 radian)
{
	D3DXVECTOR3 degree;

	degree.x = D3DXToDegree(radian.x);
	degree.y = D3DXToDegree(radian.y);
	degree.z = D3DXToDegree(radian.z);

	return degree;
}

//==================================================================
// --- INT_VECTOR3をD3DXVECTOR3に変換する処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::INTToFloat(INT_VECTOR3 nVector3)
{
	D3DXVECTOR3 rot = D3DXVECTOR3_NULL;

	rot.x = (float)nVector3.x;
	rot.y = (float)nVector3.y;
	rot.z = (float)nVector3.z;

	return rot;
}

//==================================================================
// --- INT_VECTOR2をD3DXVECTOR2に変換する処理 ---
//==================================================================
D3DXVECTOR2 MyMathUtil::INTToFloat(INT_VECTOR2 nVector2)
{
	D3DXVECTOR2 tex = D3DXVECTOR2(0.0f, 0.0f);

	tex.x = (float)nVector2.x;
	tex.y = (float)nVector2.y;

	return tex;
}

//==================================================================
// --- 位置ランダム設定処理 ---
//==================================================================
D3DXVECTOR3 MyMathUtil::GetRandomVector3(int mx, int my, int mz)
{
	int x, y, z = {};
	D3DXVECTOR3 Vector3 = {};

	x = rand() % mx - (mx / 2);
	y = rand() % my - (my / 2);
	z = rand() % mz - (mz / 2);

	Vector3.x = (FLOAT)x;
	Vector3.y = (FLOAT)y;
	Vector3.z = (FLOAT)z;

	return Vector3;
}

//==================================================================
// --- float型の値の正規処理 ---
//==================================================================
void MyMathUtil::RepairFloat(float *fRepairTarget, int nCnt)
{
	int nRepairedFloat;
	nRepairedFloat = *fRepairTarget * 10 * nCnt;
	nRepairedFloat /= 10 * nCnt;
	*fRepairTarget = nRepairedFloat;
}

//==================================================================
// --- パス指定の絶対アドレス確認処理 ---
//==================================================================
bool MyMathUtil::CheckPath(_In_ const char *pFileName)
{
#ifndef _PATHCHECK_NO_WARNINGS
	if (strstr(pFileName, "C:") != NULL)
	{
		GenerateMessageBox(MB_ICONWARNING, 
			"Warnings!", 
			"アドレスが絶対パスの可能性があります。\n相対パスに切り替えてください。\n\n対象パス : %s",
			pFileName);

		return true;
	}
#endif

	return false;
}

//==================================================================
// --- 書式付き文字列設定処理 ---
//==================================================================
void MyMathUtil::UniteChar(char* pOut, const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	const char* p1;
	char aStr[256] = {};
	char aStrEnd[256] = {};
	char aStrOut[1024] = {};
	int n = 0;
	int nc = 0;
	int d = 0;
	float f = 0.0f;

	int nCnt = 0;

	for (const char* p = fmt; *p != '\0'; p++, n++, nc++)
	{
		if (*p == '%')
		{
			p++;
			n++;

			switch (*p)
			{
			case 'd':

				nc += sprintf(&aStr[0], "%d", va_arg(ap, int));

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 'f':

				f = va_arg(ap, double);
				nc += sprintf(&aStr[0], "%f", f);

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 'c':

				nc += sprintf(&aStr[0], "%c", va_arg(ap, char));

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 's':
				p1 = va_arg(ap, const char*);
				nc += sprintf(&aStr[0], "%s", p1);

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 'b':
				nc += sprintf(&aStr[0], "%d", va_arg(ap, bool));

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case '~':

				p++;
				n++;

				sprintf(&aStr[0], "%c", *p);

				nCnt = atoi(&aStr[0]);

				p++;
				n++;

				switch (*p)
				{
				case 'd':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						nc += sprintf(&aStr[0], "%d ", va_arg(ap, int));

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 'f':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						f = va_arg(ap, double);
						nc += sprintf(&aStr[0], "%f ", f);

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 'c':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						nc += sprintf(&aStr[0], "%c ", va_arg(ap, char));

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 's':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						p1 = va_arg(ap, const char*);
						nc += sprintf(&aStr[0], "%s ", p1);

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 'b':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						nc += sprintf(&aStr[0], "%d ", va_arg(ap, bool));

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				default:

					break;
				}

				break;

			default:

				break;
			}
		}
		else
		{
			/*** 文字列を結合 ***/
			sprintf(&aStr[0], "%c", *p);
			//strncpy(&aStrCopy[0], &aStr2[n], 1);

			strcat(&aStrEnd[0], &aStr[0]);
		}

		memset(aStr, 0, sizeof aStr);
	}

	/*** クリーンアップ ***/
	va_end(ap);

	aStrEnd[nc + 1] = '\0';

	/*** 文字列を結合 ***/
	strcat(&aStrOut[0], aStrEnd);

	strcpy(pOut, &aStrOut[0]);
}

//==================================================================
// --- 書式付きメッセージボックス表示処理 ---
//==================================================================
int MyMathUtil::GenerateMessageBox(_In_ UINT nType, _In_ const char* pCaption, _In_ const char* fmt, ...)
{
#ifdef _DEBUG
	HWND hWnd = GetHandleWindow();
	if (hWnd == NULL)
	{
		return -1;
	}

	va_list ap;
	va_start(ap, fmt);
	const char* p1;
	char aStr[1024] = {};
	char aStrEnd[1024] = {};
	char aStrOut[1024] = {};
	int n = 0;
	int nc = 0;
	int d = 0;
	float f = 0.0f;

	int nCnt = 0;

	for (const char* p = fmt; *p != '\0'; p++, n++, nc++)
	{
		if (*p == '%')
		{
			p++;
			n++;

			switch (*p)
			{
			case 'd':

				nc += sprintf(&aStr[0], "%d", va_arg(ap, int));

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 'f':

				f = va_arg(ap, double);
				nc += sprintf(&aStr[0], "%f", f);

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 'c':

				nc += sprintf(&aStr[0], "%c", va_arg(ap, char));

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 's':
				p1 = va_arg(ap, const char*);
				nc += sprintf(&aStr[0], "%s", p1);

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case 'b':
				nc += sprintf(&aStr[0], "%d", va_arg(ap, bool));

				/*** 文字列を結合 ***/
				strcat(aStrEnd, &aStr[0]);

				break;

			case '~':

				p++;
				n++;

				sprintf(&aStr[0], "%c", *p);

				nCnt = atoi(&aStr[0]);

				p++;
				n++;

				switch (*p)
				{
				case 'd':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						nc += sprintf(&aStr[0], "%d ", va_arg(ap, int));

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 'f':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						f = va_arg(ap, double);
						nc += sprintf(&aStr[0], "%f ", f);

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 'c':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						nc += sprintf(&aStr[0], "%c ", va_arg(ap, char));

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 's':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						p1 = va_arg(ap, const char*);
						nc += sprintf(&aStr[0], "%s ", p1);

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				case 'b':

					for (int nCntPrint = 0; nCntPrint < nCnt; nCntPrint++)
					{
						memset(aStr, 0, sizeof aStr);

						nc += sprintf(&aStr[0], "%d ", va_arg(ap, bool));

						/*** 文字列を結合 ***/
						strcat(aStrEnd, &aStr[0]);
					}

					break;

				default:

					break;
				}

				break;

			default:

				break;
			}
		}
		else
		{
			/*** 文字列を結合 ***/
			sprintf(&aStr[0], "%c", *p);
			//strncpy(&aStrCopy[0], &aStr2[n], 1);

			strcat(&aStrEnd[0], &aStr[0]);
		}

		memset(aStr, 0, sizeof aStr);
	}

	/*** クリーンアップ ***/
	va_end(ap);

	aStrEnd[nc + 1] = '\0';

	/*** 文字列を結合 ***/
	strcat_s(aStrOut, aStrEnd);

	int nReturn = MessageBox(hWnd, &aStrOut[0], pCaption, nType);
	return nReturn;
#endif
}

//==================================================================================
// --- 二点間のLerp変換 ---
//==================================================================================
D3DXVECTOR3 MyMathUtil::GetPTPLerp(D3DXVECTOR3 Start, D3DXVECTOR3 End, float s)
{
	D3DXVECTOR3 returnLerp = D3DXVECTOR3(0, 0, 0);

	// ベクトルの差分を求める
	returnLerp = End - Start;

	// 差分をsを使用して割合計算
	returnLerp *= s;

	// 開始位置から加算して位置を取得
	returnLerp += Start;

	return returnLerp;
}

//==================================================================================
// --- 二色間のLerp変換 ---
//==================================================================================
D3DXCOLOR MyMathUtil::GetColLerp(D3DXCOLOR Start, D3DXCOLOR End, float s)
{
	D3DXCOLOR returnCol = D3DXCOLOR(1, 1, 1, 1);

	returnCol = End - Start;
	returnCol *= s;
	returnCol += Start;

	return returnCol;
}

//==================================================================================
// --- ポリゴン描画(テクスチャバッファ使用) ---
//==================================================================================
void MyMathUtil::DrawPolygon(LPDIRECT3DDEVICE9 pDevice,
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff,
	LPDIRECT3DTEXTURE9 pTexture,
	UINT VertexFormatSize,
	DWORD FVF,
	int nNumPolygon,
	UINT OffSet)
{
	// NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていません！"));
		return;
	}

	// NULLCHECK
	if (pVtxBuff == nullptr)
	{
		OutputDebugString(TEXT("pVtxBuffが設定されていません！"));
		return;
	}

	for (int nCntPoly = OffSet; nCntPoly < nNumPolygon; nCntPoly++)
	{
		/*** 頂点バッファをデータストリームに設定 ***/
		pDevice->SetStreamSource(0, pVtxBuff, 0, VertexFormatSize);

		/*** 頂点フォーマットの設定 ***/
		pDevice->SetFVF(FVF);

		/*** テクスチャの設定 ***/
		pDevice->SetTexture(0, pTexture);

		/*** ポリゴンの描画 ***/
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			4 * nCntPoly,								// 描画する最初の頂点インデックス
			2);											// 描画するプリミティブの数
	}
}

//==================================================================================
// --- ポリゴン描画(配列テクスチャバッファ使用) ---
//==================================================================================
void MyMathUtil::DrawPolygonTextureArray(LPDIRECT3DDEVICE9 pDevice,
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff,
	LPDIRECT3DTEXTURE9* pTexture,
	UINT nNumTexture,
	int* pArrayTexNo,
	UINT VertexFormatSize,
	DWORD FVF,
	int nNumPolygon,
	UINT OffSet)
{
	// NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていません！"));
		return;
	}

	// NULLCHECK
	if (pVtxBuff == nullptr)
	{
		OutputDebugString(TEXT("pVtxBuffが設定されていません！"));
		return;
	}

	// NULLCHECK
	if (pArrayTexNo == nullptr)
	{
		OutputDebugString(TEXT("pArrayTexNoが設定されていません！"));
		return;
	}

	for (int nCntPoly = OffSet; nCntPoly < nNumPolygon; nCntPoly++)
	{
		/*** 頂点バッファをデータストリームに設定 ***/
		pDevice->SetStreamSource(0, pVtxBuff, 0, VertexFormatSize);

		/*** 頂点フォーマットの設定 ***/
		pDevice->SetFVF(FVF);

		/*** テクスチャの設定 ***/
		pDevice->SetTexture(0, pTexture[pArrayTexNo[nCntPoly]]);

		/*** ポリゴンの描画 ***/
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			4 * nCntPoly,								// 描画する最初の頂点インデックス
			2);											// 描画するプリミティブの数
	}
}

//==================================================================================
// --- ポリゴン描画(GetTexture使用) ---
//==================================================================================
void MyMathUtil::DrawPolygonTextureFromIndex(LPDIRECT3DDEVICE9 pDevice,
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff,
	int nIdxTexture,
	UINT VertexFormatSize,
	DWORD FVF,
	int nNumPolygon,
	UINT OffSet)
{
	// NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていません！"));
		return;
	}

	// NULLCHECK
	if (pVtxBuff == nullptr)
	{
		OutputDebugString(TEXT("pVtxBuffがnullですわ～！おバカですわ～！"));
		return;
	}

	for (int nCntPoly = OffSet; nCntPoly < nNumPolygon; nCntPoly++)
	{
		/*** 頂点バッファをデータストリームに設定 ***/
		pDevice->SetStreamSource(0, pVtxBuff, 0, VertexFormatSize);

		/*** 頂点フォーマットの設定 ***/
		pDevice->SetFVF(FVF);

		/*** テクスチャの設定 ***/
		pDevice->SetTexture(0, GetTexture(nIdxTexture));

		/*** ポリゴンの描画 ***/
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			4 * nCntPoly,								// 描画する最初の頂点インデックス
			2);											// 描画するプリミティブの数
	}
}

//==================================================================================
// --- モデル描画 ---
//==================================================================================
void MyMathUtil::Draw3DModelFromXFile(LPDIRECT3DDEVICE9 pDevice,
	D3DXMATERIAL *pMat,
	DWORD dwNumMat,
	LPDIRECT3DTEXTURE9 *ppTexture,
	LPD3DXMESH pMesh)
{
	// NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていません！"));
		return;
	}

	// NULLCHECK
	if (pMat == nullptr)
	{
		OutputDebugString(TEXT("pMatがないよ！"));
		return;
	}

	// NULLCHECK
	if (ppTexture == nullptr)
	{
		OutputDebugString(TEXT("ppTextureが...ぐっ！"));
		return;
	}

	// NULLCHECK
	if (pMesh == nullptr)
	{
		OutputDebugString(TEXT("pMeshが...無い。"));
		return;
	}

	for (int nCntMat = 0; nCntMat < dwNumMat; nCntMat++)
	{
		/*** マテリアルの設定 ***/
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*** テクスチャの設定 ***/
		pDevice->SetTexture(0, ppTexture[nCntMat]);

		/*** モデル(パーツ)の描画 ***/
		pMesh->DrawSubset(nCntMat);
	}
}

//==================================================================================
// --- モデル描画(ModelData使用) ---
//==================================================================================
#ifdef MODELDATA_DEFINED
void MyMathUtil::Draw3DModelFromModelData(LPDIRECT3DDEVICE9 pDevice,
	LPMODELDATA pModelData)
{
	// NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていません！"));
		return;
	}

	// NULLCHECK
	if (pModelData == nullptr)
	{
		OutputDebugString(TEXT("pModelDataがnullだよ～"));
		return;
	}

	D3DMATERIAL9 matDef;				// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;					// マテリアルデータへのポインタ

		/*** 現在のマテリアルを保存 ***/
	pDevice->GetMaterial(&matDef);

	/*** マテリアルデータへのポインタを取得 ***/
	pMat = (D3DXMATERIAL*)pModelData->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pModelData->dwNumMat; nCntMat++)
	{
		/*** マテリアルの設定 ***/
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*** テクスチャの設定 ***/
		pDevice->SetTexture(0, pModelData->apTexture[nCntMat]);

		/*** モデル(パーツ)の描画 ***/
		pModelData->pMesh->DrawSubset(nCntMat);
	}

	/*** 保存していたマテリアルを戻す！ ***/
	pDevice->SetMaterial(&matDef);
}
#endif

//==================================================================================
// --- マトリックス計算 ---
//==================================================================================
void MyMathUtil::CalcWorldMatrix(LPDIRECT3DDEVICE9 pDevice,
	D3DXMATRIX* mtxWorld,
	D3DXVECTOR3 pos,
	D3DXVECTOR3 rot,
	bool bSetTransform)
{
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用マトリックス

	/*** ワールドマトリックスの初期化 ***/
	D3DXMatrixIdentity(mtxWorld);

	/*** 向きを反映 (※ 位置を反映する前に必ず行うこと！) ***/
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y,			// Y軸回転
		rot.x,			// X軸回転
		rot.z);			// Z軸回転

	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	/*** 位置を反映 (※ 向きを反映したのちに行うこと！) ***/
	D3DXMatrixTranslation(&mtxTrans,
		pos.x,
		pos.y,
		pos.z);

	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);

	// ワールドマトリックスの適用をする場合
	if (bSetTransform)
	{
		// 各NULLCHECK
		if (pDevice == nullptr)
		{
			OutputDebugString(TEXT("pDeviceが設定されていませんよ！"));
			return;
		}

		/*** ワールドマトリックスの設定 ***/
		pDevice->SetTransform(D3DTS_WORLD, mtxWorld);
	}
}

//==================================================================================
// --- マトリックス計算 (親マトリックス使用) ---
//==================================================================================
void MyMathUtil::CalcWorldMatrixFromParent(LPDIRECT3DDEVICE9 pDevice,
	D3DXMATRIX* mtxWorld,
	D3DXMATRIX* mtxParent,
	D3DXVECTOR3 pos,
	D3DXVECTOR3 rot,
	bool bSetTransform)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// パーツのワールドマトリックス初期化
	D3DXMatrixIdentity(mtxWorld);

	// パーツの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y,
		rot.x,
		rot.z);

	// かけ合わせる
	D3DXMatrixMultiply(mtxWorld,
		mtxWorld,
		&mtxRot);

	// パーツの位置(オフセット)を反映
	D3DXMatrixTranslation(&mtxTrans,
		pos.x,
		pos.y,
		pos.z);

	// かけ合わせる
	D3DXMatrixMultiply(mtxWorld,
		mtxWorld,
		&mtxTrans);

	// 算出した「パーツのワールドマトリックス」と「親のマトリックス」をかけ合わせる
	D3DXMatrixMultiply(mtxWorld,
		mtxWorld,
		mtxParent);

	// ワールドマトリックスの適用をする場合
	if (bSetTransform)
	{
		// 各NULLCHECK
		if (pDevice == nullptr)
		{
			OutputDebugString(TEXT("pDeviceが設定されていませんよ！"));
			return;
		}

		/*** ワールドマトリックスの設定 ***/
		pDevice->SetTransform(D3DTS_WORLD, mtxWorld);
	}
}

//==================================================================================
// ---シャドウマトリックスの作成処理 ---
//==================================================================================
void MyMathUtil::CreateShadowMatrix(LPDIRECT3DDEVICE9 pDevice, D3DXMATRIX *pIn, D3DXMATRIX *pOut)
{
	// 各NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていませんよ！"));
		return;
	}

	if (pIn == nullptr)
	{
		OutputDebugString(TEXT("pMtxが設定されていませんよ！"));
		return;
	}

	if (pOut == nullptr)
	{
		OutputDebugString(TEXT("pOutが設定されていませんよ！"));
		return;
	}

	D3DLIGHT9 light;
	D3DXVECTOR3 pos, nor;
	D3DXVECTOR4 LightPos;
	D3DXPLANE plane;

	// ライトの位置を設定
	pDevice->GetLight(0, &light);
	LightPos = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

	// 平面作成
	pos = D3DXVECTOR3(0, 100, 0);
	nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&plane, &pos, &nor);

	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(pOut);

	// シャドウマトリックスの作成
	D3DXMatrixShadow(pOut, &LightPos, &plane);
	D3DXMatrixMultiply(pOut, pIn, pOut);
}

//==================================================================================
// --- Zテストの設定 ---
//==================================================================================
void MyMathUtil::SetEnableZFunction(LPDIRECT3DDEVICE9 pDevice, bool bEnable)
{
	// 各NULLCHECK
	if (pDevice == nullptr)
	{
		OutputDebugString(TEXT("pDeviceが設定されていませんよ！"));
		return;
	}

	if (bEnable == true)
	{
		/*** Zテストを有効にする ***/
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
	else
	{
		/*** Zテストを無効にする ***/
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	}
}