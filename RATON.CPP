#include <raton.h>

static unsigned raton;

#define DIVID 2
int sinit(unsigned *rat)    /* Inicializa raton. nb=Numero de botones */
{
	struct REGPACK r;
	r.r_ax=0;
	intr(0x33,&r);
	*rat=r.r_bx;
	raton=*rat;
	if(r.r_ax==0xffff)
		return 0;
	raton=*rat=0;
	return 1;
}
int scurson()   /* Muestra el cursor del raton */
{
	struct REGPACK r;
	if(raton){
		r.r_ax=1;
		intr(0x33,&r);
	}
	return 0;
}
int scursoff()  /* No muestra el cursor */
{
	struct REGPACK r;
	if(raton){
		r.r_ax=2;
		intr(0x33,&r);
	}
	return 0;
}
int sboutond()   /* chequea boton derecho */
{
	struct REGPACK r;
	if(!raton)
		return 0;
	r.r_ax=3;
	intr(0x33,&r);
	return (r.r_bx & 0x0002);
}
int sboutoni()   /* chequea boton izquierdo */
{
	struct REGPACK r;
	if(!raton)
		return 0;

	r.r_ax=3;
	intr(0x33,&r);
	return (r.r_bx & 0x0001);
}
int sboutonc()   /* chequea boton central */
{
	struct REGPACK r;
	if(!raton)
		return 0;

	r.r_ax=3;
	intr(0x33,&r);
	return (r.r_bx & 0x0004);
}
int sposx()     /* devuelve posicion x */
{
	struct REGPACK r;
	if(!raton)
		return -1;

	r.r_ax=3;
	intr(0x33,&r);
	return (r.r_cx/DIVID);
}
int sposy()    /* devuelve posicion y */
{
	struct REGPACK r;
	if(!raton)
		return -1;

	r.r_ax=3;
	intr(0x33,&r);
	return (r.r_dx);
}
void posicion(int *x,int *y)  /* devuelve x e y */
{
	struct REGPACK r;
	if(!raton){
		*x=-1;
		*y=-1;
	}
	r.r_ax=3;
	intr(0x33,&r);
	*x=r.r_cx/DIVID;
	*y=r.r_dx;
	return;
}
void posicionar(int x,int y)  /* Posiciona en x,y */
{
	struct REGPACK r;
	r.r_ax=4;
	r.r_cx=x*DIVID;
	r.r_dx=y;
	intr(0x33,&r);
	return;
}
int spression(int bt) /* Devuelve estado de los botones presionados */
	      /* ENTRADA: bt=0 boton izq. */
	      /* 	  bt=1 boton der. */
	      /* SALIDA: ax=estado de los botones bit 0 izq, bit 1 der */
	      /* 	 bx=num presiones desde la ultima vez */
	      /*	 cx=x de la ultima vez */
	      /*	 dx=y de la ultima vex */
{
	struct REGPACK r;
	r.r_ax=5;
	r.r_bx=bt;
	intr(0x33,&r);
	return (r.r_bx);
}
void limite_horizontal(int min,int max)
	/* Fija limites al desplazamiento horizontal */
{
	struct REGPACK r;
	r.r_ax=7;
	r.r_cx=min;
	r.r_dx=max;
	intr(0x33,&r);
	return;
}
void limite_vertical(int min,int max) /* Fija limites al desplazamiento vertical */
{
	struct REGPACK r;
	r.r_ax=8;
	r.r_cx=min;
	r.r_dx=max;
	intr(0x33,&r);
	return;
}
void esperar_botoni()
{
	do{
	}while(sboutoni());
	return;
}




	