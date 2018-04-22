#include "Camera.h"
#include "MatrixMath.h"
#include "Vector3.h"

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

void Camera::SetCamera(Renderer* _renderer)
{
	Matrix* matWorld, matWorldX, matWorldY, matWorldZ;
	Matrix* matView = NULL;
	Matrix* matProj = NULL;

	Vector3 cameraPosition = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 cameraTarget = Vector3(0.0f, 0.0f, 5.0f);
	Vector3 cameraUpVector = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 m_right = Vector3(1.0f, 0.0f, 0.0f);

	// Where to implement these functions???
	MatrixMath* math = new MatrixMath();
	math->MatrixLookAtLH(matView, &cameraPosition, &cameraTarget, &cameraUpVector);
	_renderer->SetTransform(_renderer->VIEW, matView);

	math->MatrixPerspectiveFovLH(matProj, _renderer->PI / 4, 1.0f, 1.0f, 2000.0f);
	_renderer->SetTransform(_renderer->PROJECTION, matProj);
}

