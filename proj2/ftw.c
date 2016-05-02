#include "ftw.h"

/* init_database:	Funcao que inicia a base de dados dos clientes:
 * 					Lista de Clientes
 * 					Hashtables de ids
 * 					Hashtables de nomes
 * 
 * 					Entradas:	---
 * 					Saidas:		---
 * 					Efeitos:	Define os ponteiros next e prev do primeiro elemento de cada pacote
 * 								Coloca a NULL todas as posicoes das hashtables */
void init_database(){
	int i;
	for(i=0; i<5; i++){
		lista[i].next= &lista[i];
		lista[i].prev= &lista[i];
	}
	for (i=0;i<HASH_MAX;i++){
			nameHash[i] = NULL;
			idHash[i] 	= NULL;
	}
}

/* search_by_name:	Procura do cliente atraves do nome
 * 					Entradas:	ponteiro para o nome
 * 					Saidas:		Posicao do cliente na hashtable
 * 					Efeitos:	---
 * 
 * 					Neste caso, é mais importante que esta função devolva a posicao do cliente na
 * 						hashtable de modo a permitir que a executa_r nao tenha de procurar
 * 						o cliente duas vezes
 * 					*/	
unsigned long search_by_name(char *nome){
	unsigned long pos = name_hash(nome);		
	unsigned long k = HASH_MAX;
	while ((nameHash[pos] == NULL) || (strcmp(nameHash[pos]->cliente.nome, nome) != 0)){
		if(k==HASH_MAX)
			k=name_hash2(nome);
		pos += k;
		
		if(pos >= HASH_MAX)
			pos -= HASH_MAX;
	}
	return pos;
}

/* search_by_id:	Procura do cliente atraves do id
 * 					Entradas:	id
 * 					Saidas:		Ponteiro para o cliente
 * 					Efeitos:	---
 * 		
 * 					Neste caso, é preferível que a funcao devolva o ponteiro para o cliente
 * 						visto que esta funcao apenas e chamada na executa_u e esta nao apaga
 * 						o cliente das hastables, apenas muda a localizacao do cliente na lista
 * 					*/	
Lista * search_by_id(unsigned long id){
	unsigned long pos = id_hash(id);		
	unsigned long k = HASH_MAX;
	while ((idHash[pos] == NULL) || idHash[pos]->cliente.id != id){
		if(k==HASH_MAX)
			k=id_hash2(id);
		pos += k;
		
		if(pos >= HASH_MAX)
			pos -= HASH_MAX;
	}
	return idHash[pos];
}

/* id_hash:	Posicao do cliente na hashtable de ids
 * 					Entradas:	id
 * 					Saidas:		posicao do cliente na hashtable
 * 					Efeitos:	---
 * 					*/	
unsigned long id_hash(unsigned long id){
		return id % HASH_MAX;
}

/* id_hash2:	resolve o double hashing de ids*/
unsigned long id_hash2(unsigned long id){
		return (ID_PRIMO1 + ID_PRIMO2 * id) % HASH_MAX;
}
/* id_hash:	Posicao do cliente na hashtable de nomes
 * 					Entradas:	ponteiro para o nome
 * 					Saidas:		posicao do cliente na hashtable
 * 					Efeitos:	---
 * 					*/	unsigned long name_hash(char * v){
	unsigned long h, a = 31415, b = 27183;

	for (h = 0; * v != '\0'; v++, a = a * b % (HASH_MAX-1)){
		h = (a*h + *v) % HASH_MAX;
	}
	return h;
}

/* id_hash2:	resolve o double hashing de nomes*/
unsigned long name_hash2(char * v){
	unsigned long h, a = 31415, b = 27183;

	for (h = 0; * v != '\0'; v++, a = ((a * b * 173) % (HASH_MAX - 1))){
		h = (a*h + *v) % HASH_MAX;
	}
	return h;
}

/*	executa o comando A: adiciona o cliente */
void executa_a(){
	unsigned long id;
	char pack;
	char c= 'A';
	int size = TNOME;
	int i = 0;
	char *aux = criavector(size);
	char *aux2;
	int na;
	int k;
	/* Limpa os espacos existentes no comando antes de comecar a ler o nome*/
	do{
		c=getchar();
	}while(c==' ');
	
	/* Le o nome do input, e aloca num vetor.
	 * O tamanho desse vetor e variavel, de acordo com o tamanho do nome do cliente. */
	do{
		if(i < size-1){
			aux[i] = c;		
		}
		else{
			aux[size-1]='\0';
			na= size + TNOME;
			aux2 = criavector(na);
			strncpy(aux2, aux, size);
			free(aux);
			aux=aux2;
			aux[i]=c;
			size=na;
		}
		i++;
		c=getchar();
	}while(c!=' ');
	
	aux[i]='\0';
	/* faz trimming ao nome */
	k = strlen(aux);
	aux2 = criavector(k+1);
	strcpy(aux2,aux);
	
	scanf("%lu %c", &id, &pack);
   	adiciona_cliente(aux2, id, pack);

}

