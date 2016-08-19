#pragma once
#include "sfontsubtypes.h"
//used in the iver chunk.
struct sfVersionTag {
	WORD wMajor;
	WORD wMinor;
};

#pragma pack(push)
#pragma pack(2)
typedef struct {
	char achPresetName[20];
	WORD wPreset;
	WORD wBank;
	WORD wPresetBagNdx;
	DWORD dwLibrary;
	DWORD dwGenre;
	DWORD dwMorphology;
} sfPresetHeader;

typedef struct {
	WORD wGenNdx;
	WORD wModNdx;
} sfPresetBag;

typedef struct
{
	SFModulator sfModSrcOper;
	SFGenerator sfModDestOper;
	SHORT modAmount;
	SFModulator sfModAmtSrcOper;
	SFTransform sfModTransOper;
} sfModList;

typedef struct
{
	SFGenerator sfGenOper;
	genAmountType genAmount;
} sfGenList;

typedef struct 
{
	CHAR achInstName[20];
	WORD wInstBagNdx;
} sfInst;

typedef struct 
{
	CHAR achSampleName[20];
	DWORD dwStart;
	DWORD dwEnd;
	DWORD dwStartloop;
	DWORD dwEndloop;
	DWORD dwSampleRate;
	BYTE byOriginalKey;
	CHAR chCorrection;
	WORD wSampleLink;
	SFSampleLink sfSampleType;
} sfSample;
#pragma pack(pop)

struct sfInstBag
{
	WORD wInstGenNdx;
	WORD wInstModNdx;
};

struct sfInstModList
{
	SFModulator sfModSrcOper;
	SFGenerator sfModDestOper;
	SHORT modAmount;
	SFModulator sfModAmtSrcOper;
	SFTransform sfModTransOper;
};

struct sfInstGenList
{
	SFGenerator sfGenOper;
	genAmountType genAmount;
};

DWORD getSizeByIndex(DWORD idx);
DWORD getChunkData(chunk * (&chnk), chunk * (&nextChunk), DWORD size);