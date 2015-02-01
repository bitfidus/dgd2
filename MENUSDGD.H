#ifndef _MENUS_H
#define _MENUS_H

void check(void);   // Chequea la pila
void check(char *);


#include <string.h>
#include <raton.h>
#include <ctype.h>
#include <bios.h>
#include <dos.h>
#include <bios.h>
#include <letters.h>
#include <dir.h>

#include <alloc.h>
#include <stdlib.h>


#define MAXNUMOP 10
#define LONG 10
#define TOTAL 53+MAXNUMOP*2
#define TOTAL1 200

#define XBARRA 0
#define YBARRA 0
#define COLOR 0
#define COLORFONDO 7   // antes 8
#define COLORINICIAL 12
#define RELIEVE1 15
#define RELIEVE2 7
#define RELIEVE3 0

#define HORIZONTAL 0
#define VERTICAL   1   // Sentido de las barras

#define CON_RELIEVE 1
#define SIN_RELIEVE 0


#define ESC 0x1B
#define ENT 28

#define DEL 1
#define DEL1 8
#define ARR 3
#define ABA 4
#define IZQ 5
#define DER 6
/*#define SARR 21
#define SABA 14
#define SIZQ 15
#define SDER 16
*/
#define SARR 0x4838
#define SABA 0X5032
#define SIZQ 0X4B34
#define SDER 0X4D36
#define F1 15104
#define F2 15360
#define F3 15616
#define F4 15872
#define F5 16128
#define F6 0x4000
#define F7 0x4100
#define F8 0x4200
#define F9 0x4300
#define F10 0x4400

#define AARR 17
#define AABA 18
#define AIZQ 19
#define ADER 20


#define PAG_ARR 7
#define PAG_ABA 9


#define DIM 6

#define COLORD 7

#define NORMAL 0
#define INV    1



void coger_imagen(int x,int y,int alto,int ancho,char *graf);
void dejar_imagen(int x,int y,int alto,int ancho,char *graf);
void fill(int x,int y,int alto,int ancho,int color);
int comprobar_tecla(char *cadena);
char biostec(void);
void borrar_buffer();      // BORRA EL BUFFER DEL TECLADO
int comprobar_tecla(char tecla);
int comprobar_tecla(int tecla=-1);

void linea256(int x1,int y1,int x2,int y2,int color);
void putpixel256(int x,int y,int color);
void relieve(int x,int y,int ancho,int alto,char modo=0);
void imprimir_columna(int x,int y,char *datos,int inicio,int num,int ancho,int max,int paso);

int longitud(char *cadena);

static int reserva=0;


class mensaje;

class menus{
protected:
	int x,y;
	static int color,colorfondo,colorinicial;
	static int crelieve1,crelieve2,crelieve3;
	static int xopcion;
	static int yopcion;
//	static int salir;
	unsigned char numero_opciones;
	void (*funciones[MAXNUMOP])();
public:

//	virtual void imprimir_menu(){return;}
	void cambiar_colores(int c=COLOR,int cf=COLORFONDO,int ci=COLORINICIAL,
			int cr1=RELIEVE1,int cr2=RELIEVE2,int cr3=RELIEVE3){
		color=c; colorfondo=cf; colorinicial=ci;
		crelieve1=cr1; crelieve2=cr2; crelieve3=cr3;
	}
	void cambiar_coordenadas(int x1=XBARRA,int y1=YBARRA){
		x=x1; y=y1;
	}
	void obtener_coordenadas(int &x1,int &y1){
		x1=x; y1=y;
	}
	int numero_op(){
		return ((int)numero_opciones);
	}
};
class boton{
	int x,y;
	int ancho,alto;
	char *texto;
	char modo;
	char tcla;
public:
	boton(int x1,int y1,char *tex,char tec=0);
	boton(int x1,int y1,int ancho1,int alto1,char tec=(char)ESC);
	void imprimir();
	int gestionar1(char tecla);
	int gestionar();
	void obtener_coordenadas(int &x1,int &y1){
		x1=x; y1=y;
	}

