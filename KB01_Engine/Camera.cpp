#include "Camera.h"

/// <summary>
/// Initializes a new instance of the <see cref="Camera"/> class.
/// </summary>
Camera::Camera()
{
	m_right = DXVector3(1.0f, 0.0f, 0.0f);
	cameraPosition = DXVector3(0.0f, 0.0f, 0.0f);
	cameraTarget = DXVector3(0.0f, 0.0f, 5.0f);
	cameraUpVector = DXVector3(0.0f, 1.0f, 0.0f);

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

void Camera::SetCamera(Renderer* _renderer)
{
	_renderer->SetCamera(&m_right, &cameraPosition, &cameraTarget, &cameraUpVector);
}

