/*
	Twitter @albertobsd
	cc -o RSA_2048 RSA_2048.c `libgcrypt-config --cflags --libs`
	Prueba de generacion de claves RSA 2048 y 4096 bits.
*/

#include<stdio.h>
#include<gcrypt.h>

int main()	{
	FILE *f = NULL;
	gcry_sexp_t rsa_parms = NULL;
	gcry_sexp_t rsa_keypair = NULL;
	gcry_error_t err = 0;
	char *buffer;
	size_t length = 4;
	size_t offset = 0;
	err = gcry_control (GCRYCTL_SUSPEND_SECMEM_WARN);
	err |= gcry_control (GCRYCTL_INIT_SECMEM, 16384, 0);
	err |= gcry_control (GCRYCTL_RESUME_SECMEM_WARN);
	err |= gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
	if(err) {
		fprintf(stderr,"gcrypt: failed initialization");
		exit(0);
	}
	err = gcry_sexp_build(&rsa_parms, NULL, "(genkey (rsa (nbits 4:4096)(rsa-use-e 1:1)))");
	if (err) {
		fprintf(stderr,"gcrypt: failed initialization");
		exit(0);
	}
	
	length = gcry_sexp_sprint(rsa_keypair,GCRYSEXP_FMT_CANON,NULL,length);
	buffer = calloc(length,sizeof( char));
	offset = gcry_sexp_sprint(rsa_parms,GCRYSEXP_FMT_DEFAULT,buffer,length);

	printf("Buffer size %i\n",length);
	printf("Buffer offset %i\n",offset);
	printf("%s\n",buffer);
	memset(buffer,0,length);

	err = gcry_pk_genkey(&rsa_keypair, rsa_parms);
	if (err) {
		fprintf(stderr,"gcrypt: failed initialization");
		exit(0);
	}
	length = gcry_sexp_sprint(rsa_keypair,GCRYSEXP_FMT_CANON,NULL,length);
	buffer = realloc(buffer,length*sizeof(char));
	offset = gcry_sexp_sprint(rsa_keypair,GCRYSEXP_FMT_CANON,buffer,length);

	printf("Buffer size %i\n",length);
	printf("Buffer offset %i\n",offset);
	printf("%s\n",buffer);
	f = fopen("clave.txt","w");
	if(f)	{
		fwrite(buffer,sizeof(char),offset,f);
		fclose(f);
	}
	memset(buffer,0,length);
	free(buffer);
	gcry_sexp_release(rsa_keypair);
	gcry_sexp_release(rsa_parms);
}

