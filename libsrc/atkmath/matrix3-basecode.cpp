#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

//??
Vector3 Matrix3::toEulerAnglesXYZ() const
{
   double alpha;
   double theta;
   double beta;
   theta = asin(m13);
   if(m13 == 1){
      //beta = 0
      alpha = atan2(m21,m22);
      beta = 0;
   }else if(m13 == -1){
      alpha = atan2(-m21,m22);
      beta = 0;
   }else{
      alpha = asin(m23/-cos(theta));
      beta = asin(m12/-cos(theta));
   }
   return Vector3(alpha,theta,beta);
}

//good
Vector3 Matrix3::toEulerAnglesXZY() const
{
   double beta;
   double theta;
   double alpha;
   beta = asin(-m12);
   if(m12 == 1){
      theta = atan2(-m23,-m21);
      alpha = 0;
   }else if(m12 == -1){
      theta = atan2(m23,m21);
      alpha = 0;
   }else{
      theta = -acos(m11/cos(beta));
      alpha = acos(m22/cos(beta));
   }
   return Vector3(alpha,theta,beta);
}

// NOT good
Vector3 Matrix3::toEulerAnglesYXZ() const
{
   double alpha;
   double theta;
   double beta;
   alpha = asin(-m23);
   if(m23 == 1){
      beta = atan2(-m31,-m32);
      theta = 0;
   }else if(m23 == -1){
      beta = atan2(m31,m32);
      theta = 0;
   }else{
      beta = asin(m21/cos(alpha));
      theta = asin(m13/cos(alpha));
   }
   return Vector3(alpha,theta,beta);
}

//good
Vector3 Matrix3::toEulerAnglesYZX() const
{
   double beta;
   double alpha;
   double theta;
   beta = asin(m21);
   if(m21 == 1){
      alpha = atan2(m32,m33);
      theta = 0;
   }else if(m21 == -1){
      alpha = atan2(m32,m33);
      theta = 0;
   }else{
      alpha = acos(m22/cos(beta));
      theta = -acos(m11/cos(beta));
   }
   return Vector3(alpha, theta, beta);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   double alpha;
   double theta;
   double beta;
   alpha = asin(m32);
   if(m32 == 1){
      theta = 0;
      beta = atan2(m21,-m23);
   }else if(m32 == -1){
      theta = 0;
      beta = atan2(m21,m23);
   }else{
      theta = -acos(m33/cos(alpha));
      beta = acos(m22/cos(alpha));
   }
   return Vector3(alpha,theta,beta);
}

//good
Vector3 Matrix3::toEulerAnglesZYX() const
{
   double theta;
   double alpha;
   double beta;
   theta = asin(-m31);
   //+90
   if(m31 == -1){
      //let beta = 0
     alpha = atan2(m12,m13);
     beta = 0;
   //-90
   }else if(m31 == 1){
      alpha = atan2(-m12,-m13);
      beta = 0;
   }else{
      alpha = atan2(m32,m33);
      beta = atan2(m21,m11);
   }
   return Vector3(alpha, theta, beta);
   //z beta, y theta, x alpha
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   *this = Identity;
   *this = getXMatrix(angleRad[0])*getYMatrix(angleRad[1])*getZMatrix(angleRad[2]);
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   *this = Identity;
   *this = getXMatrix(angleRad[0])*getZMatrix(angleRad[2])*getYMatrix(angleRad[1]);
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   *this = Identity;
   *this = getYMatrix(angleRad[1])*getXMatrix(angleRad[0])*getZMatrix(angleRad[2]);
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   *this = Identity;
   *this = getYMatrix(angleRad[1])*getZMatrix(angleRad[2])*getXMatrix(angleRad[0]);
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   *this = Identity;
   *this = getZMatrix(angleRad[2])*getXMatrix(angleRad[0])*getYMatrix(angleRad[1]);
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   *this = Identity;
   *this = getZMatrix(angleRad[2])*getYMatrix(angleRad[1])*getXMatrix(angleRad[0]);
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   Quaternion q;
   q.fromMatrix(*this);
   q.toAxisAngle(axis,angleRad);
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   Quaternion q;
   q.fromAxisAngle(axis,angleRad);
   *this = q.toMatrix();
}

Matrix3 Matrix3::getXMatrix(double angleRad){
   Matrix3 Rx;
   Rx[0][0] = 1;
   Rx[0][1] = 0;
   Rx[0][2] = 0;
   Rx[1][0] = 0;
   Rx[1][1] = cos(angleRad);
   Rx[1][2] = -sin(angleRad);
   Rx[2][0] = 0;
   Rx[2][1] = sin(angleRad);
   Rx[2][2] = cos(angleRad);
   return Rx;
}

Matrix3 Matrix3::getYMatrix(double angleRad){
   Matrix3 Ry;
   Ry[0][0] = cos(angleRad);
   Ry[0][1] = 0;
   Ry[0][2] = sin(angleRad);
   Ry[1][0] = 0;
   Ry[1][1] = 1;
   Ry[1][2] = 0;
   Ry[2][0] = -sin(angleRad);
   Ry[2][1] = 0;
   Ry[2][2] = cos(angleRad);
   return Ry;
}

Matrix3 Matrix3::getZMatrix(double angleRad){
   Matrix3 Rz;
   Rz[0][0] = cos(angleRad);
   Rz[0][1] = -sin(angleRad);
   Rz[0][2] = 0;
   Rz[1][0] = sin(angleRad);
   Rz[1][1] = cos(angleRad);
   Rz[1][2] = 0;
   Rz[2][0] = 0;
   Rz[2][1] = 0;
   Rz[2][2] = 1;
   return Rz;
}

}