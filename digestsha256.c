/*
	cc -o digestsha256 digestsha256.c `libgcrypt-config --cflags --libs`
*/

#include<stdio.h>
#include<gcrypt.h>
#define buffsize 1024

int main(int argc,char **argv)	{
	FILE *input;
	unsigned char *buff;
	unsigned char *digest;
	int l,i;
	if(argc > 1)	{
		input = fopen(argv[1],"r");
		if(input != NULL)	{
			fseek(input,0,SEEK_END);
			l = ftell(input);
			fseek(input,0,SEEK_SET);
			buff = calloc(l,sizeof( unsigned char));
			digest = calloc(32,sizeof( unsigned char));
			fread(buff,l,1,input);
			fclose(input);
			gcry_md_hash_buffer(GCRY_MD_SHA256,digest,buff,l);
			i = 0;
			while(i < 32)	{
				printf("%.2x",digest[i]);
				i++;
			}
			printf("\n");
		}
		else	{
			fprintf(stderr,"The file %s does not exist\n",argv[1]);
		}
	}
	else	{
		fprintf(stderr,"Missing namefile argument\nUsage:\n %s <namefile>\n",argv[0]);
	}
	return 0;
}
