#include<stdio.h>
#include<string.h>
#include "contact.h"
#include "pds.h"
struct PdsInfo pdsInfo;
int pds_create(char *repo_name,char *ndx_name)
{
	pdsInfo.repo_fptr = fopen(repo_name,"ab+");
	strcpy(pdsInfo.repo_name,repo_name);
	pdsInfo.ndx_fptr = fopen(ndx_name,"ab+");
	if((pdsInfo.repo_fptr!=NULL)&&(pdsInfo.repo_fptr!=NULL))
		return PDS_SUCCESS;
	else
		return PDS_CREATE_ERROR;
}
int pds_open(char *repo_name, char *ndx_name)
{
	struct PdsNdxInfo c;
	struct Contact e;
	pdsInfo.repo_fptr = fopen(repo_name,"ab+");
	pdsInfo.ndx_fptr = fopen(ndx_name,"ab+");
	fseek(pdsInfo.ndx_fptr,0,SEEK_SET);
        while(fread(&c,sizeof(struct PdsNdxInfo),1,pdsInfo.ndx_fptr)==1)
        {
           	printf("1st=%d\t%d\n",c.key,c.offset);
        	pdsInfo.ndxEntries[pdsInfo.num_recs].key = c.key;
        	pdsInfo.ndxEntries[pdsInfo.num_recs++].offset = c.offset;

                
        }
	pdsInfo.ndxEntries[pdsInfo.num_recs].key = 0;
	pdsInfo.ndxEntries[pdsInfo.num_recs++].offset = 0;
	while(fread(&e,sizeof(struct Contact),1,pdsInfo.repo_fptr)==1)
	{
		printf("d=%d %s\n",e.contact_id,e.mphone);
	}
	/*fclose(pdsInfo.ndx_fptr);
	
	pdsInfo.ndx_fptr = fopen(ndx_name,"w");
	if((pdsInfo.repo_fptr!=NULL)&&(pdsInfo.repo_fptr!=NULL))
	{
		pdsInfo.num_recs = 0;
                return PDS_SUCCESS;
	}
        else
                return PDS_CREAT*/
}
int pds_store(struct Contact *c)
{
	if(pds_search_by_key((*c).contact_id,c)==PDS_REC_NOT_FOUND)
	{
	fseek(pdsInfo.repo_fptr,0,SEEK_END);

	int x = fwrite(c,sizeof(struct Contact),1,pdsInfo.repo_fptr);
	pdsInfo.ndxEntries[pdsInfo.num_recs].key = (*c).contact_id;
	pdsInfo.ndxEntries[pdsInfo.num_recs++].offset = ftell(pdsInfo.repo_fptr);
	printf("Entry\n");
	//printf("off=%ld\n",ftell(pdsInfo.repo_fptr));
	if(x==1)
	{
		printf("rec=%d\n",pdsInfo.num_recs);
		
		return PDS_SUCCESS;
	}
	else
		return PDS_STORE_ERROR;
	}
		return PDS_DUPLICATE_RECORD;
}
int pds_close()
{
	int i,j;
	struct PdsNdxInfo d;
	fseek(pdsInfo.repo_fptr,0,SEEK_SET);
	fclose(pdsInfo.repo_fptr);
	for(j=pdsInfo.num_recs-1;j>=0;j--)
	{
		if((pdsInfo.ndxEntries[j].key==0)&&(pdsInfo.ndxEntries[j].offset==0))
		{
			i = j+1;
			break;
		}
	}
	for(i=j+1;i<pdsInfo.num_recs;i++)
	{
		printf("s%d\n",pdsInfo.ndxEntries[i].key);
		fwrite(&pdsInfo.ndxEntries[i],sizeof(struct PdsNdxInfo),1,pdsInfo.ndx_fptr);
		
	}
	fseek(pdsInfo.ndx_fptr,0,SEEK_SET);
        fclose(pdsInfo.ndx_fptr);

}
int pds_search_by_key( int key, struct Contact *c )
{
	struct Contact c1;
	int i;
	for(i=0;i<pdsInfo.num_recs;i++)
	{
		if(key==pdsInfo.ndxEntries[i].key)
		{
			if(i==0)
			{
				fseek(pdsInfo.repo_fptr,0,SEEK_SET);
				fread(c,sizeof(struct Contact),1,pdsInfo.repo_fptr);
				return PDS_SUCCESS;
			}
			else
			{
				fseek(pdsInfo.repo_fptr,pdsInfo.ndxEntries[i-1].offset,SEEK_SET);
				fread(c,sizeof(struct Contact),1,pdsInfo.repo_fptr);
                                return PDS_SUCCESS;

			}
		}
		
	}
	/*fseek(pdsInfo.repo_fptr,0,SEEK_SET);
	while(fread(c,sizeof(struct Contact),1,pdsInfo.repo_fptr)==1)
	{
		if(key==(*c).contact_id)
		{
			return PDS_SUCCESS;
		}
	}*/
	return PDS_REC_NOT_FOUND;
}

/*int main()
{
return 0;
}*/

