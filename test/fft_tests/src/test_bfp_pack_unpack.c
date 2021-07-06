// Copyright 2020-2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.



#include "bfp_math.h"
#include "testing.h"
#include "tst_common.h"
#include "unity.h"

#include <string.h>


#define FFT_N   (512)
#define REPS    (30)

static void test_bfp_fft_mono_unpack_pack()
{
#if PRINT_FUNC_NAMES
    printf("%s..\n", __func__);
#endif

  unsigned seed = 2343454;

  complex_s32_t buffer[FFT_N/2+1];
  complex_s32_t buffer2[FFT_N/2];

  bfp_complex_s32_t X;
  X.data = buffer;
  X.length = FFT_N/2;
  X.exp = 0;
  X.hr = 0;

  for(int rep = 0; rep < REPS; rep++){

    for(int k = 0; k < X.length; k++){
      X.data[k].re = pseudo_rand_int32(&seed);
      X.data[k].im = pseudo_rand_int32(&seed);
    }

    memcpy(buffer2, buffer, sizeof(buffer2));

    bfp_fft_unpack_mono(&X);

    TEST_ASSERT_EQUAL(0, X.data[0].im);
    TEST_ASSERT_EQUAL(0, X.data[FFT_N/2].im);
    TEST_ASSERT_EQUAL(buffer2[0].re, X.data[0].re);
    TEST_ASSERT_EQUAL(buffer2[0].im, X.data[FFT_N/2].re);
    TEST_ASSERT_FALSE( memcmp(&buffer2[1], &buffer[1], (FFT_N/2)-1 * sizeof(complex_s32_t)) );
    TEST_ASSERT_EQUAL(FFT_N/2 + 1, X.length);

    bfp_fft_pack_mono(&X);

    TEST_ASSERT_EQUAL(FFT_N/2, X.length);
    TEST_ASSERT_FALSE( memcmp(&buffer2[0], &buffer[0], (FFT_N/2) * sizeof(complex_s32_t)) );

  }
}


static void test_bfp_fft_stereo_unpack_pack()
{
#if PRINT_FUNC_NAMES
    printf("%s..\n", __func__);
#endif

  unsigned seed = 677856;

  ch_pair_s32_t DWORD_ALIGNED buffAB[FFT_N + 2];
  complex_s32_t DWORD_ALIGNED orig_specA[FFT_N/2], DWORD_ALIGNED orig_specB[FFT_N/2];

  bfp_ch_pair_s32_t ab;

  bfp_ch_pair_s32_init(&ab, buffAB, 0, FFT_N, 0);

  for(int rep = 0; rep < REPS; rep++){

    for(int k = 0; k < ab.length; k++){
      ab.data[k].ch_a = pseudo_rand_int32(&seed);
      ab.data[k].ch_b = pseudo_rand_int32(&seed);
    }

    bfp_ch_pair_s32_headroom(&ab);

    bfp_complex_s32_t ChA, ChB;

    bfp_fft_forward_stereo(&ChA, &ChB, &ab);

    // Copy the original spectra over
    memcpy(orig_specA, &ChA.data[0], sizeof(orig_specA));
    memcpy(orig_specB, &ChB.data[0], sizeof(orig_specB));

    // Unpack spectra
    bfp_fft_unpack_stereo(&ChA, &ChB);

    // Check that everything is right

    TEST_ASSERT_EQUAL(FFT_N/2 + 1, ChA.length);
    TEST_ASSERT_EQUAL(0, ChA.data[0].im);
    TEST_ASSERT_EQUAL(0, ChA.data[FFT_N/2].im);
    TEST_ASSERT_EQUAL(orig_specA[0].re, ChA.data[0].re);
    TEST_ASSERT_EQUAL(orig_specA[0].im, ChA.data[FFT_N/2].re);
    TEST_ASSERT_FALSE( memcmp(&orig_specA[1], &ChA.data[1], FFT_N/2-1 * sizeof(complex_s32_t)) );

    TEST_ASSERT_EQUAL(FFT_N/2 + 1, ChB.length);
    TEST_ASSERT_EQUAL(0, ChB.data[0].im);
    TEST_ASSERT_EQUAL(0, ChB.data[FFT_N/2].im);
    TEST_ASSERT_EQUAL(orig_specB[0].re, ChB.data[0].re);
    TEST_ASSERT_EQUAL(orig_specB[0].im, ChB.data[FFT_N/2].re);
    TEST_ASSERT_FALSE( memcmp(&orig_specB[1], &ChB.data[1], FFT_N/2-1 * sizeof(complex_s32_t)) );

    // Re-pack spectra
    bfp_fft_pack_stereo(&ChA, &ChB);

    // Make sure everything is right again
    TEST_ASSERT_EQUAL(FFT_N/2, ChA.length);
    TEST_ASSERT_FALSE( memcmp(&orig_specA[0], &ChA.data[0], (FFT_N/2) * sizeof(complex_s32_t)) );
    
    TEST_ASSERT_EQUAL(FFT_N/2, ChB.length);
    TEST_ASSERT_FALSE( memcmp(&orig_specB[0], &ChB.data[0], (FFT_N/2) * sizeof(complex_s32_t)) );

  }
}



void test_bfp_fft_pack_unpack()
{
    SET_TEST_FILE();

    RUN_TEST(test_bfp_fft_mono_unpack_pack);
    RUN_TEST(test_bfp_fft_stereo_unpack_pack);

}