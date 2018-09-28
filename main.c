#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "arvv.h"

#define N_CHAR 122

int read_cmd (char* cmd, int max);
void print_dir (char* dir, char* user);
char* arg(char* c,int n);

char ar[N_CHAR];

int main (void) {
	
	setlocale(LC_ALL,"portuguese");
    
    char cmd[N_CHAR];
    char user[N_CHAR] = "Bruno";
    char dir[N_CHAR] = "/";
    char ax[N_CHAR];
    char pwd[N_CHAR] = "";
    
    ArvVar* dir_Atual = arvv_cria(dir);
    ArvVar* dir_Raiz = dir_Atual;

    int retVal;
    // loop principal
    do {
    	
    	memset(ax, 0, sizeof(ax));
        memset(cmd, 0, sizeof(cmd));
        memset(ar, 0, sizeof(ar));
        
        print_dir (dir, user);
        retVal = read_cmd (cmd, N_CHAR); 
        int i = arvv_altura(dir_Raiz);
        char nom[N_CHAR];
        int l;
        ArvVar* oi;

        switch (retVal) {
            case 0:
            	//cd();
            	
            	strcpy(ax,arg(cmd,3));
                if(strlen(ax)==0){
                	printf("Digite o nome do diretório desejado, ou \"..\" para voltar ao diretório anterior!\n");
				}else{
					if(arvv_pertence(dir_Atual,ax)||!strcmp(ax,"..")){
                		oi = cd(dir_Atual,ax);
                		dir_Atual = oi;
                		strcpy(dir,veInfo(dir_Atual));
                		if(!strcmp(ax,"..")){
                			for(l=strlen(pwd)-1;pwd[i]!='/';i--){
                				pwd[i]='\0';
							}
						}else{
							strcat(pwd,"/");
							strcat(pwd,veInfo(dir_Atual));
						}
					}else{
						printf("Não existe este diretório!\n");
					}
				}
            
                break;
                
            case 1:
            	//mkdir();
            	
     			strcpy(ax,arg(cmd,6)); 
                if(strlen(ax) == 0){
                	printf("O diretório precisa de um nome!\n");
				}else{
					mkdir(dir_Atual,ax);
				}
                
                break;
                
            case 2:
             	// tree ();  
             	
             	printf("\n");
             	tree(dir_Raiz,i,i);
             	printf("\n");
             	
                break;
                
            case 3:
            	//touch();
            	
            	strcpy(ax,arg(cmd,6));
             	if(strlen(ax)==0){
             		printf("O diretório precisa de um nome!\n"); 
				 }else{
				 	touch(dir_Atual,ax);
				 }
             	
                break;
                
            case 4:
            	//pwd();
            	
                if(strlen(pwd) == 0){
                    printf("/\n");
                }else{
                    printf("%s\n", pwd);
                }
                
                break;
                
            case 5:
                 //exit ();
                 printf("\nPROGRAMA ENCERRADO!");
                break;
            default:
                printf ("\rComando não encontrado\n");
        }    
    } while (retVal != 5);
    
    arvv_libera(dir_Raiz);
    return 0;
}

int read_cmd (char* cmd, int max ){
    fflush (stdin);
    fgets (cmd, max, stdin);
    cmd[strlen(cmd)-1] = '\0';
    int i;
    char com[6]="";
    
    for(i = 0;i < strlen(cmd);i++){
      if(cmd[i] == ' '){
          break;
      }else{
          com[i] = cmd[i]; 
      }
    }
    int retVal = -1;

    if (!strcmp (com, "cd"))
        retVal = 0;
    else if (!strcmp (com, "mkdir"))
        retVal = 1;
    else if (!strcmp (com, "tree"))
        retVal = 2;
    else if (!strcmp (com, "touch"))
        retVal = 3;
    else if (!strcmp (com, "pwd"))
        retVal = 4;
    else if (!strcmp (com, "exit"))
        retVal = 5;
    
    return retVal;
}

void print_dir (char* dir, char* user) {
    printf ("%s %s$ ", dir, user);
}

char* arg(char* c,int n){
	int k = 0;
	int i;
	
	for(i=n;i<strlen(c);i++){
		ar[k] = c[i];
		k++;
	}
	return ar;
}

