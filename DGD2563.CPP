void EXIT();
void EXIT(char *);

#include <menusdgd.h>
#include <pantdgd.h>
#include <raton.h>
#include <mem.h>

int x,y,xpal,ypal,xven,yven,xrgb,yrgb;
char sucio;
char automatico;             /* flag del modo automatico */
int color;
unsigned char color_actual; /* color con el que se va a pintar */


char *pantalla;
char colcursor=4;  /* color del cursor de la rejilla*/
int origx=1,origy=16+15; /* coordenadas en pixels del origen del la rejilla */
int origxpal=0,origypal=179; /* idem con la paleta */
int origxven=140,origyven=1+15; /* idem con la ventana */

char test;
unsigned char fondo;

FILE *fich;
int bucle_fill;
int ancho_texto,alto_texto;
char k[6];
struct tcolor{
		unsigned char r,g,b;
};
struct tcolor paleta_rgb[256];

class dgd;
class Cursor;
class Ventana;

class Paleta{
	Cursor *cursor;
	Cursor *cursor2;
	char color0[3];
	char color1[3];
	char color10[3];
	char color7[3];
	char color8[3];
	char color12[3];
	char color15[3];

	char color0_aux[3];
	char color1_aux[3];
	char color10_aux[3];
	char color7_aux[3];
	char color8_aux[3];
	char color12_aux[3];
	char color15_aux[3];
	void leer_paleta(char color,char &r,char &g,char &b);
	void escribir_paleta(char color,char r,char g,char b);
	void leer_colores_trabajo();

public:
	char trabajo;
	friend void cambiar_fondo();
	friend void restaurar_colores();
	friend void restaurar_colores_trabajo();
	friend void sustituir();
	Paleta();
	~Paleta();
	void imprimir();
	void imprimir_color();
        void cambiar_paleta();
	void gestionar();
	void colocar_cursor(unsigned char color);
};


class Rejilla{

	char ancho_celda;
	char color_rej;    // color de la rejilla
	Cursor *cursor;
//	Ventana *ventana;
public:
	friend void recta();
	void coordenadas(int &x,int &y);
	char tam_rejx;
	char tam_rejy;
	Rejilla();
	~Rejilla();
	void pintar(dgd *g,int x1=-1,int y1=-1);
	void calcular(dgd *);
	void imprimir();
	void imprimir_grafico(dgd *g);
	void imprimir_coordenadas();
	void color(char c){color_rej=c;}
	void fill_cuadrado(int x,int y,char color);
	void gestionar();
};
class dgd{
	friend class Rejilla;
	char *grafico;		     /* puntero a los datos del grafico */
	char *undog; 		     /* almacena grafico anterior	*/
	char *auxg;		     /* grafico auxiliar 		*/

	char nombre[14];
public:

	friend void borrar_grafico();
	friend void recta();
	friend void info();
	friend int linea(int x1,int y1,int x2,int y2,char color,char flag);
	friend void punto(int x,int y,char color,char flag);
	friend void circulo(int x0,int y0,int radio,char color,char flag);
	friend void coger_color();
	friend void fill2(int x,int y,char ci);
	friend void dibujar_linea_izq(int *x,int y,char ci);
	friend void dibujar_linea_der(int *x,int y,char ci);
	friend void fill();
	friend void scroll();
	friend void imprimir_color();
	friend void EXIT();
	friend void crear_animacion();
	friend void cargar_siguiente();
	friend void cargar_anterior();
	friend int nuevo_nombre(int inc);

	unsigned char ancho,alto;    /* dimensiones del grafico 	*/
	char manchado;
	dgd();
	~dgd();
	void undo();
	void backup();
	void imprimir_nombre();
	void reset(char *);
	void dibujar_pixels();
	void dibujar_rejilla();
	void imprimir();
	void invv();
	void invh();
	void girar_90();
	void sustituir(char original,char sustituto);
	friend void scroll();
	void scroll_arriba();
	void scroll_abajo();
	void scroll_derecha();
	void scroll_izquierda();
	int cambiar_dimensiones();
	void putpixel(int x,int y);
	unsigned char dim_ancho(){ return ancho;};
	unsigned char dim_alto(){ return alto;};
	int cargar(int modo=1);
	int grabar();
	void grabar_sin();
};
class Cursor{

	int x1,y1;
	int xdim,ydim;
	int orgx,orgy;
	int ancho;
	char color;
	char borrado;
	int arr;
	int aba;
	int der;
	int izq;
public:
	int x,y;
	void inicializar(int orgx1,int orgy1,int xdim1,int ydim1,int ancho1,char color1);
	void imprimir();
	void Cursor::borrar();
	void colocar(int x2,int y2);
//	void teclas(char der1,char arr1,char izq1,char aba1);
	void teclas(int der1,int arr1,int izq1,int aba1);
	int gestionar();
};
class Ventana{
	friend void borrar_ventana();
public:
	int orgx,orgy,tamanox,tamanoy;
	void inicializar(int ox,int oy,int tamx,int tamy);
	void imprimir(int x,int y);
	int gestionar(unsigned char ancho,unsigned char alto);
	void mover(unsigned char ancho,unsigned char alto);
};


directorio *dir_info;
preal *pant;
Rejilla *rejilla;
dgd *grf;
Paleta *paleta;
menu_barra *menub;
Ventana *ventana;
boton *boton_auto;
boton *boton_test;

void ultima(void);
#pragma exit ultima 255

void check(void);
void check(char *cad);
void inicializar();
void imprimir();
void imprimir_color();

void copiray();
void nada();
void editor();
void error(int num);
int salirados();
void undo();

void coger_color();
void gestionar_banderas();

void modo_texto();
void restaurar();

void fill2(int x,int y,char ci);
void dibujar_linea_izq(int *x,int y,char ci);
void dibujar_linea_der(int *x,int y,char ci);

void restaurar_colores();
void restaurar_colores_trabajo();


/////// OPCIONES DEL MENU PRINCIPAL //////////

void info();
void menu_dgd();
	void cargar();
	void grabar();
	void grabar_sin();
void menu_grafico();
	void invertir_hor();
	void invertir_ver();
	void girar_90();
	void scroll();
	void sustituir();
	void cambiar_fondo();
	void cambiar_dimensiones();
void menu_herramientas();
	void borrar_grafico();
	void azar();
	void recta();
	void circulo_grafico();
	void circulo(int x0,int y0,int radio,char color,char flag);
	void punto(int x,int y,char color,char flag);
	void fill();
void menu_animacion();
	void crear_animacion();
	void cargar_siguiente();
	void cargar_anterior();

main()
{
	void (*funciones[])()={info,menu_dgd,menu_grafico,menu_herramientas,menu_animacion};
	pant=new preal;
	rejilla=new Rejilla();
	rejilla->color(0);
	grf=new dgd();
	paleta=new Paleta;
	ventana=new Ventana;
	boton_auto=new boton(139+32,167,8,8,'a');
	boton_test=new boton(139+32+50,167,8,8,'t');

	dir_info=new directorio;
	inic_letras();

	pant->modo256();
	x=y=0;
	sucio=0;
	xpal=ypal=0;
	xven=yven=0;

	color_actual=0;
	automatico=0;
	test=0;
	fondo=0;


//	inic_grafico(grafico);


	menub=new menu_barra(XBARRA,YBARRA,"~* .~DGD .~Grafico .~Herramientas .A~nimacion.",funciones);
	inicializar();

	unsigned rat;
	sinit(&rat);
//	if(!rat)
//		error(1);
	scurson();

	copiray();
//	grf->cambiar_dimensiones();
//	inicializar();
	do{
		editor();
	}while(!salirados());
	modo_texto();
	delete pant;
	delete rejilla;
	delete grf;
	delete paleta;
	delete menub;
	delete ventana;
	delete boton_auto;
	delete boton_test;
	return 0;
}
void editor()
{
	char color;
	do{
		menub->gestionar();
		rejilla->gestionar();
		paleta->gestionar();
		gestionar_banderas();
		if(comprobar_tecla(' '))
			rejilla->pintar(grf);
		if(comprobar_tecla('b')){
			color=color_actual;
			color_actual=fondo;
			rejilla->pintar(grf);
			color_actual=color;
		}

		///////////////////////
		// MENU DGD
		//////////////////////

		if(comprobar_tecla(F3))
			cargar();
		if(comprobar_tecla(F2)){
			grf->grabar_sin();
		}
		if(comprobar_tecla(F4))
			borrar_ventana();


		///////////////////////
		// MENU HERRAMIENTAS
		///////////////////////

		if(comprobar_tecla('l'))
			recta();
		if(comprobar_tecla('c'))
			circulo_grafico();
		if(comprobar_tecla('i'))
			borrar_grafico();
		if(comprobar_tecla('z'))
			azar();
		if(comprobar_tecla(ENT))
			coger_color();
		if(comprobar_tecla('w'))
			fill();

		///////////////////////
		/// MENU GRAFICO
		//////////////////////

		if(comprobar_tecla('m'))
			cambiar_dimensiones();

		if(comprobar_tecla('u'))
			undo();
		if(comprobar_tecla('y'))
			sustituir();
		if(ventana->gestionar(grf->ancho,grf->alto)){
			rejilla->imprimir_grafico(grf);
			rejilla->imprimir_coordenadas();
		}
		if(comprobar_tecla('f'))
			cambiar_fondo();
		if(comprobar_tecla('o'))
			invertir_hor();
		if(comprobar_tecla('p'))
			invertir_ver();
		if(comprobar_tecla('9'))
			girar_90();

		if(comprobar_tecla('s'))
			scroll();

		///////////////////////
		/// MENU ANIMACION
		//////////////////////

		if(comprobar_tecla(F7))
			cargar_anterior();
		if(comprobar_tecla(F8))
			cargar_siguiente();

	}while(!comprobar_tecla(ESC));
}
void cambiar_dimensiones()
{

	if(grf->cambiar_dimensiones())
		inicializar();

}
void restaurar()
{
	scursoff();
	rejilla->imprimir_grafico(grf);
	ventana->imprimir(xven,yven);
	grf->dibujar_pixels();
	ventana->imprimir(xven,yven);
	scurson();
}
void undo()
{
	grf->undo();
	restaurar();
}
void display_colstr(char *texto,int x,int y,char color)
{
	int indice;
	char colorao=0;
	char col=color;

	scursoff();
	for(indice=0;texto[indice];indice++){
		if(colorao){
			colorao=0;
			col=color;
		}
		if(texto[indice]=='~'){
			colorao=1;
			col=12;
			indice++;
		}
		displaychar(texto[indice],x,y,col,0);
		x+=DIM;
	}
	scurson();
}

