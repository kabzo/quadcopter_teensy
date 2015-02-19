/*
 * Math.hpp
 *
 *  Created on: 19.2.2015
 *      Author: Juraj
 */

#ifndef LIBRARIES_MATH_MATH_HPP_
#define LIBRARIES_MATH_MATH_HPP_

#include <math.h>

#ifndef MATRIX3_HPP
#include <Matrix3.hpp>
#endif

//  Define this symbol to get debug info
#define wrap_180(x) (x < -PI ? x+2*PI : (x > PI ? x - 2*PI: x))

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105


#endif /* LIBRARIES_MATH_MATH_HPP_ */
