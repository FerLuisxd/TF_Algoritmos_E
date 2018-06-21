#include "Proto.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Proto::Proto form;
	Application::Run(%form);
}