////////////////// Sistema de menus para VGA/MCGA 256
void modo_texto();
void EXIT();
void EXIT(char *);      // IMPLEMENTADAS EN DGD2563.CPP



#include <menusdgd.h>
#include <stdio.h>
#include <conio.h>

void error_menus()
{
	modo_texto();
	printf("ERROR IRREVERSIBLE\n");
	EXIT("No hay memoria para abrir ventana");
}


boton::boton(int x1,int y1,int ancho1,int alto1,char tec)
{
	x=x1;
	y=y1;
	ancho=ancho1;
	alto=alto1;
	modo=0;
	tcla=tec;
	imprimir();
}
boton::boton(int x1,int y1,char *cadena,char tec)
{
	x=x1;
	y=y1;
	texto=new char[strlen(cadena)];
	strcpy(texto,cadena);
	ancho=longitud(texto)*DIM+8;
	alto=DIM+7;
	modo=1;
	imprimir();
	int bucle;
	tcla=0;
	if(tec)
		tcla=tec;
	else
		for(bucle=0;texto[bucle];bucle++)
			if(texto[bucle]=='~')
				tcla=tolower(texto[bucle+1]);
}
boton::~boton()
{
	if(modo)
		delete texto;
}
void boton::imprimir()
{
	int x1=x+4;
	int y1=y+4;
	int x2=x1;
	int y2=y1;

	int indice;
	char colorao=0;
	int col=menus::color;

	scursoff();

	fill(x,y,ancho,alto,menus::colorfondo);
	relieve(x,y,ancho,alto);

	if(modo)
		for(indice=0;texto[indice];indice++){
			if(colorao){
				colorao=0;
				col=menus::color;
			}
			if(texto[indice]=='~'){
				colorao=1;
				col=12;
				indice++;
			}
			displaychar(texto[indice],x2,y2,col,menus::colorfondo);
			x2+=DIM;
		}
	scurson();
}
int boton::gestionar1(char tecla=0)
{
	if(tecla){
		if(!modo)
			return 0;
		int bucle;
		for(bucle=0;texto[bucle];bucle++)
			if(texto[bucle]=='~')
				return(tolower(texto[bucle+1])==tecla);
		return 0;
	}
	int xraton,yraton;

	if(sboutoni())
	{
		posicion(&xraton,&yraton);
		if(yraton>=y && yraton<=y+alto
			&& xraton>=x && xraton<=x+ancho)
		{
			scursoff();
			relieve(x,y,ancho,alto,INV);
			scurson();
			while(sboutoni());
			scursoff();
			relieve(x,y,ancho,alto);
			scurson();
			posicion(&xraton,&yraton);
			if(yraton>=y && yraton<=y+alto
				&& xraton>=x && xraton<=x+ancho)
					return 1;
			else
				return 0;
		}
	}
	return 0;
}
int boton::gestionar()
{
	char tecla;
	int salida;
	int xraton,yraton;

	if(sboutoni())
	{
		posicion(&xraton,&yraton);
		if(yraton>=y && yraton<=y+alto
			&& xraton>=x && xraton<=x+ancho)
		{
			scursoff();
			relieve(x,y,ancho,alto,INV);
			scurson();
			while(sboutoni());
			scursoff();
			relieve(x,y,ancho,alto);
			scurson();
			posicion(&xraton,&yraton);
			if(yraton>=y && yraton<=y+alto
				&& xraton>=x && xraton<=x+ancho)
					return 1;
			else
				return 0;
		}
	}
	return(comprobar_tecla(tcla));
/*	if( (tecla=tolower(bioskey(1)) )){
		if(!modo)
			salida=(tecla==tcla);
		else{
			int bucle;
			for(bucle=0;texto[bucle];bucle++)
				if(texto[bucle]=='~')
					salida=(tolower(texto[bucle+1])==tecla);
		}
		if(salida){
			borrar_buffer();
			return 1;
		}
		return 0;
	}
	return 0;
*/
}

///////////////////////////
//////  MENUS DE BARRA
//////////////////////////


menu_barra::menu_barra(int x1,int y1,char *cadena,void(*fun[])())
{
	int f;
	x=x1;
	y=y1;
	alto=DIM+7;
	ancho=320;

	yopcion=y1+alto;
	xopcion=0;
	cambiar_colores();
	for(f=0;f<MAXNUMOP;f++)
		funciones[f]=fun[f];
	strcpy(barra,cadena);
	menu_barra::imprimir_menu();
	numero_opciones=menu_barra::contar_opciones();
	op1=-1;
	op2=-1;

}
void menu_barra::imprimir_menu()
{
	int f;
	int k;
	char colorao=0;
	int col=color;

	scursoff();
	fill(x,y,ancho,alto,colorfondo);
	relieve(x,y,ancho,alto);

	for(f=0,k=0;barra[f];f++,k++){
		if(colorao){
			colorao=0;
			col=color;
		}
		if(barra[f]=='~'){
			colorao=1;
			col=12;
			f++;
		}
		if(barra[f]=='.')
			displaychar(' ',x+k*DIM+4,y+4,col,colorfondo);
		else
			displaychar(barra[f],x+k*DIM+4,y+4,col,colorfondo);
	}
	scurson();
}
int menu_barra::contar_opciones(int limite)
{
	int numop=0;

	int f;
	int k;
	for(f=0,k=0;k<limite && barra[f];f++,k++){
		if(barra[f]=='.')
			numop++;
		if(barra[f]=='~')
			f++;
	}
	longitud=k;
	return numop;
}
void menu_barra::imprimir_opcion(int n,int color)
{
	int bucle;
	int indice=0;
	int contador=0;
	int colorao=0;
	int x2=x;
	int y2=y;

	for(bucle=0;bucle<n;indice++,contador++){
		if(!barra[indice])
			break;
		if(barra[indice]=='~')
			indice++;
		if(barra[indice]=='.')
			bucle++;
	}
	scursoff();
	int col=color;
	for(;;indice++,contador++){
		if(!barra[indice])
			break;
		if(colorao){
			colorao=0;
			col=color;
		}
		if(barra[indice]=='~'){
			colorao=1;
			col=12;
			indice++;
		}
		if(barra[indice]=='.'){
			break;
		}
		displaychar(barra[indice],x2+contador*DIM+4,y2+4,col,colorfondo);
	}
	scurson();
}


