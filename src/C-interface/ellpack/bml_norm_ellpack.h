#ifndef __BML_NORM_ELLPACK_H
#define __BML_NORM_ELLPACK_H

#include "bml_types_ellpack.h"

double bml_sum_squares_ellpack(
    const bml_matrix_ellpack_t * A);

double bml_sum_squares_ellpack_single_real(
    const bml_matrix_ellpack_t * A);

double bml_sum_squares_ellpack_double_real(
    const bml_matrix_ellpack_t * A);

double bml_sum_squares_ellpack_single_complex(
    const bml_matrix_ellpack_t * A);

double bml_sum_squares_ellpack_double_complex(
    const bml_matrix_ellpack_t * A);

double bml_sum_squares2_ellpack(
    const bml_matrix_ellpack_t * A,
    const bml_matrix_ellpack_t * B,
    const double alpha,
    const double beta);

double bml_sum_squares2_ellpack_single_real(
    const bml_matrix_ellpack_t * A,
    const bml_matrix_ellpack_t * B,
    const double alpha,
    const double beta);

double bml_sum_squares2_ellpack_double_real(
    const bml_matrix_ellpack_t * A,
    const bml_matrix_ellpack_t * B,
    const double alpha,
    const double beta);

double bml_sum_squares2_ellpack_single_complex(
    const bml_matrix_ellpack_t * A,
    const bml_matrix_ellpack_t * B,
    const double alpha,
    const double beta);

double bml_sum_squares2_ellpack_double_complex(
    const bml_matrix_ellpack_t * A,
    const bml_matrix_ellpack_t * B,
    const double alpha,
    const double beta);

double bml_fnorm_ellpack(
    const bml_matrix_ellpack_t * A);

double bml_fnorm_ellpack_single_real(
    const bml_matrix_ellpack_t * A);

double bml_fnorm_ellpack_double_real(
    const bml_matrix_ellpack_t * A);

double bml_fnorm_ellpack_single_complex(
    const bml_matrix_ellpack_t * A);

double bml_fnorm_ellpack_double_complex(
    const bml_matrix_ellpack_t * A);

#endif