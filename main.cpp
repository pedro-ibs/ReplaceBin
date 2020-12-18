#include <stdio.h>
#include <stdlib.h>
#include <cstring>


/* Private macro -------------------------------------------------------------*/
#define SIZE_LINE	16
#define ARGV_FILE	1
#define ARGV_REPLACE	2
#define ARGV_TO_REPLACE	3
/* Private variables ---------------------------------------------------------*/


/* Private Functions ---------------------------------------------------------*/
void printHEX(const unsigned char *hex, const size_t size);
size_t isWhere(FILE *f, const char* rplc, const char* tRplc);
bool eqMem(unsigned char* bf1, unsigned char* bf2, size_t sbf);

/*******************************************************************************
 * substituir uma string dentro de um arquivo binário ja compilado
 * @param const char** *argv[] entrada
 * @param const int argc contador da entrada
 *
 * @param const char**    *argv[1]  entrada arquivo
 * @param const char**    *argv[2]  entrada termo a ser substituído
 * @param const char**    *argv[3]  entrada termo a ser escrito
*******************************************************************************/
int main(const int argc, const char *argv[]){
	size_t cursor;

	if(argv[ARGV_FILE]==NULL){
		printf("\n O argumento FILE está Faltando...\n");
		exit(1);
	}

	FILE *f = fopen(argv[ARGV_FILE], "rb+");
	if(f==NULL){
		printf("\narquivo '%s' nao encontrado...\n", argv[ARGV_FILE]);
		exit(1);
	}

	if(argv[ARGV_REPLACE] == NULL){
		printf("\nArgumento REPLACE está Faltando\n");
		exit(1);
	}

	if(argv[ARGV_TO_REPLACE] == NULL){
		printf("\nArgumento TO REPLACE está Faltando\n");
		exit(1);
	}

	if(strlen(argv[ARGV_TO_REPLACE]) > strlen(argv[ARGV_REPLACE])){
		printf("\nArgumento \"%s\" não pode ser maior que \"%s\"\n", argv[ARGV_TO_REPLACE], argv[ARGV_REPLACE]);
		exit(1);
	}




	cursor = isWhere(f, argv[ARGV_REPLACE], argv[ARGV_TO_REPLACE]);

	if(cursor == (size_t)EOF){
		printf("\n%s não pode se subistituida por %s, pois o termo %s não foi encontrado\n", argv[ARGV_REPLACE], argv[ARGV_TO_REPLACE], argv[ARGV_REPLACE]);
	} else {
		fflush(f);
		fseek(f, cursor-strlen(argv[ARGV_REPLACE]), SEEK_SET);
		fwrite (argv[ARGV_TO_REPLACE], strlen(argv[ARGV_TO_REPLACE]), 1, f);
		fclose(f);
		printf("\n  '%s' por '%s' Subistituido com sucesso!!\n", argv[ARGV_REPLACE], argv[ARGV_TO_REPLACE]  );
	}

	return 0;
}

/*******************************************************************************
 * Localiza o termo retorna a posição do ponteiro do cursor quando está no
 * último caracter do mesmo
 * @param const FILE*    *f    arquivo
 *
 * @param const char*    *rplc entrada termo a ser substituído
 * @param const char*    *tRplc entrada  termo a ser escrito
 *
 * @return size_t posição do ponteiro do cursor
*******************************************************************************/
size_t isWhere(FILE *f, const char* rplc, const char* tRplc){
	const size_t sizeSuwap = strlen(rplc);
	size_t cursor =  (size_t)EOF;						// conversão de tipo EOF = -1
	unsigned char swap[sizeSuwap];
	unsigned char byte;

	for(size_t idx=0; idx<sizeSuwap; idx++) swap[idx] = 0x00;

	while(fread(&byte, 1, 1, f)){
		memcpy(swap, swap+1, sizeSuwap);
		swap[sizeSuwap-1] = byte;

		if(eqMem((unsigned char*)rplc, swap, sizeSuwap)){
			cursor = ftell(f);
			printf("\n Localizado: ");
			printHEX(swap, sizeSuwap);
			printf("\t| %s\t| %s\n", (char*)swap, rplc);
			break;
		}
	}
	return cursor;
}

/*******************************************************************************
 * mostra blocos de memória em hexadecimal
 *
 * @param const u_int8_t*    *hex    bloco de memória
 * @param const size_t    size    tamanho do bloco de memória
*******************************************************************************/
void printHEX(const unsigned char *hex, const size_t size){
	for(size_t i=0; i<size; i++ ){
		printf("%02x ",  *hex++);
	}
}

/*******************************************************************************
 * compara dois blocos
 *
 * @param const u_int8_t*    *bf1    bloco de memória 1
 * @param const u_int8_t*    *bf2    bloco de memória 2
 * @param const size_t    size    tamanho dos bloco de memória
 *
 * @return bool true se os blocos são iguais
*******************************************************************************/
bool eqMem(unsigned char* bf1, unsigned char* bf2, size_t sbf){
	for(size_t idx=0; idx<sbf; idx++){
		if(bf1[idx] != bf2[idx]) return false;
	}
	return true;
}

