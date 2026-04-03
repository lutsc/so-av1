#include "pgm.h"
#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>

struct argp argp = {options, parse_opt, args_doc, doc};
int main(int argc, char* argv[])
{
  struct arguments arguments;
  arguments.silent = 0;
  arguments.verbose = 0;
  arguments.output_file = "";
  arguments.valid = 1;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  if(!arguments.valid)
  {
    printf("Arguments not valid");
    return 1;
  }
  else
  {
    printf("Arguments are valid");
  }

  PGM pgm;
  read_pgm(arguments.args[1], &pgm);

  PGM neg = pgm_negative(pgm);

  PGM slice = pgm_slice(pgm, 100, 110);

  write_pgm("output_slice.pgm", &slice);
  write_pgm("output_neg.pgm", &neg);

  return 0;
}
