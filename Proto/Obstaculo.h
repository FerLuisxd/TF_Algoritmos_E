#pragma once
#include "string"
using namespace std;
using namespace System::Drawing;

class Obstaculo
{
protected:
	int x;
	int y;
	double ancho;
	double alto;
	bool colisiona;
	int sprite_idx;
	int sprite_idy;
	int vida;
	double dx, dy;
public:
	int getX() { return x; }
	int getY() { return y; }
	double getDx() { return dx; }
	double getDy() { return dy; }
	int getVida() { return vida; }
	void recibeD() { vida = vida - 1; }

	double getAncho() { return ancho; }
	double getAlto() { return alto; }
	bool getColisiona() { return colisiona; }
	void setColisiona(bool colisiona) { this->colisiona = colisiona; }
	virtual void Dibujar(Graphics^g, Bitmap^bmp) {

	};
	void MoverEneSig(Graphics^g, Bitmap^bmp, int px, int py,int vel) {
		if (x < px) dx = vel;
		if (x > px) dx = -vel;
		if (y < py) dy = vel;
		if (y > py) dy = -vel;

		x = x + dx;
		y = y + dy;
		Dibujar(g, bmp);
	}
	void MoverEneReb(Graphics^g, Bitmap^bmp, int px, int py) {//El 600 y 800 estan mal :(
		if (x + dx < 0 || x + ancho + dx > g->VisibleClipBounds.Right) {
			dx *= -1;
		}
		if (y + dy < 0 || y + alto + dy> g->VisibleClipBounds.Bottom) {
			dy *= -1;
		}
		x += dx;
		y += dy;
		g->FillEllipse(Brushes::Red, x, y, ancho,alto);
	}
	void MoverLa(Graphics^g) {
		if (x + dx < 0 || x + ancho + dx > g->VisibleClipBounds.Right) {
			colisiona = true;
		}
		if (y + dy < 0 || y + alto + dy> g->VisibleClipBounds.Bottom) {
			colisiona = true;
		}
		x += dx;
		y += dy;
		g->FillEllipse(Brushes::White, x, y, ancho, alto);
	}
	Obstaculo(){}
	Obstaculo(int px, int py, int pancho, int palto,double pdx , double pdy) {
		colisiona = false;
		x = px;
		y = py;
		dx = pdx;
		dy = pdy;
		ancho = pancho;
		alto = palto;
	}
	~Obstaculo() {}
};

