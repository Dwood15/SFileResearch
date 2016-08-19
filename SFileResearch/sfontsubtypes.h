#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <intrin.h>
#include "Windows.h"
#include "sfontenumerations.h"

#pragma pack(push)
#pragma pack(2)
typedef struct {
	FOURCC chunkId;
	DWORD chunkSize;
	void * data;
} chunk;

typedef struct
{
	BYTE byLo;
	BYTE byHi;
} rangesType;

typedef union {
	rangesType ranges;
	SHORT shAmount;
	WORD wAmount;
} genAmountType;
#pragma pack(pop)