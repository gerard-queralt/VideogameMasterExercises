#pragma once

#include "Module.h"
#include "Frustum.h"
#include "Geometry/AABB.h"

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
	void SetPosition(const float3& i_pos);
	void SetPosition(float i_x, float i_y, float i_z);
	void SetOrientation(const float3& i_ori);
	void SetOrientation(float i_x, float i_y, float i_z);
	void SetLookAt(const float3& i_lookAt);
	void SetLookAt(float i_x, float i_y, float i_z);
	
	void Translate(const float3& i_deltaCoords);
	void Translate(float i_deltaX, float i_deltaY, float i_deltaZ);
	
	void Rotate(const float3x3& i_rotationMatrix);
	void Rotate(const float3& i_thetasRad);
	void Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad);

	void FocusOn(const AABB* i_aabb);

private:
	Frustum m_frustum;

	float m_fovRads;
	float m_aspectRatio;
};

