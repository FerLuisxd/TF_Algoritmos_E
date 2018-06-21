#pragma once
#include "Personaje.h"
#include "Juego.h"
namespace Proto {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	bool mov[8] = { false };
	int vel = 4;
	bool ata = false;
	int contA = 0;
	bool ele = false;
	int it = -1;
	int delay = 0;

	/// <summary>
	/// Resumen de Proto
	/// </summary>
	public ref class Proto : public System::Windows::Forms::Form
	{
	private:
	
	public:
		Proto(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			Inicializar();
		}
		void Inicializar()
		{
			g = this->CreateGraphics();
			ctx = BufferedGraphicsManager::Current;
			buffer = ctx->Allocate(g, this->ClientRectangle);	
			pj = new Personaje();
			img_Link = gcnew Bitmap("img_Link.png");
			eneSigue = gcnew Bitmap("enemigoSi.png");
			fuente = gcnew System::Drawing::Font("Comics Sans MS", 18, FontStyle::Bold);


			solid = gcnew SolidBrush(Color::Red);
			j = new Juego();
			img_Roca = gcnew Bitmap("img_Roca.png");
			img_Moneda = gcnew Bitmap("img_Moneda.png");
			img_PowerUp = gcnew Bitmap("img_PowerUp.png");
			img_Mina = gcnew Bitmap("img_Mina.png");
			lose = gcnew Bitmap("img_lose.png");
		}
	public: System::Windows::Forms::Timer^  timer;
	private:
	private: System::ComponentModel::IContainer^  components;
	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Proto()
		{
			if (components)
			{
				delete components;
			}
		}
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		Graphics ^ g;
		BufferedGraphicsContext ^ctx;
		BufferedGraphics ^buffer;
		Juego* j;
		Personaje * pj;
		Bitmap ^ img_Link;
		Bitmap ^ eneSigue;
		System::Drawing::Font ^fuente;
		SolidBrush ^solid;
		Bitmap^ img_Roca;
		Bitmap^ img_Moneda;
		Bitmap^ img_PowerUp;
		Bitmap^ img_Mina;
		Bitmap^ lose;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 16;
			this->timer->Tick += gcnew System::EventHandler(this, &Proto::timer_tick);
			// 
			// Proto
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(613, 457);
			this->Name = L"Proto";
			this->Text = L"Proto";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Proto::Proto_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Proto::Proto_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	

	private: System::Void timer_tick(System::Object^  sender, System::EventArgs^  e) {
		buffer->Graphics->Clear(Color::Black);

		_DoMovement(buffer->Graphics);	
		if (j->getVida() > 0) {
			j->Render_Escenario(buffer->Graphics, img_Mina, img_PowerUp, img_Moneda, img_Roca, eneSigue, eneSigue, img_Link, pj->getX(), pj->getY());
			//UI
			//buffer->Graphics->DrawString("Vida: ", fuente, solid, 10, 10);
			buffer->Graphics->DrawString(j->getVida().ToString(), fuente, solid, delay, 10);
		}
		if (j->getVida() <= 0) {
			Rectangle region_dibujar = Rectangle(0, 0, buffer->Graphics->VisibleClipBounds.Right, buffer->Graphics->VisibleClipBounds.Bottom);
			Rectangle region_sprite = Rectangle(0, 0, buffer->Graphics->VisibleClipBounds.Right, buffer->Graphics->VisibleClipBounds.Bottom);
			buffer->Graphics->DrawImage(lose, region_dibujar, region_sprite, GraphicsUnit::Pixel);
			//buffer->Graphics->DrawImage(lose,0,0,g->VisibleClipBounds.Right,g->VisibleClipBounds.Bottom, GraphicsUnit::Pixel);
		}
		buffer->Graphics->DrawString(j->getPuntos().ToString(), fuente, solid, 300, 10);
		buffer->Render(g);
	}
	private: void _DoMovement(Graphics ^g) 
	{

		j->_PjMovement(mov,g);
		
		
	}
	private: System::Void Proto_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::S://abajo
		{
			mov[0] = true;
			break;
		}
		case Keys::A://izq
		{
			mov[1] = true;
			break;
		}
		case Keys::D://derecha
		{
			mov[2] = true;
			break;
		}
		case Keys::W://arriba
		{
			mov[3] = true;
			break;
		}
		case Keys::Down://abajo
		{
			mov[4] = true;
			break;
		}
		case Keys::Left://izq
		{
			mov[5] = true;
			break;
		}
		case Keys::Right://derecha
		{
			mov[6] = true;
			break;
		}
		case Keys::Up://arriba
		{
			mov[7] = true;
			break;
		}
		}


	}
	private: System::Void Proto_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::S://abajo
		{
			mov[0] = false;
			break;
		}
		case Keys::A://izq
		{
			mov[1] = false;
			break;
		}
		case Keys::D://derecha
		{
			mov[2] = false;
			break;
		}
		case Keys::W://arriba
		{
			mov[3] = false;
			break;
		}
		case Keys::Down://abajo
		{
			mov[4] = false;
			break;
		}
		case Keys::Left://izq
		{
			mov[5] = false;
			break;
		}
		case Keys::Right://derecha
		{
			mov[6] = false;
			break;
		}
		case Keys::Up://arriba
		{
			mov[7] = false;
			break;
		}
		}

	};


};
}
