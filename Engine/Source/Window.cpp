#include "Window.h"

Window::Window(std::string i_name)
{
	m_name = i_name;
}

Window::~Window()
{
}

void Window::Start()
{
}

update_status Window::Update()
{
	return UPDATE_CONTINUE;
}
