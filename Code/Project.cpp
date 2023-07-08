#include <string>
#include <Engine/Console.h>

// This is the name of the current project
char ProjectName[] = "GMTK-2023";

// This function returns the map that will be loaded when the game is opened
std::string GetStartupScene()
{
	Console::ExecuteConsoleCommand("ssao=0");
	return "Menu";
}