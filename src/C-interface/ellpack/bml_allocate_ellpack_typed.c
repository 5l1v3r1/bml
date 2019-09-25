#include "../../macros.h"
#include "../../typed.h"
#include "bml_allocate.h"
#include "bml_allocate_ellpack.h"
#include "bml_types.h"
#include "bml_types_ellpack.h"

#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _OPENMP
#include <omp.h>
#endif

//#define NOGPU

/** Clear a matrix.
 *
 * Numbers of non-zeroes, indeces, and values are set to zero.
 *
 * \ingroup allocate_group
 *
 * \param A The matrix.
 */
void TYPED_FUNC(
    bml_clear_ellpack) (
    bml_matrix_ellpack_t * A)
{
    int N = A->N;
    int M = A->M;
    int *A_index = A->index;
    int *A_nnz = A->nnz;
    REAL_T *A_value = A->value;

#ifdef NOGPU
#pragma omp target update from(A_value[:N*M], A_index[:N*M], A_nnz[:N])

    memset(A->nnz, 0, A->N * sizeof(int));
    memset(A->index, 0, A->N * A->M * sizeof(int));
    memset(A->value, 0.0, A->N * A->M * sizeof(REAL_T));

#pragma omp target update to(A_value[:N*M], A_index[:N*M], A_nnz[:N])
#else
    // All data and copy stays on deveice
#pragma omp target teams distribute parallel for 
    for (int i = 0; i < N; i++)
        {
             A_nnz[i] = 0;
        }

#pragma omp target teams distribute parallel for collapse(2) schedule (static, 1)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            A_index[ROWMAJOR(i,j,N,M)] = 0;
            A_value[ROWMAJOR(i,j,N,M)] = 0.0;
        }
    }

#endif
}

/** Allocate a matrix with uninitialized values.
 *
 *  Note that the matrix \f$ a \f$ will be newly allocated. If it is
 *  already allocated then the matrix will be deallocated in the
 *  process.
 *
 *  \ingroup allocate_group
 *
 *  \param matrix_precision The precision of the matrix. The default
 *  is double precision.
 *  \param matrix_dimension The matrix size.
 *  \param distrib_mode The distribution mode.
 *  \return The matrix.
 */
bml_matrix_ellpack_t *TYPED_FUNC(
    bml_noinit_matrix_ellpack) (
    const bml_matrix_dimension_t matrix_dimension,
    const bml_distribution_mode_t distrib_mode)
{
    bml_matrix_ellpack_t *A =
        bml_noinit_allocate_memory(sizeof(bml_matrix_ellpack_t));
    A->matrix_type = ellpack;
    A->matrix_precision = MATRIX_PRECISION;
    A->N = matrix_dimension.N_rows;
    A->M = matrix_dimension.N_nz_max;
    A->distribution_mode = distrib_mode;
    // need to keep these allocates for host copy
    A->index = bml_noinit_allocate_memory(sizeof(int) * A->N * A->M);
    A->nnz = bml_allocate_memory(sizeof(int) * A->N);
    A->value = bml_noinit_allocate_memory(sizeof(REAL_T) * A->N * A->M);
    A->domain = bml_default_domain(A->N, A->M, distrib_mode);
    A->domain2 = bml_default_domain(A->N, A->M, distrib_mode);

    int N = A->N;
    int M = A->M;
    int *A_index = A->index;
    int *A_nnz = A->nnz;
    REAL_T *A_value = A->value;

#pragma omp target enter data map(alloc:A_value[:N*M], A_index[:N*M], A_nnz[:N])
#pragma omp target update to(A_value[:N*M], A_index[:N*M], A_nnz[:N])

    return A;
}

/** Allocate the zero matrix.
 *
 *  Note that the matrix \f$ a \f$ will be newly allocated. If it is
 *  already allocated then the matrix will be deallocated in the
 *  process.
 *
 *  \ingroup allocate_group
 *
 *  \param matrix_precision The precision of the matrix. The default
 *  is double precision.
 *  \param N The matrix size.
 *  \param M The number of non-zeroes per row.
 *  \param distrib_mode The distribution mode.
 *  \return The matrix.
 */
bml_matrix_ellpack_t *TYPED_FUNC(
    bml_zero_matrix_ellpack) (
    const int N,
    const int M,
    const bml_distribution_mode_t distrib_mode)
{
    bml_matrix_ellpack_t *A =
        bml_allocate_memory(sizeof(bml_matrix_ellpack_t));
    A->matrix_type = ellpack;
    A->matrix_precision = MATRIX_PRECISION;
    A->N = N;
    A->M = M;
    A->distribution_mode = distrib_mode;
    // need to keep these allocates for host copy
    A->nnz = bml_allocate_memory(sizeof(int) * N);
    A->index = bml_allocate_memory(sizeof(int) * N * M);
    A->value = bml_allocate_memory(sizeof(REAL_T) * N * M);

    A->domain = bml_default_domain(N, M, distrib_mode);
    A->domain2 = bml_default_domain(N, M, distrib_mode);

    int *A_nnz = A->nnz;
    int *A_index = A->index;
    REAL_T *A_value = A->value;
    int NM = N*M;

    printf("Allocating device memory in bml_zero_matrix\n");
    printf("N = %d, M = %d\n", N, M);

#pragma omp target enter data map(alloc:A_nnz[0:N]) 
#pragma omp target enter data map(alloc:A_index[0:NM]) 
#pragma omp target enter data map(alloc:A_value[0:NM]) 

    printf("Device memory allocated\n");

    // All arrays set on device
#ifdef NOGPU
#pragma omp parallel for 
#else
#pragma omp target teams distribute parallel for schedule (static, 1)
#endif
    for (int i = 0; i < N; i++)
        {
             A_nnz[i] = 0;
        }

#ifdef NOGPU
#pragma omp parallel for 
#else
#pragma omp target teams distribute parallel for collapse(2) schedule (static, 1)
#endif
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            A_index[ROWMAJOR(i,j,N,M)] = 0;
            A_value[ROWMAJOR(i,j,N,M)] = 0.0;
        }
    }
