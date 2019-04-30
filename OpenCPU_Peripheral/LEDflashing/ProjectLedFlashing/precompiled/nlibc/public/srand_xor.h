#ifndef SRAND_XOR_H_
#define SRAND_XOR_H_

/** @defgroup NLIBC_SRAND_XOR nlibc Srand XOR
 * nlibc Srand XOR
 * @ingroup NLIBC
 * @{
 * */

/** A non-standard addition to the RNG, which just XORs the existing seed with the given value */
void srand_xor(unsigned int value);

/** @} end of group NLIBC_SRAND_XOR */

#endif

