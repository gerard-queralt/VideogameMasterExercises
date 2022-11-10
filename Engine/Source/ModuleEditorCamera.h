#pragma once

#include "Module.h"
#include "Frustum.h"

class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();

	bool Start();
	update_status Update();

	float4x4 getProj() {
		return frustum.ProjectionMatrix();
	}
	float4x4 getView() {
		return frustum.ViewMatrix();
	}

	void SetFOVrads(float rads);
	void SetFOVdeg(float deg);
	void SetAspectRatio(float ratio);
	void SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance);
	void SetPosition(float3 pos);
	void SetPosition(float x, float y, float z);
	void SetOrientation(float3 ori);
	void SetOrientation(float x, float y, float z);
	void SetLookAt(float3 lookAt);
	void SetLookAt(float x, float y, float z);
	
	void Translate(float3 deltaCoords);
	void Translate(float deltaX, float deltaY, float deltaZ);
	
	void Rotate(float3 thetasRad);
	void Rotate(float thetaXRad, float thetaYRad, float thetaZRad);

private:
	Frustum frustum;

	float fovRads;
	float aspectRatio;
};

