#include<stdio.h>
#include<string.h>
#include "contact.h"
#include "pds.h"
struct PdsInfo pdsInfo;
int pds_create(char *repo_name)
{
	pdsInfo.repo_fptr = fopen(repo_name,"ab+");
	strcpy(pdsInfo.repo_name,repo_name);
	return PDS_SUCCESS;
}
int pds_open(char *repo_name)
{
	pdsInfo.repo_fptr = fopen(repo_name,"ab+");
	return PDS_SUCCESS;
}
int pds_store(struct Contact *c)
{
	if(pds_search_by_key((*c).contact_id,c)==PDS_REC_NOT_FOUND)
	{
	
	int x = fwrite(c,sizeof(struct Contact),1,pdsInfo.repo_fptr);
	if(x==1)
	{
		return PDS_SUCCESS;
	}
	else
		return PDS_STORE_ERROR;
	}
		return PDS_DUPLICATE_RECORD;
}
int pds_search_by_key( int key, struct Contact *c )
{
	struct Contact c1;
	fseek(pdsInfo.repo_fptr,0,SEEK_SET);
	while(fread(c,sizeof(struct Contact),1,pdsInfo.repo_fptr)==1)
	{
		if(key==(*c).contact_id)
		{
			return PDS_SUCCESS;
		}
	}
	return PDS_REC_NOT_FOUND;
}

/*int main()
{
return 0;
}*/

