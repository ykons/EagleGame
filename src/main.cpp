#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

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
