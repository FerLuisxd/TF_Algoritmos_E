#pragma once

#include "Escenario.h"
#include "Personaje.h"
#include "Lagrima.h"
//#include "Universo.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
class Juego
{
	//acá deberían ir los árboles
	Escenario* e;
	Personaje* pj;
	Lagrima * lg;
	double velp = 4;
	double vell = 7;
	int contA = 0;//lagrimas
	int dLa = 15;
	int NcontA = 25;
	int delay = 0;//colisiones
	int Ndelay = 100;//delay de daño que recibe
	//int vidas = 3;
	int puntos = 0;
	vector<int> z;
	//bool a[4] = { false };//todavia no se usa
	int nEne = -1;
	string f;
public:
	void Inicializar_Escenario() 
	{
		srand(time(NULL));
		int *o;
		*o = 0;
		z.push_back(*o);
		for (size_t i = 0; i < 1000; i++)
		{
			*o = rand() % 9999999 + 0;
			z.push_back(*o);
		}
		f= std::to_string(z[0]);
		//f = msclr::interop::marshal_as<string>(r);
		e = new Escenario(f);
		pj = new Personaje();  
		lg = new Lagrima();
	}

	Juego()
	{
		Inicializar_Escenario();
	}
	int getVida() { return pj->getVidaP(); }
	int getPuntos() { return puntos; }
	// Movimiento no va aquí, va en personaje
	void _PjMovement(bool mov[],Graphics^g) {
		if (pj != nullptr) {
			if (mov[0] == true && pj->getY() + pj->getAlto() + velp<g->VisibleClipBounds.Bottom&&pj->getY() + velp > g->VisibleClipBounds.Top) pj->setY(pj->getY() + velp);
			if (mov[1] == true && pj->getX() + pj->getAncho() - velp < g->VisibleClipBounds.Right&&pj->getX() - velp >= 0) pj->setX(pj->getX() - velp);
			if (mov[2] == true&& pj->getX()+pj->getAncho()+velp <g->VisibleClipBounds.Right&&pj->getX()+velp>=0) pj->setX(pj->getX() + velp);
			if (mov[3] == true&& pj->getY() + pj->getAlto()-velp<g->VisibleClipBounds.Bottom&&pj->getY() -velp> g->VisibleClipBounds.Top) pj->setY(pj->getY() - velp);
			if (mov[4]) {
				contA++;
				mov[5] = false; mov[6] = false; mov[7] = false;
			}
			if (mov[5]) {
				contA++;
				mov[4] = false; mov[6] = false; mov[7] = false;
			}
			if (mov[6]) {
				contA++;
				mov[5] = false; mov[4] = false; mov[7] = false;
			}
			if (mov[7]) {
				contA++;
				mov[5] = false; mov[6] = false; mov[4] = false;
			}
			if (contA > NcontA) {
				
				if (mov[4]) {
					contA = 0;
					lg->AgregarLagrima(pj->getX() + pj->getAncho() / 2, pj->getY() + pj->getAlto() / 4, dLa, dLa,0, vell);//0
					
				}
				if (mov[6]) {
					contA = 0;
					lg->AgregarLagrima(pj->getX() + pj->getAncho() / 2, pj->getY() + pj->getAlto() / 4, dLa, dLa, vell,0);//3
				}
				if (mov[7]) {
					contA = 0;
					lg->AgregarLagrima(pj->getX() + pj->getAncho() / 2, pj->getY() + pj->getAlto() / 4, dLa, dLa,0,-vell);//1
				}
				if (mov[5]) {
					contA = 0;
					lg->AgregarLagrima(pj->getX() + pj->getAncho() / 2, pj->getY() + pj->getAlto() / 4, dLa, dLa,-vell, 0);//2

				}
				
				
			}
		}
	}

