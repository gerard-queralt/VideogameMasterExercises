#pragma once

#include "Module.h"
#include "Frustum.h"

class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();

	bool Start();

	float4x4 getProj() {
		return proj;
	}
	float4x4 getModel() {
		return model;
	}
	float4x4 getView() {
		return view;
	}

private:
	Frustum frustum;
	float4x4 proj;
	float4x4 model;
	float4x4 view;
};

