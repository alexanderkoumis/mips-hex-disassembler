#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdio>

#include "mips_instruction.hpp"

void PopulateOpMap(std::unordered_map<std::string, std::string>& op_map) {
  op_map[std::string("000000")] = "function";
  op_map[std::string("001000")] = "addi";
  op_map[std::string("001001")] = "addiu";
  op_map[std::string("001100")] = "andi";
  op_map[std::string("000100")] = "beq";
  op_map[std::string("000001")] = "bgez";
  op_map[std::string("100011")] = "lw";
  op_map[std::string("101011")] = "sw";
  op_map[std::string("000100")] = "lw";
  op_map[std::string("000010")] = "j";
  op_map[std::string("000011")] = "j";
}

void PopulateFuncMap(std::unordered_map<std::string, std::string>& func_map) {
  func_map[std::string("00000100000")] = "add";
  func_map[std::string("00000100001")] = "addu";
  func_map[std::string("00000100100")] = "and";
  func_map[std::string("00000011010")] = "div";
  func_map[std::string("00000011011")] = "divu";
  func_map[std::string("00000001000")] = "jr";
  func_map[std::string("00000010000")] = "mfhi";
  func_map[std::string("00000010010")] = "mflo";
  func_map[std::string("00000010010")] = "mult";
  func_map[std::string("00000011001")] = "multu";
  func_map[std::string("00000100101")] = "or";
  func_map[std::string("00000101010")] = "slt";
  func_map[std::string("00000000110")] = "srlv";
  func_map[std::string("00000100010")] = "sub";
  func_map[std::string("00000100011")] = "subu";
}

int main(int argc, char** argv) {

  if (argc != 2) {
    printf("Usage: ./assembler <path-to-asm-file>\n");
    return 1;
  }

  std::vector<MIPSInstruction> mips_instructions;
  std::unordered_map<std::string, std::string> op_map;
  std::unordered_map<std::string, std::string> func_map;
  std::ifstream mips_file(std::string(argv[1]).c_str());

  PopulateOpMap(op_map);
  PopulateFuncMap(func_map);

  MIPSInstruction mips_instr;
  while (mips_file >> mips_instr) {
    mips_instructions.push_back(mips_instr);
  }
  printf("%-08s%-30s\n", "Op", "Binary");
  for (auto& mips_instruction : mips_instructions) {
    std::string op = op_map[mips_instruction.instr_bits_op_];
    if (op == "function") {
      op = func_map[mips_instruction.FuncStr()];
    }
    printf("%-08s%-30s\n", op.c_str(), mips_instruction.instr_bits_full_.c_str());
  }
  return 0;

}