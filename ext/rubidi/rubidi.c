#include "rubidi.h"

VALUE rb_mRubidi;

void
Init_rubidi(void)
{
  rb_mRubidi = rb_define_module("Rubidi");
}