void imprimir_banderas()
{
	char color;
	int x,y;
	color=automatico?15:8;
	boton_auto->obtener_coordenadas(x,y);
	display_colstr("~Auto",x+10,y+1,color);

	color=test?15:8;
	boton_test->obtener_coordenadas(x,y);
	display_colstr("~Test",x+10,y+1,color);

}
void gestionar_banderas()
{
	char imprimir=0;
	if(boton_auto->gestionar()){
		automatico=automatico?0:1;
		imprimir=1;
	}
	if(boton_test->gestionar()){
		test=test?0:1;
		if(test)
			imprimir_color();
		else
			paleta->imprimir_color();
		imprimir=1;
	}
	if(comprobar_tecla(F5)){
		if(paleta->trabajo)
			restaurar_colores();
		else restaurar_colores_trabajo();
		paleta->trabajo=paleta->trabajo?0:1;
	}
	if(imprimir)
		imprimir_banderas();

}
void imprimir_color()
{
	char salida[30];
	int x,y;
	rejilla->coordenadas(x,y);
	x+=xven;
	y+=yven;
	sprintf(salida,"Color: %03d",(int)(unsigned char)grf->grafico[grf->ancho*y+x]);
	displaystring(salida,0,168,15,0);
}

void azar()
{
	register int n=5;
	grf->backup();
	for (;n;n--)
	   rejilla->pintar(grf,rand() % rejilla->tam_rejx,rand() % rejilla->tam_rejy);
	return;
}
void coger_color()
{
	unsigned char color;
	int x,y;
	rejilla->coordenadas(x,y);
	color=grf->grafico[(yven+y)*grf->ancho+xven+x];
	paleta->colocar_cursor(color);
}

void borrar_grafico()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Borrar Grafico",0);

	pregunta p(-1,-1,"Esta operacion borrara todos los datos. Continuar?.");
	if(p.gestionar()){
		p.borrar();
		grf->backup();
		grf->reset(grf->grafico);
		restaurar();
	}
}
void mover_ventana()
{
	ventana->mover(grf->ancho,grf->alto);
	rejilla->imprimir_grafico(grf);
}
void info()
{
	char cad[40];
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Informacion",0);

	mensaje m(-1,-1," Creador grafico DGD v2-0 Beta  .        JAB Soft 1993.",2);
	m.imprimir();
	sprintf(cad,"Grafico: %s",grf->nombre);
	m.imprimir_linea(cad,2);
	sprintf(cad,"Memoria libre: %lu",farcoreleft());
	m.imprimir_linea(cad,3);
	m.gestionar();
}
void salir()
{
	if(salirados()){
		delete pant;
		delete rejilla;
		delete grf;
		delete paleta;
		delete menub;
		delete ventana;
		delete boton_auto;
		delete boton_test;
		exit(0);
	}
}
void menu_dgd()
{
	void (*funciones[])()={cargar,grabar_sin,grabar,salir};
	menu c(-1,-1,"~Cargar F3.~Grabar F2.G~rabar como.~Salir ESC.",funciones);
	c.gestionar();
}
void menu_animacion()
{
	void (*funciones[])()={crear_animacion,cargar_anterior,cargar_siguiente};
	menu c(-1,-1,"~Crear animacion.~Anterior F7.~Siguiente F8.",funciones);
	c.gestionar();
	return;
}
void crear_animacion()
{
}
int nuevo_nombre(int inc)
{
	char *s=grf->nombre;
	char nombre[13];
	char numero[13];
	int indice=0;
	while(*s!='.' && *s!=0)
	{
		nombre[indice]=*s;
		indice++;
		s++;
	}
	nombre[indice]=0;
	if(!*s)
	{
		error(4);
		return 0;
	}
	s-=3;
	strcpy(numero,s);
	if(isdigit(s[0]) && isdigit(s[1]) && isdigit(s[2]))
	{
		numero[3]=0;
		int n=atoi(numero);
		n+=inc;
		if(n<=0)
		{
			error(4);
			return 0;
		}
		sprintf(numero,"%03d",n);
		numero[3]='.';
		nombre[strlen(nombre)-3]=0;
		strcat(nombre,numero);
		strcpy(grf->nombre,nombre);

	}
	else
	{
		error(4);
		return 0;
	}
	return 1;
}
void cargar_siguiente()
{
	if(!nuevo_nombre(1))
		return;
	int resul=grf->cargar(0);
	if(!resul)
	{
		pregunta p(-1,-1,"Crear nuevo grafico?");
		p.imprimir();
		if(!p.gestionar())
		{
			nuevo_nombre(-1);
			grf->manchado=0;
		}
		else
			grf->manchado=1;
	}
	else
		if(resul<0)
			nuevo_nombre(-1);
	inicializar();

}
void cargar_anterior()
{
	if(!nuevo_nombre(-1))
		return;
	int resul=grf->cargar(0);
	if(!resul)
	{
		pregunta p(-1,-1,"Crear nuevo grafico?");
		p.imprimir();
		if(!p.gestionar())
		{
			nuevo_nombre(1);
			grf->manchado=0;
		}
		else
			grf->manchado=1;

	}
	else
		if(resul<0)
			nuevo_nombre(1);
	inicializar();
}


void cargar()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Cargar Grafico",0);

	if(grf->cargar())
		inicializar();
}
void grabar()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Grabar Grafico",0);

	if(grf->grabar())
		inicializar();
}
void grabar_sin()
{
	grf->grabar_sin();
}

void menu_grafico()
{
	void (*funciones[])()={mover_ventana,scroll,girar_90,invertir_ver,invertir_hor,
				cambiar_dimensiones,sustituir,undo};
	menu c(-1,-1,"Mover ~Ventana.~Scroll Grafico.~Girar 90 9.Inv Vert ~P.inv H~or.Ca~mbio tamano.Sustituir ~Y.~Undo.",
		funciones);
	check("aqui");
	c.gestionar();
}
void invertir_hor()
{
	grf->invh();
	restaurar();
}
void invertir_ver()
{
	grf->invv();
	restaurar();
}
void girar_90()
{
	grf->girar_90();
	restaurar();
}
void cambiar_paleta()
{
	paleta->cambiar_paleta();
}

void menu_herramientas()
{
	void (*funciones[])()={recta,circulo_grafico,borrar_grafico,azar,fill,
		cambiar_paleta};
	menu c(-1,-1,"~Linea.~Circulo.Borrar ~I.A~zar.Fill ~W.~Paleta K.",funciones);
	c.gestionar();
}
char modo_actual()
{
	char modo;
	asm{
		mov ah,15
		int 10h
		mov modo,al
	}
	return modo;
}

void check(void)
{
	if(farheapcheck()<0){
		scursoff();
		if(modo_actual()==0x13)
			modo_texto();
		printf("Heap corrupta from checkpoint.\n" );
		EXIT();
	}
}
void check(char *cad)
{
	if(farheapcheck()<0){
		scursoff();
		if(modo_actual()==0x13)
			modo_texto();
		printf("Heap corrupta.\n" );
		printf("%s\n",cad);
		EXIT();
	}
}

void modo_texto()
{
	asm{
		mov ax,3
		int 10h
	}
}
void ultima(void)
{
	scursoff();
	if(modo_actual()==0x13)
		modo_texto();
	dir_info->restaurar();
	delete dir_info;

	if(farheapcheck()<0){
	    printf( "Heap corrupta.\n" );
	}
	else
	    printf( "Heap OK.\n" );
	printf("DGD'256 v2.0 (c)JAB'93\n");
}

