#pragma once
#include "../Utilities/utilities.h"
#include "../Utilities/Math.h"

class Camera
{
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat nearCam;
	GLfloat farCam;
	GLfloat FOV;
	GLfloat deltaTime;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	Matrix P;
	Matrix viewMatrix, worldMatrix;
public:
	void moveOx(int);
	void moveOy(int);
	void moveOz(int);
	void rotateOx(int);
	void rotateOy(int);
	void rotateOz(int);
	void calculateAxis();
	void updateWorldView();
	void setDeltaTime(GLfloat);

	GLfloat getFOV();
	GLfloat getNearCam();
	GLfloat getFarCam();
	Vector3 getPosition();
	Matrix getViewMatrix();
	Matrix getWorldMatrix();
	Matrix getPerspectiveMatrix();
	Camera();
	Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat nearCam, GLfloat farCam, GLfloat FOV);
	~Camera();
};

