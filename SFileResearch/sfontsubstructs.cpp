#include "sfontsubstructs.h"

ULONG getSizeByIndex(DWORD idx) {
	DWORD sz = 0;
	switch (idx) {
	case 0:
		if (38 == sizeof(sfPresetHeader))
			return sizeof(sfPresetHeader);
		return 38;
		//sizeof returns the padded / alignment size.
		//return sizeof(sfPresetHeader) - 2; //-2 for padding
		break;
	case 1:
		return sizeof(sfPresetBag);
		break;
	case 2: //2 => PMOD
	case 6: //6 => IMOD
		if (10 == sizeof(sfModList))
			return sizeof(sfModList);
		return 10;
		break;
	case 3:
		//This string of logic is kept for now
		//until I ensure each type is aligned correctly
		//according to the spec.
		sz = sizeof(sfGenList);
		if (sz == 4)
			return sz;
		return 4;
		break;
	case 4: 
		sz = sizeof(sfInst);
		if (sz == 22)
			return sz;
		return 22;
		break;
	case 5: 
		sz = sizeof(sfInstBag);
		if (sz == 4)
			return sz;
		return 4;
		break;
	case 7:
		return sizeof(sfInstGenList);
		break;
	case 8:
		sz = sizeof(sfSample);
		if (sz == 46)
			return sz;
		return 46;
		break;
	default:
		printf("Passed invalid index by gSBI");
		return 0x0;
		break;
	}

}

DWORD getChunkData(chunk * (&chnk), chunk * (&nextChunk), DWORD size) {

	if (!size) {
		printf("Invalid size of 0 for index: %d", size);
		return -1;
	}
	else if (chnk->chunkSize % size) {
		printf("\n\tBad chunkSize! %d\n", chnk->chunkSize);
		return -1;
	}

	if (nextChunk) {
		DWORD dLoc = (DWORD)&chnk->data + chnk->chunkSize + 8;
		DWORD dta = (DWORD)&nextChunk->data;
		//if ((DWORD)&chnk->data + chnk->chunkSize + 8 == (DWORD)&nextChunk->data)

		if (dLoc == dta)
			return chnk->chunkSize / size;
	}
	else {
		//Presumably with a null nextChunk we are at the end of the line.
		return chnk->chunkSize / size;
	}

	printf("Invalid File data! I hate the app used to create this!");
	return -1;
}
