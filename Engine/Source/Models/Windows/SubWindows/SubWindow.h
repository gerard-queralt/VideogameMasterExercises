#pragma once

#include "Models/Windows/Window.h"

class SubWindow : public Window
{
public:
	~SubWindow();

	void Draw(bool& i_enabled = s_default);

protected:
	SubWindow(const std::string& i_name);
	virtual void DrawWindowContents() = 0;

private:
	static bool s_default;
};

