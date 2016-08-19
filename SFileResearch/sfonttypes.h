#pragma once

#include "sfontenumerations.h"
#include "sfontsubstructs.h"

#define PDTACode 0x1FF

typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef DWORD FOURCC;

//The first LIST object to show up in the main FORM struct.
//The reason it's pointers all the way down is beacause 
// I need some way of plugging in and aligning the objects in memory.
// additionally, I can do a bunch of stuff.
typedef struct {
	FOURCC * chunkId; //Always LIST
	DWORD * chunkSize;
	FOURCC * listID;

	/*
	TODO: Make it more like this:
	WORD count; // The number of discovered + valid chunks
	chunk * firstChunk; //A pointer to the first  chunk
	*/ 

	//REQUIRED CHUNKS
	chunk * ifil_ck; // REQUIRED - SoundFond RIFF file version
	chunk * isng_ck; // REQUIRED - SoundFont engine
	chunk * inam_ck; // REQUIRED - SoundFont bank Name

#pragma region DunWorryBoutIt
	//In fact, we are just going to ignore these.
	chunk * irom_ck; //Sound ROM Name
	chunk * iver_ck; //Sound ROM version
	chunk * icrd_ck; //Creation Date of Bank
	chunk * ieng_ck; //Sound Designers/Eng of the Bank
	chunk * iprd_ck; //Product Bank intended for
	chunk * icop_ck; //Copyright msgs
	chunk * icmt_ck; //Comments ont he bank
	chunk * isft_ck; //SoundFont tools used to make / alter bank.
#pragma endregion

} infoList;

typedef struct {
	FOURCC * chunkId; //Always LIST
	DWORD * chunkSize;
	FOURCC * listID;

	chunk * sampleChunk;
} sdtaList;

typedef struct {
	FOURCC * chunkId; //Always LIST
	DWORD * chunkSize;
	FOURCC * listID;
	
	chunk * members[9];
	DWORD counts[9];

	DWORD foundOp = 0x0;
	//TODO: Don't do this?
} pdtaList;


//Generic, Utility struct
typedef struct {
	FOURCC chunkId; //Always LIST
	DWORD chunkSize;
	FOURCC listID;
	void * listData; //location = &listID + 4
} list;

//Utility struct, useful for form struct.
typedef struct {
	list infoList; //chunkSize - 4
	list sdtaList;
	list pdtaList;
} dataLists;

typedef struct {
	FOURCC chunkId; //Always RIFF
	DWORD chunkSize;
	FOURCC formID;
	dataLists * lists;
} form;

//function declarations
chunk* getNextChunk(chunk * il);
chunk * getNextChunkFromPDTA(SHORT idx, pdtaList &pList);


bool getPDTAListSubChunks(list * pdta, pdtaList &pList);
bool getListLocations(form &sFF, list* (&ifo), list * (&sdta), list * (&pdta));
bool getInfoListSubChunks(list * ifo, infoList &ifoList, bool fullList = false);