#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	float cosA = q0[0]*q1[0] + q0[1]*q1[1] + q0[2]*q1[2] + q0[3]*q1[3];
 	float a = acos(cosA);
	Quaternion q = Quaternion((sin(a*(1-t))/sin(a))*q0 + (sin(a*t)/sin(a))*q1);
	return q;
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	angleRad = acos(mW)*2;
	if(sin(angleRad/2) == 0){
		axis = Vector3(1,0,0);
	}else{
		double x = mX/sin(angleRad/2);
		double y = mY/sin(angleRad/2);
		double z = mZ/sin(angleRad/2);
		axis = Vector3(x,y,z);
	}
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	double vx = sin(angleRad/2)*axis[0];
	double vy = sin(angleRad/2)*axis[1];
	double vz = sin(angleRad/2)*axis[2];
	double vw = cos(angleRad/2);
	Quaternion q = Quaternion(vx,vy,vz,vw);
	*this = q;
}

Matrix3 Quaternion::toMatrix () const
{
	double vx = mX;
	double vy = mY;
	double vz = mZ;
	double vw = mW;

	double b11 = 1-2*(vy*vy + vz*vz); //
	double b12 = 2*(vx*vy - vw*vz); //
	double b13 = 2*(vx*vz + vw*vy); //
	double b21 = 2*(vx*vy + vw*vz); //
	double b22 = 1-2*(vx*vx + vz*vz); //
	double b23 = 2*(vy*vz - vw*vx); //
	double b31 = 2*(vx*vz - vw*vy); //
	double b32 = 2*(vy*vz + vw*vx); //
	double b33 = 1-2*(vx*vx + vy*vy); //

	Matrix3 matrix = Matrix3(b11, b12, b13,
							 b21, b22, b23,
							 b31, b32, b33);
	return matrix;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	//get all variables squared
	float w2 = (rot[0][0] + rot[1][1] + rot[2][2] + 1)/4;
	float x2 = (1 + rot[0][0] - rot[1][1] - rot[2][2])/4;
	float y2 = (1 - rot[0][0] + rot[1][1] - rot[2][2])/4;
	float z2 = (1 - rot[0][0] - rot[1][1] + rot[2][2])/4;

	float vx;
	float vy;
	float vw;
	float vz;
	//use off diagonal terms depending on which is largest 
	//w2 largest
	if(w2 >= x2 && w2 >= y2 && w2 >= z2){
		vw = sqrt(w2);
		vz = (1/(4*vw))*(rot[1][0] - rot[0][1]); //wz = 21 - 12
		vx = (1/(4*vw))*(rot[2][1] - rot[1][2]); //wx = 32 - 23
		vy = (1/(4*vw))*(rot[0][2] - rot[2][0]);
		//vy = ((1/4)*(rot[0][2] - rot[2][0]))/vw; //yw = 13 - 31
	//x2 largest
	}else if(x2 >= w2 && x2 >= y2 && x2 >= z2){
		vx = sqrt(x2);
		//vw = (1/(4*vx))*(rot[2][1] - rot[1][2]);
		vw = ((1/4)*rot[2][1] - rot[1][2])/vx; // xw = 32 - 23 (FORMERLY 0 instead of 1)
		//vy = (1/(4*vx))*(rot[1][0] + rot[0][1]);
		vy = ((1/4)*rot[1][0] + rot[0][1])/vx; //xy = 21 + 12 (FORMERLY MINUS)
		//vz = (1/(4*vw))*(rot[1][0] - rot[0][1]);
		vz = ((1/4)*(rot[0][2] + rot[2][0]))/vx; //zx = 13 + 31
	//y2 largest
	}else if(y2 >= w2 && y2 >= x2 && y2 >= z2){
		vy = sqrt(y2);
		vx = ((1/4)*rot[1][0] + rot[0][1])/vy; // yx = 21 + 12 (FORMERLY MINUS)
		//vz = (1/(4*vy))*(rot[2][1] + rot[1][2]);
		vz = ((1/4)*(rot[1][2] + rot[2][1]))/vy; //yz = 13 + 31
		vw = ((1/4)*(rot[0][2] - rot[2][0]))/vy; //yw = 13 - 31
		//vw = (1/(4*vz))*(rot[1][0] - rot[0][1]);
	//z2 largest
	}else if(z2 >= w2 && z2 >= x2 && z2 >= y2){
		vz = sqrt(z2);
		//vy = (1/(4*vz))*(rot[2][1] + rot[1][2]);
		vy = ((1/4)*(rot[1][2] + rot[2][1]))/vz; // yz = 23 + 32
		vw = ((1/4)*(rot[1][0] - rot[0][1]))/vz; // zw = 21 - 12
		//vx = (1/(4*vy))*(rot[1][0] + rot[0][1]);
		vx = ((1/4)*(rot[0][2] + rot[2][0]))/vz; // zx = 13 + 31
	}

	*this = Quaternion(vx,vy,vz,vw);
}

}