void copiray()
{
	mensaje m(-1,-1," DGD256 v2-0 Beta. JAB Soft 1993.");
	m.imprimir();
	m.gestionar();
}
void nada()
{
	mensaje m(-1,-1,"Opcion no implementada.");
	m.imprimir();
	m.gestionar();
}
void imprimir()
{
	scursoff();
	grf->dibujar_pixels();
	rejilla->imprimir_grafico(grf);
	scurson();
}
void borrar_ventana()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Ver Grafico",0);

	ventana->imprimir(xven,yven);
	do{
	}while(!comprobar_tecla() && !sboutoni());
	ventana->imprimir(xven,yven);
}
void restaurar_colores_trabajo()
{
	paleta->escribir_paleta(0,paleta->color0[0],paleta->color0[1],paleta->color0[2]);
	paleta->escribir_paleta(1,paleta->color1[0],paleta->color1[1],paleta->color1[2]);
	paleta->escribir_paleta(10,paleta->color10[0],paleta->color10[1],paleta->color10[2]);
	paleta->escribir_paleta(7,paleta->color7[0],paleta->color7[1],paleta->color7[2]);
	paleta->escribir_paleta(8,paleta->color8[0],paleta->color8[1],paleta->color8[2]);
	paleta->escribir_paleta(12,paleta->color12[0],paleta->color12[1],paleta->color12[2]);
	paleta->escribir_paleta(15,paleta->color15[0],paleta->color15[1],paleta->color15[2]);

}
void restaurar_colores()
{
	if(paleta->color0_aux[0]==100)
		return;
	paleta->escribir_paleta(0,paleta->color0_aux[0],
		paleta->color0_aux[1],paleta->color0_aux[2]);
	paleta->escribir_paleta(1,paleta->color1_aux[0],
		paleta->color1_aux[1],paleta->color1_aux[2]);
	paleta->escribir_paleta(10,paleta->color10_aux[0],
		paleta->color10_aux[1],paleta->color10_aux[2]);
	paleta->escribir_paleta(7,paleta->color7_aux[0],
		paleta->color7_aux[1],paleta->color7_aux[2]);
	paleta->escribir_paleta(8,paleta->color8_aux[0],
		paleta->color8_aux[1],paleta->color8_aux[2]);
	paleta->escribir_paleta(12,paleta->color12_aux[0],
		paleta->color12_aux[1],paleta->color12_aux[2]);
	paleta->escribir_paleta(15,paleta->color15_aux[0],
		paleta->color15_aux[1],paleta->color15_aux[2]);

}

void inicializar()
{
	preal p;
	scursoff();
	p.cls256();
	menub->imprimir_menu();
	xven=yven=0;
//	displaystring("DGD256 (c)JAB'93",0,15,15,0);
	grf->imprimir_nombre();
	p.rectangulo(139,15,308,169-9,15);      ////// DIMENSIONES MAXIMAS
	int anch=grf->dim_ancho();
	int alt=grf->dim_alto();
	p.rectangulo(139,15,139+anch+3,alt+3+15,15);

	paleta->imprimir();
	rejilla->calcular(grf);
	imprimir();
	rejilla->imprimir();
	ventana->inicializar(origxven,origyven,rejilla->tam_rejx,rejilla->tam_rejy);
	ventana->imprimir(0,0);
	boton_auto->imprimir();
	boton_test->imprimir();
	imprimir_banderas();
	rejilla->imprimir_coordenadas();
	scurson();
//	imprimir_opciones();
	return;
}
int salirados()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Salir a DOS",0);

	pregunta k(-1,-1," Quieres salir a DOS .");
	return(k.gestionar());
}

/////////////////////////////////////
//// 	REJILLA DE GRAFICOS	/////
/////////////////////////////////////
/************************************************
class Rejilla{
	char tam_rej;
	char ancho_celda;
	char color_rej;    // color de la rejilla
	Cursor *cursor;
public:
	Rejilla();
	~Rejilla();
	void calcular(dgd *);
	void imprimir();
	void imprimir_grafico(dgd *g);
	void color(char c){color_rej=c;}
	void gestionar();
	void imprimir_ventana();
};
***********************************************/

Rejilla::Rejilla()
{
	cursor=new Cursor;
//	ventana=new Ventana;
}

void Rejilla::pintar(dgd *g,int x1,int y1)
{
	preal p;
	int x,y;
	if(x1==-1){
		x=cursor->x;
		y=cursor->y;
	}
	else
	{
		x=x1;
		y=y1;
	}
	scursoff();
	p.fill_cuadrado(origx+x*ancho_celda+1,origy+y*ancho_celda+1,
		ancho_celda-1,color_actual);
	p.putpixel256(origxven+xven+x+1,origyven+yven+y+1,color_actual);
	g->putpixel(x,y);
	scurson();
}


void Rejilla::calcular(dgd *g)
{
/*	if(g->ancho<=32 && g->alto<=32){
		tam_rejx=g->ancho;
		tam_rejy=g->alto;
		if(tam_rejx>16 || tam_rejy>16)
			ancho_celda=4;
		else
			ancho_celda=8;
		return;
	}
	if(g->ancho<16 || g->alto<16){
		tam_rejx=tam_rejy=8;
		ancho_celda=8;
		return;
	}
	if(g->ancho<32 || g->alto<32){
		tam_rejx=tam_rejy=16;
		ancho_celda=8;
		return;
	};
	tam_rejx=tam_rejy=32;
	ancho_celda=4;
*/
	if(g->ancho<=32 && g->alto<=32){
		tam_rejx=g->ancho;
		tam_rejy=g->alto;
		if(tam_rejx>16 || tam_rejy>16)
			ancho_celda=4;
		else
			ancho_celda=8;
		return;
	}
	if(g->ancho<=32){
		tam_rejx=g->ancho;
		tam_rejy=32;
		ancho_celda=4;
		return;
	}
	if(g->alto<=32){
		tam_rejx=32;
		tam_rejy=g->alto;
		ancho_celda=4;
		return;
	}
	tam_rejx=tam_rejy=32;
	ancho_celda=4;
	return;
}
void Rejilla::imprimir()
{
	preal p;
	int margen=16+15;
	int buclex,bucley;
	scursoff();
	for(buclex=0;buclex<=tam_rejx*ancho_celda;buclex+=ancho_celda)
	 p.linea_vertical(origx+buclex,margen,tam_rejx*ancho_celda+1,color_rej);
	for(bucley=0;bucley<=tam_rejy*ancho_celda;bucley+=ancho_celda)
	 p.linea_horizontal(origx,bucley+margen,tam_rejy*ancho_celda+1,color_rej);
	p.rectangulo(origx-1,origy-1,origx+tam_rejx*ancho_celda+1,
		origy+tam_rejy*ancho_celda+1,1);

	cursor->inicializar(origx,origy,tam_rejx,tam_rejy,ancho_celda,15);
	// ANTES 4
	cursor->colocar(0,0);
	cursor->imprimir();
	scurson();
	return;
}
void Rejilla::fill_cuadrado(int x,int y,char color)
{
	preal p;
	if(y-yven<0 || y-yven>=tam_rejy || x-xven<0 || x-xven>=tam_rejx)
		return;
	p.fill_cuadrado(origx+(x-xven)*ancho_celda+1,origy+(y-yven)*ancho_celda+1,
	ancho_celda-1,color);

}

void Rejilla::imprimir_grafico(dgd *g)
{
   int despla;
   register int x;
   register int y;
   preal p;

   despla=xven+yven*g->ancho;
   scursoff();
   for(y=0;y<tam_rejy;y++)
	for(x=0;x<tam_rejx;x++)
		p.fill_cuadrado(origx+x*ancho_celda+1,origy+y*ancho_celda+1,
			ancho_celda-1,g->grafico[despla+y*g->ancho+x]);
   scurson();
}
void Rejilla::gestionar()
{
	if(cursor->gestionar()){
		imprimir_coordenadas();
		if(automatico)
			pintar(grf);
		if(test)
			imprimir_color();
	}
}
void Rejilla::coordenadas(int &x,int &y)
{
	x=cursor->x;
	y=cursor->y;
}
void Rejilla::imprimir_coordenadas()
{
	int x,y;
	char salida[25];
	coordenadas(x,y);
	x+=xven;
	y+=yven;
	sprintf(salida,"x:%03d y:%03d",x,y);
	scursoff();
	displaystring(salida,0,23,15,0);
	scurson();
}


Rejilla::~Rejilla()
{
	delete cursor;
//	delete ventana;
}


///////////////////////////
///  CLASE DGD
//////////////////////////

