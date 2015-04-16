#include "mips_instruction.hpp"

std::string MIPSInstruction::FuncStr() {
  return std::bitset<11>(instr_bits_full_.substr(21, 11)).to_string();
}

void MIPSInstruction::SetValues() {
  int instr_bits = std::stoul(instr_hex_, nullptr, 16);
  instr_bits_ = instr_bits;
  instr_bits_full_ = instr_bits_.to_string();
  instr_bits_op_ = instr_bits_full_.substr(0, 6);
}

std::istream& operator >> (std::istream& ist, MIPSInstruction& mips_instruction) {
  ist >> mips_instruction.instr_hex_;
  mips_instruction.SetValues();
  return ist;
}

std::ostream& operator << (std::ostream& ost, MIPSInstruction& mips_instruction) {
  ost << mips_instruction.instr_hex_;
  return ost;
}