void menu_barra::gestionar()
{
	int xraton,yraton;
	int f,k;
	int xop=0;
	int op=0;
	int c_aux;
	char t;
	int opcion=1;
	int salir=0;
//	int op1=-1;
//	int op2=-1;


	op=0;
	xop=0;
	posicion(&xraton,&yraton);
	if(yraton>=y && yraton<=y+DIM+4)     //&& xraton/2>=x && xraton/2<=x+ancho)
	{
		op1=contar_opciones((xraton+8)/DIM);   // /(DIM*2)
		if(op1!=op2)
		{
			imprimir_opcion(op1,15);
			if(op2!=-1)
			imprimir_opcion(op2,color);
			op2=op1;
		}
	}else{
		op1=-1;
		if(op1!=op2)
			imprimir_opcion(op2,color);
		op2=op1;
	}
	if(sboutoni() && yraton>=y && yraton<=y+DIM+4){
		while(sboutoni());
		posicion(&xraton,&yraton);
		if(yraton>=y && yraton<=y+DIM+4){  /////////////  VIGILAR
			opcion=contar_opciones((xraton+8)/DIM);  // DIM*2
			for(f=0,k=0;barra[f];f++,k++){
				if(barra[f]=='~')
					f++;
				if(barra[f]=='.'){
					if(op==opcion)
						break;
					else{
					     op++;
					     xop=(k+1)*DIM;
					}
				}
			}
			xopcion=xop;
			if(opcion<numero_opciones){
				menu_barra::ceder_control(opcion);
				op2=-1;
			}
		}
	}
	opcion=comprobar_tecla(barra);
	if(opcion!=-1){
		int bucle;
		for(bucle=0,f=0,k=0;bucle<opcion;f++,k++){
			if(barra[f]=='~'){
				f++;
				continue;
			}
			if(barra[f]=='.')
			{
				bucle++;
			}
		}
		xopcion=k*DIM;
		if(opcion<numero_opciones)
			menu_barra::ceder_control(opcion);
	}

}
void menu_barra::ceder_control(int opcion_elegida)
{
	funciones[opcion_elegida]();
	scursoff();
	menu_barra::imprimir_menu();
	scurson();
}

/////////////////////////////////
//  MENUS DE VENTANA            //
////////////////////////////////

void menu::borrar()
{
	if(!borrado){
		scursoff();
		dejar_imagen(x,y,alto,ancho,buffer);
		scurson();
	}
	borrado=1;
}
void menu::imprimir_opcion(int n,int color)
{
	int bucle;
	int indice=0;
	int contador=0;
	int colorao=0;
	int x2=x+4;
	int y2=y+n*(DIM+4)+3+1;
	for(bucle=0;bucle<n;indice++){
		if(!texto[indice])
			break;
		if(texto[indice]=='.')
			bucle++;
	}
	scursoff();
	int col=color;
	for(;;indice++,contador++){
		if(!texto[indice])
			break;
		if(colorao){
			colorao=0;
			col=color;
		}
		if(texto[indice]=='~'){
			colorao=1;
			col=12;
			indice++;
		}
		if(texto[indice]=='.'){
			break;
		}
		displaychar(texto[indice],x2+contador*DIM,y2,col,colorfondo);
	}
	scurson();
}


menu::menu(int x1,int y1,char *cadena,void(*fun[])())
{
	int f;

	if(x1==-1)
		x=xopcion;
	else
		x=x1;
	if(y1==-1)
		y=yopcion;
	else
		y=y1;
	borrado=0;
	cambiar_colores();
	for(f=0;f<MAXNUMOP;f++)
		funciones[f]=fun[f];
	strcpy(texto,cadena);
	calcular_dimensiones();
	if(x+ancho>=320)
		x=320-ancho;
	menu::imprimir();
}
void menu::calcular_dimensiones()
{
	int indice;

	int maximo=0;
	int actual=0;

	num_op=0;
	for(indice=0;indice<TOTAL1 && texto[indice];indice++){
		if(texto[indice]=='~')
			indice++;
		if(texto[indice]=='.'){
			num_op++;
			if(maximo<actual)
				maximo=actual;
			actual=0;
			continue;
		}
		actual++;
	}
	if(!maximo){
		maximo=actual;
		num_op++;		// MIRAR ESTO
	}
	ancho=maximo*DIM+DIM+1;
	if(ancho % 2)
		ancho++;
	alto=num_op*(DIM+4)+3;
	if ((buffer = (char *)farmalloc(ancho*alto+4)) == NULL)
	{
		error_menus();
	}
	numero_opciones=num_op;
}
void menu::imprimir()
{
	int x1=x+4;
	int y1=y+4;
	int x2=x1;
	int y2=y1;

	int indice;
	char colorao=0;
	int col=color;

	scursoff();

	borrado=0;
	coger_imagen(x,y,alto,ancho,buffer);
	fill(x,y,ancho,alto,colorfondo);
	relieve(x,y,ancho,alto);

	for(indice=0;indice<TOTAL1 && texto[indice];indice++){
		if(colorao){
			colorao=0;
			col=color;
		}
		if(texto[indice]=='~'){
			colorao=1;
			col=12;
			indice++;
		}
		if(texto[indice]=='.'){
			y1+=DIM+4;
			y2=y1;
			x2=x1;
			continue;
		}
		displaychar(texto[indice],x2,y2,col,colorfondo);
		x2+=DIM;
	}
	scurson();
}
void menu::gestionar()
{
	int xraton,yraton;
	int opcion;
	int op=-1;
	int op1=-1;

	do{
		opcion=-1;
		if(!kbhit())  // raton
		{
			posicion(&xraton,&yraton);
			if(yraton>=y && yraton<=y+alto
				&& xraton>=x && xraton<=x+ancho)
			{
				op=(yraton-(y+4))/(DIM+4);
				if(op!=op1)
				{
					imprimir_opcion(op,15);
					if(op1!=-1)
						imprimir_opcion(op1,color);
					op1=op;
				}
			}
			else
			{
				op=-1;
				if(op!=op1)
					imprimir_opcion(op1,color);
				op1=op;
			}

			if(sboutoni())
			{
				posicion(&xraton,&yraton);
				if(yraton>=y && yraton<=y+alto
					&& xraton>=x && xraton<=x+ancho)
				{
					while(sboutoni());
					opcion=(yraton-(y+4))/(DIM+4); // cambiar si cambia alfabeto
					break;
				}
			}
			if(sboutond()){
				break;
			}
		}
		else
		{
			char tecla;
			if(comprobar_tecla(ESC))
				break;
			opcion=comprobar_tecla(texto);

		}
	}while(opcion==-1);
	if(opcion!=-1){
		borrar();
		funciones[opcion]();
	}
/*	scursoff();
	menu_barra::imprimir_menu();
	scurson(); */
}

menu::~menu()
{
	scursoff();
	if(!borrado)
		dejar_imagen(x,y,alto,ancho,buffer);
	if(buffer!=0)
		farfree(buffer);
	scurson();
}

//////////////////////////
//       MENSAJES
//////////////////////////

mensaje::mensaje(int x1,int y1,int ancho1,int alto1)
{
	x=x1;
	y=y1;
	ancho=ancho1;
	alto=alto1;

	if(ancho % 2)
		ancho++;
	if ((buffer = (char *)farmalloc(ancho*alto+4)) == NULL)
	{
		error_menus();
	}
	bandera=0;
	borrado=1;
	resto(x1,y1);
}

