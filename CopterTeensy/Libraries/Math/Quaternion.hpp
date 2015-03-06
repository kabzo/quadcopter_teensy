/*
 * Quaternion.hpp
 *
 *  Created on: 16.2.2015
 *      Author: Juraj
 */

#ifndef LIBRARIES_HIL_QUATERNION_HPP_
#define LIBRARIES_HIL_QUATERNION_HPP_

//#include <Vector3.hpp>

template<typename T>
class Vector3;

class Quaternion
{
public:
	float w; //q0
	float x; //q1
	float y; //q2
	float z; //q3

	Quaternion() :
			w(1.0f), x(0), y(0), z(0)
	{
	}

	Quaternion(float nw, float nx, float ny, float nz) :
			w(nw), x(nx), y(ny), z(nz)
	{
	}

	Quaternion getProduct(Quaternion q);

	Quaternion getConjugate();

	float getMagnitude();
	void normalize();

	Quaternion getNormalized();

	template<typename T>
	void operator ()(const T* value);

	template<typename T>
	void operator ()(const T w0,const T x0, const T y0, const T z0);

	Quaternion operator *(Quaternion multiply);

	template<typename T>
	void setQuaternion(T* value);
};

#endif /* LIBRARIES_HIL_QUATERNION_HPP_ */
