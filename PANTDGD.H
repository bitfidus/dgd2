#ifndef _PANTALLA_H
#define _PANTALLA_H

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

#define COPY 0
#define XOR 1

#define BIT1 1
#define BIT2 2
#define BIT3 4
#define BIT4 8
#define BIT5 16
#define BIT6 32
#define BIT7 64
#define BIT8 128
#define BIT9 256
#define BIT10 512
#define BIT12 1024
#define BIT13 2048
#define BIT14 4096
#define BIT15 8192
#define BIT16 16384


void check(void);   // Chequea la pila
void check(char *);


class pantalla{
protected:
public:
	unsigned segmento,desplazamiento;
	char far *puntero;
	void cls256(char c=0);
	void modo256();
	void putpixel256(int x,int y,char c,char modo=COPY);
	char getpixel256(int,int);
	void linea256(int x1,int y1,int x2,int y2,char color,char modo=COPY);
	void linea_vertical(int x,int y,int longitud,char color,char modo=COPY);
	void linea_horizontal(int x,int y,int longitud,char color,char modo=COPY);
	void rectangulo(int izq,int arr,int der,int aba,char color,char modo=COPY);
	void fill_cuadrado(int x,int y,int l,char color,char modo=COPY);

};
class preal:public pantalla{
public:
	preal();
};
#endif