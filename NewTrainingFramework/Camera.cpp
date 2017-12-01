#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(Vector3 position_, Vector3 target_, Vector3 up_, GLfloat moveSpeed_, GLfloat rotateSpeed_, GLfloat nearCam_, GLfloat farCam_, GLfloat FOV_)
{
	position = position_;
	target = target_;
	up = up_;
	moveSpeed = moveSpeed_;
	rotateSpeed = rotateSpeed_;
	nearCam = nearCam_;
	farCam = farCam_;
	FOV = FOV_;
}

void Camera::calculateAxis()
{
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

void Camera::updateWorldView()
{
	calculateAxis();
	Matrix R, T;
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0;		 R.m[3][1] = 0;		  R.m[3][2] = 0;	   R.m[3][3] = 1;

	T.SetTranslation(position);
	
	worldMatrix = R * T;
	R = R.Transpose();
	T.SetTranslation(-(position));

	viewMatrix = T * R;
}

void Camera::moveOz(int dir)
{
	Vector3 forward = -(target - position).Normalize() * dir;
	Vector3 deplasare = forward * moveSpeed * deltaTime;
	position += deplasare;
	target += deplasare;
	updateWorldView();
}

void Camera::moveOy(int dir)
{
	Vector3 forward = up.Normalize() * dir;
	Vector3 deplasare = forward * moveSpeed * deltaTime;
	position += deplasare;
	target += deplasare;
	updateWorldView();
}

void Camera::moveOx(int dir)
{
	Vector3 forward = up.Cross(-(target - position)).Normalize() * dir;
	Vector3 deplasare = forward * moveSpeed * deltaTime;
	position += deplasare;
	target += deplasare;
	updateWorldView();
}

void Camera::rotateOx(int dir)
{
	Matrix	m;
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * m.SetRotationX(rotateSpeed * deltaTime * dir);
	Vector4 u = rotatedLocalUp * worldMatrix;
	up = Vector3(u.x, u.y, u.z).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * m;
	u = rotatedTarget * worldMatrix;
	target = Vector3(u.x, u.y, u.z);
	updateWorldView();
}

void Camera::rotateOz(int dir)
{
	Matrix	m;
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * m.SetRotationZ(rotateSpeed * deltaTime * dir);
	Vector4 u = rotatedLocalUp * worldMatrix;
	up = Vector3(u.x, u.y, u.z).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * m;
	u = rotatedTarget * worldMatrix;
	target = Vector3(u.x, u.y, u.z);
	updateWorldView();
}

void Camera::rotateOy(int dir)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix	m;
	m.SetRotationY(rotateSpeed * deltaTime * dir);
	Vector4 rotatedTarget = localTarget * m;
	Vector4 u = rotatedTarget * worldMatrix;
	target = Vector3(u.x, u.y, u.z);
	updateWorldView();
}

Matrix Camera::getViewMatrix()
{
	return viewMatrix;
}

Matrix Camera::getWorldMatrix()
{
	return worldMatrix;
}

GLfloat Camera::getFOV()
{
	return FOV;
}

GLfloat Camera::getNearCam()
{
	return nearCam;
}

GLfloat Camera::getFarCam()
{
	return farCam;
}

void Camera::setDeltaTime(GLfloat deltaTime_)
{
	deltaTime = deltaTime_;
}

Camera::~Camera()
{
}
