// ago4501patch.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#include <Wincrypt.h>
BOOL CalcMD5(BYTE* buf,int bufsize,BYTE* md5)
{
	HCRYPTPROV m_hCryptProv;
	HCRYPTHASH m_hHash;
	BOOL ret=FALSE;
	if(!CryptAcquireContext(&m_hCryptProv,NULL,NULL,PROV_RSA_FULL,0))
	{
		if(!CryptAcquireContext(&m_hCryptProv, NULL, NULL,PROV_RSA_FULL, CRYPT_NEWKEYSET))
		{
			return FALSE;
		}
	}

	if(!CryptCreateHash(m_hCryptProv, CALG_MD5, NULL, 0, &m_hHash))
	{
		goto md5_error;
	}
	if(!CryptHashData(m_hHash,buf,bufsize, 0))
	{
		goto md5_error;
	}
	DWORD dwDataLen=16;
	if(!CryptGetHashParam(m_hHash, HP_HASHVAL,(BYTE *) md5, &dwDataLen, 0))
	{
		goto md5_error;
	}
	ret=TRUE;
md5_error:
	CryptDestroyHash(m_hHash);
	CryptAcquireContext(&m_hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_DELETEKEYSET);
	return ret;
}


unsigned char data[16] = {
	0x7E, 0x97, 0xE9, 0x27, 0x82, 0xA8, 0xF6, 0xE1, 0xE9, 0x37, 0x9D, 0x1F, 0x8E, 0x8A, 0x14, 0xA7
};

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp=fopen("ago4501.dll","r+b");

	printf("����ǰ��ע�ⱸ�ݺ�Դ�ļ���ȡ��ֻ������\n");
	system("pause");

	if(fp)
	{
		printf("�ҵ�ago4501.dll������У��...\n");
		fseek(fp,0,SEEK_END);DWORD size=ftell(fp);rewind(fp);
		if(size)
		{
			BYTE *buf=new BYTE[size];
			fread(buf,1,size,fp);
			BYTE md5[16];
			CalcMD5(buf,size,md5);
			delete[] buf;
			if(memcmp(md5,data,16)==0)
			{
				fseek(fp,0xc053e,SEEK_SET);
				BYTE isEB=0xeb;
				if(fwrite(&isEB,1,1,fp)==1)
				{
					printf("�����ɹ�\n");
				}
				else
				{
					printf("����ʧ��\n");
				}
			}
			else
			{
				printf("�ļ�У�鲻��ȷ\n");
			}
		}
		else
		{
			printf("���ļ�\n");
		}
		fclose(fp);
	}
	else
	{
		printf("�Ҳ���ago4501.dll����ѱ��������ͬһĿ¼��\n");
	}
	system("pause");
	return 0;
}

