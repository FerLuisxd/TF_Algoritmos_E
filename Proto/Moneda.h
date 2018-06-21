#pragma once
#include "Obstaculo.h"
class Moneda :
	public Obstaculo
{
public:
	Moneda(int px, int py) {
		x = px;
		y = py;
		sprite_idx = 0;
		sprite_idy = 0;
		ancho = 24.7;
		alto = 24;
	}
	~Moneda(){}
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);

		if (sprite_idx < 6)
			sprite_idx++;
		else sprite_idx = 0;
	}
};

