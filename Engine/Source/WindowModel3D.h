#pragma once

#include "Window.h"

#include "Model3D.h"

class WindowModel3D : public Window
{
public:
	WindowModel3D();
	~WindowModel3D();

	update_status Update();

	void SetModel(const Model3D* i_model);

private:
	const Model3D* m_model = nullptr;
};

