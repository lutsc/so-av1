#include "arguments.h"
#include <argp.h>
#include <string.h>

error_t parse_opt (int key, char *arg, struct argp_state* state)
{
  struct arguments *arguments = state->input;

  switch(key)
  {
    case 'q': case 's':
      arguments->silent = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      break;
    case 'o':
      arguments->output_file = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 2) //Too many arguments
      {
        argp_usage(state);
      }
      arguments->args[state->arg_num] = arg;
      if(state->arg_num == 0)
      {
        if(strcmp(arg, "negative"))
        {
          arguments->mode = MODE_NEG;
          break;
        }
        else if(strcmp(arg, "slice"))
        {
          arguments->mode = MODE_SLICE;
          break;
        }
        arguments->valid = 0;
      }
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 2) //Not enough arguments
      {
        argp_usage(state);
      }
      arguments->valid = 0;
      break;
    default:
      arguments->valid = 0;
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
