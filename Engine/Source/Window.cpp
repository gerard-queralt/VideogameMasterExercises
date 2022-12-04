#include "Window.h"

Window::Window(const std::string& i_name)
{
	m_name = i_name;
}

Window::~Window()
{
}

update_status Window::Update()
{
	return UPDATE_CONTINUE;
}