mensaje::mensaje(int x1,int y1,char *cadena,int lineas)
{
	cambiar_colores();
	strcpy(texto,cadena);
	calcular_dimensiones();
	bandera=1;
	resto(x1,y1,lineas);
}
void mensaje::resto(int x1,int y1,int lineas)
{
	if(x1==-1)
		x=160-ancho/2;
	else
		x=x1;
	if(y1==-1)
		y=100-alto/2;
	else
		y=y1;
	if(lineas){
		num_op+=lineas;
		alto=num_op*(DIM+4)+4;
		if(y1==-1)
			y=100-alto/2;
		farfree(buffer);
		if ((buffer = (char *)farmalloc(ancho*alto+4)) == NULL)
		{
			error_menus();
		}

/*		if ((buffer = (char *)farrealloc((void *)buffer,ancho*alto+4)) == NULL)
		{
			clrscr();
			printf("No hay suficiente memoria.\n");
			exit(1);
		}*/
	}

//	menu::imprimir();
	borrar_buffer();
}
void mensaje::gestionar()
{
	do{
		if(comprobar_tecla())
			return;
		if(sboutond())
			return;
	}while(1);
}
void mensaje::imprimir()
{
	if(bandera)
		menu::imprimir();
	else
	{
		scursoff();
		borrado=0;
		coger_imagen(x,y,alto,ancho,buffer);
		fill(x,y,ancho,alto,colorfondo);
		relieve(x,y,ancho,alto);
		scurson();
	}
}

mensaje::~mensaje()
{
}
void mensaje::imprimir_linea(char *str,int linea)
{
	int x2=x+4;
	int y2=y+4+(DIM+4)*linea;

	x2=x+ancho/2-(strlen(str)*DIM)/2;

	scursoff();
	displaystring(str,x2,y2,color,colorfondo);
	scurson();
}


////////////////////////////
// PREGUNTAS	       ////
////////////////////////////


pregunta::pregunta(int x1,int y1,char *cadena) : mensaje(x1,y1,cadena,2)
{
	imprimir();
}
pregunta::gestionar()
{
	boton si(x+ancho/2-DIM-15-4,y+alto-15-4,"~Si");
	boton no(x+ancho/2+15-4,y+alto-15-4,"~No");

	do{
		if(si.gestionar())
			return 1;
		if(no.gestionar())
			return 0;
		if(sboutond())
			return 0;
		if(comprobar_tecla(ESC))
			return 0;
/*		if(!kbhit() && raton)
		{
			if(si.gestionar())
				return 1;
			if(no.gestionar())
				return 0;
			if(sboutond())
				return 0;
		}
		else
		{
			char tecla=(char)tolower(biostec());
			if(tecla==ESC)
				return 0;
			if(si.gestionar(tecla))
				return 1;
			if(no.gestionar(tecla))
				return 0;
		}
*/
	}while(1);
}

pregunta::~pregunta()
{
}

///////////////////////////
///   CADENAS 	///////
////////////////////////

cadena::cadena(int x1,int y1,int l,char mod)
{
	int ancho,alto;
	l++;
	longit=(unsigned char)l;
	alto=DIM+12+1;
	ancho=DIM*l+12;
	if(x1==-1)
		x=160-ancho/2;
	else
		x=x1;
	if(y1==-1)
		y=100-alto/2;
	else
		y=y1;
	modo=mod;
	vacio=0;
	str=new char [longit];
	str[0]=0;
}
void cadena::imprimir(char *str1)
{
	char *blancos;
	int bucle;
	if(modo==CON_RELIEVE){
		blancos=new char [longit];
		memset(blancos,' ',longit);
		blancos[longit]=0;
		vacio=new mensaje(x,y,blancos);
		vacio->imprimir();
		x+=3;
		y+=3;
		delete blancos;
	}
	if(strlen(str1)<longit){
		if(str1)
			strcpy(str,str1);
	}
	else
		memcpy(str,str1,longit-1);
	scursoff();
	fill(x,y,DIM*longit+2,DIM+1,0);
	for(bucle=0;str[bucle];bucle++){
		if(bucle==longit-1)
			break;
		displaychar(str[bucle],x+2+DIM*bucle,y+1,15,0);
	}
	indice=bucle;
	displaychar(' ',x+2+DIM*indice,y+1,0,15);
	scurson();
}

cadena::~cadena()
{
	delete str;
	if(vacio!=0)
		delete vacio;
}
void cadena::gestionar(char *cad)
{
	scursoff();
//	int indice;
	int l=(int) longit;

//	indice=0;
//	cad[0]=0;
	strcpy(cad,str);
	int final=0;
	do
	{
		displaychar(' ',x+2+DIM*indice,y+1,0,15); // x+6,Y+7
		char tecla=(char)tolower(biostec());
		switch(tecla)
		{
			case ESC:cad[0]=0;
				 final=1;
				 break;
			case DEL:
			case DEL1:
				 displaychar(' ',x+2+DIM*indice,y+1,15,0);
				 if(indice!=0)
					 indice--;
				 break;
			case  13:cad[indice]=0;
				 final=1;
				 break;
			default:
				if(indice!=l-1){
					cad[indice]=tecla;
					displaychar(cad[indice],x+2+DIM*indice,y+1,15,0);
					indice++;

				}
				break;
		}
	}while(!final);
	if(vacio!=0)
		vacio->borrar();
	scurson();
}
////////////////////////////
// BARRAS
////////////////////////////

