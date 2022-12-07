#pragma once

#include "EditorWindow.h"

#include "Models/3DModels/Model3D.h"

class WindowModel3D : public EditorWindow
{
public:
	WindowModel3D();
	~WindowModel3D();

	void DrawWindowContents();

	void SetModel(const Model3D* i_model);

private:
	const Model3D* m_model = nullptr;
};

