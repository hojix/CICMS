/*************************************************
 * This file just starts up the whole program by *
 * rendering the form                            *
 * Done by Visual Studios 2012                   *
 ************************************************/

#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace CEGHypermarket;

[System::STAThreadAttribute]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

	CEGHypermarket::MyForm form;
    Application::Run(%form);
}