dgd::dgd()
{
//	nombre[0]=0;
	sprintf(nombre,"<Sin_nombre>");
	ancho=alto=32;
	grafico=new char[(unsigned)ancho*(unsigned)alto];
	undog=new char[(unsigned)ancho*(unsigned)alto];
	reset(grafico);
	reset(undog);
	manchado=0;
}
void dgd::backup()
{
	memcpy(undog,grafico,(unsigned int)ancho*(unsigned int)alto);
}
void dgd::undo()
{
	memcpy(grafico,undog,(unsigned int)ancho*(unsigned int)alto);
}
void dgd::putpixel(int x,int y)
{
	grafico[(yven+y)*this->ancho+xven+x]=color_actual;
	manchado=1;
}
void dgd::reset(char *g)
{
	memset(g,0,(unsigned)ancho*(unsigned)alto);
	check("Desde reset");
}
int dgd::cambiar_dimensiones()
{
	char salida[50];
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Cambiar Tamanno",0);

	cadena cad(-1,-1,3);
	cadena cad2(-1,-1,3);
	char num[4];
	int entero;
	int x,y,ancho2,alto2,ancho3;

	ancho2=ancho;
	alto2=alto;
	ancho3=ancho;


	sprintf(salida,"Introduce nuevo ancho (max: 166)");
	sprintf(num,"%d",(unsigned int)ancho);
	mensaje m1(-1,70,salida);
	m1.imprimir();
	cad.imprimir();
	cad.gestionar(num);
	m1.borrar();
	entero=atoi(num);
	if(entero==0 || entero>166)
		return 0;
	ancho=entero;
	sprintf(salida,"Introduce nuevo alto (max: 142)");
	sprintf(num,"%d",(unsigned int)alto);
	mensaje m2(-1,70,salida);
	m2.imprimir();
	cad2.imprimir();
	cad2.gestionar(num);
	m2.borrar();
	entero=atoi(num);
	if(entero==0 || entero>142){
		ancho=ancho2;
		return 0;
	}
	alto=entero;

	delete undog;
	undog=new char[ancho*alto];
	auxg=new char[ancho*alto];
	reset(auxg);

	if(ancho2>=ancho)
		ancho2=ancho;
	if(alto2>=alto)
		alto2=alto;
	for(y=0;y<alto2;y++)
		for(x=0;x<ancho2;x++)
			auxg[y*ancho+x]=grafico[y*ancho3+x];
	delete grafico;
	grafico=auxg;
	return 1;
}


void dgd::imprimir_nombre()
{
	char salida[30];
	displaystring("            ",9*6,15,15,0);
//	if(nombre[0])
		sprintf(salida,"Grafico: %s",nombre);
//	else
//		sprintf(salida,"Grafico: <Sin_nombre>");
	scursoff();
	displaystring(salida,0,15,15,0);
	sprintf(salida,"(%03dx%03d)",ancho,alto);
	displaystring(salida,78,23,15,0);
	scurson();
}
void dgd::dibujar_pixels()
{
	register int x;
	register int y;
	preal p;
	for(y=0;y<alto;y++)
	   for(x=0;x<ancho;x++)
		p.putpixel256(x+origxven+1,y+origyven+1,grafico[y*ancho+x]);
	return;
}
int dgd::grabar()
{
	int x2,y2;
	char nombre1[13];
	FILE *fich;

	directorio d("dgd");
	d.gestionar(nombre1);

	if(nombre1[0]==0)
		return 0;
	sprintf(nombre,"%s",nombre1);
        grabar_sin();
/*	if((fich=fopen(nombre1,"wb"))==NULL){
		error(2);
		return 0;
	}
	putc(ancho,fich);
	putc(alto,fich);
	for(y2=0;y2<alto;y2++)
		for(x2=0;x2<ancho;x2++)
			putc(grafico[x2+y2*ancho],fich);
	fclose(fich);
	manchado=0;
	sprintf(nombre,"%s",nombre1);*/
	return 1;
}
void dgd::grabar_sin()
{
	int x2,y2;
	FILE *fich;
	if(nombre[0]=='<'){
		error(3);
		return;
        }
	if((fich=fopen(nombre,"wb"))==NULL){
		error(2);
		return;
	}
	putc(ancho,fich);
	putc(alto,fich);
	for(y2=0;y2<alto;y2++)
		for(x2=0;x2<ancho;x2++)
			putc(grafico[x2+y2*ancho],fich);
	fclose(fich);
	manchado=0;
	return;
}

int dgd::cargar(int modo)
{
	char name[13];
	FILE *entrada;
	name [0]=0;
	if(modo)
	{
		directorio d("dgd");
		d.gestionar(name);
	}
	else
		strcpy(name,nombre);
	if(name[0]){
		if(manchado){
			pregunta p(-1,-1,"El grafico actual no ha sido grabado. Cargar el nuevo?.");
			if(!p.gestionar())
				return -1;
		}
		if((entrada=fopen(name,"rb"))==NULL){
			fclose(entrada);
			if(modo)
				error(2);
			return 0;
		}
		delete grafico;
		delete undog;
		ancho=getc(entrada);
		alto=getc(entrada);
		grafico=new char[ancho*alto];
		undog=new char[ancho*alto];
		int y2,x2;
		for(y2=0;y2<alto;y2++)
			for(x2=0;x2<ancho;x2++)
				grafico[x2+y2*ancho]=getc(entrada);
		fclose(entrada);
		manchado=0;
//		name[strlen(name)-4]=0;
		strcpy(nombre,name);
		return 1;
	}
	else
		return 0;
}
void dgd::sustituir(char original,char sustituto)
{
	unsigned longitud=(int)ancho*(int)alto;
	register unsigned f;

	backup();
	for(f=0;f<longitud;f++)
		if(grafico[f]==original)
			grafico[f]=sustituto;
}

void dgd::invh()
{
	int x2,x3,y2;
	auxg=new char[ancho*alto];
	backup();

	memcpy(auxg,grafico,(unsigned int)ancho*(unsigned int)alto);
/*	for (y2=0;y2<alto;y2++)
		for(x2=0;x2<ancho;x2++)
			auxg[x2+ancho*y2]=grafico[x2+ancho*y2];
*/
	for (y2=0;y2<alto;y2++)
		for(x3=0,x2=ancho;x2;x2--,x3++)
			grafico[x3+ancho*y2]=auxg[x2-1+ancho*y2];
	delete auxg;
	return;
}
void dgd::invv()
{
	int x2,y3,y2;

	auxg=new char[ancho*alto];
	backup();
	memcpy(auxg,grafico,(unsigned int)ancho*(unsigned int)alto);
/*	for (y2=0;y2<alto;y2++)
		for(x2=0;x2<ancho;x2++)
			auxg[x2+ancho*y2]=grafico[x2+ancho*y2];
*/
	for (x2=0;x2<ancho;x2++)
		for(y3=0,y2=alto;y2;y2--,y3++)
			grafico[x2+ancho*y3]=auxg[x2+ancho*(y2-1)];
		delete auxg;
	return;
}
void dgd::girar_90()
{
	int x2,y3,y2;

	auxg=new char[ancho*alto];
	for (x2=0;x2<ancho;x2++)
		for(y2=0;y2<alto;y2++)
			auxg[x2*alto+ancho-y2-1]=grafico[ancho*y2+x2];
	memcpy(grafico,auxg,(unsigned int)ancho*(unsigned int)alto);
	delete auxg;
	unsigned char auxiliar=alto;
	alto=ancho;
	ancho=auxiliar;
	return;
}


dgd::~dgd()
{
	delete grafico;
	delete undog;
}
////////////////////////////
////  CLASE PALETA
///////////////////////////

Paleta::Paleta()
{
	cursor=new Cursor;
	cursor2=new Cursor;
	color0[0]=0;
	color0[1]=0;
	color0[2]=0;

	color1[0]=0;
	color1[1]=0;
	color1[2]=42;

	color10[0]=21;
	color10[1]=63;
	color10[2]=21;

	color7[0]=42;
	color7[1]=42;
	color7[2]=42;

	color8[0]=21;
	color8[1]=21;
	color8[2]=21;

	color12[0]=63;
	color12[1]=21;
	color12[2]=21;

	color15[0]=63;
	color15[1]=63;
	color15[2]=63;

	color0_aux[0]=0;
	color0_aux[1]=0;
	color0_aux[2]=0;

	color1_aux[0]=0;
	color1_aux[1]=0;
	color1_aux[2]=42;

	color10_aux[0]=0;
	color10_aux[1]=42;
	color10_aux[2]=0;

	color7_aux[0]=42;
	color7_aux[1]=42;
	color7_aux[2]=42;

	color8_aux[0]=21;
	color8_aux[1]=21;
	color8_aux[2]=21;

	color12_aux[0]=63;
	color12_aux[1]=21;
	color12_aux[2]=21;

	color15_aux[0]=63;
	color15_aux[1]=63;
	color15_aux[2]=63;

	trabajo=0;
}
Paleta::~Paleta()
{
	delete cursor;
	delete cursor2;
}
void Paleta::leer_colores_trabajo()
{
	paleta->leer_paleta(0,color0_aux[0],color0_aux[1],color0_aux[2]);
	paleta->leer_paleta(1,color1_aux[0],color1_aux[1],color1_aux[2]);
	paleta->leer_paleta(10,color10_aux[0],color10_aux[1],color10_aux[2]);
	paleta->leer_paleta(7,color7_aux[0],color7_aux[1],color7_aux[2]);
	paleta->leer_paleta(8,color8_aux[0],color8_aux[1],color8_aux[2]);
	paleta->leer_paleta(12,color12_aux[0],color12_aux[1],color12_aux[2]);
	paleta->leer_paleta(15,color15_aux[0],color15_aux[1],color15_aux[2]);
}

