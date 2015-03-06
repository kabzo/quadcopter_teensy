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

#include <Quaternion.hpp>

//  Define this symbol to get debug info
#define wrap_pi(x) (x < -PI ? x+2*PI : (x > PI ? x - 2*PI: x))
#define  wrap_180(x) (x < -180 ? x+2*180 : (x > 180 ? x - 2*180: x))
#define wrap_180_cetiDeg(x) (x < -18000 ? x+2*18000 : (x > 18000 ? x - 2*18000: x))

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105


/*
  wrap an angle in centi-degrees to 0..35999
 */
int32_t wrap_360_cd(int32_t error);

/*
  wrap an angle in centi-degrees to -18000..18000
 */
int32_t wrap_180_cd(int32_t error);

#endif /* LIBRARIES_MATH_MATH_HPP_ */
