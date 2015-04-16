#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>

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
}

class MIPSInstruction {
 public:
  MIPSInstruction() {}
  MIPSInstruction(std::string& instr_hex) : instr_hex_(instr_hex) {}
  void SetValues();
  std::string FuncStr();
  std::bitset<32> instr_bits_;
  std::string instr_hex_;
  std::string instr_bits_str_;
  std::string instr_bits_op_;
 private:
  friend std::istream& operator >> (std::istream& ost, MIPSInstruction& mips_instruction);
  friend std::ostream& operator << (std::ostream& ost, MIPSInstruction& mips_instruction);
};

std::string MIPSInstruction::FuncStr() {
  return std::bitset<11>(instr_bits_str_.substr(21, 11)).to_string();
}

void MIPSInstruction::SetValues() {
  int instr_bits = std::stoul(instr_hex_, nullptr, 16);
  instr_bits_ = instr_bits;
  instr_bits_str_ = instr_bits_.to_string();
  instr_bits_op_ = instr_bits_str_.substr(0, 6);
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

int main(int argc, char** argv) {

  if (argc != 2) {
    std::cout << "Usage: ./assembler <path-to-asm-file>" << std::endl;
    return 1;
  }

  std::vector<MIPSInstruction> mips_instructions;
  std::unordered_map<std::string, std::string> op_map;
  std::unordered_map<std::string, std::string> func_map;

  PopulateOpMap(op_map);
  PopulateFuncMap(func_map);

  std::ifstream mips_file(std::string(argv[1]).c_str());
  MIPSInstruction mips_instr;
  while (mips_file >> mips_instr) {
    mips_instructions.push_back(mips_instr);
  }
  for (auto& mips_instruction : mips_instructions) {
    std::string op = op_map[mips_instruction.instr_bits_op_];
    std::cout << "Hex: " << mips_instruction << "\tFunction: " << mips_instruction.FuncStr() << " ";
    if (op == "function") {
      op = func_map[mips_instruction.FuncStr()];
      std::cout << "Op: " << op;
    }
    std::cout << std::endl;
  }
  return 0;
}