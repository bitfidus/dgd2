#include <letters.h>

#define PRIMERA 48  /* CODIGO DE LA LETRA */
#define DIMENSION 6

#include <ctype.h>
#include <dos.h>

static char *letras;


void letras_dat()
{

	asm{
		db 'JAB'

		db 000000000b
		db 000000000b
		db 000000000b
		db 000000000b
		db 000000000b

		db 000000000b

		db 000100000b
		db 000100000b
		db 000100000b
		db 000000000b
		db 000100000b

		db 000000000b

		db 001001000b
		db 001001000b
		db 000000000b
		db 000000000b
		db 000000000b

		db 000000000b

		db 001010000b
		db 011111000b
		db 001010000b
		db 011111000b
		db 001010000b

		db 000000000b

		db 001111000b
		db 010100000b
		db 001110000b
		db 000101000b
		db 011110000b

		db 000000000b

		db 000001000b
		db 010010000b
		db 000100000b
		db 001001000b
		db 010000000b

		db 000000000b

		db 000100000b
		db 001010000b
		db 001101000b
		db 010011000b
		db 001110000b

		db 000000000b

		db 000010000b
		db 000100000b
		db 000000000b
		db 000000000b
		db 000000000b

		db 000000000b

		db 000010000b
		db 000100000b
		db 000100000b
		db 000100000b
		db 000010000b

		db 000000000b

		db 001000000b
		db 000100000b
		db 000100000b
		db 000100000b
		db 001000000b

		db 000000000b

		db 010101000b
		db 001110000b
		db 011111000b
		db 001110000b
		db 010101000b

		db 000000000b

		db 000100000b
		db 000100000b
		db 011111000b
		db 000100000b
		db 000100000b

		db 000000000b

		db 000000000b
		db 000000000b
		db 000000000b
		db 000010000b
		db 000100000b

		db 000000000b

		db 000000000b
		db 000000000b
		db 011111000b
		db 000000000b
		db 000000000b

		db 000000000b

		db 000000000b
		db 000000000b
		db 000000000b
		db 000110000b
		db 000110000b

		db 000000000b

		db 000001000b
		db 000010000b
		db 000100000b
		db 001000000b
		db 010000000b

		db 000000000b


		db 001110000b
		db 010011000b
		db 010101000b
		db 011001000b
		db 001110000b
		db 000000000b

		db 000100000b
		db 011100000b
		db 000100000b
		db 000100000b
		db 001110000b

		db 000000000b

	   db 001110000b
	   db 010001000b
	   db 000010000b
	   db 001100000b
	   db 011111000b

	   db 000000000b

	   db 011111000b
	   db 000001000b
	   db 001110000b
	   db 000001000b
	   db 011110000b

	   db 000000000b

	   db 000010000b
	   db 010010000b
	   db 011111000b
	   db 000010000b
	   db 000010000b

	   db 000000000b

	   db 011111000b
	   db 010000000b
	   db 011110000b
	   db 000001000b
	   db 011110000b

	   db 000000000b

	   db 001110000b
	   db 010000000b
	   db 011110000b
	   db 010001000b
	   db 001110000b

	   db 000000000b

	   db 011111000b
	   db 000001000b
	   db 000010000b
	   db 000100000b
	   db 000100000b

	   db 000000000b

	   db 001110000b
	   db 010001000b
	   db 001110000b
	   db 010001000b
	   db 001110000b

	   db 000000000b

	   db 001110000b
	   db 010001000b
	   db 001111000b
	   db 000001000b
	   db 000010000b

	   db 000000000b
	}
	// FIN NUMEROS
	asm{
		db 000000000b
		db 000100000b
		db 000000000b
		db 000100000b
		db 000000000b

		db 000000000b

		db 000000000b
		db 000100000b
		db 000000000b
		db 000100000b
		db 001000000b

		db 000000000b

		db 000001000b
		db 000110000b
		db 011000000b
		db 000110000b
		db 000001000b

		db 000000000b


		db 000000000b
		db 011111000b
		db 000000000b
		db 011111000b
		db 000000000b

		db 000000000b

		db 010000000b
		db 001100000b
		db 000011000b
		db 001100000b
		db 010000000b

		db 000000000b

		db 001110000b
		db 010001000b
		db 000110000b
		db 000000000b
		db 000100000b

		db 000000000b


		db 001111000b
		db 010000000b
		db 010111000b
		db 001111000b
		db 000111000b

		db 000000000b
	}
		// EMPIEZAN LAS LETRAS
	asm{
		db 001110000b
		db 010001000b
		db 011111000b
		db 010001000b
		db 010001000b

		db 000000000b

		db 011110000b
		db 010001000b
		db 011110000b
		db 010001000b
		db 011110000b

		db 000000000b

		db 001111000b
		db 010000000b
		db 010000000b
		db 010000000b
		db 001111000b

		db 000000000b

		db 011110000b
		db 010001000b
		db 010001000b
		db 010001000b
		db 011110000b

		db 000000000b

		db 011111000b
		db 010000000b
		db 011110000b
		db 010000000b
		db 011111000b

		db 000000000b

		db 011111000b
		db 010000000b
		db 011110000b
		db 010000000b
		db 010000000b

		db 000000000b

		db 001111000b
		db 010000000b
		db 010111000b
		db 010001000b
		db 001110000b

		db 000000000b

		db 010001000b
		db 010001000b
		db 011111000b
		db 010001000b
		db 010001000b

		db 000000000b

		db 011111000b
		db 000100000b
		db 000100000b
		db 000100000b
		db 011111000b

		db 000000000b

		db 011111000b
		db 000001000b
		db 000001000b
		db 010001000b
		db 001110000b

		db 000000000b

		db 010011000b
		db 010100000b
		db 011000000b
		db 010100000b
		db 010011000b

		db 000000000b

		db 010000000b
		db 010000000b
		db 010000000b
		db 010000000b
		db 011111000b

		db 000000000b

		db 010001000b
		db 011011000b
		db 010101000b
		db 010001000b
		db 010001000b

		db 000000000b

		db 010001000b
		db 011001000b
		db 010101000b
		db 010011000b
		db 010001000b

		db 000000000b

		db 001110000b
		db 010001000b
		db 010001000b
		db 010001000b
		db 001110000b

		db 000000000b

		db 011110000b
		db 010001000b
		db 011110000b
		db 010000000b
		db 010000000b

		db 000000000b

		db 001110000b
		db 010001000b
		db 010001000b
		db 010111000b
		db 001111000b

		db 000000000b

		db 011110000b
		db 010001000b
		db 011110000b
		db 010010000b
		db 010001000b

		db 000000000b

		db 001111000b
		db 010000000b
		db 001110000b
		db 000001000b
		db 011110000b

		db 000000000b

		db 011111000b
		db 000100000b
		db 000100000b
		db 000100000b
		db 000100000b

		db 000000000b

		db 010001000b
		db 010001000b
		db 010001000b
		db 010001000b
		db 001110000b

		db 000000000b

		db 010001000b
		db 010001000b
		db 001010000b
		db 001010000b
		db 000100000b

		db 000000000b

		db 010001000b
		db 010001000b
		db 010101000b
		db 011011000b
		db 010001000b

		db 000000000b

		db 010001000b
		db 001010000b
		db 000100000b
		db 001010000b
		db 010001000b

		db 000000000b

		db 010001000b
		db 001010000b
		db 000100000b
		db 000100000b
		db 000100000b

		db 000000000b

		db 011111000b
		db 000010000b
		db 000100000b
		db 001000000b
		db 011111000b

		db 000000000b
	}
	asm{
		db 001110000b
		db 001000000b
		db 001000000b
		db 001000000b
		db 001110000b

		db 000000000b

		db 010000000b
		db 001000000b
		db 000100000b
		db 000010000b
		db 000001000b

		db 000000000b

		db 001110000b
		db 000010000b
		db 000010000b
		db 000010000b
		db 001110000b

		db 000000000b

		db 000100000b
		db 001010000b
		db 010001000b
		db 000000000b
		db 000000000b

		db 000000000b

		db 000000000b
		db 000000000b
		db 000000000b
		db 000000000b
		db 011111000b

		db 000000000b

		db 001000000b
		db 000100000b
		db 000000000b
		db 000000000b
		db 000000000b

		db 000000000b

		db 011110000b
		db 000001000b
		db 001111000b
		db 010001000b
		db 001111000b

		db 000000000b

		db 010000000b
		db 010000000b
		db 011110000b
		db 010001000b
		db 011110000b

		db 000000000b

		db 000000000b
		db 001111000b
		db 010000000b
		db 010000000b
		db 001111000b

		db 000000000b

		db 000001000b
		db 000001000b
		db 001111000b
		db 010001000b
		db 001111000b

		db 000000000b

		db 001110000b
		db 010001000b
		db 011110000b
		db 010000000b
		db 001111000b

		db 000000000b

		db 001110000b
		db 010000000b
		db 011000000b
		db 010000000b
		db 010000000b

		db 000000000b

		db 001111000b
		db 010001000b
		db 001111000b
		db 000001000b
		db 011110000b

		db 000000000b

		db 010000000b
		db 010000000b
		db 011110000b
		db 010001000b
		db 010001000b

		db 000000000b

		db 000100000b
		db 000000000b
		db 000100000b
		db 000100000b
		db 000100000b

		db 000000000b

		db 000100000b
		db 000000000b
		db 000100000b
		db 010100000b
		db 001000000b

		db 000000000b

		db 000000000b
		db 010100000b
		db 011000000b
		db 010100000b
		db 010010000b

		db 000000000b

		db 000100000b
		db 000100000b
		db 000100000b
		db 000100000b
		db 000011000b

		db 000000000b

		db 000000000b
		db 011010000b
		db 010101000b
		db 010101000b
		db 010101000b

		db 000000000b

		db 000000000b
		db 011100000b
		db 010001000b
		db 010001000b
		db 010001000b

		db 000000000b

		db 000000000b
		db 001110000b
		db 010001000b
		db 010001000b
		db 001110000b

		db 000000000b

		db 000000000b
		db 011110000b
		db 010001000b
		db 011110000b
		db 010000000b

		db 000000000b

		db 000000000b
		db 001111000b
		db 010001000b
		db 001111000b
		db 000001000b

		db 000000000b

		db 000000000b
		db 010110000b
		db 011001000b
		db 010000000b
		db 010000000b

		db 000000000b

		db 000000000b
		db 011110000b
		db 011110000b
		db 000001000b
		db 011110000b

		db 000000000b

		db 000100000b
		db 011111000b
		db 000100000b
		db 000100000b
		db 000010000b

		db 000000000b

		db 000000000b
		db 010001000b
		db 010001000b
		db 010001000b
		db 001110000b

		db 000000000b

		db 000000000b
		db 010001000b
		db 001010000b
		db 001010000b
		db 000100000b

		db 000000000b

		db 000000000b
		db 010001000b
		db 001110000b
		db 001010000b
		db 000100000b

		db 000000000b

		db 000000000b
		db 010010000b
		db 001100000b
		db 001100000b
		db 010010000b

		db 000000000b

		db 000000000b
		db 010001000b
		db 011011000b
		db 000100000b
		db 000100000b

		db 000000000b

		db 000000000b
		db 011111000b
		db 000100000b
		db 001000000b
		db 011111000b

		db 000000000b

	}

}
void inic_letras()
{
	void (* point)(void);
	point=&letras_dat;
	letras=(char *)point;
	do{
		if(letras[0]=='J' && letras[1]=='A' && letras[2]=='B'){
			letras+=3;
			break;
		}
		else letras++;
	}while(1);
}
void displaychar(int c,int x,int y,int fgd,int bkgd)
{
	c=toupper(c);
	c-=32;
	asm{
		push si
		push di
		push ds
		mov ax,y
		mov bx,x

		xchg ah,al
		add bx,ax
		shr ax,1
		shr ax,1
		add bx,ax
		mov ax,0A000h
		mov es,ax

		mov di,bx
	}
		asm mov cx,6
		asm mov ax,c
	_SI=FP_OFF(letras);
	_DS=FP_SEG(letras);
	//add si,ax
	asm{
		mul cl
		add si,ax

		mov bl,fgd
		mov bh,bkgd
	}
l10:
	asm{
		push cx
		mov cx,6
		lodsb
		mov ah,al
	}
l11:
	asm{
		mov al,bl
		shl ah,1
		jc l12
		mov al,bh
	}
l12:
	asm{
		stosb
		loop l11
		add di,320-6
		pop cx
		loop l10
		pop ds
		pop di
		pop si
	}
}
void displaystring(char *s,int x,int y,int fgd,int bkgd)
{
	int f;
	for(f=0;s[f];f++)
		displaychar(toupper(s[f]),x+f*DIMENSION,y,fgd,bkgd);
}
void displaychar1(int c,int x,int y,int fgd,int bkgd)
{
	asm{
		push si
		push di
		push ds
		mov ax,y
		mov bx,x

		xchg ah,al
		add bx,ax
		shr ax,1
		shr ax,1
		add bx,ax
		mov ax,0A000h
		mov es,ax

		mov di,bx
		mov ax,040h
		mov ds,ax
		mov cx,ds:[085h]
		xor ax,ax
		mov ds,ax
		mov ax,c
		mov bx,43h*4
		lds si,ds:[bx]
		mul cl
		add si,ax

		mov bl,fgd
		mov bh,bkgd
	}
l10:
	asm{
		push cx
		mov cx,8
		lodsb
		mov ah,al
	}
l11:
	asm{
		mov al,bl
		shl ah,1
		jc l12
		mov al,bh
	}
l12:
	asm{
		stosb
		loop l11
		add di,320-8
		pop cx
		loop l10
		pop ds
		pop di
		pop si
	}
}
void displaystring1(char *s,int x,int y,int fgd,int bkgd)
{
	int f;
	for(f=0;s[f];f++)
		displaychar1(s[f],x+f*8,y,fgd,bkgd);
}
