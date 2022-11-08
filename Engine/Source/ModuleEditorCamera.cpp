#include "ModuleEditorCamera.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "SDL.h"

ModuleEditorCamera::ModuleEditorCamera()
{
}

ModuleEditorCamera::~ModuleEditorCamera()
{
}

bool ModuleEditorCamera::Start()
{
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);

	frustum.SetPos(float3(0.0f, 3.0f, 5.0f));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);

	frustum.SetViewPlaneDistances(0.1f, 100.0f);

	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	frustum.SetHorizontalFovAndAspectRatio((math::pi / 180.0f) * 90.0f, ((float)w) / ((float)h));

	proj = frustum.ProjectionMatrix();
	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));
	view = frustum.ViewMatrix();

	return true;
}
