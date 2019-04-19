/** \file */

#ifndef __BML_GETTERS_ELLBLOCK_H
#define __BML_GETTERS_ELLBLOCK_H

#include "bml_types_ellblock.h"

#include <complex.h>

void *bml_get_ellblock(
    const bml_matrix_ellblock_t * A,
    const int i,
    const int j);

float *bml_get_ellblock_single_real(
    const bml_matrix_ellblock_t * A,
    const int i,
    const int j);

double *bml_get_ellblock_double_real(
    const bml_matrix_ellblock_t * A,
    const int i,
    const int j);

float complex *bml_get_ellblock_single_complex(
    const bml_matrix_ellblock_t * A,
    const int i,
    const int j);

double complex *bml_get_ellblock_double_complex(
    const bml_matrix_ellblock_t * A,
    const int i,
    const int j);

void *bml_get_row_ellblock(
    bml_matrix_ellblock_t * A,
    const int i);

void *bml_get_row_ellblock_single_real(
    bml_matrix_ellblock_t * A,
    const int i);

void *bml_get_row_ellblock_double_real(
    bml_matrix_ellblock_t * A,
    const int i);

void *bml_get_row_ellblock_single_complex(
    bml_matrix_ellblock_t * A,
    const int i);

void *bml_get_row_ellblock_double_complex(
    bml_matrix_ellblock_t * A,
    const int i);

void *bml_get_diagonal_ellblock(
    bml_matrix_ellblock_t * A);

void *bml_get_diagonal_ellblock_single_real(
    bml_matrix_ellblock_t * A);

void *bml_get_diagonal_ellblock_double_real(
    bml_matrix_ellblock_t * A);

void *bml_get_diagonal_ellblock_single_complex(
    bml_matrix_ellblock_t * A);

void *bml_get_diagonal_ellblock_double_complex(
    bml_matrix_ellblock_t * A);

#endif
