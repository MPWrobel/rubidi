#include "rubidi.h"

VALUE bidi(VALUE _self, VALUE str) {
  char *input, output[MAX_STR_LEN + 1];
  int len, len_utf8;
  FriBidiParType base_dir;
  FriBidiChar input_utf8[MAX_STR_LEN], output_utf8[MAX_STR_LEN];

  input = StringValueCStr(str);
  len = (int)strlen(input);

  if (len > MAX_STR_LEN) {
    fprintf(stderr, "Error: Input length exceeds the maximum (>%d)\n",
            MAX_STR_LEN);
    exit(1);
  }

  base_dir = FRIBIDI_PAR_RTL;

  int charset = fribidi_parse_charset("UTF-8");
  if (!charset) {
    fprintf(stderr, "Error: Invalid charset\n");
    exit(1);
  }

  len_utf8 = fribidi_charset_to_unicode(charset, input, len, input_utf8);

  if (len_utf8 > len) {
    fprintf(stderr, "String longer after decoding than before\n");
    exit(1);
  }

  fribidi_log2vis(
      input_utf8,  /* input logical string */
      len_utf8,    /* input string length */
      &base_dir,   /* requested and resolved paragraph base direction */
      output_utf8, /* output visual string */
      NULL, NULL, NULL);

  fribidi_unicode_to_charset(charset, output_utf8, len_utf8, output);

  printf("len: %d\tlen_utf8: %d\n", len, len_utf8);
  printf("input:  \"%s\"\n", input);
  printf("output: \"%s\"\n", output);

  return rb_utf8_str_new_cstr(output);
}

void Init_rubidi(void) {
  VALUE mod = rb_define_module("Rubidi");
  rb_define_module_function(mod, "bidi", bidi, 1);
}
