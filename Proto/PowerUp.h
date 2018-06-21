#pragma once
#include "Obstaculo.h"
class PowerUp :
	public Obstaculo
{
public:
	PowerUp(int px, int py) {
		x = px;
		y = py;
		sprite_idx = 0;
		sprite_idy = 0;
		ancho = 19;
		alto = 19;
	}
	~PowerUp(){}
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);
	}
};

