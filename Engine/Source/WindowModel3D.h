#pragma once

#include "Window.h"

#include "Model3D.h"

class WindowModel3D : public Window
{
public:
	WindowModel3D();
	~WindowModel3D();

	void Draw();

	void SetModel(const Model3D* i_model);

private:
	const Model3D* m_model = nullptr;
};

