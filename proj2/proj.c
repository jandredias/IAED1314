#include "ftw.h"

int main(){

	char c;
	init_database();
	while(1){
		c = getchar();
		switch(c){
			case 'a':
				executa_a();
				break;			
			case 'u':
				executa_u();
				break;
			case 'l':
				executa_l();
				break;
			case 'p':
				executa_p();
				break;
			case 'r':
				executa_r();
				break;
			case 'm':
				mostra_lista();
				break;
			case 'x':
				return 0;				
		}
	}
	return 1;
	
}