char * criavector(int size){
	char *v=(char *) calloc(1,size*sizeof(char));
	return v;
}
/*adiciona_cliente: Adiciona um cliente nas listas e nas hastables*/
void adiciona_cliente(char* nome, int id, char pack){
	Lista *aux, *novo;
	int i = pack-'A'; /*Escolhe a lista a ser usada, tendo em conta o pack*/
	unsigned long id_pos 	= id_hash(id);
	unsigned long name_pos 	= name_hash(nome);
	/* Encontra a primeira posicao livre nas hashtables atraves de double hashing */
	while (idHash[id_pos] != NULL ){
		id_pos += id_hash2(id);							
		if(id_pos > HASH_MAX)
			id_pos -= HASH_MAX;
		}
	
	while(nameHash[name_pos] != NULL ){
		name_pos += name_hash2(nome);							
		if(name_pos > HASH_MAX)
			name_pos -= HASH_MAX;
		}
	
	aux = lista[i].prev;
	/* Coloca o cliente nas listas*/
	novo=(Lista *) calloc(1, sizeof(Lista));
	novo->cliente.nome = nome;
	novo->cliente.id=id;
	novo->cliente.pack = pack;
	novo->next=aux->next;
	aux->next=novo;
	novo->prev=aux;
	lista[i].prev=novo;
	/* Coloca o cliente nas hashtables*/
	nameHash[name_pos] = novo;
	idHash[id_pos] = novo;
	
}
/*Executa o comando L: lista o primeiro cliente e devolve-o para o comando P*/
Lista* executa_l(){
	int i;
	Lista *aux = NULL;
	for(i=0; i<5; i++){
		if(lista[i].next==&lista[i]) /*Caso a lista seja vazia, passa a lista seguinte */
			continue;
		aux=lista[i].next;
		break;
	}
	if(aux == NULL){	/* Se nao houver clientes */
		printf("NA\n");
		return NULL;
	}
	
	printf("%s %lu %c\n", aux->cliente.nome, aux->cliente.id, aux->cliente.pack);
	return aux;
}

/*Executa o comando U:	Actualiza o pacote do Cliente
 * 						Nao altera as hashtables	*/
void executa_u(){
	Lista *aux;	/*Clientes anterior e seguintes das listas a modificar*/
	Lista *cl;	/*Cliente a alterar */
	int i;
	unsigned long id;
	char pack;
	
	scanf("%lu %c", &id, &pack); 
	cl = search_by_id(id);
	/*Remove o cliente das listas*/
	aux = cl->prev;
	aux->next = cl->next;
	aux = cl->next;
	aux->prev = cl->prev;
	
	i = pack - 'A';
	cl->cliente.pack = pack;
	/* Coloca o cliente na nova posicao */
	aux = lista[i].prev;
	lista[i].prev = cl;
	aux->next = cl,
	cl->prev=aux;
	cl->next=&lista[i];
}	
/* Executa o comando P: Lista o primeiro cliente usando o comando L e elimina-o das listas e hastables
 * 
 * 						Elimina o cliente das listas usando a apaga_cliente
 * 						Elimina da hastable de nomes e de ids usando as respecivas funções hash e
 * 						comparando os ponteiros*/
void executa_p(){
	Lista *cl = executa_l();
	unsigned long name_pos;
	unsigned long id_pos;
	unsigned long k=HASH_MAX;
	if(cl==NULL)
		return;
	name_pos = name_hash(cl->cliente.nome);
	id_pos = id_hash(cl->cliente.id);
	/* procura o cliente nas hashtables*/
	while(nameHash[name_pos] != cl){
		if(k==HASH_MAX)
			k = name_hash2(cl->cliente.nome);
		name_pos += k;
		if(name_pos > HASH_MAX){
			name_pos -= HASH_MAX;
		}
	}
	nameHash[name_pos]=NULL;
	k=HASH_MAX;
	while(idHash[id_pos] != cl){
		if(k==HASH_MAX)
			k = id_hash2(cl->cliente.id);
		id_pos += k;
		if(id_pos > HASH_MAX){
			id_pos -= HASH_MAX;
		}
	}
	idHash[id_pos]=NULL;
	apaga_cliente(cl);
	
}
/*Executa o comando R: elimina um cliente após o procurar na hashtable de nomes usando a search_by_name
 * Elimina o cliente das listas usando a apaga_cliente.
 * Elimina da hashtable de nomes usando a sua posição (devolvida na search_by_name)
 * Elimina da hashtable de ids usandos as funcoes hash e comparando os ponteiros*/
void executa_r(){
	char nome[TNOME];
	Lista *cl;
	unsigned long name_pos;
	unsigned long id_pos;
	scanf("%s",nome);
	
	name_pos = search_by_name(nome);
	
	cl = nameHash[name_pos];
	
	id_pos = id_hash(cl->cliente.id);
	/* procura o cliente na hashtable de ids*/
	while(idHash[id_pos] != cl){
		id_pos += id_hash2(cl->cliente.id);
		if(id_pos > HASH_MAX){
			id_pos -= HASH_MAX;
		}
	}
	nameHash[name_pos] = NULL;
	idHash[id_pos] = NULL;

	
	apaga_cliente(cl);
}
/*Apaga um cliente das listas*/
void apaga_cliente(Lista *cl){
	Lista * aux;
	aux= cl->prev;
	aux->next=cl->next;
	aux=cl->next;
	aux->prev=cl->prev;
	free(cl->cliente.nome);
	free(cl);
}
/*FUNCAO AUXILIAR QUE LISTA TODOS OS CLIENTES*/
void mostra_lista(){
	Lista *aux;
	int i;
	for(i=0; i<5; i++){
		if(lista[i].next==&lista[i])
			continue;
		for(aux=lista[i].next; aux!=&lista[i]; aux=aux->next){
			printf("nome %s\t", aux->cliente.nome);
			printf("id %lu\t", aux->cliente.id);
			printf("pack %c\n", aux->cliente.pack);
		}
	}

}
