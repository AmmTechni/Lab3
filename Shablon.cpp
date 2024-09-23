#include <stddef.h>
#include "Shablon.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

Shablon::Shablon() : mArrSize(0)
{

}

Shablon::~Shablon()
{
}


int Shablon::FindChar(unsigned char chr, const unsigned char* pTemplArr)
{
	if (!pTemplArr )
		return -1;
	for(unsigned int i=0; i<mArrSize; ++i)
	{
		if (chr == pTemplArr[i])
			return i;
	}
	return -1;
}

int Shablon::Encrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize)
{
	int j = 0;
	if (!psource || !pout || !sourcesize || !outsize || outsize< sourcesize)
		return -1;
	for (unsigned int i = 0; i < sourcesize; ++i)
	{
		pout[i] = mEncryptTable[1][ psource[i] ];
		//pout[i] = mEncryptTable[1][i];
		//j = FindChar(psource[i], mTemplateTable[0]);
		//if (j < 0)
		//	pout[i] = psource[i];
		//else
		//	pout[i] = mTemplateTable[1][j];
	}
	return 0;
}

int Shablon::Decrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize)
{
	int j = 0;
	if (!psource || !pout || !sourcesize || !outsize || outsize < sourcesize)
		return -1;
	for (unsigned int i = 0; i < sourcesize; ++i)
	{
		pout[i] = mDecryptTable[1][ psource[i] ];
		//pout[i] = mDecryptTable[1][i];
		//j = FindChar(psource[i], mTemplateTable[1]);
		//if (j < 0)
		//	pout[i] = psource[i];
		//else
		//	pout[i] = mTemplateTable[0][j];
	}
	return 0;
}

int Shablon::SetTemplateTable(const unsigned char* pEncodeArr, const unsigned char* pDecodeArr, size_t size)
{
	if (!pEncodeArr || !pDecodeArr || !size)
		return -1;

	std::memcpy(mEncryptTable[0], pEncodeArr, size);
	std::memcpy(mEncryptTable[1], pDecodeArr, size);

	std::memcpy(mDecryptTable[0], mEncryptTable[1], size);
	std::memcpy(mDecryptTable[1], mEncryptTable[0], size);

	unsigned int i, j;

	for (i = 0; i < size; ++i)
	{
		for (j = i; j < size; ++j)
		{
			if (i == mDecryptTable[0][j])
				break;
		}
		if (j != i)
		{
			std::swap(mDecryptTable[0][j], mDecryptTable[0][i]);
			std::swap(mDecryptTable[1][j], mDecryptTable[1][i]);
		}
	}

	std::cout << "\n\nSetTemplateTable\n\n";

	for (i = 0; i < TemplateSize; ++i)
	{
		std::cout << (unsigned int)mDecryptTable[0][i] << ' ';
	}

	std::cout << "\n\nSetTemplateTable second\n\n";

	for (i = 0; i < TemplateSize; ++i)
	{
		std::cout << (unsigned int)mDecryptTable[1][i] << ' ';
	}

	std::cout << "\n\nSetTemplateTable end\n\n";
	mArrSize = size;


	return 0;
}
