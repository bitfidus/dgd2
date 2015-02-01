#ifndef _RATON_H_
#define _RATON_H_
#include <dos.h>
int sinit(unsigned *rat);    /* Inicializa raton. nb=Numero de botones */
int scurson();   /* Muestra el cursor del raton */


int scursoff();  /* No muestra el cursor */
int sboutond();   /* chequea boton derecho */
int sboutoni();   /* chequea boton izquierdo */
int sboutonc();   /* chequea boton central */
int sposx();     /* devuelve posicion x */
int sposy();    /* devuelve posicion y */
void posicion(int *x,int *y);  /* devuelve x e y */
void posicionar(int x,int y);  /* Posiciona en x,y */
int spression(int bt); /* Devuelve estado de los botones presionados */
              /* ENTRADA: bt=0 boton izq. */
	      /*          bt=1 boton der. */
              /* SALIDA: ax=estado de los botones bit 0 izq, bit 1 der */
              /*         bx=num presiones desde la ultima vez */
              /*         cx=x de la ultima vez */
              /*         dx=y de la ultima vex */
void limite_horizontal(int min,int max);
        /* Fija limites al desplazamiento horizontal */
void limite_vertical(int min,int max); /* Fija limites al desplazamiento vertical */
void esperar_botoni();

#endif

