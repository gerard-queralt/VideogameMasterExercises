#include "ModuleEditorCamera.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "float3x3.h"

ModuleEditorCamera::ModuleEditorCamera()
{
}

ModuleEditorCamera::~ModuleEditorCamera()
{
}

bool ModuleEditorCamera::Start()
{
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);

	SetPosition(float3(0.0f, 3.0f, 5.0f));
	SetLookAt(-float3::unitZ);
	SetOrientation(float3::unitY);

	SetPlaneDistances(0.1f, 100.0f);

	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	aspectRatio = ((float)w) / ((float)h);
	SetFOVdeg(90.0f);

	return true;
}

update_status ModuleEditorCamera::Update()
{
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	aspectRatio = ((float)w) / ((float)h);
	SetAspectRatio(aspectRatio);

	return UPDATE_CONTINUE;
}

void ModuleEditorCamera::SetFOVrads(float rads)
{
	fovRads = rads;
	frustum.SetHorizontalFovAndAspectRatio(fovRads, aspectRatio);
}

void ModuleEditorCamera::SetFOVdeg(float deg)
{
	SetFOVrads((math::pi / 180.0f) * deg);
}

void ModuleEditorCamera::SetAspectRatio(float ratio)
{
	aspectRatio = ratio;
	frustum.SetHorizontalFovAndAspectRatio(fovRads, aspectRatio);
}

void ModuleEditorCamera::SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
{
	frustum.SetViewPlaneDistances(nearPlaneDistance, farPlaneDistance);
}

void ModuleEditorCamera::SetPosition(float3 pos)
{
	frustum.SetPos(pos);
}

void ModuleEditorCamera::SetPosition(float x, float y, float z)
{
	SetPosition(float3(x, y, z));
}

void ModuleEditorCamera::SetOrientation(float3 ori)
{
	frustum.SetUp(ori);
}

void ModuleEditorCamera::SetOrientation(float x, float y, float z)
{
	SetOrientation(float3(x, y, z));
}

void ModuleEditorCamera::SetLookAt(float3 lookAt)
{
	frustum.SetFront(lookAt);
}

void ModuleEditorCamera::SetLookAt(float x, float y, float z)
{
	SetLookAt(float3(x, y, z));
}

void ModuleEditorCamera::Translate(float3 deltaCoords)
{
	float3 deltaCoordsWithRespectFront = frustum.Front().Mul(deltaCoords);

	float3 translationColumn = float3::zero;
	translationColumn += frustum.Front().Normalized() * deltaCoords.x;
	translationColumn += float3::unitY * deltaCoords.y;
	translationColumn += frustum.WorldRight().Normalized() * deltaCoords.z;

	float4x4 translationMat = float4x4(float3x4(float3x3::identity, translationColumn));

	float3 oldPos = frustum.Pos();
	float3 translatedPos = (translationMat * float4(oldPos, 1.0f)).xyz();

	SetPosition(translatedPos);
}

void ModuleEditorCamera::Translate(float deltaX, float deltaY, float deltaZ)
{
	Translate(float3(deltaX, deltaY, deltaZ));
}

void ModuleEditorCamera::Rotate(float3 thetasRad) //TODO: not working properly with multiple rotations
{
	float3x3 rotationX = float3x3::RotateAxisAngle(frustum.WorldRight(), thetasRad.x);
	float3x3 rotationY = float3x3::RotateY(thetasRad.y);
	float3x3 rotationZ = float3x3::RotateZ(thetasRad.z);

	float3x3 rotationMat = rotationY * rotationX * rotationZ;

	float3 oldFront = frustum.Front().Normalized();
	SetLookAt(rotationMat.MulDir(oldFront));

	float3 oldUp = frustum.Up().Normalized();
	SetOrientation(rotationMat.MulDir(oldUp));
}

void ModuleEditorCamera::Rotate(float thetaXRad, float thetaYRad, float thetaZRad)
{
	Rotate(float3(thetaXRad, thetaYRad, thetaZRad));
}
