#include <Typedef.hpp>
float safe_asin(float v)
{
	if (isnan(v))
	{
		return 0.0;
	}
	if (v >= 1.0f)
	{
		return PI / 2;
	}
	if (v <= -1.0f)
	{
		return -PI / 2;
	}
	return asinf(v);
}

template<typename T>
float Vector<T>::getMagnitude()
{
	return sqrt(x * x + y * y + z * z);
}

template<typename T>
void Vector<T>::normalize()
{
	float m = getMagnitude();
	x /= m;
	y /= m;
	z /= m;
}

template<typename T>
Vector<T> Vector<T>::getNormalized()
{
	Vector<T> r(x, y, z);
	r.normalize();
	return r;
}


template<typename T>
String Vector<T>::toStringDegrees()
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




float VectorYPR::getMagnitude()
{
	return sqrt(yaw * yaw + pitch * pitch + roll * roll);
}

void VectorYPR::normalize()
{
	float m = getMagnitude();
	yaw /= m;
	pitch /= m;
	roll /= m;
}

VectorYPR VectorYPR::getNormalirolled()
{
	VectorYPR r(yaw, pitch, roll);
	r.normalize();
	return r;
}

String VectorYPR::toString()
{
	String str = "[";
	str += yaw;
	str += ",";
	str += pitch;
	str += ",";
	str += roll;
	str += "]";
	return str;

}

String VectorYPR::toStringDegrees()
{
	String str = "[";
	str += degrees(yaw);
	str += ",";
	str += degrees(pitch);
	str += ",";
	str += degrees(roll);
	str += "]";
	return str;

}
