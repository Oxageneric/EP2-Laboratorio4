#include "lab4.h"

void main(){
    abb *arbol = iniciaArbol();

    arbol = InsertarValorArbol(arbol,1);
    arbol = InsertarValorArbol(arbol,2);

    recorreAbb(arbol,0);
    serializa(arbol);
    eliminarArbol(arbol);

    printf("\nCREACION DEL ARBOL DESDE EL ARCHIVO\n");

    abb *prueba = iniciaArbol();
    prueba = crearArbol("serializacion.txt");
    recorreAbb(prueba,0);
    printf("\n\n");
    eliminarArbol(prueba);
}
