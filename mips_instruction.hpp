#ifndef MIPS_INSTRUCTION_HPP
#define MIPS_INSTRUCTION_HPP

#include <bitset>
#include <string>
#include <iostream>

class MIPSInstruction {
 public:
  MIPSInstruction() {}
  MIPSInstruction(std::string& instr_hex) : instr_hex_(instr_hex) {}
  void SetValues();
  std::string FuncStr();
  std::bitset<32> instr_bits_;
  std::string instr_hex_;
  std::string instr_bits_full_;
  std::string instr_bits_op_;
 private:
  friend std::istream& operator >> (std::istream& ost, MIPSInstruction& mips_instruction);
  friend std::ostream& operator << (std::ostream& ost, MIPSInstruction& mips_instruction);
};

#endif