barra::barra(int x1,int y1,int ancho1,int alto1,int n,char tecla1a,char tecla2a,char sentido1)
{
	x=x1; y=y1;
	ancho=ancho1; alto=alto1;
	tecla1=tecla1a; tecla2=tecla2a;
	nelementos=n;
	sentido=sentido1;
	pos=0;
	fill(x,y,ancho,alto,0);
	imprimir(0);
}
void barra::imprimir(int posicion)
{
	int x1;
	int y1;
	int paso;
	if(posicion>=nelementos || posicion<0)
		return;
	if(sentido==VERTICAL)
	{
		paso=(pos*alto)/nelementos;
		y1=y+paso;
		x1=x;
		scursoff();
		linea256(x1,y1,x1+ancho-1,y1,0);
		paso=(posicion*alto)/nelementos;
		y1=y+paso;
		linea256(x1,y1,x1+ancho-1,y1,15);
		scurson();
		pos=posicion;
	}
	else
	{
		paso=(pos*ancho)/nelementos;
		y1=y;
		x1=x+paso;
		scursoff();
		linea256(x1,y1,x1,y1+alto-1,0);
		paso=(posicion*ancho)/nelementos;
		x1=x+paso;
		linea256(x1,y1,x1,y1+alto-1,0);
		scurson();
		pos=posicion;
	}
}
int barra::gestionar(int &pos1,int incremento)
{
	int xraton,yraton;
	int y1;
	int paso;
	if(sboutoni()){
		posicion(&xraton,&yraton);
		if(yraton>=y && yraton<=y+alto
			&& xraton>=x && xraton<=x+ancho)
		{
			while(sboutoni());
			switch(sentido){
			case VERTICAL:
				paso=(pos*alto)/nelementos;
				y1=y+paso;
				if(yraton<y1)
					pos1=pos-incremento;
				else pos1=pos+incremento;
				break;
			}
			imprimir(pos1);
			return 1;
		}
	}
	if(comprobar_tecla(tecla1))
	{
		pos1=pos-incremento;
		if(pos1<0)
			pos1=0;
		imprimir(pos1);
		return 1;
	}
	if(comprobar_tecla(tecla2))
	{
		pos1=pos+incremento;
		if(pos1>=nelementos)
			pos1=nelementos-1;
		imprimir(pos1);
		return 1;
	}
	return 0;
}
barra2::barra2(int x1,int y1,int alto1,int n,char tecb11,char tecb21)
{
	x=x1; y=y1;
	alto=alto1;
	nelementos=n;
	tecb1=ARR;
	tecb2=ABA;
	if(tecb11)
		tecb1=tecb11;
	if(tecb21)
		tecb2=tecb21;
	p_up=PAG_ARR;
	p_do=PAG_ABA;
	boton1=new boton(x,y,8,8,tecb1);
	boton2=new boton(x,y+8+2+alto+2,8,8,tecb2);
	fill(x,y+8+2,8,alto,0);
	pos=0;
	imprimir(0);
}
void barra2::borrar()
{
	scursoff();
	fill(x,y+8+2,8,alto,0);
	scurson();
}
barra2::~barra2()
{
	delete boton1;
	delete boton2;
}
void barra2::imprimir(int posicion)
{
	int x1;
	int y1;
	int paso;
	if(posicion>=nelementos || posicion<0)
		return;
	paso=(pos*alto)/nelementos;
	y1=y+paso+10;
	x1=x;
	scursoff();
	linea256(x1,y1,x1+8-1,y1,0);
	paso=(posicion*alto)/nelementos;
	y1=y+paso+10;
	linea256(x1,y1,x1+8-1,y1,15);
	scurson();
	pos=posicion;
}
int barra2::gestionar(int &pos1,int incremento)
{
	int xraton,yraton;
	int y1;
	int paso;
	posicion(&xraton,&yraton);
	if(yraton>=y+10 && yraton<=y+alto+10
	&& xraton>=x && xraton<=x+8)
	{
		if(sboutoni()){
			while(sboutoni());
			paso=(pos*alto)/nelementos;
			y1=y+paso;
			if(yraton<y1){
				pos1=pos-incremento;
				if(pos1<0)
					pos1=0;
			}
			else{
				pos1=pos+incremento;
				if(pos1>=nelementos)
					pos1=nelementos-1;
			}
			imprimir(pos1);
			return 1;
		}
	}
	if(comprobar_tecla(p_up)){
		pos1=pos-incremento;
		if(pos1<0)
			pos1=0;
		imprimir(pos1);
		return 1;
	}
	if(comprobar_tecla(p_do)){
		pos1=pos+incremento;
		if(pos1>=nelementos)
			pos1=nelementos-1;
		imprimir(pos1);
		return 1;

	}
	if(boton1->gestionar()){
		if(pos!=0)
			pos1=pos-1;
		imprimir(pos1);
		return 1;
	}
	if(boton2->gestionar()){
		if(pos!=nelementos-1)
			pos1=pos+1;
		imprimir(pos1);
		return 1;
	}
	return 0;
}

///////////////////////////////
////  DIRECTORIO
//////////////////////////////

////////////////////////////
//	EDITOR             //
///////////////////////////
#ifdef _EDITOR_
editor::editor(int numero_de_lineas)
{

	numlin=numero_de_lineas;
	if(numlin>255)
		numlin=255;
	if(numlin<0)
		numlin=2;
	if(!(buffer=new char [numlin*51]))  // 51 caracteres por linea
	{
		printf("No hay memoria");
		exit(13);
	}
	memset(buffer,0,numlin*51);
	tam=numlin*51;
	vacio=new mensaje(0,200-15-8-70,320,15+8+70); // 107
	x=5;
	y=200-15-8-70+5;
}
void editor::imprimir()
{
	int lineas_impresas;
	int x,y;
	vacio->imprimir();

	lineas_impresas=numlin;
	if(lineas_impresas>10)
		lineas_impresas=10;
	vacio->obtener_coordenadas(x,y);
	scursoff();
	fill(x+4,y+4,320-8,lineas_impresas*(DIM+1),0);
	scurson();
	cargar=new boton(4,183,"Cargar");
	salvar=new boton(56,183,"Salvar");
	cancel=new boton(108,183,"Cancel",ESC);
	ok    =new boton(160,183,"Ok");

}
char *editor::linea(int lin)
{
	char *aux;
	aux=buffer+lin*51;
	return aux;
}


int editor::fin_linea(int lin)
{
	char *aux;
	aux=linea(lin);
	int indice=0;
	while(aux[indice]!=1 && aux[indice]!=0)
		indice++;
	return indice;
}
#define ON 1
#define OFF 0
void editor::escribir(char c)
{
	int color,color_f;
	color=15;
	color_f=0;
	scursoff();
	displaychar(c,x+2+DIM*columna,y+(fila-inicial)*(DIM+1),color,color_f);
	scurson();
}
void editor::escribir_linea(int lin)
{
	char *aux;
	int color=15;
	int color_f=0;
	int col=columna;
	int fil=fila;
	columna=0;
	fila=lin;
	aux=linea(lin);
	scursoff();
	while(aux[0]!=0 && aux[0]!=1){
		displaychar(aux[0],x+2+DIM*columna,y+(fila-inicial)*(DIM+1),color,color_f);
		aux++;
		columna++;
	}
	for(;columna<50;columna++)
		displaychar(' ',x+2+DIM*columna,y+(fila-inicial)*(DIM+1),color,color_f);
	scurson();
	columna=col;
	fila=fil;
}
void editor::escribir_ventana()
{
	int f;
	for(f=inicial;f<inicial+10;f++)
		escribir_linea(f);
}

