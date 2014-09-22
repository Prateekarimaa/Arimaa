// Arimaa.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include "SFML-Graphics/ConfigOptions.h"
#include "SFML-Graphics/InputHandler.h"
#include "SFML-Graphics/Screen.h"
#include "SFML-Graphics/GameScreen.h"

using namespace sf;

//comment this line to hide console
#define CONSOLE_ON


int _tmain(int argc, _TCHAR* argv[])
{
#ifdef CONSOLE_ON
	void InitializeConsoleStdIO();
#endif

	ConfigOptions::initIHandler();
	RenderWindow app(VideoMode(ConfigOptions::getResolution().x, ConfigOptions::getResolution().y, 32), "TRPG", Style::Close | Style::Titlebar); //Cr�ation de la fen�tre app
	app.SetFramerateLimit(60); 

	sf::String loadingText("Loading...", *ResourceManager::getFont(/*Default font*/), 48);
	loadingText.SetCenter(loadingText.GetRect().GetWidth()/2, loadingText.GetRect().GetHeight()/2);
	loadingText.SetPosition(ConfigOptions::getScreenCenter());

	std::vector<Screen*> screens;

	//Screens creation
	GameScreen gameScreen(screens.size());
	screens.push_back(&gameScreen);

	int screen = 0;
	int oldScreen = 0;

	app.Clear();
	app.Draw(loadingText);
	app.Display();

	screens.at(screen)->initialize();
	while (screen >= 0)
	{
		screen = screens.at(screen)->run(app);
		if(oldScreen != screen && screen != EXIT)
		{
			app.Clear();
			app.Draw(loadingText);
			app.Display();
			screens.at(oldScreen)->uninitialize();
			screens.at(screen)->initialize();
		}
		oldScreen = screen;
	}
	return EXIT_SUCCESS;
}



#ifdef CONSOLE_ON
void InitializeConsoleStdIO()
{
    // si une console est rattach�e au processus, alors il existe des fichiers
    // virtuel CONIN$ et CONOUT$ qui permettent respectivement de lire
    // et d'�crire depuis / dans cette console (voir la doc de CreateFile).

#if _MSC_VER >= 1400 // VC++ 8 
    { 
    // �viter le warning C4996: 'freopen' was declared deprecated 
    // This function or variable may be unsafe. Consider using freopen_s instead. 
    FILE *stream; 
    freopen_s( &stream, "CONIN$", "r", stdin ); 
    freopen_s( &stream, "CONOUT$", "w", stdout ); 
    freopen_s( &stream, "CONOUT$", "w", stderr ); 
    } 
#else 
    std::freopen( "CONIN$", "r", stdin ); 
    std::freopen( "CONOUT$", "w", stdout ); 
    std::freopen( "CONOUT$", "w", stderr ); 
#endif 

    // la ligne suivante synchronise les flux standards C++ (cin, cout, cerr...)
    std::ios_base::sync_with_stdio();    
}

int WINAPI WinMain(          
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    // cr�er une console
    ::AllocConsole();
    // synchroniser la CRT
    InitializeConsoleStdIO();
    // tester
    std::cout << "Hello World!\n";
    std::cout << "Appuyez sur Entree pour quitter...";
    std::cin.ignore();
}
#endif