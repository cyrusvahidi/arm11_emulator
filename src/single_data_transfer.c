#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "utility.h"
#include "data_processing.h"
#include "machine.h"
#include "single_data_transfer.h"

int32_t* get_address(int32_t instr, struct machine_state *mach) {
  int32_t *ret = (int32_t*) malloc(3 * sizeof(int32_t));
  
  struct trans_instr instruction;
  
  instruction.immediate = read_bit(instr, 25);
  instruction.pre = read_bit(instr, 24);
  instruction.up = read_bit(instr, 23);
  instruction.load = read_bit(instr, 20);
  instruction.rn = extract_bits(instr, 16, 4);
  instruction.rd = extract_bits(instr, 12, 4);
  instruction.offset = extract_bits(instr, 0, 12);
 
  int32_t address;
  
  if (instruction.immediate) {
    int32_t processed_offset = process_args(instr, mach)[1];
    address 
      = mach->registers[instruction.rn] - (1 - 2 * instruction.up) * 
        processed_offset;
  } else { 
    address = mach->registers[instruction.rn] - (1 - 2 * instruction.up) * 
              instruction.offset;
  }
  int32_t arg2;
  if (instruction.pre ==1) {
    arg2 = address; 
  } else {
    arg2 = mach->registers[instruction.rn]; 
    mach->registers[instruction.rn] = address; 
  }
  int32_t arr[3] = {instruction.rd, arg2, instruction.load};
  ret = &arr[0];
  return ret;
}

void transfer (int32_t* args, struct machine_state *mach) {
  if (args[2] == 1) {
    mach->registers[args[0]] = mach->memory[args[1]];
  } else {
    mach->memory[args[1]] = mach->registers[args[0]];
  }
}


void decode_data_trans(int32_t instr, struct pipeline *pip, struct 
  machine_state *mach) {

  pip->decoded_args = get_address(instr,  mach);
  pip->decoded = &transfer;

}
