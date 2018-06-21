#pragma once
#include <cstdlib>
#include "Lagrima.h"
using namespace System::Drawing;
class Personaje
{
protected:
	int x, y, dx=3, dy=3;
	float t;
	int ancho, alto, indiceX, indiceY;
	bool danado;
	int vida=3;
public:
	int getVidaP() { return vida; }
	void VMenos() { vida = vida - 1; }
	void VMas() { vida = vida + 1; }
	Personaje();
	~Personaje();
	void dibujar(Graphics ^g, Bitmap ^bmp);

	Personaje(int px, int py);
	void setX(int a) { x = a; };
	int getX() { return x; };
	void setY(int a) { y = a; };
	int getY() { return y; };
	bool getDanado() { return danado; }
	int getAncho() { return ancho * 0.5; }
	int getAlto() { return alto * 0.5; }
	void Menos();
};



Personaje::Personaje()
{
	x = 300;
	y = 300;
}


Personaje::~Personaje()
{
}


inline void Personaje::dibujar(Graphics^ g, Bitmap ^ bmp)
{
	ancho = bmp->Width;
	alto = bmp->Height;
	Rectangle area = Rectangle(0, 0, ancho, alto);
	Rectangle aum = Rectangle(x, y, ancho*0.5, alto*0.5);
	g->DrawImage(bmp, aum, area, GraphicsUnit::Pixel);
}



inline Personaje::Personaje(int px, int py)
{
	x = px;
	y = py;
	vida = 3;
}

inline void Personaje::Menos()
{
}
