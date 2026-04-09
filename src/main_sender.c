#include "pgm.h"
#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

struct argp argp = {options_sender, parse_opt_sender, args_doc_sender, doc_sender};
int main(int argc, char** argv){

  struct arguments_sender args;
  init_args_sender(&args);
  argp_parse(&argp, argc, argv, 0, 0, &args);

  // 1) Ensure FIFO exists (mkfifo if necessary)
  if(mkfifo(args.fifo, 0666) == -1 && errno != EEXIST){
    perror("Error creating FIFO.");
    return 1;
  }
  
  // 2) Read PGM image (P5) from disk
  PGM pgm;
  read_pgm(args.input_file, &pgm);

  // 3) Prepare header
  Header header;
  header.w = pgm.w;
  header.h = pgm.h;
  header.maxv = pgm.maxv;
  
  // 4) Open FIFO for writing (blocked until worker opens for reading)
  FILE* fd = fopen(args.fifo, "wb");
  if(fd == NULL){
    perror("Error opening FIFO for writing.");
    free(pgm.data);
    return 1;
  }

  // 5) Send header + pixels
  if(fwrite(&header, sizeof(Header), 1, fd) != 1){
    fprintf(stderr, "Error writing header to FIFO.\n");
    fclose(fd);
    free(pgm.data);
    return 1;
  }
  
  size_t img_size = ((size_t)pgm.w * (size_t)pgm.h);
  if(fwrite(pgm.data, 1, img_size, fd) != img_size){
    fprintf(stderr, "Error writing image data to FIFO.\n");
    fclose(fd);
    free(pgm.data);
    return 1;
  }

  // 6) Close FIFO and free up memory 
  free(pgm.data);
  fflush(fd);
  fclose(fd);

  return 0;
}
