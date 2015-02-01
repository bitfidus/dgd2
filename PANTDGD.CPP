#include <pantdgd.h>

void pantalla::putpixel256(int x,int y,char c,char modo)
{
	unsigned despla=(unsigned)(y*320)+x;
	switch (modo){
		case COPY:puntero[despla]=c;
			  break;
		case XOR :puntero[despla]^=c;
			  break;
	}
}
char pantalla::getpixel256(int x,int y)
{
	return puntero[(unsigned)(y*320)+x];
}
void pantalla::modo256()
{
	asm{
		mov ax,013h
		int 10h
	}
}
void pantalla::cls256(char c)
{
	asm push es
	_ES=segmento;
	_DI=0;
	_CX=32000;
	asm{
		mov ah,c
		mov al,ah
		cld
		rep stosw
		pop es
	}
}

preal::preal()
{
	desplazamiento=0;
	segmento=0xA000;
	puntero=(char *)MK_FP(segmento,0);
}
void pantalla::linea256(int x1,int y1,int x2,int y2,char color,char modo)
{
	int deltax,deltay,ay,deltayd,ax,deltaxd,aux,deltayr,deltaxr,
	    x,y,er,ed,e,i;
	
	
	deltax=1;
	deltay=1;
	ay=y2-y1;
	if(ay<0){
		deltay=-deltay;
		ay=-ay;
	}
	deltayd=deltay;
	ax=x2-x1;
	if(ax<0){
		deltax=-deltax;
		ax=-ax;
	}
	deltaxd=deltax;
	if(ax>=ay) 
		deltay=0;
	else{ 
		deltax=0;
		aux=ax;
		ax=ay;
		ay=aux;
	}
	deltayr=deltay; deltaxr=deltax;
	x=x1;
	y=y1;
	er=2*ay;
	ed=2*ay-2*ax;
	e=2*ay-ax;
	for(i=1;i<=ax+1;i++){
		putpixel256(x,y,color,modo);
		if(e>=0){
			x=x+deltaxd;
			y=y+deltayd;
			e=e+ed;
		}
		else{
			x=x+deltaxr;
			y=y+deltayr;
			e=e+er;
		}
	}
	return;
}
void pantalla::linea_horizontal(int x,int y,int longitud,char color,char modo)
{
	linea256(x,y,x+longitud,y,color,modo);
	return;
}
void pantalla::linea_vertical(int x,int y,int longitud,char color,char modo)
{
	linea256(x,y,x,y+longitud,color,modo);
	return;
}
void pantalla::rectangulo(int izq,int arr,int der,int aba,char color,char modo)
{
	linea256(izq,arr,der-1,arr,color,modo);
	linea256(izq,arr+1,izq,aba,color,modo);
	linea256(izq+1,aba,der,aba,color,modo);
	linea256(der,aba-1,der,arr,color,modo);

	return;
}
/*void pantalla::fill_cuadrado(int x,int y,int l,char color,char modo)
{
	register int bucle,xfin;
	
	xfin=x+l;
	for(bucle=x;bucle<xfin;bucle++)
		linea_vertical(bucle,y,l-1,color,modo);
	return;
} */
void pantalla::fill_cuadrado(int x,int y,int l,char color,char modo)
{
	_ES=segmento;
	_DI=y*320+x;
	asm mov cx,l
	asm mov ah,color
	asm mov al,ah
Bucle:;
	asm{
		push cx
		push di
		mov cx,l
		rep stosb
		pop di
		pop cx
		add di,320
		loop Bucle
	}
}