void editor::cursor(char c)
{
	int color,color_f;
	int col_aux;
	char pos_cursor[20];
	color=15;
	color_f=0;
	if(fila<0){
		fila=0;
		cambiar_actual();
	}
	if(fila==numlin){
		fila--;
		cambiar_actual();
	}
	if(fila<inicial){
		inicial--;
		escribir_ventana();
	}
	if(fila>=inicial+10){
		inicial++;
		escribir_ventana();
	}
	if(c){
		color=0;
		color_f=15;
		col_aux=fin_linea(fila);
		if(columna>col_aux)
			columna=col_aux;
	}
	c=actual[columna];
	switch(c){
		case 0:
		case 1:
			c=' ';
	}
	scursoff();
	sprintf(pos_cursor,"%03d:%03d MAX:%03d",fila+1,columna+1,numlin);
	displaystring(pos_cursor,200,187,15,7);
	displaychar(c,x+2+DIM*columna,y+(fila-inicial)*(DIM+1),color,color_f);
	scurson();
}
void editor::cambiar_actual()
{
	actual=linea(fila);
}
void editor::del(char modo)
{
	int numbytes;
	switch(modo){
	case DEL1:
		numbytes=fin_linea(fila)-columna+1;
		if((fila*51+columna)!=0)
		{
			if(columna==0){
				if(actual[0]==0 || actual[0]==1){
					cursor(OFF);
					fila--;
					cambiar_actual();
					columna=fin_linea(fila);
					numbytes=tam-(fila+2)*51;
					memcpy(buffer+(fila+1)*51,buffer+(fila+2)*51,numbytes);
					escribir_ventana();
					cursor(ON);
				}
			}
			else
			{
				cursor(OFF);
				columna--;
				buffer[(fila*51+columna)]=0;
				memcpy(buffer+(fila*51+columna),buffer+(fila*51+columna)+1,numbytes);
				escribir_linea(fila);
				cursor(ON);
			}
		}
		break;
	case DEL:
		if(columna==0 && (actual[0]==0 || actual[0]==1)){
			if(actual[51]!=0 && actual[51]!=1){
				cursor(OFF);
				columna=fin_linea(fila);
				numbytes=tam-(fila+1)*51;
				memcpy(buffer+(fila)*51,buffer+(fila+1)*51,numbytes);
				escribir_ventana();
				cursor(ON);
			}
		}
		else
		{
			if(actual[columna]!=0 && actual[columna]!=1){
				numbytes=fin_linea(fila)-columna+1;
				cursor(OFF);
				buffer[(fila*51+columna)]=0;
				memcpy(buffer+(fila*51+columna),buffer+(fila*51+columna)+1,numbytes);
				escribir_linea(fila);
				cursor(ON);
			}
		}

		break;
	}
}
void editor::grabar(void)
{
	char nombre[13];
	FILE *fichero;
	int fila,columna;
	char c;
	mensaje m(-1,65,"Introduce Nombre");
	cadena ca(-1,-1,8);
	m.imprimir();
	ca.imprimir();
	ca.gestionar(nombre);
	if(nombre[0]){
		strcat(nombre,".CND");
		if((fichero=fopen(nombre,"wb"))==NULL)
			exit(4);
		for(fila=0;fila<numlin;fila++){
			if(buffer[fila*51]==0)
				break;
			for(columna=0;columna<51;columna++){
				c=buffer[fila*51+columna];
				if(c==0)
					continue;
				if(c==1){
					putc(10,fichero);
					putc(13,fichero);
					continue;
				}
				putc(c,fichero);
			}
		}
	}
	fclose(fichero);
}
void editor::load(void)
{
	char nombre[13];
	FILE *fichero;
	int fila,columna;
	int c;
//	directorio d("cnd");

	mensaje m(-1,65,"Introduce Nombre"); /*  */
	cadena ca(-1,-1,8);                  /*  */
	m.imprimir();                        /* QUITAR ESTAS LINEAS EN LA */
	ca.imprimir();			     /* VERSION DEFINITIVA */
	ca.gestionar(nombre);                /* AUTO-GESTION DEL DIRECTORIO */
//	d.gestionar(nombre);		     /*  */
	if(nombre[0]){
		strcat(nombre,".CND");     // QUITAR
		if((fichero=fopen(nombre,"rb"))==NULL)
			exit(4);
		for(fila=0;fila<numlin;fila++){
			for(columna=0;columna<51;columna++){
				c=getc(fichero);
				if(feof(fichero))
					goto fuera;
				if(c==0)
					break;
				if(c==10){
					c=getc(fichero);
					buffer[fila*51+columna]=1;
					break;
				}
				buffer[fila*51+columna]=c;
			}
		}
	}
	fuera:
	fclose(fichero);
}
void editor::intro()
{
	char *aux1,*aux2;
	int tam;

	tam=(numlin-2-fila)*51;

	aux1=buffer+(numlin*51)-1;
	aux2=aux1-51;
	asm{
		push ds
		push es
		push si
		push di
		mov cx,tam
		lds si,aux2
		les di,aux1
		std
		rep movsb
		pop di
		pop si
		pop es
		pop ds
	}

	memcpy(buffer+(fila+1)*51,buffer+(fila)*51+columna,51-columna);
	aux1=buffer+fila*51+columna;
	memset(buffer+fila*51+columna,0,51-columna);
	buffer[(fila*51+columna)]=1;
	cursor(OFF);
	columna=0;
	fila++;
	cambiar_actual();
	escribir_ventana();
	cursor(ON);
//	check("intro");
}

void editor::gestionar()
{
	int final=0;
	columna=0;
	fila=0;
	inicial=0;
	actual=buffer;

	cursor(ON);
	do
	{
		char tecla=comprobar_tecla();
		switch(tecla)
		{
			case 0:break;
			case ESC:
				 return;
			case DEL:
			case DEL1:
				 del(tecla);
				 break;
			case  13:intro();
				 break;
			case ARR:
				 if(fila!=0){
					cursor(OFF);
					fila--;
					cambiar_actual();
					cursor(ON);
				 }
				 break;
			case ABA:
				 if(fila!=numlin){
					cursor(OFF);
					fila++;
					cambiar_actual();
					if(actual[0]==0){
						fila--;
						cambiar_actual();
					}
					cursor(ON);
				 }
				 break;
			case IZQ:
				 if(columna!=0){
					 cursor(OFF);
					 columna--;
					 cursor(ON);
				 }
				 break;
			case DER:
				 if(columna!=50){
					 cursor(OFF);
					 columna++;
					 cursor(ON);
				 }
				 break;
			default:
				if(columna!=50){
					buffer[fila*51+columna]=tecla;
					escribir(buffer[(fila*51+columna)]);
					columna++;
					cursor(ON);
				}
				break;
		}
		if(cancel->gestionar())
			return;
		if(salvar->gestionar())
			grabar();
		if(cargar->gestionar()){
			load();
			cursor(OFF);
			fila=columna=inicial=0;
			cambiar_actual();
			escribir_ventana();
			cursor(ON);
		}
	}while(!final);
}


editor::~editor()
{
	delete cargar;
	delete salvar;
	delete cancel;
	delete ok;
	delete buffer;
	delete vacio;
}
#endif
/////////////////////////
//   VENTANAS DE DATOS
/////////////////////////


ventana_datos::ventana_datos(int x1,int y1,char *datos1,int num1,int anchocar1,int max1,int paso1)
{
	x=x1;
	y=y1;
	datos=datos1;
	anchocar=anchocar1;
	num=num1;
	paso=paso1;
	max=max1;
	seleccion=-1;
}
void ventana_datos::imprimir(int x1,int y1,int inicio)
{
	int x2=x;
	int y2=y;
	x=x1;
	y=y1;
	imprimir(inicio);
	y=y2;
	x=x2;
}
void ventana_datos::imprimir(int inicio)
{
	int f;
	int x1=x;
	int y1=y;
	char *blancos;
	if(inicio>max)
		inicio=max;

	int fin=inicio+num;
	int fin1=fin;
	blancos=new char[anchocar];
	if(fin>max)
		fin=max;

	char *aux;
	for(f=0;f<anchocar;f++)
		blancos[f]=' ';

	blancos[anchocar-1]=0;


	aux=datos+anchocar*inicio;
	scursoff();
	for(f=inicio;f<fin;f++){
		displaystring(blancos,x,y,15,0);
		displaystring(aux,x,y,15,0);
		aux+=anchocar;
		y+=paso;
	}
	for(f=fin;f<fin1;f++){
		displaystring(blancos,x,y,15,0);
		y+=paso;
	}
	scurson();
	delete blancos;
	x=x1;
	y=y1;
	seleccion=-1;
}
void ventana_datos::imprimir_linea(int linea,int inicio,char modo)
{
	int f;
	int y1;
	int color,color_fondo;
	char *blancos;
	if(linea==-1)
		return;
	blancos=new char[anchocar];

	char *aux;
	for(f=0;f<anchocar;f++)
		blancos[f]=' ';

	blancos[anchocar-1]=0;


	aux=datos+anchocar*(linea+inicio);
	y1=y+linea*paso;
	if(modo==INV){
		color=0;
		color_fondo=15;
	}
	else
	{
		color=15;
		color_fondo=0;
	}

	scursoff();

	displaystring(blancos,x,y1,color,color_fondo);
	displaystring(aux,x,y1,color,color_fondo);
	scurson();
	delete blancos;
}
#define SIN_TECLADO 0