void Paleta::imprimir_color()
{
	char salida[30];
	sprintf(salida,"Color: %03d",(int)color_actual);
	displaystring(salida,0,168,15,0);
	sprintf(salida,"~Fondo: %03d",(int)fondo);
	display_colstr(salida,12*6,168,15);
}
void Paleta::colocar_cursor(unsigned char color)
{
	int x,y;

	x=((int)color) % 64;
	y=((int)color) / 64;
	cursor->borrar();
	cursor->colocar(x,y);
	cursor->imprimir();
	color_actual=color;
	imprimir_color();
}

void Paleta::imprimir()
{
	register int bucle;
	preal p;
	scursoff();
	for(bucle=0;bucle<64;bucle++)
		p.fill_cuadrado(bucle*5+1,180,4,bucle);
	for(bucle=0;bucle<64;bucle++)
		p.fill_cuadrado(bucle*5+1,185,4,bucle+64);
	for(bucle=0;bucle<64;bucle++)
		p.fill_cuadrado(bucle*5+1,190,4,bucle+128);
	for(bucle=0;bucle<64;bucle++)
		p.fill_cuadrado(bucle*5+1,195,4,bucle+192);
	// ANTES 4
	cursor2->inicializar(origxpal,origypal,64,4,5,10);
	cursor2->colocar(0,0);
	cursor2->teclas(DER,ARR,IZQ,ABA);
	cursor2->imprimir();


	cursor->inicializar(origxpal,origypal,64,4,5,15);
	cursor->colocar(0,0);
	cursor->teclas(SDER,SARR,SIZQ,SABA);
	cursor->imprimir();

	imprimir_color();
	scurson();
	return;
}
void Paleta::escribir_paleta(char color,char r,char g,char b)
{
     union REGS regs;

     regs.x.ax=0x1010;
     regs.x.bx=(unsigned char)color;
     regs.h.dh=r;
     regs.h.ch=g;
     regs.h.cl=b;
     int86(0x10,&regs,&regs);
     return;
}

void Paleta::leer_paleta(char color,char &r,char &g,char &b)
{
     union REGS inr,outr;

     inr.x.ax=0x1015;
     inr.x.bx=(unsigned char)color;
     int86(0x10,&inr,&outr);
     r=outr.h.dh;
     g=outr.h.ch;
     b=outr.h.cl;
     return;
}

void Paleta::gestionar()
{
	if(comprobar_tecla('k')){
		cambiar_paleta();
	}
	if(cursor->gestionar()){
		color_actual=cursor->y*64+cursor->x;
		imprimir_color();
	}
/*	if(comprobar_tecla('f')){
		do{
			if(cursor2->gestionar()){
				fondo=cursor2->y*64+cursor2->x;
				imprimir_color();
			}
		}while(!comprobar_tecla(' '));
	}
*/
}
void cambiar_fondo()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Cambiar Fondo",0);
	int x,y;
	x=paleta->cursor2->x;
	y=paleta->cursor2->y;

	do{
		if(paleta->cursor2->gestionar()){
			fondo=paleta->cursor2->y*64+paleta->cursor2->x;
			paleta->imprimir_color();
		}
		if(comprobar_tecla(ESC)){
			paleta->cursor2->borrar();
			paleta->cursor2->colocar(x,y);
			paleta->cursor2->imprimir();
			return;
		}
	}while(!comprobar_tecla(' '));
	grf->sustituir(color_actual,fondo);
}
/////////////////////////////
///// CLASE CURSOR
/////////////////////////////

void Cursor::inicializar(int orgx1,int orgy1,int xdim1,int ydim1,int ancho1,char color1)
{
	orgx=orgx1;
	orgy=orgy1;
	ancho=ancho1;
	color=color1;
	x1=-1;
	borrado=1;
	xdim=xdim1;
	ydim=ydim1;
	arr=ARR;
	aba=ABA;
	izq=IZQ;
	der=DER;
}
//void Cursor::teclas(char der1,char arr1,char izq1,char aba1)
void Cursor::teclas(int der1,int arr1,int izq1,int aba1)
{
	arr=arr1;
	aba=aba1;
	izq=izq1;
	der=der1;
}
void Cursor::colocar(int x2,int y2)
{
	x=x2;
	y=y2;
}

void Cursor::imprimir()
{
	preal p;
	scursoff();
	if(!borrado)
		p.rectangulo(orgx+x1*ancho,orgy+y1*ancho,
		     orgx+x1*ancho+ancho,orgy+y1*ancho+ancho,color,XOR);
	p.rectangulo(orgx+x*ancho,orgy+y*ancho,
	     orgx+x*ancho+ancho,orgy+y*ancho+ancho,color,XOR);
	scurson();
	x1=x;
	y1=y;
	borrado=0;
//     cursor_pixel();
     return;
}
void Cursor::borrar()
{
	preal p;
	if(!borrado){
		scursoff();
		p.rectangulo(orgx+x1*ancho,orgy+y1*ancho,
		     orgx+x1*ancho+ancho,orgy+y1*ancho+ancho,color,XOR);
		scurson();
	}
	borrado=1;
	return;
}

int Cursor::gestionar()
{
	char movido=0;
	int x2=x;
	int y2=y;
	int xrat,yrat;

	posicion(&xrat,&yrat);
	if((xrat>=orgx && xrat<orgx+ancho*xdim) &&
	   (yrat>=orgy && yrat<orgy+ancho*ydim)){
		if(sboutoni()){
			while(sboutoni());
			x2=(xrat-orgx)/ancho;
			y2=(yrat-orgy)/ancho;
			movido=1;
		}
	}

	if(comprobar_tecla(arr)){
		y2--;
		if(y2<0) y2=ydim-1;
		movido=1;
	}
	if(comprobar_tecla(aba)){
		y2++;
		if(y2==ydim) y2=0;
		movido=1;
	}
	if(comprobar_tecla(der)){
		x2++;
		if(x2==xdim) x2=0;
		movido=1;
	}
	if(comprobar_tecla(izq)){
		x2--;
		if(x2<0) x2=xdim-1;
		movido=1;
	}
	if(movido){
		borrar();
		colocar(x2,y2);
		imprimir();
		return 1;
	}
	return 0;
}
/////////////////////////////////
//	CLASE VENTANA
////////////////////////////////

void Ventana::inicializar(int ox,int oy,int tamx,int tamy)
{
	orgx=ox;
	orgy=oy;
	tamanox=tamx;
	tamanoy=tamy;
}

void Ventana::imprimir(int x,int y)
{
	preal p;
	scursoff();
	p.rectangulo(orgx+x,orgy+y,orgx+x+tamanox+1,orgy+y+tamanoy+1,4,XOR);
	scurson();
	xven=x;
	yven=y;
	return;
}
int Ventana::gestionar(unsigned char ancho,unsigned char alto)
{

	int xrat,yrat;

	posicion(&xrat,&yrat);

	if(((xrat>=orgx && xrat<orgx+ancho) &&
	   (yrat>=orgy && yrat<orgy+alto) && sboutoni()) ||
		comprobar_tecla('v'))
	{
		while(sboutoni());
		mover(ancho,alto);
		return 1;
	}
	return 0;
}
void Ventana::mover(unsigned char ancho,unsigned char alto)
{
	char sigue=1;
	int xv,yv;
	int xrat,yrat;
	char movido=0;

	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Mover Ventana",0);


	limite_horizontal(0,(ancho-tamanox)*2);
	limite_vertical(0,alto-tamanoy);
	scursoff();

//	posicion(&xrat,&yrat);
	posicionar(xven,yven);
	do{
		xv=xven;
		yv=yven;
		if(comprobar_tecla(ARR)){
			yv--;
			if(yv<0)
				yv=alto-tamanoy;
			movido=1;
		}
		if(comprobar_tecla(ABA)){
			yv++;
			if(yv+tamanoy>alto)
				yv=0;
			movido=1;
		}
		if(comprobar_tecla(DER)){
			xv++;
			if(xv+tamanox>ancho)
				xv=0;
			movido=1;
		}
		if(comprobar_tecla(IZQ)){
			xv--;
			if(xv<0)
				xv=ancho-tamanox;
			movido=1;
		}
		xrat=sposx();
		yrat=sposy();
		if((xrat!=xv || yrat!=yv) && !movido){
			movido=1;
			xv=xrat;
			yv=yrat;
		}

		if(comprobar_tecla(' ') || sboutoni()){
			 sigue=0;
		}
		if(movido){
			imprimir(xven,yven);
			imprimir(xv,yv);
			posicionar(xv,yv);
			rejilla->imprimir_grafico(grf);
			movido=0;
		}
	}while(sigue);
	limite_horizontal(0,639);
	limite_vertical(0,200);
	posicionar(160,100);
	while(sboutoni());
	scurson();
	return;
}

