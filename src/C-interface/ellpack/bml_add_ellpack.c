#include "bml_add.h"
#include "bml_add_ellpack.h"
#include "bml_logger.h"
#include "bml_types.h"
#include "bml_types_ellpack.h"

#include <stdlib.h>
#include <string.h>

/** Matrix addition.
 *
 * \f$ A = \alpha A + \beta B \f$
 *
 * \ingroup add_group
 *
 * \param A Matrix A
 * \param B Matrix B
 * \param alpha Scalar factor multiplied by A
 * \param beta Scalar factor multiplied by B
 * \param threshold Threshold for matrix addition
 */
void
bml_add_ellpack(
    bml_matrix_ellpack_t * const A,
    bml_matrix_ellpack_t const *const B,
    double const alpha,
    double const beta,
    double const threshold)
{
    switch (B->matrix_precision)
    {
        case single_real:
            bml_add_ellpack_single_real(A, B, alpha, beta, threshold);
            break;
        case double_real:
            bml_add_ellpack_double_real(A, B, alpha, beta, threshold);
            break;
        case single_complex:
            bml_add_ellpack_single_complex(A, B, alpha, beta, threshold);
            break;
        case double_complex:
            bml_add_ellpack_double_complex(A, B, alpha, beta, threshold);
            break;
        default:
            LOG_ERROR("unknown precision\n");
            break;
    }
}

/** Matrix addition and TrNorm calculation.
 *
 * \f$ A = \alpha A + \beta B \f$
 *
 * \ingroup add_group
 *
 * \param A Matrix A
 * \param B Matrix B
 * \param alpha Scalar factor multiplied by A
 * \param beta Scalar factor multiplied by B
 * \param threshold Threshold for matrix addition
 */
double
bml_add_norm_ellpack(
    bml_matrix_ellpack_t * const A,
    bml_matrix_ellpack_t const *const B,
    double const alpha,
    double const beta,
    double const threshold)
{
    double trnorm = 0.0;

    switch (B->matrix_precision)
    {
        case single_real:
            trnorm =
                bml_add_norm_ellpack_single_real(A, B, alpha, beta,
                                                 threshold);
            break;
        case double_real:
            trnorm =
                bml_add_norm_ellpack_double_real(A, B, alpha, beta,
                                                 threshold);
            break;
        case single_complex:
            trnorm =
                bml_add_norm_ellpack_single_complex(A, B, alpha, beta,
                                                    threshold);
            break;
        case double_complex:
            trnorm =
                bml_add_norm_ellpack_double_complex(A, B, alpha, beta,
                                                    threshold);
            break;
        default:
            LOG_ERROR("unknown precision\n");
            break;
    }
    return trnorm;
}

/** Matrix addition.
 *
 * \f$ A = A + \beta \mathrm{Id} \f$
 *
 * \ingroup add_group
 *
 * \param A Matrix A
 * \param beta Scalar factor multiplied by A
 * \param threshold Threshold for matrix addition
 */
void
bml_add_identity_ellpack(
    bml_matrix_ellpack_t * const A,
    double const beta,
    double const threshold)
{
    switch (A->matrix_precision)
    {
        case single_real:
            bml_add_identity_ellpack_single_real(A, beta, threshold);
            break;
        case double_real:
            bml_add_identity_ellpack_double_real(A, beta, threshold);
            break;
        case single_complex:
            bml_add_identity_ellpack_single_complex(A, beta, threshold);
            break;
        case double_complex:
            bml_add_identity_ellpack_double_complex(A, beta, threshold);
            break;
        default:
            LOG_ERROR("unknown precision\n");
            break;
    }
}

/** Matrix addition.
 *
 * \f$ A = A + \beta \mathrm{Id} \f$
 *
 * \ingroup add_group
 *
 * \param A Matrix A
 * \param beta Scalar factor multiplied by A
 * \param threshold Threshold for matrix addition
 */
void
bml_scale_add_identity_ellpack(
    const bml_matrix_ellpack_t * A,
    const double alpha,
    const double beta,
    const double threshold)
{
    switch (A->matrix_precision)
    {
        case single_real:
            bml_scale_add_identity_ellpack_single_real(A, alpha, beta,
                                                       threshold);
            break;
        case double_real:
            bml_scale_add_identity_ellpack_double_real(A, alpha, beta,
                                                       threshold);
            break;
        case single_complex:
            bml_scale_add_identity_ellpack_single_complex(A, alpha, beta,
                                                          threshold);
            break;
        case double_complex:
            bml_scale_add_identity_ellpack_double_complex(A, alpha, beta,
                                                          threshold);
            break;
        default:
            LOG_ERROR("unknown precision\n");
            break;
    }
}
