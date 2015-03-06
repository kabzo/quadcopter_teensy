/*
 * Quaternion.cpp
 *
 *  Created on: 27.2.2015
 *      Author: Juraj
 */

#include <Vector3.hpp>
#include <Quaternion.hpp>

Quaternion Quaternion::getProduct(Quaternion q)
{
	// Quaternion multiplication is defined by:
	//     (Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
	//     (Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
	//     (Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
	//     (Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2
	return Quaternion(w * q.w - x * q.x - y * q.y - z * q.z,  // new w
										w * q.x + x * q.w + y * q.z - z * q.y,  // new x
										w * q.y - x * q.z + y * q.w + z * q.x,  // new y
										w * q.z + x * q.y - y * q.x + z * q.w);  // new z
}

Quaternion Quaternion::getConjugate()
{
	return Quaternion(w, -x, -y, -z);
}

float Quaternion::getMagnitude()
{
	return sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::normalize()
{
	float m = getMagnitude();
	w /= m;
	x /= m;
	y /= m;
	z /= m;
}

Quaternion Quaternion::getNormalized()
{
	Quaternion r(w, x, y, z);
	r.normalize();
	return r;
}

template<typename T>
void Quaternion::operator ()(const T* value)
{
	w = (float) value[0];
	x = (float) value[1];
	y = (float) value[2];
	z = (float) value[3];
}

template<typename T>
void Quaternion::operator ()(const T w0,const T x0, const T y0, const T z0){
	w = (float) w0;
	x = (float) x0;
	y = (float) y0;
	z = (float) z0;
}


Quaternion Quaternion::operator *(Quaternion multiply)
{
	Vector3<float> va;
	Vector3<float> vb;
	Vector3<float> crossAB;
	float dotAB;

	va.x = x;
	va.y = y;
	va.z = z;

	vb.x = multiply.x;
	vb.y = multiply.y;
	vb.z = multiply.z;

	dotAB = va.dot_product(vb);
	crossAB = va%vb;

	Quaternion ret;

	ret.w = w * multiply.w - dotAB;
  ret.x = w * vb.x + multiply.w * va.x + crossAB.x;
  ret.y = w * vb.y + multiply.w * va.y + crossAB.y;
  ret.z= w * vb.z + multiply.w * va.z + crossAB.z;
  return ret;
}

template<typename T>
void Quaternion::setQuaternion(T* value)
{
	w = (float) value[0];
	x = (float) value[1];
	y = (float) value[2];
	z = (float) value[3];
}


template void Quaternion::operator ()(const long* value);
template void Quaternion::operator ()(const float w,const float x0, const float y0, const float z0);
