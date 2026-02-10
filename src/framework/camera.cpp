#include "camera.h"

#include "main/includes.h"
#include <iostream>

Camera::Camera()
{
	view_matrix.SetIdentity();
	SetOrthographic(-1,1,1,-1,-1,1);
}

Vector3 Camera::GetLocalVector(const Vector3& v)
{
	Matrix44 iV = view_matrix;
	if (iV.Inverse() == false)
		std::cout << "Matrix Inverse error" << std::endl;
	Vector3 result = iV.RotateVector(v);
	return result;
}

Vector3 Camera::ProjectVector(Vector3 pos)
{
	Vector4 pos4 = Vector4(pos.x, pos.y, pos.z, 1.0);
	Vector4 result = viewprojection_matrix * pos4;
	if (type == ORTHOGRAPHIC)
		return result.GetVector3();
	else
		return result.GetVector3() / result.w;
}

void Camera::Rotate(float angle, const Vector3& axis)
{
	Matrix44 R;
	R.MakeRotationMatrix(angle, axis);
	Vector3 new_front = R * (center - eye);
	center = eye + new_front;
	UpdateViewMatrix();
}

void Camera::Move(Vector3 delta)
{
	Vector3 localDelta = GetLocalVector(delta);
	eye = eye - localDelta;
	center = center - localDelta;
	UpdateViewMatrix();
}

void Camera::SetOrthographic(float left, float right, float top, float bottom, float near_plane, float far_plane)
{
	type = ORTHOGRAPHIC;

	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->near_plane = near_plane;
	this->far_plane = far_plane;

	UpdateProjectionMatrix();
}

void Camera::SetPerspective(float fov, float aspect, float near_plane, float far_plane)
{
	type = PERSPECTIVE;

	this->fov = fov;
	this->aspect = aspect;
	this->near_plane = near_plane;
	this->far_plane = far_plane;

	UpdateProjectionMatrix();
}

void Camera::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// Reset Matrix (Identity)
	view_matrix.SetIdentity();

	// Comment this line to create your own projection matrix!
	// SetExampleViewMatrix();

	// Remember how to fill a Matrix4x4 (check framework slides)
	// Careful with the order of matrix multiplications, and be sure to use normalized vectors!
    
    Vector3 f = (center - eye).Normalize();
    Vector3 r = f.Cross(up).Normalize();
    Vector3 u = r.Cross(f);

    Matrix44 rotation;
    rotation.SetIdentity();
    
    rotation.M[0][0] = r.x;
    rotation.M[1][0] = r.y;
    rotation.M[2][0] = r.z;
    
    rotation.M[0][1] = u.x;
    rotation.M[1][1] = u.y;
    rotation.M[2][1] = u.z;

    rotation.M[0][2] = -f.x;
    rotation.M[1][2] = -f.y;
    rotation.M[2][2] = -f.z;

    Matrix44 translation;
    translation.MakeTranslationMatrix(-eye.x, -eye.y, -eye.z);
    
    view_matrix = rotation * translation;

	UpdateViewProjectionMatrix();
}

// Create a projection matrix
void Camera::UpdateProjectionMatrix()
{
	// Reset Matrix (Identity)
	projection_matrix.SetIdentity();

	// Comment this line to create your own projection matrix!
	// SetExampleProjectionMatrix();
    
	// Remember how to fill a Matrix4x4 (check framework slides)
	
	if (type == PERSPECTIVE) {
        float f = 1.0f/tanf(fov * DEG2RAD * 0.5f);
        
        Matrix44 p;
        p.SetIdentity();
        
        p.M[0][0] = f/aspect;
        p.M[1][1] = f;
        p.M[2][2] = (far_plane+near_plane)/(near_plane-far_plane);
        p.M[2][3] = -1.0f;
        p.M[3][2] = (2.0f*far_plane*near_plane)/(near_plane-far_plane);
        p.M[3][3] = 0.0f;
        
        projection_matrix = p;
	}
	else if (type == ORTHOGRAPHIC) {
        
        Matrix44 orto;
        orto.SetIdentity();
        
        orto.M[0][0] = 2/(right-left);
        orto.M[1][1] = 2/(top-bottom);
        orto.M[2][2] = 2/(near_plane-far_plane);
        
        orto.M[3][0] = (-right-left)/(right-left);
        orto.M[3][1] = (-top-bottom)/(top-bottom);
        orto.M[3][2] = (-near_plane-far_plane)/(near_plane-far_plane);
        
        projection_matrix = orto;
	}

	UpdateViewProjectionMatrix();
}

void Camera::UpdateViewProjectionMatrix()
{
	viewprojection_matrix = projection_matrix * view_matrix;
}

Matrix44 Camera::GetViewProjectionMatrix()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	return viewprojection_matrix;
}

// The following methods have been created for testing.
// Do not modify them.

void Camera::SetExampleViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, view_matrix.m );
}

void Camera::SetExampleProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (type == PERSPECTIVE)
		gluPerspective(fov, aspect, near_plane, far_plane);
	else
		glOrtho(left,right,bottom,top,near_plane,far_plane);

	glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix.m );
	glMatrixMode(GL_MODELVIEW);
}
