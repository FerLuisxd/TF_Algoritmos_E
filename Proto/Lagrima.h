#pragma once
#include "Obstaculo.h"
#include "string"
#include "vector"
class Lagrima :
	public Obstaculo
{
	Obstaculo * *vec;
	int n=0;
public:
	int getN() { return n; }
	Lagrima() {
		n = 0;
		vec = new Obstaculo*[n];
	}
	
	~Lagrima();
	void AgregarLagrima(int px, int py, int pancho, int palto, int pdx,int pdy) {
		Obstaculo * o = new Obstaculo(px, py,pancho,palto,pdx,pdy);
		Obstaculo * *aux = new Obstaculo *[n + 1];
		for (size_t i = 0; i < n; i++)
		{
			aux[i] = vec[i];
		}
		aux[n] = o;
		delete vec;
		vec = aux;
		n = n + 1;
	}
	Obstaculo * getLagrima(int i) { return vec[i]; }
	void Dibujar(Graphics ^g, Bitmap ^bmp)
	{
		ancho = bmp->Width;
		alto = bmp->Height;
		Rectangle  region_sprite = Rectangle(sprite_idx*ancho, sprite_idy*alto, ancho, alto);
		Rectangle region_dibujar = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, region_dibujar, region_sprite, GraphicsUnit::Pixel);
	}
	void MoverLagrimas(Graphics^g) {
		for (size_t i = 0; i < n; i++)
		{
			vec[i]->MoverLa(g);
		}
	}
	void EleLag() {
		int it = -1;
		for (int i = 0; i < n; i++)
		{
			if (vec[i]->getColisiona() == true)
				it = i;
		}
		if (it != -1) {
			Obstaculo * *aux = new Obstaculo *[n + 1];

			for (int i = 0; i < it; i++)
			{
				aux[i] = vec[i];
			}
			for (int i = it; i < n - 1; i++)
			{
				aux[i] = vec[i + 1];
			}
			delete vec;
			vec = aux;
			n = n - 1;
		}

	}

};




