macro(bml_add_typed_library TARGET MATRIX_PRECISION SOURCES)
  set(TYPED_TARGET ${TARGET}-${MATRIX_PRECISION})
  message(STATUS "Adding typed library ${TYPED_TARGET}")
  add_library(${TYPED_TARGET} OBJECT ${SOURCES})
  string(TOUPPER ${MATRIX_PRECISION} PRECISION_DEF)
  set_target_properties(${TYPED_TARGET}
    PROPERTIES
    COMPILE_DEFINITIONS ${PRECISION_DEF}
    POSITION_INDEPENDENT_CODE yes)
endmacro()
