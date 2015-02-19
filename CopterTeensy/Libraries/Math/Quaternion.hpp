/*
 * Quaternion.hpp
 *
 *  Created on: 16.2.2015
 *      Author: Juraj
 */

#ifndef LIBRARIES_HIL_QUATERNION_HPP_
#define LIBRARIES_HIL_QUATERNION_HPP_

#include <Vector3.hpp>

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

	Quaternion getProduct(Quaternion q)
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

	Quaternion getConjugate()
	{
		return Quaternion(w, -x, -y, -z);
	}

	float getMagnitude()
	{
		return sqrt(w * w + x * x + y * y + z * z);
	}

	void normalize()
	{
		float m = getMagnitude();
		w /= m;
		x /= m;
		y /= m;
		z /= m;
	}

	Quaternion getNormalized()
	{
		Quaternion r(w, x, y, z);
		r.normalize();
		return r;
	}

	template<typename T>
	void setQuaternion(T* value)
	{
		w = (float) value[0];
		x = (float) value[1];
		y = (float) value[2];
		z = (float) value[3];
	}

};

#endif /* LIBRARIES_HIL_QUATERNION_HPP_ */