int ventana_datos::gestionar(int inicio,char mod=1)
{
	int xraton,yraton;
	int selec;
	if(sboutoni()){
		posicion(&xraton,&yraton);
		if(yraton>=y && yraton<=y+num*paso
			&& xraton>=x && xraton<=x+(anchocar-1)*DIM)
		{
			selec=(yraton-y)/paso;
			if(seleccion!=selec){
				if(inicio+selec>=max)
					return -1;
				imprimir_linea(seleccion,inicio,NORMAL);
				imprimir_linea(selec,inicio,INV);
				seleccion=selec;
				while(sboutoni());
				return -1;
			}
			else{
				while(sboutoni());
				return (selec+inicio);
			}
		}
	}
	if(mod){
		if(comprobar_tecla(ENT))
			return (inicio);
	}
	return -1;
}
int ventana_datos::gestionar(int x1,int y1,int inicio)
{
	int x2=x;
	int y2=y;
	int salida;
	x=x1;
	y=y1;
	salida=gestionar(inicio,SIN_TECLADO);
	y=y2;
	x=x2;
	return(salida);
}

//////////////////////////////////
//////  DIRECTORIO
/////////////////////////////////
int sort_function( const void *a, const void *b)
{
   return( strcmp((const char*)a,(const char*)b) );
}

directorio::directorio(char ext1[4])
{
	strcpy(ext,ext1);
	iniciar();
}
void directorio::iniciar()
{
	getcwd(dir_orig,MAXPATH);
	strcpy(dir_actual,dir_orig);
	disco_orig=getdisk();
	disco_actual=disco_orig;
	numero_discos=setdisk(disco_actual);
}
void directorio::restaurar()
{
	setdisk(disco_orig);
	chdir(dir_orig);
}
directorio::~directorio()
{
//	restaurar();
	check("DIRECTORIO");
}
void directorio::imprimir_directorio(int x,int y,int len)
{
	int longitud=34;
	char espacios[]="                                 ";
	displaystring(espacios,x,y,15,7);
	char *aux=dir_actual;
	if(strlen(dir_actual)>longitud){
		char nombre[35]="c:\..";
		nombre[0]=dir_actual[0];   //c
		nombre[1]=dir_actual[1];   //:
		nombre[2]=dir_actual[2];   //\
		aux=dir_actual+strlen(dir_actual)-28;
		strcat(nombre,aux);
		aux=nombre;
	}
	displaystring(aux,x,y,15,7);
}
void directorio::cambiar_camino()
{
	char cade[45];
	char men[30];
	int unidad;
	char drive1[4];
	char dir1[81];
	char file1[10];
	char ext1[5];
	int flags;

	sprintf(men,"Introduce nuevo camino");
	mensaje pedir(-1,30,men);
	pedir.imprimir();
	cadena c(-1,58,40);
	c.imprimir();
	c.gestionar(cade);
	if(cade[0]==0)
		return;

	strcat(cade,"\\");
	flags=fnsplit(cade,drive1,dir1,file1,ext1);
	if(flags & DRIVE){
		unidad=drive1[0]-'a';
		setdisk(unidad);
	}
	dir1[strlen(dir1)-1]=0;
	if(flags & DIRECTORY){
		if(!chdir(dir1)){
			getcwd(dir_actual,MAXPATH);
		}
		else{
			setdisk(disco_actual);
			return;
		}
	}
	disco_actual=unidad;
/*	Subdir subdir;
	subdir.gestionar(dir_actual);*/
	return;

}
void directorio::nuevo_directorio(int nuevo)
{
	char dir1[14];
	char *p;
	p=fich[nuevo];
	p++;

	sprintf(dir1,"%s",p);
	dir1[strlen(dir1)-1]=0;
	if(!chdir(dir1)){
		getcwd(dir_actual,MAXPATH);
	}
}
void directorio::error_dir()
{
	char men[]="ERROR: Nombre de fichero invalido";
	mensaje m(-1,30,men);
	m.imprimir();
	m.gestionar();
}

int directorio::obtener_nombre()
{
	char cade[45];
	char men[30];
	int unidad;
	char drive1[4];
	char dir1[81];
	char file1[10];
	char ext1[5];
	int flags;

	sprintf(men,"Introduce nombre del fichero");
	mensaje pedir(-1,30,men);
	pedir.imprimir();
	cadena c(-1,58,12);
	c.imprimir();
	c.gestionar(cade);
	pedir.borrar();
	if(cade[0]==0)
		return -1;

	flags=fnsplit(cade,drive1,dir1,file1,ext1);
	if(flags & DRIVE){
		error_dir();
		return -1;
	}
	if(flags & DIRECTORY){
		error_dir();
		return -1;
	}
	if(strlen(file1)>8){
		error_dir();
		return -1;
	}

	if(!(flags & EXTENSION)){
		sprintf(n1,"%s.%s",file1,ext);
	}
	else
		sprintf(n1,"%s",file1);
	return -2;

}
//int error_en_disco;

void directorio::cambiar_unidad()
{
	char cad[4];
	char men[40];
	sprintf(men,"Introduce unidad: (Actual: %c)",(char)(disco_actual+65));
	mensaje pedir(-1,30,men);
	pedir.imprimir();
	cadena c(-1,45,1);
	c.imprimir();
	c.gestionar(cad);

	if(!cad[0])
		return;
	int unidad=(int)toupper(cad[0])-65;
  //	do{
//		error_en_disco=0;
	setdisk(unidad);
/*		if(error_en_disco){
			mensaje m(-1,-1,"Introduzca un disco en la unidad");
			m.imprimir();
			m.gestionar();
		}
	}while(error_en_disco); */
	if(unidad==getdisk()){
		disco_actual=unidad;
		getcwd(dir_actual,MAXPATH);
	}
//	error_en_disco=0;

}
void directorio::cambiar_extension()
{
	char men[40];
	char cad[4];

	sprintf(men,"Introduce extension: (Actual: %s)",ext);
	mensaje pedir(-1,30,men);
	pedir.imprimir();
	cadena c(-1,50,3);
	c.imprimir();
	c.gestionar(cad);
	if(!cad[0])
		return;
	strcpy(ext,cad);
}