void error(int num)
{
	char salida[80];
	char mensajes[][40]={"","Error general","No puedo abrir el fichero",
	"El grafico actual no tiene nombre","Nombre incorrecto"};

	sprintf(salida,"ERROR %d: %s",num,mensajes[num]);
	mensaje m(-1,-1,salida);
	m.imprimir();
	m.gestionar();
}

int linea(int x1,int y1,int x2,int y2,char color,char flag)
{
	int deltax,deltay,ay,deltayd,ax,deltaxd,aux,deltayr,deltaxr,
	    x,y,er,ed,e,i;
	int longitud=0;
	preal p;
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
		if(flag)
			grf->grafico[y*grf->ancho+x]=color;
		else{
			p.putpixel256(x,y,color,XOR);
			rejilla->fill_cuadrado(x-origxven-1,y-origyven-1,
				p.getpixel256(x,y));
		}
		longitud++;
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
	return longitud;
}
void recta()
{
	int x,y,x1,y1,x2,y2;
	preal p;
	char tecla;
	char sigue=1;
	char abortado=0;
	int incx,incy;
	char sucio=0;
	int xrat,yrat;
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Linea",0);


//	incx=origxven+xven+1;
//	incy=origyven+yven+1;
	incx=origxven+1;
	incy=origyven+1;

	rejilla->coordenadas(x,y);
	rejilla->coordenadas(x1,y1);
//	ventana->imprimir(xven,yven);
	x1+=xven;
	y1+=yven;
	x=x1;
	y=y1;
	limite_horizontal(0,(grf->ancho)*2-1);
	limite_vertical(0,grf->alto-1);
	scursoff();

	linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
	posicionar(x,y);

	do{

		if(comprobar_tecla(DER)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			x1++;
//			if(x1+xven==grf->ancho)
//				x1=-xven;
			if(x1==grf->ancho)
				x1=0;
			sucio=1;
		}
		if(comprobar_tecla(IZQ)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			x1--;
//			if(x1+xven<0)
//				x1=grf->ancho-1-xven;
			if(x1<0)
				x1=grf->ancho-1;
			sucio=1;
		}
		if(comprobar_tecla(ARR)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			y1--;
//			if(y1+yven<0)
//				y1=grf->alto-1-yven;
			if(y1<0)
				y1=grf->alto-1;
			sucio=1;
		}
		if(comprobar_tecla(ABA)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			y1++;
//			if(y1+yven==grf->alto)
//				y1=-yven;
			if(y1==grf->alto)
				y1=0;
			sucio=1;
		}
		xrat=sposx();
		yrat=sposy();
		if(xrat<0)
		{
			xrat=x1;
			yrat=y1;
		}

		if((xrat!=x1 || yrat!=y1) && !sucio){
                	linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			sucio=1;
			x1=xrat;
			y1=yrat;
		}
		if(comprobar_tecla(' ') || sboutoni())
			sigue=0;
		if(sucio){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			sucio=0;
			posicionar(x1,y1);
		}
		if(comprobar_tecla(ESC)){
			sigue=0;
			abortado=1;
		}
	}while(sigue);
	linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
	if(abortado)
	{
		scurson();
		return;
	}
	grf->backup();
	ventana->imprimir(xven,yven);
	p.linea256(incx+x,incy+y,incx+x1,incy+y1,color_actual);
//	linea(x+xven,y+yven,x1+xven,y1+yven,color_actual,1);
	linea(x,y,x1,y1,color_actual,1);
	rejilla->imprimir_grafico(grf);
	ventana->imprimir(xven,yven);
	limite_horizontal(0,639);
	limite_vertical(0,200);
	posicionar(160,100);
	scurson();

	return;
	
}
void punto(int x,int y,char color,char flag)
{
	preal p;
	if(flag==COPY)
		grf->grafico[(y-origyven-1)*grf->ancho+x-origxven-1]=color;
	p.putpixel256(x,y,color,flag);
	rejilla->fill_cuadrado(x-origxven-1,y-origyven-1,
		p.getpixel256(x,y));

	return;
}
void circulo(int x0,int y0,int radio,char color,char flag)
{
     int x,y,p;
     unsigned int op1,op2,op3,op4,op5,op6,op7,op8;

     x=0;
     y=radio;
     p=3-2*radio;
     while(x<y){
	 op1=(y0+y);
	 op2=(y0-y);
	 op3=(y0+x);
	 op4=(y0-x);
	 op5=(x0+x);
	 op6=(x0-x);
	 op7=(x0+y);
	 op8=(x0-y);
	 

if((op1>origyven) && (op1<=origyven+grf->alto) && (op5>origxven)
		  && (op5<=origxven+grf->ancho))
		punto(op5,op1,color,flag);
if((op1>origyven) && (op1<=origyven+grf->alto) && (op6>origxven)
		  && (op6<=origxven+grf->ancho))
	 punto(op6,op1,color,flag);
if((op2>origyven) && (op2<=origyven+grf->alto) && (op5>origxven)
		  && (op5<=origxven+grf->ancho))
	 punto(op5,op2,color,flag);
if((op2>origyven) && (op2<=origyven+grf->alto) && (op6>origxven)
		  && (op6<=origxven+grf->ancho))
	 punto(op6,op2,color,flag);
if((op3>origyven) && (op3<=origyven+grf->alto) && (op7>origxven)
		  && (op7<=origxven+grf->ancho))
	 punto(op7,op3,color,flag);
if((op3>origyven) && (op3<=origyven+grf->alto) && (op8>origxven)
		  && (op8<=origxven+grf->ancho))
	 punto(op8,op3,color,flag);
if((op4>origyven) && (op4<=origyven+grf->alto) && (op7>origxven)
		  && (op7<=origxven+grf->ancho))
	 punto(op7,op4,color,flag);
if((op4>origyven) && (op4<=origyven+grf->alto) && (op8>origxven)
		  && (op8<=origxven+grf->ancho))
	 punto(op8,op4,color,flag);
	 if(p<0)
	   p=p+4*x+6;
	 else{
	      p=p+4*(x-y)+10;
	      y--;
	 }
	 x++;
     }
     if(x==y){
	 op1=(y0+y);
	 op2=(y0-y);
	 op3=(y0+x);
	 op4=(y0-x);
	 op5=(x0+x);
	 op6=(x0-x);
	 op7=(x0+y);
	 op8=(x0-y);

	 if((op1>origyven) && (op1<=origyven+grf->alto) && (op5>origxven)
		  && (op5<=origxven+grf->ancho))
		punto(op5,op1,color,flag);
if((op1>origyven) && (op1<=origyven+grf->alto) && (op6>origxven)
		  && (op6<=origxven+grf->ancho))
	 punto(op6,op1,color,flag);
if((op2>origyven) && (op2<=origyven+grf->alto) && (op5>origxven)
		  && (op5<=origxven+grf->ancho))
	 punto(op5,op2,color,flag);
if((op2>origyven) && (op2<=origyven+grf->alto) && (op6>origxven)
		  && (op6<=origxven+grf->ancho))
	 punto(op6,op2,color,flag);
if((op3>origyven) && (op3<=origyven+grf->alto) && (op7>origxven)
		  && (op7<=origxven+grf->ancho))
	 punto(op7,op3,color,flag);
if((op3>origyven) && (op3<=origyven+grf->alto) && (op8>origxven)
		  && (op8<=origxven+grf->ancho))
	 punto(op8,op3,color,flag);
if((op4>origyven) && (op4<=origyven+grf->alto) && (op7>origxven)
		  && (op7<=origxven+grf->ancho))
	 punto(op7,op4,color,flag);
if((op4>origyven) && (op4<=origyven+grf->alto) && (op8>origxven)
		  && (op8<=origxven+grf->ancho))
	 punto(op8,op4,color,flag);
     }
     return;
}
void circulo_grafico()
{
	int x,y,x1,y1,x2,y2;
	char tecla;
	char sigue=1;
	char abortado=0;
	int incx,incy;
	int r;
//	double radio;
	int xrat,yrat;
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Circulo",0);

	incx=origxven+1;
	incy=origyven+1;
	rejilla->coordenadas(x,y);
	rejilla->coordenadas(x1,y1);
//	ventana->imprimir(xven,yven);
	x1+=xven;
	y1+=yven;
	x=x1;
	y=y1;

	limite_horizontal(0,(grf->ancho)*2-1);
	limite_vertical(0,grf->alto-1);
	scursoff();
	linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
	circulo(incx+x,incy+y,0,color_actual,XOR);
	r=0;
	posicionar(x,y);
	do{
		if(comprobar_tecla(DER)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			circulo(incx+x,incy+y,r,color_actual,XOR);
			x1++;
//			if(x1+xven==grf->ancho) x1=-xven;
			if(x1==grf->ancho)
				x1=0;
		
			sucio=1;
		}
		if(comprobar_tecla(IZQ)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			circulo(incx+x,incy+y,r,color_actual,XOR);
			x1--;
//			if(x1+xven<0) x1=grf->ancho-1-xven;
			if(x1<0)
				x1=grf->ancho-1;

			sucio=1;
		}
		if(comprobar_tecla(ARR)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			circulo(incx+x,incy+y,r,color_actual,XOR);
			y1--;
//			if(y1+yven<0) y1=grf->alto-1-yven;
			if(y1<0)
				y1=grf->alto-1;
		
			sucio=1;
		}
		if(comprobar_tecla(ABA)){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			circulo(incx+x,incy+y,r,color_actual,XOR);
			y1++;
//			if(y1+yven==grf->alto) y1=-yven;
			if(y1==grf->alto)
				y1=0;

			sucio=1;
		}
		xrat=sposx();
		yrat=sposy();
		if(xrat<0)
		{
			xrat=x1;
			yrat=y1;
		}

		if((xrat!=x1 || yrat!=y1) && !sucio){
			linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			circulo(incx+x,incy+y,r,color_actual,XOR);
			sucio=1;
			x1=xrat;
			y1=yrat;
		}

		if(comprobar_tecla(' ') || sboutoni())
			sigue=0;
		if(sucio){
	   //		radio=(x-x1)*(x-x1)+(y-y1)*(y-y1);
	   //		radio=sqrt(radio);
	   //		r=(int)radio;
			r=linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
			circulo(incx+x,incy+y,r,color_actual,XOR);
			sucio=0;
			posicionar(x1,y1);
		}
		if(comprobar_tecla(ESC)){
			sigue=0;
			abortado=1;
		}


	}while(sigue);
//	radio=(x-x1)*(x-x1)+(y-y1)*(y-y1);
//	radio=floor(sqrt(radio));
//	r=(int)radio;
	r=linea(incx+x,incy+y,incx+x1,incy+y1,color_actual,0);
	circulo(incx+x,incy+y,r,color_actual,XOR);
	if(abortado){
		scurson();
		return;
	}
	grf->backup();
	ventana->imprimir(xven,yven);
	circulo(incx+x,incy+y,r,color_actual,COPY);
	rejilla->imprimir_grafico(grf);
	ventana->imprimir(xven,yven);

	limite_horizontal(0,639);
	limite_vertical(0,200);
	posicionar(160,100);
	scurson();

	return;
}

