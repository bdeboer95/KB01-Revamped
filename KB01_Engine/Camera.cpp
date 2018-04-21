#include "Camera.h"

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
	D3DXMATRIX matWorld, matWorldX, matWorldY, matWorldZ;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;

	D3DXVECTOR3 cameraPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 cameraTarget = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	D3DXVECTOR3 cameraUpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &cameraPosition, &cameraTarget, &cameraUpVector);

	_renderer->SetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 2000.0f);
	//
	_renderer->SetTransform(D3DTS_PROJECTION, &matProj);

	_renderer->InitCamera();
}

