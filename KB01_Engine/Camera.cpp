#include "Camera.h"
#include "d3dx9.h"

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
	//D3DXMatrixRotationX(&matWorldX, 1.0f);  //--沿X轴旋转   
	//D3DXMatrixRotationY(&matWorldY, 1.0f);  //--沿Y轴旋转   
	//D3DXMatrixRotationZ(&matWorldZ, 1.0f);  //--沿Z轴旋转   

	//D3DXMatrixMultiply(&matWorld, &matWorldX, &matWorldY);   //--组合变换   
	//D3DXMatrixMultiply(&matWorld, &matWorld, &matWorldZ);
	/*cameraPosition = D3DXVECTOR3(-45, 0, 60);
	cameraTarget = D3DXVECTOR3(0, 0, 0);
	cameraUpVector = D3DXVECTOR3(1, 0, 0);*/

	cameraPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cameraTarget = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	cameraUpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &cameraPosition, &cameraTarget, &cameraUpVector);
	static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice())->SetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	/*D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 500 / 500, 1, 100);*/
	static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice())->SetTransform(D3DTS_PROJECTION, &matProj);
	/*static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice())->SetTransform(D3DTS_WORLD, &matWorld);*/

}

