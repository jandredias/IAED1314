#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TNOME 			200
#define HASH_MAX		274777
#define ID_PRIMO1		347
#define ID_PRIMO2		997

typedef struct{
	char* nome;
	unsigned long id;
	char pack;	
}Cliente;

typedef struct listac{
	struct listac *next;
	struct listac *prev;
	Cliente cliente;
}Lista;

Lista lista[5];				/* Lista de Clientes */
Lista * idHash[HASH_MAX];	/* HASHTABLE de ids */
Lista * nameHash[HASH_MAX];	/* HASHTABLE de nomes*/

void init_database();
Lista * search_by_id(unsigned long id);
unsigned long id_hash(unsigned long id);
unsigned long id_hash2(unsigned long id);
unsigned long name_hash(char * v);
unsigned long name_hash2(char * v);
void executa_a();
char * criavector(int size);
void adiciona_cliente(char* nome, int id, char pack);
Lista* executa_l();
void executa_u();
void executa_p();
void executa_r();
void mostra_lista();
void apaga_cliente(Lista *cl);
