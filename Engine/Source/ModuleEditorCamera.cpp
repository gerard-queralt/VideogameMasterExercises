#include "ModuleEditorCamera.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "float3x3.h"
#include "Sphere.h"

ModuleEditorCamera::ModuleEditorCamera()
{
}

ModuleEditorCamera::~ModuleEditorCamera()
{
}

bool ModuleEditorCamera::Start()
{
	m_frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);

	SetPosition(float3(0.0f, 3.0f, 5.0f));
	SetLookAt(-float3::unitZ);
	SetOrientation(float3::unitY);

	SetPlaneDistances(0.1f, 100.0f);

	int w, h;
	SDL_GetWindowSize(App->window->m_window, &w, &h);
	m_aspectRatio = ((float)w) / ((float)h);
	SetFOVdeg(90.0f);

	return true;
}

void ModuleEditorCamera::SetFOVrads(float i_rads)
{
	m_fovRads = i_rads;
	m_frustum.SetHorizontalFovAndAspectRatio(m_fovRads, m_aspectRatio);
}

void ModuleEditorCamera::SetFOVdeg(float i_deg)
{
	SetFOVrads((math::pi / 180.0f) * i_deg);
}

void ModuleEditorCamera::SetAspectRatio(float i_ratio)
{
	m_aspectRatio = i_ratio;
	m_frustum.SetHorizontalFovAndAspectRatio(m_fovRads, m_aspectRatio);
}

void ModuleEditorCamera::SetPlaneDistances(float i_nearPlaneDistance, float i_farPlaneDistance)
{
	m_frustum.SetViewPlaneDistances(i_nearPlaneDistance, i_farPlaneDistance);
}

void ModuleEditorCamera::SetPosition(const float3& i_pos)
{
	m_frustum.SetPos(i_pos);
}

void ModuleEditorCamera::SetPosition(float i_x, float i_y, float i_z)
{
	SetPosition(float3(i_x, i_y, i_z));
}

void ModuleEditorCamera::SetOrientation(const float3& i_ori)
{
	m_frustum.SetUp(i_ori);
}

void ModuleEditorCamera::SetOrientation(float i_x, float i_y, float i_z)
{
	SetOrientation(float3(i_x, i_y, i_z));
}

void ModuleEditorCamera::SetLookAt(const float3& i_lookAt)
{
	m_frustum.SetFront(i_lookAt);
}

void ModuleEditorCamera::SetLookAt(float i_x, float i_y, float i_z)
{
	SetLookAt(float3(i_x, i_y, i_z));
}

void ModuleEditorCamera::Translate(const float3& i_deltaCoords)
{
	float3 deltaCoordsWithRespectFront = m_frustum.Front().Mul(i_deltaCoords);

	float3 translationColumn = float3::zero;
	translationColumn += m_frustum.Front().Normalized() * i_deltaCoords.x;
	translationColumn += float3::unitY * i_deltaCoords.y;
	translationColumn += m_frustum.WorldRight().Normalized() * i_deltaCoords.z;

	float4x4 translationMat = float4x4(float3x4(float3x3::identity, translationColumn));

	float3 oldPos = m_frustum.Pos();
	float3 translatedPos = (translationMat * float4(oldPos, 1.0f)).xyz();

	SetPosition(translatedPos);
}

void ModuleEditorCamera::Translate(float i_deltaX, float i_deltaY, float i_deltaZ)
{
	Translate(float3(i_deltaX, i_deltaY, i_deltaZ));
}

void ModuleEditorCamera::Rotate(const float3x3& i_rotationMatrix)
{
	float3 oldFront = m_frustum.Front().Normalized();
	float3 newFront = i_rotationMatrix.MulDir(oldFront);

	float3 oldUp = m_frustum.Up().Normalized();
	float3 newUp = i_rotationMatrix.MulDir(oldUp);

	SetLookAt(newFront);
	SetOrientation(newUp);
}

void ModuleEditorCamera::Rotate(const float3& i_thetasRad)
{
	float3x3 rotationX = float3x3::RotateAxisAngle(m_frustum.WorldRight(), i_thetasRad.x);
	float3x3 rotationY = float3x3::RotateY(i_thetasRad.y);
	float3x3 rotationZ = float3x3::RotateAxisAngle(m_frustum.Front(), i_thetasRad.z);

	float3x3 rotationMat = rotationY * rotationX * rotationZ;

	float3 oldFront = m_frustum.Front().Normalized();
	float3 newFront = rotationMat.MulDir(oldFront);

	float3 oldUp = m_frustum.Up().Normalized();
	float3 newUp = rotationMat.MulDir(oldUp);

	if (newUp.y < 0.f) { //TODO: when migrating this function to ComponentTransform, check if parent GameObject has camera? Maybe this check is not needed?
		//ignore rotation in X axis
		rotationMat = rotationY * float3x3::identity * rotationZ;

		newFront = rotationMat.MulDir(oldFront);
		newUp = rotationMat.MulDir(oldUp);
	}

	Rotate(rotationMat);
}

void ModuleEditorCamera::Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad)
{
	Rotate(float3(i_thetaXRad, i_thetaYRad, i_thetaZRad));
}

void ModuleEditorCamera::FocusOn(const AABB* i_aabb)
{
	float3 enclosingSpherePos = i_aabb->MinimalEnclosingSphere().pos;

	float3 direction = enclosingSpherePos - m_frustum.Pos();

	float3x3 rotMat = 
		float3x3::LookAt(m_frustum.Front().Normalized(), direction.Normalized(), m_frustum.Up().Normalized(), float3::unitY);

	Rotate(rotMat);
}
