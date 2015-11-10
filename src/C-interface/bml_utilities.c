#include "bml_introspection.h"
#include "bml_logger.h"
#include "bml_types.h"
#include "bml_utilities.h"
#include "dense/bml_utilities_dense.h"

#include <complex.h>
#include <stdio.h>

/** Print a bml vector.
 *
 * \param N The number of rows/columns.
 * \param matrix_precision The real precision.
 * \param v The vector.
 * \param i_l The lower row index.
 * \param i_u The upper row index.
 */
void
bml_print_bml_vector(
    const bml_vector_t * v,
    const int i_l,
    const int i_u)
{
    LOG_ERROR("[FIXME]\n");
}

/** Print a dense matrix.
 *
 * \param N The number of rows/columns.
 * \param matrix_precision The real precision.
 * \param A The matrix.
 * \param i_l The lower row index.
 * \param i_u The upper row index.
 * \param j_l The lower column index.
 * \param j_u The upper column index.
 */
void
bml_print_bml_matrix(
    const bml_matrix_t * A,
    const int i_l,
    const int i_u,
    const int j_l,
    const int j_u)
{
    switch (bml_get_type(A))
    {
        case dense:
            bml_print_bml_matrix_dense(A, i_l, i_u, j_l, j_u);
            break;
        default:
            LOG_ERROR("unknown type (%d)\n", bml_get_type(A));
            break;
    }
}

/** Print a dense matrix.
 *
 * \param N The number of rows/columns.
 * \param matrix_precision The real precision.
 * \param A The matrix.
 * \param i_l The lower row index.
 * \param i_u The upper row index.
 * \param j_l The lower column index.
 * \param j_u The upper column index.
 */
void
bml_print_dense_matrix(
    const int N,
    bml_matrix_precision_t matrix_precision,
    const void *A,
    const int i_l,
    const int i_u,
    const int j_l,
    const int j_u)
{
    LOG_DEBUG("printing matrix [%d:%d][%d:%d]\n", i_l, i_u, j_l, j_u);
    switch (matrix_precision)
    {
        case single_real:
        {
            const float *A_typed = A;
            for (int i = i_l; i < i_u; i++)
            {
                for (int j = j_l; j < j_u; j++)
                {
                    printf(" % 1.3f", A_typed[i + j * N]);
                }
                printf("\n");
            }
            break;
        }
        case double_real:
        {
            const double *A_typed = A;
            for (int i = i_l; i < i_u; i++)
            {
                for (int j = j_l; j < j_u; j++)
                {
                    printf(" % 1.3f", A_typed[i + j * N]);
                }
                printf("\n");
            }
            break;
        }
        case single_complex:
        {
            const float complex *A_typed = A;
            for (int i = i_l; i < i_u; i++)
            {
                for (int j = j_l; j < j_u; j++)
                {
                    printf(" % 1.3f%+1.3fi", creal(A_typed[i + j * N]),
                           cimag(A_typed[i + j * N]));
                }
                printf("\n");
            }
            break;
        }
        case double_complex:
        {
            const double complex *A_typed = A;
            for (int i = i_l; i < i_u; i++)
            {
                for (int j = j_l; j < j_u; j++)
                {
                    printf(" % 1.3f%+1.3fi", creal(A_typed[i + j * N]),
                           cimag(A_typed[i + j * N]));
                }
                printf("\n");
            }
            break;
        }
        default:
            LOG_ERROR("unknown matrix precision");
            break;
    }
}

/** Print a dense vector.
 *
 * \param N The number of rows/columns.
 * \param matrix_precision The real precision.
 * \param v The vector.
 * \param i_l The lower row index.
 * \param i_u The upper row index.
 */
void
bml_print_dense_vector(
    const int N,
    bml_matrix_precision_t matrix_precision,
    const void *v,
    const int i_l,
    const int i_u)
{
    LOG_DEBUG("printing vector [%d:%d]\n", i_l, i_u);
    switch (matrix_precision)
    {
        case single_real:
        {
            const float *v_typed = v;
            for (int i = i_l; i < i_u; i++)
            {
                printf(" % 1.3f", v_typed[i]);
            }
            printf("\n");
            break;
        }
        case double_real:
        {
            const double *v_typed = v;
            for (int i = i_l; i < i_u; i++)
            {
                printf(" % 1.3f", v_typed[i]);
            }
            printf("\n");
            break;
        }
        case single_complex:
        {
            const float complex *v_typed = v;
            for (int i = i_l; i < i_u; i++)
            {
                printf(" % 1.3f%+1.3fi", creal(v_typed[i]),
                       cimag(v_typed[i]));
            }
            printf("\n");
            break;
        }
        case double_complex:
        {
            const double complex *v_typed = v;
            for (int i = i_l; i < i_u; i++)
            {
                printf(" % 1.3f%+1.3fi", creal(v_typed[i]),
                       cimag(v_typed[i]));
            }
            printf("\n");
            break;
        }
        default:
            LOG_ERROR("unknown matrix precision");
            break;
    }
}