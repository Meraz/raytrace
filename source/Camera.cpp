#include "Camera.h"

using namespace std;

XMFLOAT4 operator*(const XMFLOAT4 &l, const XMFLOAT4 &r) 
{
    XMVECTOR lvec(XMLoadFloat4(&l));
    XMVECTOR rvec(XMLoadFloat4(&r));

	lvec *= rvec;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	
	return a;
}

XMFLOAT4 operator*(const XMFLOAT4 &l, const float &r) {
    
	XMVECTOR lvec(XMLoadFloat4(&l));
	
	lvec *= r;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}

XMFLOAT4 operator*(const float &l, const XMFLOAT4 &r) 
{
	XMVECTOR lvec(XMLoadFloat4(&r));
	
	lvec *= l;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}


XMFLOAT4 operator+(const XMFLOAT4 &l, const XMFLOAT4 &r) 
{
    XMVECTOR lvec(XMLoadFloat4(&l));
    XMVECTOR rvec(XMLoadFloat4(&r));

	lvec += rvec;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}

XMFLOAT4 operator+=(const XMFLOAT4 &l, const XMFLOAT4 &r) 
{
    XMVECTOR lvec(XMLoadFloat4(&l));
    XMVECTOR rvec(XMLoadFloat4(&r));

	lvec += rvec;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}

std::vector<Camera*> Camera::m_camera = std::vector<Camera*>(10);

Camera* Camera::GetCamera(int index)				// Quite the awful multiton here. Easy, not very good if getting cameras above 10.
{
	if(m_camera.at(index) == nullptr)
		m_camera.at(index) = new Camera();
	return m_camera.at(index);
}

Camera::Camera()
{
	mPosition	= XMFLOAT4(0.0f, 0.0f, 250.0f, 1.0f);
	mRight		= XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	mDefaultRight = mRight;
	mUp				= XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	mDefaultUp	= mUp;
	mLook		 = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	mDefaultLook = mLook;


	XMStoreFloat4x4(&m_view, XMMatrixIdentity());
	XMStoreFloat4x4(&m_proj, XMMatrixIdentity());
//	setLens(3.1415f/4.0f, 1.0f, 1.0f, 1000.0f );

	mYaw = PI;
	mPitch = PI;
}

Camera::~Camera()
{
}

void Camera::SetPosition(XMFLOAT4 lPos)
{
	mPosition = lPos;
}

void Camera::setYPosition(float y)
{
	mPosition.y = y;
}

void Camera::setLens(float fovY, float aspect, float zn, float zf)
{
	XMMATRIX temp = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
	XMStoreFloat4x4(&m_proj, temp);
}

void Camera::strafe(float d)
{
	mPosition = mPosition + -d * mRight;
}

void Camera::walk(float d)
{
	mPosition = mPosition + d * mLook;
}

void Camera::pitch(float angle)
{
	XMMATRIX R;
	
	R = XMMatrixRotationX(angle);

	//XMStoreFloat4(&mUp, XMVector4Transform(XMLoadFloat4(&mUp), R));
	XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mLook), R));
}

void Camera::rotateY(float angle)
{
	XMMATRIX R;
	R = XMMatrixRotationY(angle);


//	XMStoreFloat4(&mRight, XMVector4Transform(XMLoadFloat4(&mRight), R));
	//XMStoreFloat4(&mUp, XMVector4Transform(XMLoadFloat4(&mUp), R));
	XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mLook), R));
}

void Camera::update(float jaw, float pitch) 
{
	mYaw += jaw;

	/*
	if (mYaw > 360)
		mYaw = 0.0f;
	if (mYaw < 0)
		mYaw = 360.0f;
	*/


	mPitch += -pitch;

//	if (mPitch > PI/2)
//		mPitch = PI / 2;
//	if (mPitch < PI * 0.05 )
//		mPitch = PI * 0.05;

	XMMATRIX R;
	R = XMMatrixRotationRollPitchYaw(mPitch, mYaw, 0.0f);
	
    XMStoreFloat4(&mRight, XMVector4Transform(XMLoadFloat4(&mDefaultRight), R));
//	XMStoreFloat4(&mUp, XMVector4Transform(XMLoadFloat4(&mUp), R));
	XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mDefaultLook), R));
}

void Camera::rebuildView()
{
	// Not sure which one to use. I would pressume that I'd use "LookAt", however, "LookTo" is the one to give the right results

	/* Definitions on both functions
	// XMMatrixLookAtLH method
	// Builds a view matrix for a left-handed coordinate system using a camera position, an up direction, and a focal point. 	

	// XMMatrixLookToLH method
	// Builds a view matrix for a left-handed coordinate system using a camera position, an up direction, and a camera direction. 	
	*/
	XMMATRIX temp = XMMatrixLookToLH(XMLoadFloat4(&mPosition), XMLoadFloat4(&mLook), XMLoadFloat4(&mUp));
	XMStoreFloat4x4(&m_view, temp); 
}

void Camera::MoveY(float p_step)
{
	mPosition.y = mPosition.y + p_step;
}