#ifdef NOGPU
#pragma omp target update to(A_value[:N*M], A_index[:N*M], A_nnz[:N])
#endif
    return A;
}

/** Allocate a banded random matrix.
 *
 *  Note that the matrix \f$ a \f$ will be newly allocated. If it is
 *  already allocated then the matrix will be deallocated in the
 *  process.
 *
 *  \ingroup allocate_group
 *
 *  \param matrix_precision The precision of the matrix. The default
 *  is double precision.
 *  \param N The matrix size.
 *  \param M The number of non-zeroes per row.
 *  \param distrib_mode The distribution mode.
 *  \return The matrix.
 */
bml_matrix_ellpack_t *TYPED_FUNC(
    bml_banded_matrix_ellpack) (
    const int N,
    const int M,
    const bml_distribution_mode_t distrib_mode)
{
    bml_matrix_ellpack_t *A =
        TYPED_FUNC(bml_zero_matrix_ellpack) (N, M, distrib_mode);

    REAL_T *A_value = A->value;
    int *A_index = A->index;
    int *A_nnz = A->nnz;

#pragma omp target enter data map(alloc:A_value[0:N*M], A_index[0:N*M], A_nnz[0:N])
#pragma omp parallel for default(none) shared(A_value, A_index, A_nnz, N, M)
    for (int i = 0; i < N; i++)
    {
        int jind = 0;
        for (int j = (i - M / 2 >= 0 ? i - M / 2 : 0);
             j < (i - M / 2 + M <= N ? i - M / 2 + M : N); j++)
        {
            A_value[ROWMAJOR(i, jind, N, M)] = rand() / (REAL_T) RAND_MAX;
            A_index[ROWMAJOR(i, jind, N, M)] = j;
            jind++;
        }
        A_nnz[i] = jind;
    }
#pragma omp target update to(A_value[:N*M], A_index[:N*M], A_nnz[:N])

    return A;
}

/** Allocate a random matrix.
 *
 *  Note that the matrix \f$ a \f$ will be newly allocated. If it is
 *  already allocated then the matrix will be deallocated in the
 *  process.
 *
 *  \ingroup allocate_group
 *
 *  \param matrix_precision The precision of the matrix. The default
 *  is double precision.
 *  \param N The matrix size.
 *  \param M The number of non-zeroes per row.
 *  \param distrib_mode The distribution mode.
 *  \return The matrix.
 *
 *  Note: Do not use OpenMP when setting values for a random matrix,
 *  this makes the operation non-repeatable.
 */
bml_matrix_ellpack_t *TYPED_FUNC(
    bml_random_matrix_ellpack) (
    const int N,
    const int M,
    const bml_distribution_mode_t distrib_mode)
{
    // Note this allocates space on the device already!
    bml_matrix_ellpack_t *A =
        TYPED_FUNC(bml_zero_matrix_ellpack) (N, M, distrib_mode);

    REAL_T *A_value = A->value;
    int *A_index = A->index;
    int *A_nnz = A->nnz;

//#pragma omp target enter data map(alloc:A_value[:N*M], A_index[:N*M], A_nnz[:N])
#pragma omp target update from(A_value[:N*M], A_index[:N*M], A_nnz[:N])

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        int jind = 0;
        for (int j = 0; j < M; j++)
        {
            A_value[ROWMAJOR(i, jind, N, M)] = rand() / (REAL_T) RAND_MAX;
            A_index[ROWMAJOR(i, jind, N, M)] = j;
            jind++;
        }
        A_nnz[i] = jind;
    }
#pragma omp target update to(A_value[:N*M], A_index[:N*M], A_nnz[:N])

    return A;
}

/** Allocate the identity matrix.
 *
 *  Note that the matrix \f$ a \f$ will be newly allocated. If it is
 *  already allocated then the matrix will be deallocated in the
 *  process.
 *
 *  \ingroup allocate_group
 *
 *  \param matrix_precision The precision of the matrix. The default
 *  is double precision.
 *  \param N The matrix size.
 *  \param M The number of non-zeroes per row.
 *  \param distrib_mode The distribution mode.
 *  \return The matrix.
 */
bml_matrix_ellpack_t *TYPED_FUNC(
    bml_identity_matrix_ellpack) (
    const int N,
    const int M,
    const bml_distribution_mode_t distrib_mode)
{
    // this allocates space on the gpu already
    bml_matrix_ellpack_t *A =
        TYPED_FUNC(bml_zero_matrix_ellpack) (N, M, distrib_mode);

    REAL_T *A_value = A->value;
    int *A_index = A->index;
    int *A_nnz = A->nnz;

#pragma omp \
    parallel for default(none) shared(A_value, A_index, A_nnz, N, M)
    for (int i = 0; i < N; i++)
    {
        A_value[ROWMAJOR(i, 0, N, M)] = (REAL_T) 1.0;
        A_index[ROWMAJOR(i, 0, N, M)] = i;
        A_nnz[i] = 1;
    }
#pragma omp target update to(A_value[:N*M], A_index[:N*M], A_nnz[:N])

    return A;
}
