/*
 * Vector3.cpp
 *
 *  Created on: 16.2.2015
 *      Author: Juraj
 */

#include <Vector3.hpp>
#include <Quaternion.hpp>

template<typename T>
Vector3<T> &Vector3<T>::operator *=(const T num)
{
	x *= num;
	y *= num;
	z *= num;
	return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator *=(const Vector3<T> vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator /=(const T num)
{
	x /= num;
	y /= num;
	z /= num;
	return *this;
}

template<typename T> template<typename U>
Vector3<T> &Vector3<T>::operator /=(const Vector3<U> &v)
{
	x /= (T) v.x;
	y /= (T) v.y;
	z /= (T) v.z;
	return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator -=(const Vector3<T> &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

template<typename T>
bool Vector3<T>::is_nan(void) const
{
	return isnan(x) || isnan(y) || isnan(z);
}

template<typename T>
bool Vector3<T>::is_inf(void) const
{
	return isinf(x) || isinf(y) || isinf(z);
}

template<typename T>
Vector3<T> &Vector3<T>::operator +=(const Vector3<T> &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator /(const T num) const
{
	return Vector3<T>(x / num, y / num, z / num);
}

template<typename T>
Vector3<T> Vector3<T>::operator *(const T num) const
{
	return Vector3<T>(x * num, y * num, z * num);
}

template<typename T>
Vector3<T> Vector3<T>::operator *(Vector3<T> vec) const
{
	return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);
}

template<typename T> template<typename U>
Vector3<U> Vector3<T>::operator -(const Vector3<U> &v) const
{
	Vector3<U> a(x - v.x, y - v.y, z - v.z);
	return a;
}

template<typename T>
Vector3<T> Vector3<T>::operator +(const Vector3<T> &v) const
{
	return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template<typename T> template<typename U>
Vector3<T> &Vector3<T>::operator =(Vector3<U> v)
{
	x = (T) v.x;
	y = (T) v.y;
	z = (T) v.z;
	return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator -(void) const
{
	return Vector3<T>(-x, -y, -z);
}

template<typename T>
bool Vector3<T>::operator ==(const Vector3<T> &v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

template<typename T>
bool Vector3<T>::operator !=(const Vector3<T> &v) const
{
	return (x != v.x && y != v.y && z != v.z);
}

template<typename T>
Vector3<T> Vector3<T>::rad_to_centi_deg()
{
	Vector3<T> vec;
	vec.x = radToCentiDeg(x);
	vec.y = radToCentiDeg(y);
	vec.z = radToCentiDeg(z);
	return vec;
}

template<typename T>
Vector3<T> Vector3<T>::to_centi_deg()
{
	Vector3<T> vec;
	vec.x = toCentiDeg(x);
	vec.y = toCentiDeg(y);
	vec.z = toCentiDeg(z);
	return vec;
}

template<typename T>
void Vector3<T>::reset()
{
	x = 0;
	y = 0;
	z = 0;
}

template<typename T>

T& Vector3<T>::operator[](uint8_t id)
{
	T *_v = &x;
	return _v[id];

}

template<typename T>
float Vector3<T>::average()
{
	float avg = x + y + z;
	avg /= 3;
	return avg;
}

template<typename T>
void Vector3<T>::rotate(Quaternion *q)
{
	// http://www.cprogramming.com/tutorial/3d/quaternions.html
	// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
	// http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
	// ^ or: http://webcache.googleusercontent.com/search?q=cache:xgJAp3bDNhQJ:content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation&hl=en&gl=us&strip=1

	// P_out = q * P_in * conj(q)
	// - P_out is the output vector
	// - q is the orientation quaternion
	// - P_in is the input vector (a*aReal)
	// - conj(q) is the conjugate of the orientation quaternion (q=[w,x,y,z], q*=[w,-x,-y,-z])
	Quaternion p(0, x, y, z);

	// quaternion multiplication: q * p, stored back in p
	p = q->getProduct(p);

	// quaternion multiplication: p * conj(q), stored back in p
	p = p.getProduct(q->getConjugate());

	// p quaternion is now [0, x', y', z']
	x = p.x;
	y = p.y;
	z = p.z;
}

template<typename T>
Vector3<T> Vector3<T>::get_rotated(Quaternion *q)
{
	Vector3<T> r(x, y, z);
	r.rotate(q);
	return r;
}

template<typename T>
void Vector3<T>::quaternion_to_euler(Quaternion &q)
{
	ROLL = atan2(2.0f * (q.w * q.x + q.y * q.z), 1.0f - 2.0f * (q.x * q.x + q.y * q.y));			//roll
	PITCH = asin(2.0f * (q.w * q.y - q.z * q.x)); //pitch
	YAW = atan2(2.0f * (q.w * q.z + q.x * q.y), 1.0f - 2.0f * (q.z * q.z + q.y * q.y));

//	ROLL = atan2(2 * q.y * q.w - 2 * q.x * q.z, 1 - 2 * q.y * q.y - 2 * q.z * q.z);
//	PITCH = atan2(2 * q.x * q.w - 2 * q.y * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z);
//	YAW = asin(2 * q.x * q.y + 2 * q.z * q.w);

//	float pole = M_PI / 2.0f - 0.05f;                       // fix roll near poles with this tolerance
//
//	y = asin(2.0f * (q.w * q.y - q.x * q.z)); //pitch
//
//	if ((y < pole) && (y > -pole))
//		z = atan2(2.0f * (q.y * q.z + q.w * q.x), 1.0f - 2.0f * (q.x * q.x + q.y * q.y)); //roll
//
//	x = atan2(2.0f * (q.x * q.y + q.w * q.z), 1.0f - 2.0f * (q.y * q.y + q.z * q.z)); //yaw
}

template<typename T>
Quaternion Vector3<T>::euler_to_quaternion()
{
	Quaternion q;
	float cosX2 = cos(z / 2.0f);
	float sinX2 = sin(z / 2.0f);
	float cosY2 = cos(y / 2.0f);
	float sinY2 = sin(y / 2.0f);
	float cosZ2 = cos(x / 2.0f);
	float sinZ2 = sin(x / 2.0f);

	q.w = cosX2 * cosY2 * cosZ2 + sinX2 * sinY2 * sinZ2;
	q.x = sinX2 * cosY2 * cosZ2 - cosX2 * sinY2 * sinZ2;
	q.y = cosX2 * sinY2 * cosZ2 + sinX2 * cosY2 * sinZ2;
	q.z = cosX2 * cosY2 * sinZ2 - sinX2 * sinY2 * cosZ2;
	q.normalize();
	return q;
}

template<typename T>
void Vector3<T>::quaternion_to_gravity(Quaternion &q)
{
	x = 2 * (q.x * q.z - q.w * q.y);
	y = 2 * (q.w * q.x + q.y * q.z);
	z = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;
}

template<typename T>
void Vector3<T>::quaternion_to_ypr(Quaternion &q)
{
	YAW = atan2(2 * q.x * q.y - 2 * q.w * q.z, 2 * (q.w * q.w) + 2 * (q.x * q.x) - 1);
	PITCH = asin(2 * q.x * q.z + 2 * q.w * q.y);
	ROLL = -atan2(2 * q.y * q.z - 2 * q.w * q.x, 2 * (q.w * q.w) + 2 * (q.z * q.z) - 1);
}

template<typename T>
String Vector3<T>::to_string()
{
	String str = "[";
	str += x;
	str += ",";
	str += y;
	str += ",";
	str += z;
	str += "]";
	return str;
}

template<typename T>
void Vector3<T>::multiply(float mx, float my, float mz)
{
	x *= mx;
	y *= my;
	z *= mz;
}

template<typename T>
float Vector3<T>::get_magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

template<typename T>
void Vector3<T>::normalize()
{
	float m = get_magnitude();
	x /= m;
	y /= m;
	z /= m;
}

template<typename T>
Vector3<T> Vector3<T>::get_normalized()
{
	Vector3<T> r(x, y, z);
	r.normalize();
	return r;
}

template<typename T>
String Vector3<T>::to_string_degrees()
{
	String str = "[";
	str += degrees(x);
	str += ",";
	str += degrees(y);
	str += ",";
	str += degrees(z);
	str += "]";
	return str;
}

template<typename T>
void Vector3<T>::operator ()(const T x0, const T y0, const T z0)
{
	x = x0;
	y = y0;
	z = z0;
}

template<typename T> template<typename U>
void Vector3<T>::operator ()(const U* value)
{
	x = (T) value[0];
	y = (T) value[1];
	z = (T) value[2];
}

template<typename T>
float Vector3<T>::dot_product(Vector3<T> vec1)
{
	return (float) vec1.x * x + vec1.y * y + vec1.z * z;
}

// vector cross product
template<typename T>
Vector3<T> Vector3<T>::operator %(const Vector3<T> &v) const
{
	Vector3<T> temp(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return temp;
}

template<typename T> 	template<typename U>
void Vector3<T>::get_array(U* array)
{
	array[0] =(U) x;
	array[1] =(U) y;
	array[2] =(U) z;
}

template Quaternion Vector3<float>::euler_to_quaternion();
template float Vector3<float>::get_magnitude();
template void Vector3<float>::normalize();
template Vector3<float> Vector3<float>::get_normalized();
template void Vector3<float>::multiply(float mx, float my, float mz);
template String Vector3<float>::to_string();
template String Vector3<float>::to_string_degrees();
template void Vector3<float>::rotate(Quaternion *q);
template Vector3<float> Vector3<float>::get_rotated(Quaternion *q);
template void Vector3<float>::quaternion_to_euler(Quaternion &q);
template void Vector3<float>::quaternion_to_ypr(Quaternion &q);
template void Vector3<float>::quaternion_to_gravity(Quaternion &q);
template void Vector3<float>::get_array(float* array);
template float& Vector3<float>::operator[](uint8_t id);
template bool Vector3<float>::operator ==(const Vector3<float> &v) const;
template bool Vector3<float>::operator !=(const Vector3<float> &v) const;
template Vector3<float> Vector3<float>::operator -(void) const;
template Vector3<float> Vector3<float>::operator +(const Vector3<float> &v) const;
template Vector3<float> Vector3<float>::operator -(const Vector3<float> &v) const;
template Vector3<float> Vector3<int32_t>::operator -(const Vector3<float> &v) const;
template Vector3<int16_t> Vector3<float>::operator -(const Vector3<int16_t> &v) const;
template Vector3<float> Vector3<int16_t>::operator -(const Vector3<float> &v) const;
template Vector3<float> &Vector3<float>::operator =(Vector3<int16_t> v);
template Vector3<float> Vector3<float>::operator *(const float num) const;
template Vector3<float> Vector3<float>::operator *(Vector3<float> vec) const;
template Vector3<float> Vector3<float>::operator /(const float num) const;
template Vector3<float> &Vector3<float>::operator +=(const Vector3<float> &v);
template Vector3<float> &Vector3<float>::operator -=(const Vector3<float> &v);
template Vector3<float> &Vector3<float>::operator *=(const float num);
template Vector3<float> &Vector3<float>::operator *=(const Vector3<float> vec);
template Vector3<float> Vector3<float>::operator %(const Vector3<float> &v) const;
template Vector3<float> &Vector3<float>::operator /=(const float num);
template Vector3<float> &Vector3<float>::operator /=(const Vector3<float> &v);
template float Vector3<float>::dot_product(Vector3<float> vec1);
template void Vector3<float>::operator ()(const float x0, const float y0, const float z0);
template void Vector3<float>::operator ()(const int16_t* value);
template bool Vector3<float>::is_nan(void) const;
template bool Vector3<float>::is_inf(void) const;
template Vector3<float> Vector3<float>::rad_to_centi_deg();
template Vector3<float> Vector3<float>::to_centi_deg();
template void Vector3<float>::reset();
template float Vector3<float>::average();
template void Vector3<float>::get_array(long* array);


template void Vector3<int16_t>::operator ()(const int16_t* value);
template float Vector3<int16_t>::get_magnitude();
template void Vector3<int16_t>::normalize();
template Vector3<int16_t> Vector3<int16_t>::get_normalized();
template void Vector3<int16_t>::multiply(float mx, float my, float mz);
template String Vector3<int16_t>::to_string();
template String Vector3<int16_t>::to_string_degrees();
template void Vector3<int16_t>::rotate(Quaternion *q);
template Vector3<int16_t> Vector3<int16_t>::get_rotated(Quaternion *q);
template void Vector3<int16_t>::quaternion_to_euler(Quaternion &q);
template void Vector3<int16_t>::get_array(int16_t* array);
template int16_t& Vector3<int16_t>::operator[](uint8_t id);
template bool Vector3<int16_t>::operator ==(const Vector3<int16_t> &v) const;
template bool Vector3<int16_t>::operator !=(const Vector3<int16_t> &v) const;
template Vector3<int16_t> Vector3<int16_t>::operator -(void) const;
template Vector3<int16_t> Vector3<int16_t>::operator +(const Vector3<int16_t> &v) const;
template Vector3<int16_t> Vector3<int16_t>::operator -(const Vector3<int16_t> &v) const;
template Vector3<int16_t> Vector3<int16_t>::operator *(const int16_t num) const;
template Vector3<int16_t> Vector3<int16_t>::operator *(Vector3<int16_t> vec) const;
template Vector3<int16_t> Vector3<int16_t>::operator /(const int16_t num) const;
template Vector3<int16_t> &Vector3<int16_t>::operator +=(const Vector3<int16_t> &v);
template Vector3<int16_t> &Vector3<int16_t>::operator -=(const Vector3<int16_t> &v);
template Vector3<int16_t> &Vector3<int16_t>::operator *=(const int16_t num);
template Vector3<int16_t> &Vector3<int16_t>::operator /=(const int16_t num);
template void Vector3<int16_t>::operator ()(const int16_t x0, const int16_t y0, const int16_t z0);
template bool Vector3<int16_t>::is_nan(void) const;
template bool Vector3<int16_t>::is_inf(void) const;

template String Vector3<int32_t>::to_string();

template Vector3<int32_t> Vector3<int32_t>::operator +(const Vector3<int32_t> &v) const;
template float Vector3<int32_t>::average();
template void Vector3<int32_t>::get_array(int32_t* array);
template Vector3<int32_t> Vector3<int16_t>::operator -(const Vector3<int32_t> &v) const;
template Vector3<float> &Vector3<float>::operator =(Vector3<int32_t> v);
template void Vector3<int32_t>::operator ()(const int32_t x0, const int32_t y0, const int32_t z0);
template Vector3<int32_t> Vector3<int32_t>::operator /(const int32_t num) const;
template Vector3<int32_t> &Vector3<int32_t>::operator /=(const int32_t num);