void dibujar_linea_der(int *x,int y,char ci)
{
		bucle_fill=*x;
		while((bucle_fill<grf->ancho) && grf->grafico[bucle_fill+y*grf->ancho]==ci){
			grf->grafico[bucle_fill+y*grf->ancho]=color_actual;
			bucle_fill++;
		}     
		bucle_fill--;
		*x=bucle_fill;
		return;
}  
void dibujar_linea_izq(int *x,int y,char ci)
{

		bucle_fill=(*x)-1;
		while((bucle_fill>=0) && grf->grafico[bucle_fill+y*grf->ancho]==ci){
			grf->grafico[bucle_fill+y*grf->ancho]=color_actual;
			bucle_fill--;
		}
		bucle_fill++;
		*x=bucle_fill;
		return;
}  

void fill2(int x,int y,char ci)
{
	int x2,x3;

	x2=x3=x;
	if(((x<grf->ancho) && (x>=0)) && ((y<grf->alto) && (y>=0))
			&& (grf->grafico[x+y*grf->ancho]==ci)){
		dibujar_linea_der(&x2,y,ci);
		dibujar_linea_izq(&x3,y,ci);
		       
		 
		fill2(x,y+1,ci);
		fill2(x,y-1,ci);
                fill2(x2,y+1,ci); 
		fill2(x2,y-1,ci);
		       
		
		fill2(x,y+1,ci);
		fill2(x,y-1,ci);
                fill2(x3,y+1,ci); 
		fill2(x3,y-1,ci); 
	}
	else return;                    
	return;
}

void fill()
{
	int x,y;
	rejilla->coordenadas(x,y);
	x+=xven;
	y+=yven;
	if(color_actual!=grf->grafico[x+y*grf->ancho]){
		grf->backup();
		fill2(x,y,grf->grafico[x+y*grf->ancho]);
		restaurar();
	}
	check("DESDE FILL");
	return;
}
void dgd::scroll_arriba()
{
	char *graf;
	register int bucle;

	graf=new char[ancho];

	for(bucle=0;bucle<ancho;bucle++)
		graf[bucle]=grafico[bucle];
	auxg=grafico+ancho;
	movmem(auxg,grafico,ancho*(alto-1));
	auxg=grafico+ancho*(alto-1);
	for(bucle=0;bucle<ancho;bucle++)
		auxg[bucle]=graf[bucle];
	delete graf;
	return;
}
void dgd::scroll_abajo()
{
	char *graf;
	register int bucle;

	graf=new char[ancho];
	for(bucle=0;bucle<ancho;bucle++)
		graf[bucle]=grafico[ancho*(alto-1)+bucle];
	auxg=grafico+ancho;
	movmem(grafico,auxg,ancho*(alto-1));
	auxg=grafico;
	for(bucle=0;bucle<ancho;bucle++)
		auxg[bucle]=graf[bucle];
	delete graf;
	return;
}
void dgd::scroll_derecha()
{
	char *graf;
	char aux;
	register int x;
	register int y;

	graf=new char[ancho];
	for(y=0;y<alto;y++){
		aux=grafico[(y+1)*ancho-1];
		for(x=0;x<ancho;x++)
			graf[x]=grafico[y*ancho+x];
		for(x=0;x<ancho-1;x++)
			grafico[y*ancho+x+1]=graf[x];
		grafico[y*ancho]=aux;
	}
	delete graf;
	return;
}

void dgd::scroll_izquierda()
{
	char *graf;
	char aux;
	register int x;
	register int y;

	graf=new char[ancho];
	for(y=0;y<alto;y++){
		aux=grafico[y*ancho];
		for(x=0;x<ancho;x++)
			graf[x]=grafico[y*ancho+x];
		for(x=0;x<ancho-1;x++)
			grafico[y*ancho+x]=graf[x+1];
		grafico[(y+1)*ancho-1]=aux;
	}
	delete graf;
	return;
}
void scroll()
{
	char sigue=1;
	char movido=0;
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Scroll de Grafico",0);

	scursoff();
	ventana->imprimir(xven,yven);
	grf->backup();
	do{
		if(comprobar_tecla(ARR)){
			grf->scroll_arriba();
			movido=1;
		}
		if(comprobar_tecla(ABA)){
			grf->scroll_abajo();
			movido=1;
		}
		if(comprobar_tecla(DER)){
			grf->scroll_derecha();
			movido=1;
		}
		if(comprobar_tecla(IZQ)){
			grf->scroll_izquierda();
			movido=1;
		}
		if(movido){
			grf->dibujar_pixels();
			rejilla->imprimir_grafico(grf);
			movido=0;
		}

		if(comprobar_tecla(' '))
			sigue=0;
	}while(sigue);
	ventana->imprimir(xven,yven);
	restaurar();
	scurson();
	check("DESDE SCROLL");
	return;
}
void sustituir()
{
	char color;
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Sustituir color",0);

	Cursor cursor2;
	cursor2.inicializar(origxpal,origypal,64,4,5,10);
	cursor2.colocar(0,0);
	cursor2.teclas(DER,ARR,IZQ,ABA);
	cursor2.imprimir();
	paleta->cursor2->borrar();
	do{
		cursor2.gestionar();
//		paleta->cursor2->gestionar();
		if(comprobar_tecla(ESC)){
			cursor2.borrar();
			paleta->cursor2->imprimir();
			return;
		}

	}while(!comprobar_tecla(' '));
	color=cursor2.y*64+cursor2.x;
//	color=paleta->cursor2->y*64+paleta->cursor2->x;
	grf->sustituir(color_actual,color);
	cursor2.borrar();
	paleta->cursor2->imprimir();
	restaurar();
}
class Plantilla{
	friend class Paleta;
	boton *botonr;
	boton *botong;

	boton *botonb;
	boton *botone;

	boton *botonf;
	boton *botonv;

	boton *botonr00;
	boton *botonr64;

	boton *botong00;
	boton *botong64;

	boton *botonb00;
	boton *botonb64;

	boton *copiar;
	boton *boton_cargar;
	boton *boton_grabar;
	boton *boton_salida;