	bool HayColision(Rectangle r1, Rectangle r2) { return r1.IntersectsWith(r2); }
	void EvaluaColisiones()
	{
		if (delay <= Ndelay) {
			delay++;
		}
		Rectangle r_personaje = Rectangle(pj->getX(), pj->getY(), pj->getAncho(), pj->getAlto());
		int it2 = -1;
		for (int i = 0; i < e->getVec().size(); i++)
		{
			
			if (e->getVec()[i] != NULL) {
				Rectangle r_obs = Rectangle(e->getVec()[i]->getX(), e->getVec()[i]->getY(), e->getVec()[i]->getAncho(), e->getVec()[i]->getAncho());
				if (HayColision(r_personaje, r_obs))
				{
					//efectos de cada colisión aquí, usar dynamic cast
					if (dynamic_cast<Mina*>(e->getVec()[i]))
					{
						
						pj->VMenos();
						it2 = i;
						//e->Borrar(i);

					}
					if (dynamic_cast<EneSig*>(e->getVec()[i]))
					{
						//e->Borrar(i);
						if (delay >= Ndelay) {
							pj->VMenos();
							delay = 0;
						}

					}
					if (dynamic_cast<EneReb*>(e->getVec()[i]))
					{
						//e->Borrar(i);
						if (delay >= Ndelay) {
							pj->VMenos();
							delay = 0;
						}
					}
					if (dynamic_cast<PowerUp*>(e->getVec()[i]))
					{
						
						pj->VMas();
						it2 = i;
						//e->Borrar(i);
					}
					if (dynamic_cast<Moneda*>(e->getVec()[i]))
					{
						it2 = i;
						//e->Borrar(i);
						puntos += 20;
					}
					if (dynamic_cast<Roca*>(e->getVec()[i]))
					{
						if (pj->getY() < e->getVec()[i]->getY()) {
							Detener_Up(e->getVec()[i]->getY(), pj->getAlto());
						}
						else if (pj->getY() > e->getVec()[i]->getY()) {
							Detener_Down(e->getVec()[i]->getY(), pj->getAlto());
						}
						else if (pj->getX() > e->getVec()[i]->getX()) {
							//a[2] = true;
							pj->setX(pj->getX());
							//Detener_Left(e->getVec()[i]->getX(), pj->getAncho());
						}
						else if (pj->getX() > e->getVec()[i]->getX()) {
							//a[3] = true;
							pj->setX(pj->getX());
							Detener_Right(e->getVec()[i]->getX(), pj->getAncho());
						}
					}
					else {
						for (size_t i = 0; i < 4; i++)
						{
							//a[i] = false;
						}
					}
				}
			}
		}
		if (it2 != -1) {
				e->Borrar(it2);
			}
		int it = -1;
		for (int j = 0; j < lg->getN(); j++)
				{
					it = -1;
					if (lg->getLagrima(j) != NULL) {
						Rectangle r_lagrima = Rectangle(lg->getLagrima(j)->getX(), lg->getLagrima(j)->getY(), lg->getLagrima(j)->getAncho(), lg->getLagrima(j)->getAlto());
						for (int i = 0; i < e->getVec().size(); i++) {
							if (e->getVec()[i] != NULL) {
								if (dynamic_cast<EneReb*>(e->getVec()[i]) || dynamic_cast<EneSig*>(e->getVec()[i])) {
									Rectangle r_obs = Rectangle(e->getVec()[i]->getX(), e->getVec()[i]->getY(), e->getVec()[i]->getAncho(), e->getVec()[i]->getAncho());
									if (HayColision(r_lagrima, r_obs))
									{
										it = i;
										break;
									}
								}
							}
						}
						if (it != -1) {
							e->getVec()[it]->recibeD();
							if (dynamic_cast<EneReb*>(e->getVec()[it])) {
								e->Agregar(it);
								e->Borrar(it);
							}
							else if (e->getVec()[it]->getVida() <= 0) {
								e->Borrar(it);
							}
						}
					}
				}
		if(nEne = -1 ){
			for (int i = 0; i < e->getVec().size(); i++) {
				nEne = 1;
				if (dynamic_cast<EneSig*>(e->getVec()[i]))
				{
					nEne = -1;
				}
				if (dynamic_cast<EneReb*>(e->getVec()[i]))
				{
					nEne = -1;
				}
		}
			
		}
		if (nEne == 1) {
			pj->VMas();
		}
	
	}
	void Render_Escenario(Graphics^g, Bitmap^ img_Mina, Bitmap^ img_PowerUp, Bitmap^ img_Moneda, Bitmap^ img_Roca, Bitmap^ img_Sig, Bitmap^ img_Reb, Bitmap^ img_Link,int px, int py)
	{
		e->Dibujar(g, img_Mina, img_PowerUp, img_Moneda, img_Roca, img_Sig, img_Reb, pj->getX(), pj->getY());
		pj->dibujar(g, img_Link);   
		lg->MoverLagrimas(g);	
		EvaluaColisiones();
	}
	~Juego(){}
	void Detener_Up(int y, double alto)
	{
		pj->setY(y - alto);
	}
	void Detener_Down(int y, double alto)
	{
		pj->setY(y + alto);
	}
	void Detener_Left(int x, double ancho)
	{
		pj->setX(x - ancho);
	}
	void Detener_Right(int x, double ancho)
	{
		pj->setX(x + ancho);
	}
};

