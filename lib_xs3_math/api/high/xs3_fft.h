

#ifndef XS3_FFT_H_
#define XS3_FFT_H_

#include "xs3_math_types.h"

#ifdef __XC__
extern "C" {
#endif


#define SIN_TABLE(N)    (NULL) //TODO

/** Perform a forward FFT on a BFP vector of samples.
 * 
 * ``samples->length`` must be a power of 2.
 * 
 * The FFT is performed in-place on the input BFP vector, and the result is passed back
 * to the user in the returned pointer, which uses the same data buffer as the input
 * argument. Therefore, the input vector no longer contains time-domain data, and should
 * not be used to access the underlying data.
 * 
 * The complex result will have a length of ``samples->length / 2``, reflecting that only
 * half of the symmetric complex spectrum is available.
 * 
 * The exponent and headroom of the resulting complex BFP vector will both be updated to
 * reflect the effect of the FFT on the magnitude and headroom of the underlying sample
 * data.
 * 
 * \note    The imaginary part of the Nyquist rate will be packed into the imaginary part
 *          of vector element 0 of the result.
 * 
 * \param samples   Vector of time-domain samples to be transformed.
 * \param sin_table sine table for N-point FFT
 * 
 * \returns         Complex spectrum of ``samples``
 */
bfp_complex_s32_t* bfp_fft_forward( bfp_s32_t* samples, int32_t* sin_table);




/** Perform an inverse FFT on a BFP vector containing a complex spectrum.
 * 
 * ``spectrum->length`` must be a power of 2.
 * 
 * The IFFT is performed in-place on the input complex BFP vector, and the result is passed
 * back to the user in the returned pointer, which uses the same data buffer as the input
 * argument. Therefore, the input vector no longer contains frequency-domain data, and should
 * not be used toa ccess the underlying data.
 * 
 * The time-domain result will have a length of ``spectrum->length * 2``, reflecting that
 * the input is assumed to be only half the symmetric complex spectrum (e.g. that given
 * by ``bfp_fft_forward``).
 * 
 * The exponent and headroom of the resulting BFP vector will both be updated to reflect 
 * the effect of the IFFT on the magnitude and headroom of the underlying data.
 * 
 * \note    The imaginary part of the Nyquist rate must be packed into the imaginary
 *          part of vector element 0.
 * 
 * \param spectrum  Vector of  
 * \param sin_table Sine table for N-point FFT
 */
bfp_s32_t* bfp_fft_inverse( bfp_complex_s32_t* spectrum, int32_t* sin_table );



/** Perform a complex FFT
 * 
 */
void bfp_complex_fft_forward( 
    bfp_complex_s32_t* a, 
    bfp_complex_s32_t* b);

/** Perform a complex IFFT
 * 
 */
void bfp_complex_fft_inverse(
    bfp_complex_s32_t* a,
    bfp_complex_s32_t* b);

/** Perform FFTs on a pair of real signals
 * 
 */
void bfp_dual_fft_forward( 
    bfp_complex_s32_t* a,
    bfp_complex_s32_t* b,
    bfp_ch_pair_s32_t* c);

/** Perform an IFFT to yield a pair of real signals
 * 
 */
void bfp_dual_fft_inverse(
    bfp_ch_pair_s32_t* a,
    bfp_complex_s32_t* b,
    bfp_complex_s32_t* c);


#ifdef __XC__
}   //extern "C"
#endif

#endif //XS3_FFT_H_