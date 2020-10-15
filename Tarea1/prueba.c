#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

struct juego{
  char nombre[50];
  int categorias;
};


//Funcion ordenarArreglo: ordena un arreglo según cantidad de lo medido, la ordena descendentemente (imprimimos al revés los datos luego)
void ordenarArreglo(struct juego *juegos,int tamanioJuegos){
    int i;
    int j;
    struct juego auxiliar;
    for(i = 0;i < tamanioJuegos - 1;i++){
        for(j = 1; j < tamanioJuegos;j++){
            if (juegos[j].categorias > juegos[j-1].categorias){
                auxiliar = juegos[j];
                juegos[j] = juegos[j-1];
                juegos[j-1] = auxiliar;
            }
        }
    }
}

void all_texts(){
    DIR *dir;
    DIR *dirpollo;
    FILE *aux;
    char *variable;
    char *genero;
    char linea[300];
    char titulo[300];
    char nom[300];
    char nombrejuego[300];
    struct dirent *ent;
    const char *path = "/mnt/c/Users/nandi/OneDrive/Escritorio/Tarea_SO";
    char archivo[100];
    dir = opendir(path);
    if (dir != NULL) {
      while ((ent = readdir (dir))) {
        if ((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0) || (strcmp(ent->d_name,"prueba.c")==0) || (strcmp(ent->d_name,"pruebita")==0)){
        }
        else{
          //printf ("%s\n", ent->d_name);
          aux  = fopen(ent->d_name,"r");
          if(aux == NULL){
            printf("error");
            exit(2);
          }
          fgets(titulo,300,aux);
          fgets(linea,150,aux);
          //printf("%s ", linea);
          variable = strtok(linea,",");
          genero = strtok(variable,"\n");

          strcpy(archivo,path);
          strcat(archivo,"/");
          strcat(archivo,genero);
          //printf("%s \n", archivo);
          //printf("%s \n", path);
          //printf("%s\n", variable);
          strcat(nom,"./");
          strcat(nom,genero);
          dirpollo = opendir(nom);
          if(dirpollo==NULL){
            mkdir(genero, 0777);

          }
          strcpy(nombrejuego,genero);
          strcat(nombrejuego,"/");
          strcat(nombrejuego, ent->d_name);
          rename(ent->d_name,nombrejuego);
        }
      }
      closedir (dir);
      }
    else {
      printf ("No se puede abrir directorio");
    }
}

int main(){
    char titulo1[300];
    char categoria1[300];
    char *token;
    struct juego juegos[50];
    int contador=0;
    all_texts();
    int accion = 0;
    int *y = &accion;
    FILE *game_aux;
    while (accion != 2){
      printf("Bienvenide :D\n");
      printf("¿Qué acción desea realizar?:\n");
      printf("1.- Revisar carpetas.\n");
      printf("2.- Salir.\n");
      scanf("%i", y);
      if (accion == 1){
        printf("A continuacion, se muestran todas las categorias disponibles:\n");
        DIR *dir2;
        struct dirent *ent2;
        const char *path2 = "/mnt/c/Users/nandi/OneDrive/Escritorio/Tarea_SO";
        dir2 = opendir(path2);
        char actual[300];
        int cont=1;
        char carpeta[300];
        if (dir2 != NULL){
          while ((ent2 = readdir (dir2))) {
            if ((strcmp(ent2->d_name,".")==0) || (strcmp(ent2->d_name,"..")==0) || (strcmp(ent2->d_name,"prueba.c")==0) || (strcmp(ent2->d_name,"pruebita")==0)  || (strcmp(ent2->d_name,"makefile")==0)){
            }
            else{
              printf ("%s\n", ent2->d_name);
              cont++;
            }
          }
       }

        printf("Escoja la carpeta que desea revisar\n");
        scanf("%s",carpeta);
        getcwd(actual,sizeof(actual));
        strcat(actual,"/");
        strcat(actual,carpeta);
        //printf("%s\n",actual);

        DIR *dir3;
        struct dirent *ent3;
        dir3 = opendir(actual);
        chdir(actual);
        if (dir3 != NULL){
          while ((ent3 = readdir (dir3))) {
            if ((strcmp(ent3->d_name,".")==0) || (strcmp(ent3->d_name,"..")==0)){
            }
            else{//printear en forma ascendente
            if (strstr(ent3->d_name, ".txt") != NULL) {
              int k=0;
              game_aux = fopen(ent3->d_name,"r");
              fgets(titulo1, sizeof(char)*300, game_aux);
              fgets(categoria1, sizeof(char)*300, game_aux);
              fclose(game_aux);
              token = strtok(categoria1, ",");      
              while( token != NULL ) {
                  k+=1;
                  token = strtok(NULL,",");
              }
              juegos[contador].categorias=k;
              strcpy(juegos[contador].nombre,ent3->d_name);
              contador+=1;
            }
            else{
              ;
            }
          }
        }
        ordenarArreglo(juegos,contador);
        for(int i=contador-1;i>=0;i--){
          printf("%s \n",juegos[i].nombre);
        }
        contador = 0;

        char juego[300];
        char titulo[300];
        char categoria[300];
        char creador[300];
        char descripcion[300];
        printf("Escoja el archivo que desea leer\n");
        scanf("%s", juego);
        game_aux = fopen(juego,"r");
        fgets(titulo,300,game_aux);
        printf("%s\n",titulo);
        fgets(categoria,300,game_aux);
        printf("%s\n",categoria);
        fgets(creador,300,game_aux);
        printf("%s\n",creador);
        fgets(descripcion,300,game_aux);
        printf("%s\n",descripcion);

        strcat(actual,"/"); //estas tres lineas vuelven a la carpeta principal, dd tan todas las categorias c:
        strcat(actual,"..");
        chdir(actual);  

    }
  } 
  
}
  return 0;
}



