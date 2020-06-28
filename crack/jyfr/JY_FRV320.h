#include "stdafx.h"

#include <vector>
using namespace std;
typedef struct tagEyePos
{
	int    xleft;
	int    yleft;
	int    xright;
	int    yright;
} EyePos;


typedef struct tagFaceInfo_t
{
	EyePos  stEyePos;
	float   afFeature[400];
}   FaceInfo_t;
typedef  FaceInfo_t*  pFaceInfo_t;



BOOL WINAPI   JY_InitModule();
BOOL WINAPI   JY_FreeModule();



int  WINAPI  JY_ExtractFaceFeatureAuto( BYTE* pImage, 
	    int imgWidth, int imgHeight, pFaceInfo_t** pFaceInfoList, int* pFaceCount);

BOOL  WINAPI   JY_FreeFaceList( pFaceInfo_t*  pFaceInfoList, int nFaceCount);

int  WINAPI    JY_ExtractFaceFeatureManu( BYTE   *pImage, 
		int imgWidth, int imgHeight, EyePos stEye, float *pFeature);

BOOL WINAPI   JY_NormalizeRawFeature(float *pRawFea, float *pNormFea, int nDim);


float  WINAPI JY_CompareFaceVsFaceV2(float *pFea1, float *pFea2, int  nDim);


int  WINAPI   JY_FuseSimilarityForRecogn(float *pSimilarity, int nClassNum, 
		 int nCandidNum, int *pIdx, BYTE *pNewSimilarity);
