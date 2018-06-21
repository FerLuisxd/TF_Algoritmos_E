#pragma once
#include "Obstaculo.h"
class EneSig :
	public Obstaculo
{
	int vel;

public:
	EneSig(int px, int py) {
		x = px;
		y = py;
		colisiona = false;
		sprite_idx = 0;
		sprite_idy = 0;
		ancho = 50;
		alto = 50;
		vel = 1;
		vida = 60;
	}
	~EneSig() {}
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		ancho = bmp->Width;
		alto = bmp->Height;
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);
	}
};



