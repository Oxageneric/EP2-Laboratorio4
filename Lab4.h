#include <stdio.h>
#include <stdlib.h>

typedef struct _arbol{
    int valor;
    struct _arbol *hijoizq,*hijoder;
    }abb;

int esArbolVacio(abb *arbol){
    if(arbol == NULL){
        return 0;
    }
    return 1;
}

abb *iniciaArbol(){
    abb *aux = NULL;
    return aux;
}

abb *InsertarValorArbol(abb *arbol,int valor){
        if(esArbolVacio(arbol) == 1){
            if(valor < arbol->valor){
                arbol->hijoizq = InsertarValorArbol(arbol->hijoizq,valor);
            }else if(valor > arbol->valor){
                arbol->hijoder = InsertarValorArbol(arbol->hijoder,valor);
            }
        }else{
            arbol = malloc(sizeof(abb));
            arbol->valor = valor;
            arbol->hijoder = NULL;
            arbol->hijoizq = NULL;
        }
    return(arbol);
}

void escribe(char *valor){
    FILE *serializacion;
    serializacion = fopen("serializacion.txt","a");
    fprintf(serializacion,"%s",valor);
    fclose(serializacion);
}

void serializa(abb *arbol){
    if(esArbolVacio(arbol) == 1){
        char *valor;
        valor = (char *)malloc(sizeof(char)*2);
        sprintf(valor,"%d",arbol->valor);  //converti el entero a char
        printf("\nDATO DEL ARBOL %d",arbol->valor);
        escribe(valor);
        serializa(arbol->hijoizq);
        serializa(arbol->hijoder);
    }else{
        escribe("N");
    }
}

void eliminarArbol(abb *arbol){
    if(esArbolVacio(arbol) == 1){
        eliminarArbol(arbol->hijoizq);
        eliminarArbol(arbol->hijoder);
        printf("se libero de la memoria el valor %d\n",arbol->valor);
        free(arbol);
        arbol =NULL;
    }
}

void espaciado(char n,int nivel){
    int espacio;

    for(espacio = 0; espacio < nivel; espacio++){
        printf("%c",n);
    }
}

void recorreAbb(abb * arbol, int nivel){
    if(esArbolVacio(arbol) == 1){
        recorreAbb(arbol->hijoder,nivel+1);
        espaciado('\t',nivel);
        printf("%d\n",arbol->valor);
        recorreAbb(arbol->hijoizq,nivel+1);
    }else{
        espaciado('\t',nivel);
        printf("N\n");
    }
}

abb *crearArbol(char *nombreArchivoArbol){
    FILE *archivo;
    int caracter;

    abb *arbol;
    arbol = iniciaArbol();

    archivo = fopen(nombreArchivoArbol,"r");
    while(1){
        caracter = fgetc(archivo);      //Toma un caracter del archivo
        if(feof(archivo)){
            break;
        }else if(caracter != 'N'){
            caracter=caracter-'0';
            if(caracter != -38){        //Espacio ASCII
                arbol = InsertarValorArbol(arbol,caracter);
            }
        }
    }
    fclose(archivo);
    return(arbol);
}
