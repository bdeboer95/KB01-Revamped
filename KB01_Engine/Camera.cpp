#include "Camera.h"
#include "Vector3.h"
#include "Renderer.h"
/// <summary>
/// Initializes a new instance of the <see cref="Camera"/> class.
/// </summary>
Camera::Camera()
{
	//TODO
	Log::Instance()->LogMessage("Camera - Camera created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Camera"/> class.
/// </summary>
Camera::~Camera(void)
{
	//TODO
	Log::Instance()->LogMessage("~Camera - Camera cleaned up!", Log::MESSAGE_INFO);
}

void Camera::SetCamera(Renderer* renderer)
{
	Matrix matWorld, matWorldX, matWorldY, matWorldZ;
	Matrix matView;
	Matrix matProj;

	Vector3 cameraPosition = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 cameraTarget = Vector3(0.0f, 0.0f, 5.0f);
	Vector3 cameraUpVector = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 m_right = Vector3(1.0f, 0.0f, 0.0f);

	// Where to implement these functions???
	

	LookAtLH(&matView, &cameraPosition, &cameraTarget, &cameraUpVector);
	renderer->SetTransform(Renderer::VIEW, &matView);

	PerspectiveFovLH(&matProj, 3.141592654f / 4, 1.0f, 1.0f, 2000.0f);
	renderer->SetTransform(Renderer::PROJECTION, &matProj);
}

