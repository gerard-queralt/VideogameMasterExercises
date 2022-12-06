#pragma once

#include "Module.h"
#include "Frustum.h"

class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();

	bool Start();

	float4x4 GetProjection() {
		return m_frustum.ProjectionMatrix();
	}
	float4x4 GetView() {
		return m_frustum.ViewMatrix();
	}

	void SetFOVrads(float i_rads);
	void SetFOVdeg(float i_deg);
	void SetAspectRatio(float i_ratio);
	void SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance);
	void SetPosition(float3 i_pos);
	void SetPosition(float i_x, float i_y, float i_z);
	void SetOrientation(float3 i_ori);
	void SetOrientation(float i_x, float i_y, float i_z);
	void SetLookAt(float3 i_lookAt);
	void SetLookAt(float i_x, float i_y, float i_z);
	
	void Translate(float3 i_deltaCoords);
	void Translate(float i_deltaX, float i_deltaY, float i_deltaZ);
	
	void Rotate(float3 i_thetasRad);
	void Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad);

private:
	Frustum m_frustum;

	float m_fovRads;
	float m_aspectRatio;
};