void directorio::crear_tabla(char tabla[][15],int &num)
{
	int done;
	int buc=0;
	struct ffblk ffblk;
	char tipo[6];

	sprintf(tipo,"*.*");
	done = findfirst(tipo,&ffblk,16);
//	if(!(ffblk.ff_attrib & 16))
//			done=-1;

	while (!done && buc<200){
//		strcpy(tabla[buc],ffblk.ff_name);
//		if(!(strcmp(ffblk.ff_name,".")))
//			buc--;
//		else
			if((ffblk.ff_attrib & 16) &&
			(strcmp(ffblk.ff_name,".")))
			{
				sprintf(tabla[buc],"<%s>",ffblk.ff_name);
				buc++;
			}
		done = findnext(&ffblk);
//		if(!(ffblk.ff_attrib & 16))
//			done=-1;
//		buc++;
	}
	qsort((void *)tabla,buc,15,sort_function);
	directorios=buc;
	sprintf(tipo,"*.%s",ext);
	done = findfirst(tipo,&ffblk,0);
	while (!done && buc<200){
		strcpy(tabla[buc],ffblk.ff_name);
		done = findnext(&ffblk);
		buc++;
	}
	tabla[buc][0]=0;
	num=buc;
	char *aux;
	aux=(char *)tabla+directorios*15;
//	qsort(tabla+directorios*15,num-directorios,15,sort_function);
	qsort((void *)aux,num-directorios,15,sort_function);
}
void directorio::imprimir()
{
}
/*#pragma warn -par

int handler(int errval,int ax,int bp,int si)
{
	error_en_disco=1;
	hardresume(2);
	return 2;
}
#pragma warn +par
*/

void directorio::gestionar(char *nombre)
{
	int x,y;

//	harderr((int (far *)())handler);

	inicio=0;
//	char fich[200][13];
	crear_tabla(fich,num_ficheros);
	mensaje p(-1,-1,"                                        .",10);
	p.imprimir();
	p.obtener_coordenadas(x,y);
	int xdir=x+5;
	int ydir=y+2*DIM+5;
	int xdirpaso=6;
	int ydirpaso=7;
	int ancho=152+24;
	int alto=92;

	boton escape(x+4,y+4,8,8);
	scursoff();
	fill(x+4,y+2*DIM+4,ancho,alto,0);    // 25 * 13
	linea256(xdir+xdirpaso*12+2+12,ydir,xdir+xdirpaso*12+2+12,ydir+88,15);
	inicio=0;
	imprimir_directorio(x+16,y+6,30);

	barra2 control(x+4+ancho+2,ydir,alto-22,num_ficheros);
	int x1=x+4+ancho+2+10;
	int y1=ydir-1;

	boton unidad(x1,y1,"~Disco");
	boton camino(x1,y1+15,"~Chdir");
	boton extension(x1,y1+30,"~Ext");
	boton atras(x1,y1+50,"~..");
	boton origen(x1,y1+65,"~Origen");
	boton nombr(x1,y1+80,"~Nombre");

	displaystring(ext,x1+30,y1+34,15,7);

	scurson();
	ventana_datos direc(xdir,ydir,(char *)fich,13,15,num_ficheros,7);
	char cambiado=1;
	char directorio_cambiado=0;
	int elegido;
	do{

		if(escape.gestionar()){
			nombre[0]=0;
			return;
		}
		if(unidad.gestionar()){
			cambiar_unidad();
			imprimir_directorio(x+16,y+6,30);
			directorio_cambiado=1;
		}
		if(extension.gestionar()){
			cambiar_extension();
			scursoff();
			displaystring("   ",x1+30,y1+34,15,7);
			displaystring(ext,x1+30,y1+34,15,7);
			scurson();
			directorio_cambiado=1;
		}
		if(origen.gestionar()){
			setdisk(disco_orig);
			chdir(dir_orig);
			disco_actual=disco_orig;
			strcpy(dir_actual,dir_orig);
			imprimir_directorio(x+16,y+6,30);
			directorio_cambiado=1;
		}
		if(camino.gestionar()){
			cambiar_camino();
			imprimir_directorio(x+16,y+6,30);
			directorio_cambiado=1;
		}

		if(atras.gestionar()){
			if(!chdir("..")){
                        	getcwd(dir_actual,MAXPATH);
				imprimir_directorio(x+16,y+6,30);
				directorio_cambiado=1;
			}
		}
		if(control.gestionar(inicio,13))
			cambiado=1;
		elegido=direc.gestionar(inicio);
		if(elegido==-1)
			elegido=direc.gestionar(xdir+DIM*15,ydir,inicio+13);
		if(elegido>=0 && elegido<directorios){
			nuevo_directorio(elegido);
			imprimir_directorio(x+16,y+6,30);
			elegido=-1;
			directorio_cambiado=1;
		}

		if(directorio_cambiado){
			crear_tabla(fich,num_ficheros);
			directorio_cambiado=0;
			inicio=0;
			control.cambiar_nelementos(num_ficheros);
			direc.cambiar_nelementos(num_ficheros);
			control.borrar();
			cambiado=1;
		}
		if(cambiado){
			direc.imprimir(inicio);
			direc.imprimir(xdir+DIM*15,ydir,inicio+13);
			control.imprimir(inicio);
			cambiado=0;
		}
		if(nombr.gestionar())
			elegido=obtener_nombre();
		check("DIR NOMBRE");
	}while(elegido==-1);
	if(elegido==-2)
		strcpy(nombre,n1);
	else
		strcpy(nombre,fich[elegido]);
	check("DIR DESPUES");

}

///////////////////////////
/// OTRAS FUNCIONES	   //
//////////////////////////

int longitud(char *cadena)
{
	int indice,contador;

	for(indice=0,contador=0;cadena[indice];indice++,contador++)
		if(cadena[indice]=='~')
			indice++;
	return(contador);
}

