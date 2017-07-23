#include<stdio.h>
#include<string.h>
#include "contact.h"
#include "pds.h"
struct PdsInfo pdsInfo;
int pds_create(char *repo_name)
{
	pdsInfo.repo_fptr = fopen(repo_name,"a+b");
	strcpy(pdsInfo.repo_name,repo_name);
	return PDS_SUCCESS;
}
int pds_open(char *repo_name)
{
	pdsInfo.repo_fptr = fopen(repo_name,"a+b");
	return PDS_SUCCESS;
}
int pds_store(struct Contact *c)
{
	int x = fwrite(&c,sizeof(struct Contact),1,pdsInfo.repo_fptr);
	if(x==1)
	{
		return PDS_SUCCESS;
	}
	else
		return PDS_STORE_ERROR;
}

/*int main()
{
return 0;
}*/

