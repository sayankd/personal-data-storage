#include<stdio.h>
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 50
#define MAX_PHONE_LEN 11

struct Contact{
	int contact_id;
	char cname[MAX_NAME_LEN];
	char mphone[MAX_PHONE_LEN];
	char email[MAX_EMAIL_LEN];
};
int main()
{
struct Contact c;
FILE *fp;
fp = fopen("pds_demo.dat","rb");

if(fp == NULL){

   puts("Cannot open file");

}

//fp = fopen("MYContacts.DAT","rb");


while(fread(&c,sizeof(c),1,fp)==1){

   printf("%d %s",c.contact_id,c.cname);

}

fclose(fp);
return 0;
}

