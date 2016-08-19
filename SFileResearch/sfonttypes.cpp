#include "main.h"

//These are debugged functions, not likely to change without a rewrite.
chunk* getNextChunk(chunk * il) {
	if (!il)
		return il;

	return (chunk*)((int)il + (il->chunkSize + 8));
}

bool getListLocations(form &sFF, list* (&ifo), list * (&sdta), list * (&pdta))
{
	if (ifo == NULL)
		return false;

	ifo = &sFF.lists->infoList;
	sdta = (list*)((int)ifo + (ifo->chunkSize + 8));
	pdta = (list*)((int)sdta + (sdta->chunkSize + 8));

	return true;
}

bool getPDTAListSubChunks(list * pdta, pdtaList &pList)
{
	if (pdta->listID != _byteswap_ulong((unsigned long)accepted_formIDs::pdta))
		return false;

	pList.chunkId = &pdta->chunkId;
	pList.chunkSize = &pdta->chunkSize;
	pList.listID = &pdta->listID;

	printf("Getting PDTAList Sub-chunks aligned properly!");

	chunk * currentChunk = (chunk*)&pdta->listData;

	SHORT currentFound = 0;

	while (pList.foundOp < PDTACode) {
		switch (currentChunk->chunkId) {
		case (FOURCC)bswapped_pdtaIDs::phdr:
			pList.foundOp |= 0x1;
			pList.members[0] = currentChunk;

			if (pList.counts[0] < 2)
				throw; //TODO: Make useful throws.
			printf("\tFound all the phdr sections!\n");
			break;

		case (FOURCC)bswapped_pdtaIDs::pbag:
			pList.foundOp |= 0x2;
			pList.members[1] = currentChunk;
			printf("\tFound all the pbag sections!\n");
			break;

		case (FOURCC)bswapped_pdtaIDs::pmod:
			pList.foundOp |= 0x4;
			pList.members[2] = currentChunk;
			break;

		case (FOURCC)bswapped_pdtaIDs::pgen:
			pList.foundOp |= 0x8;
			pList.members[3] = currentChunk;
			break;

		case (FOURCC)bswapped_pdtaIDs::inst:
			pList.foundOp |= 0x10;
			pList.members[4] = currentChunk;
			break;

		case (FOURCC)bswapped_pdtaIDs::ibag:
			pList.foundOp |= 0x20;
			pList.members[5] = currentChunk;
			break;

		case (FOURCC)bswapped_pdtaIDs::imod:
			pList.foundOp |= 0x40;
			pList.members[6] = currentChunk;
			break;

		case (FOURCC)bswapped_pdtaIDs::igen:
			pList.foundOp |= 0x80;
			pList.members[7] = currentChunk;
			break;

		case (FOURCC)bswapped_pdtaIDs::shdr:
			pList.foundOp |= 0x100;
			pList.members[8] = currentChunk;
			break;

		default:
			printf("Error reading the pdtaList! Found a chunk id we didn't expect!");
			printf("Found an incompatible sf file tag: %.4s\n", (char*)&currentChunk->chunkId);
			throw; //TODO: Make useful throws.
			break;

		}

		currentChunk = getNextChunk(currentChunk);
	}
	//This section requires that all the rest are FOUND
	for (int i = 0; i < 9; i++)
	{
		chunk * next = getNextChunkFromPDTA(i, pList);
		pList.counts[i] = getChunkData(pList.members[i], next, getSizeByIndex(i));
	}
	return true;
}

//The goal is to allow an out of-order PDTA.
chunk * getNextChunkFromPDTA(SHORT idx, pdtaList &pList)
{				 
		//We can just do memory comparisons if we already have a full pList.
		chunk * curr = pList.members[idx];
		chunk * test;

		if (idx != 0)
			test = pList.members[0];
		else
			test = pList.members[1];

		for (int i = 0; i < 9; i++) {
			if ((test > curr) && (test > pList.members[i]) && (curr < pList.members[i])) 			{
				test = pList.members[i];
			}
			else if (test <= curr && idx != i) {
				test = pList.members[i];
			}
		}

		if (test <= curr)
			return (chunk *)0x0;
		else
			return test;
}

//fulllist - basically, we only care about the 3 mandatory ifil sections. Optionals are ignored by default.
bool getInfoListSubChunks(list * ifo, infoList &ifoList, bool fullList)
{
	if (ifo->listID != _byteswap_ulong((unsigned long)accepted_formIDs::info))
		return false;

	ifoList.chunkId = &ifo->chunkId;
	ifoList.chunkSize = &ifo->chunkSize;
	ifoList.listID = &ifo->listID;

	printf("Getting InfoList Sub-chunks aligned properly!");

	chunk * currentChunk = (chunk*)&ifo->listData;

	LONG max = 0x0;
	LONG found = 0x0;

	if (fullList)
		max = 0x7ff;
	else
		max = 0x7;
	//remember, the 3 mandatory parts of the file are: ifil, ising, and inam chunks!
	//search for each type of enumer first.
	while (found < max) {
		switch (currentChunk->chunkId) {
			case (FOURCC)bswapped_infoIDs::ifil:
				ifoList.ifil_ck = currentChunk;
				found |= 0x1; // the first bit is ifil's.
				break;
			case (FOURCC)bswapped_infoIDs::isng:
				ifoList.isng_ck = currentChunk;
				found |= 0x2; //second bit
				break;
			case (FOURCC)bswapped_infoIDs::inam:
				ifoList.inam_ck = currentChunk;
				found |= 0x4; //third bit
				break;
			case (FOURCC)bswapped_infoIDs::irom:
				ifoList.irom_ck = currentChunk;
				found |= 0x8;
				break;
			case (FOURCC)bswapped_infoIDs::iver:
				ifoList.iver_ck = currentChunk;
				found |= 0x10;
				break;
			case (FOURCC)bswapped_infoIDs::icrd:
				ifoList.icrd_ck = currentChunk;
				found |= 0x20;
				break;
			case (FOURCC)bswapped_infoIDs::ieng:
				ifoList.ieng_ck = currentChunk;
				found |= 0x40;
				break;
			case (FOURCC)bswapped_infoIDs::iprd:
				ifoList.iprd_ck = currentChunk;
				found |= 0x80;
				break;
			case (FOURCC)bswapped_infoIDs::icop:
				ifoList.icop_ck = currentChunk;
				found |= 0x100;
				break;
			case (FOURCC)bswapped_infoIDs::icmt:
				ifoList.icmt_ck = currentChunk;
				found |= 0x200;
				break;
			case (FOURCC)bswapped_infoIDs::isft:
				ifoList.isft_ck = currentChunk;
				found |= 0x400;
				break;
			default:
				printf("Found an incompatible sf file tag: %.4s\n", (char*)&currentChunk->chunkId);
				printf("Exiting!\n");
				max = 0xFFFF;
				throw; //Temporary.
				break;
		}

		currentChunk = getNextChunk(currentChunk);
	}

	if (max == 0xFFFF)
		return false;
	else if (max == 0x7FF)
		return true;
	else if (max == 0x7 && !fullList)
		return true;
	else return false;
}