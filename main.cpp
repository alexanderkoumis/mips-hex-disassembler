#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>

void PopulateOpMap(std::unordered_map<std::bitset<6>, std::string>& op_map) {
  op_map[std::bitset<6>(std::string("000000"))] = "function";
  op_map[std::bitset<6>(std::string("001000"))] = "addi";
  op_map[std::bitset<6>(std::string("001001"))] = "addiu";
}

void PopulateFuncMap(std::unordered_map<std::bitset<11>, std::string>& func_map) {
  func_map[std::bitset<11>(std::string("00000100000"))] = "add";
  func_map[std::bitset<11>(std::string("00000100001"))] = "addu";
  func_map[std::bitset<11>(std::string("00000100100"))] = "and";
  func_map[std::bitset<11>(std::string("00000011010"))] = "div";
  func_map[std::bitset<11>(std::string("00000011011"))] = "divu";
  func_map[std::bitset<11>(std::string("00000001000"))] = "jr";
  func_map[std::bitset<11>(std::string("00000010000"))] = "mfhi";
  func_map[std::bitset<11>(std::string("00000010010"))] = "mflo";
  func_map[std::bitset<11>(std::string("00000010010"))] = "mult";
  func_map[std::bitset<11>(std::string("00000011001"))] = "multu";
}


class MIPSInstruction {
 public:
  MIPSInstruction() {}
  MIPSInstruction(std::string& instr_hex) : instr_hex_(instr_hex) {}
  std::bitset<32> instr_bits_;
  std::string String();
  std::string instr_hex_;
  std::string instr_bits_str_;
  std::string instr_bin_op_;
  void SetValues(int instr_bits) {
    unsigned int instr_bits = std::stoul(mips_instruction.instr_hex_, nullptr, 32);
    instr_bits_ = instr_bits;
    instr_bits_str_ = instr_bits_.to_string();
    instr_bin_op_ = instr_bin_.substr(0, 6);
  }
 private:
  friend std::istream& operator >> (std::istream& ost, MIPSInstruction& mips_instruction);
  friend std::ostream& operator << (std::ostream& ost, MIPSInstruction& mips_instruction);
};

std::string MIPSInstruction::String() {
  return instr_bits_.to_string();
}

std::istream& operator >> (std::istream& ist, MIPSInstruction& mips_instruction) {
  ist >> mips_instruction.instr_hex_;
  SetValues();
  std::bitset<6> op_bits(mips_instruction.instr_hex_.substr(0,6));

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

  std::unordered_map<std::bitset<6>, std::string> op_map;
  std::unordered_map<std::bitset<11>, std::string> func_map;

  std::vector<MIPSInstruction> mips_instructions;
  std::string mips_file_arg(argv[1]);
  std::ifstream mips_file(mips_file_arg.c_str());

  PopulateOpMap(op_map);
  PopulateFuncMap(func_map);

  MIPSInstruction mips_instr;
  while (mips_file >> mips_instr) {
      mips_instructions.push_back(mips_instr);
  }
  for (auto& mips_instruction : mips_instructions) {
      std::string asm_str(mips_instruction.String());
      std::bitset<6> op_bits(asm_str.substr(0,6));
      std::string op = op_map[op_bits];
      if (op == "function") {
        std::bitset<11> func_bits(asm_str.substr(0, 31));
          std::cout << "Hex: " << mips_instruction << "\tFunction: " << func_bits << std::endl;
          op = func_map[func_bits];
      }
      // std::cout << op << std::endl;
  }
  return 0;
}