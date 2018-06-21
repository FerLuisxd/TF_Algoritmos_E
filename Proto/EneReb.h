#pragma once
#include "Obstaculo.h"
class EneReb :
	public Obstaculo
{
	double vel;
public:

	EneReb(int px, int py,double pdx,double pdy,int vida,int pa,int pl) {
		x = px;
		y = py;
		colisiona = false;
		sprite_idx = 0;
		sprite_idy = 0;

		ancho = pa;
		alto = pl;
		vel = 1;
		dx = pdx;
		dy = pdy;
		this->vida = vida;
	}
	~EneReb() {}
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		ancho = bmp->Width;
		alto = bmp->Height;
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);
	}

};