	mensaje *m;
	Cursor *cursor;
	Cursor *cursor2;
	unsigned char color,r,g,b,cogido;
	void imprimir_color();
	void leer_paleta_rgb256();
	void cambiar_paleta_rgb256();
	void cargar();
	void grabar();
	void copy();

public:
	Plantilla();
	int gestionar();
	~Plantilla();
};
Plantilla::Plantilla()
{
	int x,y;
	char salida[10];
	color=cogido=0;
	m=new mensaje(0,50,320,75);
	m->imprimir();
	m->obtener_coordenadas(x,y);
	x+=110;
	y+=15;
	botone=new boton(x,y,"~e");
	botonr=new boton(x+80,y,"~r");
	botonr00=new boton(x-25,y,"00",'w');
	botonr64=new boton(x+80+19,y,"63",'t');
	scursoff();
	displaychar('w',x-25-9,y+4,12,7);
	displaychar('t',x+80+19+15+9,y+4,12,7);
	copiar=new boton(x-25-9-60,y,"C~opiar");
	y+=15;

	botonf=new boton(x,y,"~f");
	botong=new boton(x+80,y,"~g");
	botong00=new boton(x-25,y,"00",'d');
	botong64=new boton(x+80+19,y,"63",'h');
	displaychar('d',x-25-9,y+4,12,7);
	displaychar('h',x+80+19+15+9,y+4,12,7);


	y+=15;

	botonv=new boton(x,y,"~v");
	botonb=new boton(x+80,y,"~b");
	botonb00=new boton(x-25,y,"00",'c');
	botonb64=new boton(x+80+19,y,"63",'n');
	displaychar('c',x-25-9,y+4,12,7);
	displaychar('n',x+80+19+15+9,y+4,12,7);
	boton_cargar=new boton(x+80+19+15+9+20,y-30,"Cargar ~L");
	boton_grabar=new boton(x+80+19+15+9+20,y-15,"Grabar ~S");
	boton_salida=new boton(x+80+19+15+9+20,y,"Salida ~Q");

	cursor=new Cursor;
	cursor->inicializar(origxpal,origypal,64,4,5,15);
	cursor->colocar(0,0);
	cursor->teclas(DER,ARR,IZQ,ABA);
	cursor->imprimir();
	cursor2=new Cursor;
	cursor2->inicializar(origxpal,origypal,64,4,5,10);
	cursor2->colocar(0,0);
	cursor2->teclas(DER,ARR,IZQ,ABA);
	cursor2->imprimir();

	copiar->obtener_coordenadas(x,y);
/*	sprintf(salida,"%03d",cogido);
	displaystring(salida,x+40,y+4,15,7);
*/
	imprimir_color();
	scurson();
}
Plantilla::~Plantilla()
{
	delete m;

	delete botone;
	delete botonr;
	delete botong;
	delete botonf;
	delete botonb;
	delete botonv;
	delete botonr00;
	delete botonr64;
	delete botong00;
	delete botong64;
	delete botonb00;
	delete botonb64;

	delete copiar;
	delete boton_cargar;
	delete boton_grabar;
	delete boton_salida;

	delete cursor;
	delete cursor2;
}
void Plantilla::copy()
{
	unsigned char nuevo,aux;
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Copiar Color",0);

	do{
		if(cursor2->gestionar())
			nuevo=cursor2->y*64+cursor2->x;
	}while(!comprobar_tecla(' '));
	aux=color;
	color=nuevo;
	leer_paleta_rgb256();
	color=aux;
	cambiar_paleta_rgb256();

}
void Plantilla::cargar()
{
	int x;
	char nombre[14];
	char aux;
	char salida[25];

	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Cargar paleta",0);


	directorio d("rgb");
	d.gestionar(nombre);

	if(nombre[0]==0)
		return;
	if((fich=fopen(nombre,"rb"))==NULL) {
		error(2);
		return;
	}
	aux=color;
	mensaje m(-1,-1,"                      ");
	m.imprimir();
	for(x=0;x<256;x++){
		sprintf(salida,"Cargando registro: %03d",x);

		m.imprimir_linea(salida,0);
		r=getc(fich);
		g=getc(fich);
		b=getc(fich);
		color=x;
		cambiar_paleta_rgb256();
	}
	fclose(fich);
	color=aux;
	return;
}
void Plantilla::grabar()
{
	int x;
	char nombre[14];
	char aux;
	char salida[25];
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Grabar paleta",0);


	directorio d("rgb");
	d.gestionar(nombre);
	if(nombre[0]==0)
		return;

	if((fich=fopen(nombre,"wb"))==NULL){
		error(2);
		return;
	}
	aux=color;
	mensaje m(-1,-1,"                      ");
	m.imprimir();
	for(x=0;x<256;x++){
		sprintf(salida,"Grabando registro: %03d",x);
		m.imprimir_linea(salida,0);

		color=x;
		leer_paleta_rgb256();
		putc(r,fich);
		putc(g,fich);
		putc(b,fich);
	}
	fclose(fich);
	color=aux;
	return;
}

int Plantilla::gestionar()
{
	char cambiado=0;
	char salida=0;
	do{
		if(cursor->gestionar()){
			color=cursor->y*64+cursor->x;
			imprimir_color();
		}
		if(boton_cargar->gestionar() || comprobar_tecla(F3)){
			cargar();
			salida=1;
		}
		if(boton_grabar->gestionar() || comprobar_tecla(F2))
			grabar();
		if(copiar->gestionar()){
			copy();
			salida=1;
		}
		if(botonr->gestionar()){
			r++;
			cambiado=1;
		}
		if(botone->gestionar()){
			r--;
			cambiado=1;
		}
		if(botong->gestionar()){
			g++;
			cambiado=1;
		}
		if(botonf->gestionar()){
			g--;
			cambiado=1;
		}
		if(botonb->gestionar()){
			b++;
			cambiado=1;
		}
		if(botonv->gestionar()){
			b--;
			cambiado=1;
		}
		if(botonr00->gestionar()){
			r=0;
			cambiado=1;
		}
		if(botonr64->gestionar()){
			r=63;
			cambiado=1;
		}
		if(botong00->gestionar()){
			g=0;
			cambiado=1;
		}
		if(botong64->gestionar()){
			g=63;
			cambiado=1;
		}
		if(botonb00->gestionar()){
			b=0;
			cambiado=1;
		}
		if(botonb64->gestionar()){
			b=63;
			cambiado=1;
		}

		if(cambiado){
			cambiar_paleta_rgb256();
			imprimir_color();
			cambiado=0;
			salida=1;
		}
	}while(!comprobar_tecla(' ') && !comprobar_tecla(ESC)
		&& !boton_salida->gestionar());
	cursor->borrar();
	cursor2->borrar();
	return salida;
}
void Plantilla::cambiar_paleta_rgb256()
{
     union REGS regs;

     regs.x.ax=0x1010;
     regs.x.bx=(unsigned char)color;
     regs.h.dh=r;
     regs.h.ch=g;
     regs.h.cl=b;
     int86(0x10,&regs,&regs);
     return;
}

void Plantilla::leer_paleta_rgb256()
{
     union REGS inr,outr;

     inr.x.ax=0x1015;
     inr.x.bx=(unsigned char)color;
     int86(0x10,&inr,&outr);
     r=outr.h.dh;
     g=outr.h.ch;
     b=outr.h.cl;
     return;
}

void Plantilla::imprimir_color()
{
	int x,y;
	int bucle;
	char salida[20];
	preal p;

	char c;
	char col;

	scursoff();
	col=12;
	botone->obtener_coordenadas(x,y);
	sprintf(salida,"Color: %03d",(int)color);
	displaystring(salida,x+20,y-10,15,7);
	x+=15;
	y+=3;
	leer_paleta_rgb256();
	sprintf(salida,"%03d",(int)r);

	for(bucle=x;bucle<x+64;bucle++){
		if(bucle<r+x) c=col;
		else c=0;
		p.linea_vertical(bucle,y,8,c);
	}
	displaystring(salida,x+20,y+2,15,0);

	col=2;
	botonf->obtener_coordenadas(x,y);
	x+=15;
	y+=3;
	leer_paleta_rgb256();
	sprintf(salida,"%03d",(int)g);

	for(bucle=x;bucle<x+64;bucle++){
		if(bucle<g+x) c=col;
		else c=0;
		p.linea_vertical(bucle,y,8,c);
	}
	displaystring(salida,x+20,y+2,15,0);

	col=1;
	botonv->obtener_coordenadas(x,y);
	x+=15;
	y+=3;
	leer_paleta_rgb256();
	sprintf(salida,"%03d",(int)b);

	for(bucle=x;bucle<x+64;bucle++){
		if(bucle<b+x) c=col;
		else c=0;
		p.linea_vertical(bucle,y,8,c);
	}
	displaystring(salida,x+20,y+2,15,0);
	scurson();
}


void Paleta::cambiar_paleta()
{
	mensaje tit(0,0,320,13);
	tit.imprimir();
	tit.imprimir_linea("Opciones de paleta",0);
	Plantilla plantilla;
	cursor->borrar();
	cursor2->borrar();
	if(plantilla.gestionar()){
		leer_colores_trabajo();
		trabajo=0;
	}
	cursor->imprimir();
	cursor2->imprimir();

}
void EXIT()
{
	printf("\nGrafico grabado en NONAME.DGD\n");
	sprintf(grf->nombre,"NONAME.DGD");
	grf->grabar_sin();
	exit(2);
}
void EXIT(char *mensaje)
{
	if(modo_actual()==0x13)
		modo_texto();
	printf(mensaje);
	EXIT();
}
char clave[]="kismsmypopnrt,rkp";