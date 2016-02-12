/** \file */

#ifndef __BML_NORMALIZE_H
#define __BML_NORMALIZE_H

#include "bml_types.h"

// Normalize
void bml_normalize(
    bml_matrix_t * A, 
    const double maxeval,
    const double maxminusmin);

// Calculate Gershgorin bounds
void *bml_gershgorin(
    const bml_matrix_t * A);

#endif