void coger_imagen(int x,int y,int alto,int ancho,char *graf)
{
	asm push di
	asm push es
	asm push ds
	_ES=FP_SEG(graf);
	_DI=FP_OFF(graf);

	_DS=0xA000;
	_CX=alto;
	_SI=y*320+x;
	_BX=ancho;
	asm sar bx,1

   bucle:
	asm push si
	asm push cx
	_CX=_BX;
	asm rep movsw
	asm pop cx
	asm pop si
	_SI+=320;
	asm loop bucle
	asm pop ds
	asm pop es
	asm pop di
}
void dejar_imagen(int x,int y,int alto,int ancho,char *graf)
{
	asm push di
	asm push es
	asm push ds
	_ES=0xA000;
	_DI=y*320+x;

	_BX=ancho;
	_CX=alto;

	_DS=FP_SEG(graf);
	_SI=FP_OFF(graf);

	asm sar bx,1

   bucle:
	asm push di
	asm push cx
	_CX=_BX;
	asm rep movsw

	asm pop cx
	asm pop di
	_DI+=320;
	asm loop bucle
	asm pop ds
	asm pop es
	asm pop di
}
void fill(int x,int y,int ancho,int alto,int color)
{
	asm push di
	asm push es
	asm push ds
	_ES=0xA000;
	_CX=alto;
	_DI=y*320+x;
	_BX=ancho;
	asm sar bx,1
	asm mov ax,color
	asm mov ah,al

   bucle:
	asm push di
	asm push cx
	_CX=_BX;
	asm rep stosw
	asm pop cx
	asm pop di
	_DI+=320;
	asm loop bucle
	asm pop ds
	asm pop es
	asm pop di
}
int comprobar_tecla(char *cadena)
{
	int opcion=0;
	int indice=0;
	int comp=0;

	while(cadena[indice] && !comp){
		if(cadena[indice]=='~')
//			comp=(c==tolower(cadena[indice+1]));
			comp=comprobar_tecla(tolower(cadena[indice+1]));
		if(cadena[indice]=='.')
			opcion++;
		indice++;
	}
	if(comp)
		return opcion;
	else    return -1;
}
void borrar_buffer()
{
	while(bioskey(1))
		bioskey(0);
	reserva=0;
}
char biostec()
{
	char codigo,ident;

	union REGS regs;

	regs.h.ah=0;
	int86(0x016,&regs,&regs);
	ident=regs.h.ah;
	codigo=regs.h.al;
	if(!codigo){
/*		if (ident==73) return(PAGARR);
		if (ident==81) return(PAGABA);
		if (ident==72) return(ARR);
		if (ident==80) return(ABA);
		if (ident==75) return(IZQ);
		if (ident==77) return(DER);
		if (ident==82) return(INS); */

		if (ident==01) return(ESC);

		if (ident==28) return(ENT);
/*		if (ident==59) return(F1);
		if (ident==60) return(F2);
		if (ident==61) return(F3);
		if (ident==62) return(F4);  */
		if (ident==83) return(DEL);
	}
	return(codigo);
/*	return(regs.x.ax);
	return(codigo);*/
}

void linea256(int x1,int y1,int x2,int y2,int color)
{
	int ay,deltaxd,deltayd,ax,aux,deltayr,deltaxr,
	    x,y,er,ed,e,i;


	_DX=1;
	_BX=1;
	ay=y2-y1;
	if(ay<0){
		asm neg bx;
		ay=-ay;
	}
	deltayd=_BX;
	ax=x2-x1;
	if(ax<0){
		asm neg dx;
		ax=-ax;
	}
	deltaxd=_DX;
	if(ax>=ay) 
		_BX=0;
	else{ 
		_DX=0;
		aux=ax;
		ax=ay;
		ay=aux;
	}
	deltayr=_BX; deltaxr=_DX;
	x=x1;
	y=y1;
	er=2*ay;
	ed=2*ay-2*ax;
	e=2*ay-ax;
	for(i=1;i<=ax+1;i++){
		putpixel256(x,y,color);
		if(e>=0){
			x+=deltaxd;
			y+=deltayd;
			e+=ed;
		}
		else{
			x+=deltaxr;
			y+=deltayr;
			e+=er;
		}
	}
	return;
}
void putpixel256(int x,int y,int color)
{
		char *pantalla=(char *)MK_FP(0xA000,0);
		pantalla[y*320+x]=(char)color;
}
void relieve(int x,int y,int ancho,int alto,char modo)
{
	int c1=15;
	int c2=0;

	if(modo){
		c1=0;
		c2=15;
	}
	linea256(x,y,x+ancho-1,y,c1);
	linea256(x+ancho-1,y,x+ancho-1,y+alto-1,8);
	linea256(x+ancho-1,y+alto-1,x,y+alto-1,c2);
	linea256(x,y+alto-1,x,y,8);

	linea256(x+1,y+1,x+ancho-2,y+1,c1);
	linea256(x+ancho-2,y+1,x+ancho-2,y+alto-2,8);
	linea256(x+ancho-2,y+alto-2,x+1,y+alto-2,c2);
	linea256(x+1,y+alto-2,x+1,y+1,8);
}
int comprobar_tecla(int tecla)
{
	union teclado{
		int tecla;
		char alto[2];
	}teclas;
	int k;
	if(bioskey(1))
	{
		teclas.tecla=bioskey(0);
		k=teclas.alto[0];
		if(k==0){
			k=teclas.alto[1];
			switch(k){
				case 72:k=ARR;
					break;
				case 75:k=IZQ;
					break;
				case 77:k=DER;
					break;
				case 80:k=ABA;
					break;
				case 73:k=PAG_ARR;
					break;
				case 81:k=PAG_ABA;
					break;
				case 83:k=DEL;
					break;
				case 14:k=DEL1;
					break;
				case 59:k=F1;
					break;
				case 60:k=F2;
					break;
				case 61:k=F3;
					break;
				case 62:k=F4;
					break;
				default:k=teclas.tecla;
					break;

			}

			borrar_buffer();
		}
		else
		{
			switch(teclas.tecla){
				case 7181:k=ENT;
					  break;
				case 0x5032:
				case 2559:k=SABA;
					  break;
				case 0x4B34:
				case 2047:k=SIZQ;
					  break;
				case 0x4D36:
				case 2303:k=SDER;
					  break;

				case 0x4838:
				case 1791:k=SARR;
					  break;
				case    2:k=AABA;
					  break;
				case    4:k=AIZQ;
					  break;
				case    6:k=ADER;
					  break;
				case    8:k=AARR;
					  break;
			}
		}
	}
	else
		k=reserva;
	if(tecla==-1 && k)
		tecla=(char)k;
	if(k==tecla){
		reserva=0;
		return tecla;
	}
	reserva=k;
	return 0;
}
int comprobar_tecla(char tecla)
{
	return(comprobar_tecla((int)tecla));
}
/*int comprobar_tecla(char tecla)
{
	union teclado{
		int tecla;
		char alto[2];
	}teclas;
	char k;
	if(bioskey(1))
	{
		teclas.tecla=bioskey(0);
		k=teclas.alto[0];
		if(k==0){
			k=teclas.alto[1];
			switch(k){
				case 72:k=ARR;
					break;
				case 75:k=IZQ;
					break;
				case 77:k=DER;
					break;
				case 80:k=ABA;
					break;
				case 73:k=PAG_ARR;
					break;
				case 81:k=PAG_ABA;
					break;
				case 83:k=DEL;
					break;
				case 14:k=DEL1;
					break;
			}
			borrar_buffer();
		}
		else
		{
			switch(teclas.tecla){
				case 7181:k=ENT;
					  break;
				case 0x5032:
				case 2559:k=SABA;
					  break;
				case 0x4B34:
				case 2047:k=SIZQ;
					  break;
				case 0x4D36:
				case 2303:k=SDER;
					  break;
				case 0x4838:
				case 1791:k=SARR;
					  break;
				case    2:k=AABA;
					  break;
				case    4:k=AIZQ;
					  break;
				case    6:k=ADER;
					  break;
				case    8:k=AARR;
					  break;
			}
		}
	}
	else
		k=reserva;
	if(tecla==-1 && k)
		tecla=k;
	if(k==tecla){
		reserva=0;
		return tecla;
	}
	reserva=k;
	return 0;
}

*/