/*
 * Vector.hpp
 *
 *  Created on: 16.2.2015
 *      Author: Juraj
 */

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <Arduino.h>
#include <Quaternion.hpp>
//#include <Math.hpp>

#define toRad(deg) ((deg)*DEG_TO_RAD)
#define toDeg(rad) ((rad)*RAD_TO_DEG)
#define radToCentiDeg(rad) ((rad)*RAD_TO_DEG*100)
#define toCentiDeg(deg) deg*100

#define YAW x
#define PITCH y
#define ROLL z

#define VEC3_X 0
#define VEC3_Y 1
#define VEC3_Z 2

template<typename T>
class Vector3
{
public:
	T x;
	T y;
	T z;

	Vector3<T>()
	{
	}

	Vector3(T nx, T ny, T nz) :
			x(nx), y(ny), z(nz)
	{
	}

	float get_magnitude();
	void normalize();
	Vector3<T> get_normalized();
	void multiply(float mx, float my, float mz);
	float average();
	Vector3<T> rad_to_centi_deg();
	Vector3<T> to_centi_deg();
	void reset();
	float dot_product(Vector3<T> vec1, Vector3<T> vec2);
	String to_string();
	String to_string_degrees();
	void rotate(Quaternion *q);
	Vector3<T> get_rotated(Quaternion *q);
	void quaternion_to_euler(Quaternion &q);
	void quaternion_to_ypr(Quaternion &q);
	void get_array(T* array);

  Vector3<T> operator %(const Vector3<T> &v) const;

	T& operator[](uint8_t id);

  // function call operator
   void operator ()(const T x0, const T y0, const T z0);

   // test for equality
   bool operator ==(const Vector3<T> &v) const;

   // test for inequality
   bool operator !=(const Vector3<T> &v) const;

   // negation
   Vector3<T> operator -(void) const;

   // addition
   Vector3<T> operator +(const Vector3<T> &v) const;

   // subtraction
   Vector3<T> operator -(const Vector3<T> &v) const;

   // uniform scaling
   Vector3<T> operator *(const T num) const;

   Vector3<T> operator *(Vector3<T> vec) const;

   // uniform scaling
   Vector3<T> operator  /(const T num) const;

   // addition
   Vector3<T> &operator +=(const Vector3<T> &v);

   // subtraction
   Vector3<T> &operator -=(const Vector3<T> &v);

   // uniform scaling
   Vector3<T> &operator *=(const T num);

   Vector3<T> &operator *=(const Vector3<T> vec);


//   Vector3<T> &operator *=(Matrix3<T> mat);

   // uniform scaling
   Vector3<T> &operator /=(const T num);

   // check if any elements are NAN
    bool is_nan(void) const;

    // check if any elements are infinity
    bool is_inf(void) const;

    template<typename U>
	void setVector(U* value);

};


typedef Vector3<int16_t> Vector3Int16;
typedef Vector3<int32_t> Vector3Int32;
typedef Vector3<float> Vector3Float;

#endif /* LIBRARIES_HIL_VECTOR3_HPP_ */
