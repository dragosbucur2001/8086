#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
#include <sys/types.h>

enum class Ins {
  MOV,
};

constexpr std::array<std::array<std::string_view, 2>, 8> register_encodings{
    std::array<std::string_view, 2>{"al", "ax"},
    std::array<std::string_view, 2>{"cl", "cx"},
    std::array<std::string_view, 2>{"dl", "dx"},
    std::array<std::string_view, 2>{"bl", "bx"},
    std::array<std::string_view, 2>{"ah", "sp"},
    std::array<std::string_view, 2>{"ch", "bp"},
    std::array<std::string_view, 2>{"dh", "si"},
    std::array<std::string_view, 2>{"bh", "di"},
};

enum class BitsCoding : uint8_t {
  NONE,
  LITERAL,
  D,
  W,
  REG,
  SR,
  MOD,
  RM,
  DISP_LO,
  DISP_HI,
  DATA_LO,
  DATA_HI,
};

using BC = BitsCoding;

struct InsBits {
  BitsCoding code;
  uint8_t bits_no = 0;
};

struct Instruction {
  std::string_view name;
  uint8_t value;
  uint8_t mask;
  std::array<InsBits, 10> bits;
};

constexpr std::string_view MOV_NAME{"mov"};

constexpr std::array<Instruction, 90> instructions{
    Instruction{MOV_NAME,
                0b10001000,
                0b11111100,
                {
                    InsBits{BC::LITERAL, 6},
                    InsBits{BC::D},
                    InsBits{BC::W},
                    InsBits{BC::MOD},
                    InsBits{BC::REG},
                    InsBits{BC::RM},
                    InsBits{BC::DISP_LO},
                    InsBits{BC::DISP_HI},
                }},
    Instruction{MOV_NAME,
                0b11000110,
                0b11111110,
                {
                    InsBits{BC::LITERAL, 6},
                    InsBits{BC::D},
                    InsBits{BC::W},
                    InsBits{BC::MOD},
                    InsBits{BC::REG},
                    InsBits{BC::RM},
                    InsBits{BC::DISP_LO},
                    InsBits{BC::DISP_HI},
                }},
};

struct DecodedInstruction {
  Ins ins;
  uint8_t d;
  uint8_t w;
  uint8_t mod;
  uint8_t reg;
  uint8_t rm;

  uint8_t low;
  uint8_t high;

  uint8_t low2;
  uint8_t high2;
};

struct BitReader {
  std::ifstream in;
  uint8_t buff;
  uint8_t bit;

  uint8_t read(uint8_t bits_num) {
    uint8_t res{};

    

    return res;
  }
};

DecodedInstruction read_instruction(std::istream &in) {
  DecodedInstruction result{};

  char byte{};
  in.read(&byte, 1);

  for (const auto& instr : instructions) {
    const bool matches = (byte & instr.mask) == instr.value;
    if (!matches) continue;

    for (const auto& grouping : instr.bits) {
      switch (grouping.code) {
        case BC::NONE: continue;
        case BC::LITERAL: ;
      }
    }

  }

  return result;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "./emulator <binary_file>";
    std::exit(1);
  }

  std::ifstream in(argv[1]);

  return 0;
}
