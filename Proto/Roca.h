#pragma once
#include "Obstaculo.h"
class Roca :
	public Obstaculo
{
public:
	Roca(int px, int py) {
		x = px;
		y = py;
		colisiona = false;
		sprite_idx = 0;
		sprite_idy = 0;
		ancho = 54;
		alto = 52;
	}
	~Roca(){}
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);

	}
};

