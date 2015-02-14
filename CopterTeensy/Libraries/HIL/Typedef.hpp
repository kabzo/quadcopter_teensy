#ifndef TYPEDEF_HPP_
#define TYPEDEF_HPP_

#include <math.h>
#include <stdint.h>
#include<Arduino.h>
#include <arm_math.h>

#define DEBUG2(X,Y) Serial.print(X);Serial.print(":"); Serial.print(Y);Serial.print(",")
#define DEBUGLN2(X,Y) Serial.print(X);Serial.print(":"); Serial.println(Y)
#define DEBUGLN3(X,Y,Z) Serial.print(X);Serial.print(","); Serial.print(Y);Serial.print(",");Serial.println(Z)
#define DEBUGLN1(X) Serial.println(X)
#define DEBUG1(X) Serial.print(X);Serial.print(",")

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define toRad(deg) ((deg)*DEG_TO_RAD)
#define toDeg(rad) ((rad)*RAD_TO_DEG)
#define radToCentiDeg(rad) ((rad)*RAD_TO_DEG*100)
#define toCentiDeg(deg) deg*100

float safe_asin(float v);

// read something the size of a byte, far version
static inline uint8_t pgm_read_one_byte(const void *s)
{
	return *(const uint8_t *) s;
}

// read something the size of a word
static inline uint16_t pgm_read_short_word(const void *s)
{
	return *(const uint16_t *) s;
}

// read something the size of a dword
static inline uint32_t pgm_read_long_word(const void *s)
{
	return *(const uint32_t *) s;
}

static inline float pgm_read_fl(const void *s)
{
	return *(const float *) s;
}

// read something the size of a pointer. This makes the menu code more
// portable
static inline uintptr_t pgm_read_pointer(const void *s)
{
	return *(const uintptr_t *) s;
}

#define PGM_UINT8(addr) pgm_read_one_byte((const prog_char *)addr)
#define PGM_UINT16(addr) pgm_read_short_word((const uint16_t *)addr)
#define PGM_FLOAT(addr) pgm_read_fl((const float *)addr)
#define PGM_POINTER(addr) pgm_read_pointer((const void *)addr)

typedef char prog_char;

class VectorYPR
{
public:
	float yaw;
	float pitch;
	float roll;

	VectorYPR()
	{
		yaw = 0;
		pitch = 0;
		roll = 0;
	}

	VectorYPR(float Yaw, float Pitch, float Roll)
	{
		yaw = Yaw;
		pitch = Pitch;
		roll = Roll;
	}

	float getMagnitude();

	void normalize();

	VectorYPR getNormalirolled();

	template<typename U>
	void setVector(U* value)
	{
		yaw = (float) value[0];
		pitch = (float) value[1];
		roll = (float) value[2];
	}

	String toString();
	String toStringDegrees();
};

class Quaternion
{
public:
	float w; //q0
	float x; //q1
	float y; //q2
	float z; //q3

	Quaternion()
	{
		w = 1.0f;
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Quaternion(float nw, float nx, float ny, float nz)
	{
		w = nw;
		x = nx;
		y = ny;
		z = nz;
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

	VectorYPR getEuler()
	{
		VectorYPR r(0, 0, 0);
//		float pole = M_PI / 2.0f - 0.05f;                           // fix roll near poles with this tolerance
		r.roll = atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y));														//roll
		r.pitch = asin(2.0f * (w * y - z * x)); //pitch
		r.yaw = atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (z * z + y * y));

//		if ((r.pitch < pole) && (r.pitch > -pole))														//yaw
//			r.yaw = atan2(2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));

		return r;

	}

};

template<typename T>
class Vector
{
public:
	T x;
	T y;
	T z;

	Vector<T>()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector(T nx, T ny, T nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}

	float getMagnitude();
	void normalize();
	Vector<T> getNormalized();

	void change(float X, float Y, float Z)
	{
		x = (T) X;
		y = (T) Y;
		z = (T) Z;
	}

	template<typename U>
	void multiply(Vector<U> vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;

	}

	void multiply(float mult)
	{
		x *= mult;
		y *= mult;
		z *= mult;
	}

	void multiply(float mx, float my, float mz)
	{
		x *= mx;
		y *= my;
		z *= mz;
	}

	String toString()
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
	String toStringDegrees();

	template<typename U>
	void setVector(U* value)
	{
		x = (float) value[0];
		y = (float) value[1];
		z = (float) value[2];
	}

	void getArray(T* array)
	{
		array[0] = x;
		array[1] = y;
		array[2] = z;
	}

	float average()
	{
		float avg = x + y + z;
		avg /= 3;
		return avg;
	}

	void rotate(Quaternion *q)
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

	Vector<T> getRotated(Quaternion *q)
	{
		Vector<T> r(x, y, z);
		r.rotate(q);
		return r;
	}
};

typedef Vector<int16_t> VectorInt16;
typedef Vector<int32_t> VectorInt32;
typedef Vector<float> VectorFloat;

class Timer
{
public:
	Timer()
	{

	}

	void start()
	{
		actualTime = micros();
	}

	float stopDiff()
	{
		stopTime = micros();
		differenz = stopTime - actualTime;
		return differenz / 1000;
	}

	float diff()
	{
		uint32_t now = micros();
		differenz = now - actualTime;
		return differenz / 1000;
	}

	void printDiff()
	{
		Serial.println(diff());
	}

private:
	uint32_t actualTime;
	uint32_t stopTime;
	float differenz;
};

#endif /* TYPEDEF_HPP_ */
