#pragma once
#include "string"
#include "vector"
#include "Obstaculo.h"
#include "Moneda.h"
#include "Mina.h"
#include "PowerUp.h"
#include "Roca.h"
#include "EneSig.h"
#include "EneReb.h"
using namespace std;

class Escenario
{
	int seed;
	int s_rocas;
	int s_moviles;
	int s_monedas;
	int s_minas;
	int s_rebotantes;
	int s_bonus;

	int xi;//cambiar por random de verdad

	vector<Obstaculo*> vec_Obstaculos;
public:
	int rng() {//random
		xi = (2 * xi + 5) % 500;
		return xi;
	}

	Escenario(string s)
	{
		System::Random r;
		xi = r.Next(1, 30);
		seed = stoi(s, nullptr, 10);
		s_bonus = seed % 10;
		seed = seed / 10;
		s_rebotantes = seed % 10;
		seed = seed / 10;
		s_minas = seed % 10;
		seed = seed / 10;
		s_monedas = seed % 10;
		seed = seed / 10;
		s_moviles = seed % 10;
		seed = seed / 10;
		s_rocas = seed % 10;
		seed = seed / 10;	


		for (int i = 0; i < s_monedas; i++)
		{
			Moneda* m = new Moneda(rng(),rng());
			vec_Obstaculos.push_back(m);
		}
		for (int i = 0; i < s_rocas; i++)
		{
			Roca* r = new Roca(rng(), rng());
			vec_Obstaculos.push_back(r);
		}
		for (int i = 0; i < s_bonus; i++)
		{
			PowerUp* p = new PowerUp(rng(), rng());
			vec_Obstaculos.push_back(p);
		}
		for (int i = 0; i < s_minas; i++)
		{
			Mina* mi = new Mina(rng(), rng());
			vec_Obstaculos.push_back(mi);
		}
		for (int i = 0; i < s_moviles; i++)
		{	
			EneSig* es = new EneSig(rng(), rng());
			vec_Obstaculos.push_back(es);
		}
		for (int i = 0; i < s_rebotantes; i++)
		{
			EneReb* er = new EneReb(rng(), rng(),1.5,1.5,3,35,35);
			vec_Obstaculos.push_back(er);
		}

	}
	Escenario(){}
	~Escenario(){}
	vector<Obstaculo*> getVec() { return vec_Obstaculos; }
	void Agregar(int i) {
		EneReb* er;
		EneReb* er2;
		if (vec_Obstaculos[i]->getVida() == 2) {
			er = new EneReb(vec_Obstaculos[i]->getX(), vec_Obstaculos[i]->getY(), vec_Obstaculos[i]->getDx()*1.2, vec_Obstaculos[i]->getDy()*-1.2, 2, 27, 27);
			er2 = new EneReb(vec_Obstaculos[i]->getX(), vec_Obstaculos[i]->getY(), vec_Obstaculos[i]->getDx()*-1.2, vec_Obstaculos[i]->getDy()*1.2, 2, 27, 27);
			vec_Obstaculos.push_back(er);
			vec_Obstaculos.push_back(er2);
		}
		
		if (vec_Obstaculos[i]->getVida() == 1) {
			er = new EneReb(vec_Obstaculos[i]->getX(), vec_Obstaculos[i]->getY(), vec_Obstaculos[i]->getDx()*1.7, vec_Obstaculos[i]->getDy()*-1.3, 1, 20, 20);
			er2 = new EneReb(vec_Obstaculos[i]->getX(), vec_Obstaculos[i]->getY(), vec_Obstaculos[i]->getDx()*-1.7, vec_Obstaculos[i]->getDy()*1.3, 1, 20, 20);
			vec_Obstaculos.push_back(er);
			vec_Obstaculos.push_back(er2);
		}

	}
	void Dibujar(Graphics^g, Bitmap^ img_Mina, Bitmap^ img_PowerUp, Bitmap^ img_Moneda, Bitmap^ img_Roca,Bitmap^ img_Sig, Bitmap^ img_Reb, int px,int py)
	{
		for (int i = 0; i < vec_Obstaculos.size(); i++)
		{
			if (dynamic_cast<EneReb*>(vec_Obstaculos[i]))
				vec_Obstaculos[i]->MoverEneReb(g, img_Sig, px, py);
			if (dynamic_cast<Mina*>(vec_Obstaculos[i]))
				vec_Obstaculos[i]->Dibujar(g, img_Mina);
			if (dynamic_cast<PowerUp*>(vec_Obstaculos[i]))
				vec_Obstaculos[i]->Dibujar(g, img_PowerUp);
			if (dynamic_cast<Moneda*>(vec_Obstaculos[i]))
				vec_Obstaculos[i]->Dibujar(g, img_Moneda);
			if (dynamic_cast<Roca*>(vec_Obstaculos[i]))
				vec_Obstaculos[i]->Dibujar(g, img_Roca);
			if (dynamic_cast<EneSig*>(vec_Obstaculos[i]))
				vec_Obstaculos[i]->MoverEneSig(g, img_Sig,px,py,1);

		}
	}
	void Borrar(int pos) {
		vec_Obstaculos.erase(vec_Obstaculos.begin() + pos);
	}
};

