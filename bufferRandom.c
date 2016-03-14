#include<stdio.h>
#include<gcrypt.h>

#define buffsize 1024

int main()	{
	register int i;
	unsigned char *buffer;
	unsigned int sum;
	gcry_err_code_t r_code;
	gcry_error_t r;
	gcry_md_hd_t hd
	printf("checking for libgcrypt %s\n",GCRYPT_VERSION);
	if(!gcry_check_version(GCRYPT_VERSION))	{
		fprintf(stderr,"libgrypt version mismatch %s\n",GCRYPT_VERSION);
		exit(2);
	}
	gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
	gcry_control(GCRYCTL_INIT_SECMEM,1638,0);
	gcry_control(GCRYCTL_INITIALIZATION_FINISHED,0);
	if(!gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P))	{
		fprintf(stderr,"libgrypt has not been initialized\n");
		exit(2);		
	}
	buffer = calloc(buffsize,sizeof(unsigned char));
	gcry_randomize(buffer,buffsize,GCRY_VERY_STRONG_RANDOM);
	i = 0;
	sum = 0;
	while(i < buffsize)	{
		sum+=(unsigned int)buffer[i];
		i++;
	}
	printf("Buffer size: %i\n",buffsize);
	printf("Suma %i\nPromedio %f\n",sum,(float)(sum/buffsize));
	memset(buffer,0,buffsize);
	free(buffer);
	return 0;
}