	friend class menus;
	~boton();
};
class menu_barra:public menus{
	char barra[TOTAL];
	int longitud;
	int ancho,alto;
	void imprimir_opcion(int n,int color);
	int op1;
	int op2;

public:
	menu_barra(int x1,int y1,char *cadena,void(*f[])());
	void imprimir_menu();
	int contar_opciones(int limite=TOTAL);
	void gestionar();
	void ceder_control(int opcion_elegida);

};
class menu:public menus{
protected:
	char texto[TOTAL1];
	int num_op;
	int ancho,alto;
	char *buffer;
	char borrado;
	void imprimir_opcion(int n,int color);
public:
	inline menu(){borrado=0;};
	menu(int x1,int y1,char *cadena,void(*fun[])());
	void imprimir();
	void calcular_dimensiones();
	void gestionar();
	void borrar();
	~menu();
};
class mensaje:public menu{
	char bandera;
	void resto(int x1,int y1,int lineas=0);
public:
	mensaje(int x1,int y1,char *cadena,int lineas=0);
	mensaje(int x1,int y1,int ancho1,int alto1);
	~mensaje();
	void gestionar();
	void imprimir();
//	void borrar();
	void imprimir_linea(char *str,int linea);
};



class pregunta:public mensaje{
public:
	pregunta(int x1,int y1,char *cadena);
	~pregunta();
	int gestionar();
};

class barra{
	int x,y,ancho,alto;
	char tecla1,tecla2;
	int nelementos;
	int pos;
	char sentido;
public:
	barra(int x1,int y1,int ancho1,int alto1,int n,char tecla1a,char tecla2a,char sentido1);
	void imprimir(int posicion);
	int gestionar(int &pos1,int incremento);
	void cambiar_nelementos(int n){ nelementos=n; };
};
class barra2{
	int x,y;
	int alto;
	int nelementos;
	int pos;
	int p_up,p_do;
	boton *boton1,*boton2;
	char tecb1,tecb2;
//	void imprimir();
public:
	barra2(int x1,int y1,int alto1,int n,char tecb11=0,char tecb21=0);
	~barra2();
	int gestionar(int &,int);
	void imprimir(int);
	void borrar();
	void cambiar_nelementos(int n){ nelementos=n; };
};

class directorio{
	char dir_orig[MAXPATH];
	static char dir_actual[MAXPATH];
	int  disco_orig;
	int directorios;
	static int  disco_actual;
	static int numero_discos;
	static char fich[200][15];
	int inicio;
	int num_ficheros;
	char ext[4];
	char n1[15];
	void imprimir_directorio(int x,int y,int len);
	void cambiar_unidad();
	void cambiar_extension();
	void cambiar_camino();
	void nuevo_directorio(int nuevo);
	void crear_tabla(char tabla[][15],int &num);
	int obtener_nombre();
	void error_dir();
public:
	directorio(char ext1[4]="*");
	~directorio();
	void iniciar();
	void restaurar();
	void imprimir();
	void gestionar(char *nombre);
};
class cadena{
	int x,y;
	int longit;
	char modo;
	mensaje *vacio;
	char *str;
	int indice;
public:
	cadena(int x1,int y1,int l,char mod=CON_RELIEVE);
	~cadena();
	void gestionar(char *cad);
	void imprimir(char *str1=0);
};


class editor{
	int x,y;
//	int indice;
	int columna;
	int fila;
	int inicial;
	int numlin;
	int tam;

	mensaje *vacio;
	char *buffer;
	boton *cargar;
	boton *salvar;
	boton *cancel;
	boton *ok;
	char *actual;

	int fin_linea(int lin);
	char *linea(int lin);
	void escribir(char c);
	void cambiar_actual();
	void cursor(char c);
	void del(char modo);
	void escribir_linea(int lin);
	void escribir_ventana();
	void grabar(void);
	void load(void);
	void intro();
public:
	editor(int numero_de_lineas);
	void imprimir();
	void gestionar();
	char * texto(){
		return buffer;}
	~editor();
};

class ventana_datos{
	// num= numero de datos a presentar
	// max= numero de datos total
	//
	int x,y,num,anchocar,max,paso;
	char *datos;
	int seleccion;
public:
	ventana_datos(int x1,int y1,char *datos1,int num1,int anchocar1,int max1,int paso1);
	void imprimir(int inicio);
	void imprimir(int x1,int y1,int inicio);
	void cambiar_nelementos(int n){max=n;};
	int gestionar(int inicio,char mod);
	int gestionar(int x1,int y1,int inicio);
	void imprimir_linea(int linea,int inicio,char modo);
};
#endif