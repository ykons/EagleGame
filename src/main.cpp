#include <iostream>

#include <Application.hpp>

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception &e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
