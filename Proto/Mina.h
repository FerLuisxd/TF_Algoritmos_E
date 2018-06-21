#pragma once
#include "Obstaculo.h"
class Mina :
	public Obstaculo
{
public:
	Mina()
	{
		System::Random r;
		x = r.Next(1, 500);
		y = r.Next(1, 300);
		colisiona = false;
		sprite_idx = 0;
		sprite_idy = 0;
		ancho = 26;
		alto = 26;
	}
	Mina(int px, int py) {
		x = px;
		y = py;
		colisiona = false;
		sprite_idx = 0;
		sprite_idy = 0;
		ancho = 26;
		alto = 26;
	}
	~Mina(){}
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);
	}
};

