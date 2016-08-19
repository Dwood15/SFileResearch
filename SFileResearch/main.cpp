#include "main.h"

using namespace std;


void readSFF(ifstream &ifn, form& sFF)
{
	ifn.read((char*)&sFF, sizeof(FOURCC));
	ifn.read((char*)&sFF.chunkSize, sizeof(FOURCC));
	ifn.read((char*)&sFF.formID, sizeof(FOURCC));

	sFF.lists = (dataLists *) malloc((size_t)(sFF.chunkSize - 4));
	ifn.read((char*)sFF.lists, sFF.chunkSize - 4);

	if (ifn.fail())
		throw;
	else if (ifn.eofbit)
		printf("Eofbit found! - Continuing with program\n");
	else
		printf("Looks like we've got some leftovers!");
}

void verifyData(form &sFF)
{
	printf("Main chunk tag: %.4s\nSize of file (bytes): %d\n", (char *)&sFF, (int)sFF.chunkSize);
	printf("Form ID: %.4s\n", (char *)&sFF.formID);

	printf("Verify INFO List!\n\tChunk Id:%.4s\n", (char*)&sFF.lists->infoList.chunkId);
	printf("\tList ID: %.4s\n", (char*)&sFF.lists->infoList.listID);
	printf("\tChunk size:%d\n", sFF.lists->infoList.chunkSize);

	printf("Verify INFO List!\n\tChunk Id:%.4s\n", (char*)&sFF.lists->sdtaList.chunkId);
	printf("\tList ID: %.4s\n", (char*)&sFF.lists->sdtaList.listID);
	printf("\tChunk size:%d\n", sFF.lists->sdtaList.chunkSize);
	printf("\tSize of data:%d\n", sizeof(sFF.lists->sdtaList.listData));

	printf("Verify INFO List!\n\tChunk Id:%.4s\n", (char*)&sFF.lists->pdtaList.chunkId);
	printf("\tList ID: %.4s\n", (char*)&sFF.lists->pdtaList.listID);
	printf("\tChunk size:%d\n", sFF.lists->pdtaList.chunkSize);
	printf("\tSize of data:%d\n", sizeof(sFF.lists->pdtaList.listData));
}

void organizeTopLists(form &sFF)
{
	list * il = &sFF.lists->infoList;
	list * next = (list*)((int)il + (il->chunkSize + 8));
	list * after = (list*)((int)next + (next->chunkSize + 8));
}



int main()
{
	char file[] = "D:\\Valence Gaming\\Virtual Conductance\\SoundFonts\\TOH\\tohShort.sf2";
	printf("testing\n");
	ifstream ifn = ifstream(file, std::iostream::binary | ios::in);
	form sFF;
	list * iList, * sdtaList, * pdList;
	infoList il;
	pdtaList pList;
	SHORT phdrCt = -1;
	try
	{
		readSFF(ifn, sFF);
		verifyData(sFF);
		organizeTopLists(sFF);
		getListLocations(sFF, iList, sdtaList, pdList);
		if (getInfoListSubChunks(iList, il)) {
			printf("Got proper list data info!\n");
			printf("File name: %.*s\n", il.inam_ck->chunkSize, (char*)&il.inam_ck->data);
		}
		else
			printf("Failed getting the proper Info LIST data!");
			
		if (getPDTAListSubChunks(pdList, pList)) {
			sfSample * current = 0x0;
			for (int i = 0; i < pList.counts[8]; i++) {
				current = (sfSample*) (&(pList.members[8]->data) + (i * 46));
				printf("Sample Header Name: %.*s\n", 20, current->achSampleName);
			}
		}
		else 
			printf("failed getting the proper Info LIST data!");
	}
	catch(...)
	{
		printf("had some trouble!");
	}
	system("pause");
	return 0;
}

