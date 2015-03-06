/*
 * Math.cpp
 *
 *  Created on: 6.3.2015
 *      Author: Juraj
 */
#include <Math.hpp>



/*
  wrap an angle in centi-degrees to 0..35999
 */
int32_t wrap_360_cd(int32_t error)
{
    if (error > 360000 || error < -360000) {
        // for very large numbers use modulus
        error = error % 36000;
    }
    while (error >= 36000) error -= 36000;
    while (error < 0) error += 36000;
    return error;
}

/*
  wrap an angle in centi-degrees to -18000..18000
 */
int32_t wrap_180_cd(int32_t error)
{
    if (error > 360000 || error < -360000) {
        // for very large numbers use modulus
        error = error % 36000;
    }
    while (error > 18000) { error -= 36000; }
    while (error < -18000) { error += 36000; }
    return error;
}
