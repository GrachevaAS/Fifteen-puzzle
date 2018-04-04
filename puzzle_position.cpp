#include <cmath>

#include "puzzle_position.h"

const unsigned long long Masks[] = {
    0x000000000000000F, 0x00000000000000F0, 0x0000000000000F00,
    0x000000000000F000, 0x00000000000F0000, 0x0000000000F00000,
    0x000000000F000000, 0x00000000F0000000, 0x0000000F00000000,
    0x000000F000000000, 0x00000F0000000000, 0x0000F00000000000,
    0x000F000000000000, 0x00F0000000000000, 0x0F00000000000000,
    0xF000000000000000,
};
const unsigned long long AntiMasks[] = {
    0xFFFFFFFFFFFFFFF0, 0xFFFFFFFFFFFFFF0F, 0xFFFFFFFFFFFFF0FF,
    0xFFFFFFFFFFFF0FFF, 0xFFFFFFFFFFF0FFFF, 0xFFFFFFFFFF0FFFFF,
    0xFFFFFFFFF0FFFFFF, 0xFFFFFFFF0FFFFFFF, 0xFFFFFFF0FFFFFFFF,
    0xFFFFFF0FFFFFFFFF, 0xFFFFF0FFFFFFFFFF, 0xFFFF0FFFFFFFFFFF,
    0xFFF0FFFFFFFFFFFF, 0xFF0FFFFFFFFFFFFF, 0xF0FFFFFFFFFFFFFF,
    0x0FFFFFFFFFFFFFFF};

inline unsigned char puzzle_position::getFrom(int place) const {
  return static_cast<unsigned char>((table_pos & Masks[place]) >> (place * 4));
}

inline unsigned long long puzzle_position::setTo(int place,
                                                 unsigned char value) const {
  return (table_pos & AntiMasks[place]) |
         (static_cast<unsigned long long>(value) << (place * 4));
}

inline unsigned long long puzzle_position::Left() const {
  unsigned char value = getFrom(null_pos - 1);
  return setTo(null_pos, value) & AntiMasks[null_pos - 1];
}

inline unsigned long long puzzle_position::Right() const {
  unsigned char value = getFrom(null_pos + 1);
  return setTo(null_pos, value) & AntiMasks[null_pos + 1];
}

inline unsigned long long puzzle_position::Up() const {
  unsigned char value = getFrom(null_pos - 4);
  return setTo(null_pos, value) & AntiMasks[null_pos - 4];
}

inline unsigned long long puzzle_position::Down() const {
  unsigned char value = getFrom(null_pos + 4);
  return setTo(null_pos, value) & AntiMasks[null_pos + 4];
}

void puzzle_position::getNext(
    std::vector<puzzle_position>& nextPositions) const {
  if (null_pos % 4 != 0)
    nextPositions.emplace(nextPositions.end(), Left(), null_pos - 1);
  if (null_pos % 4 != 3)
    nextPositions.emplace(nextPositions.end(), Right(), null_pos + 1);
  if (null_pos >= 4)
    nextPositions.emplace(nextPositions.end(), Up(), null_pos - 4);
  if (null_pos < gameSIZE - 4)
    nextPositions.emplace(nextPositions.end(), Down(), null_pos + 4);
}

inline int puzzle_position::manDist(unsigned char value, int pos) const {
  if (value == 0) return 0;
  int i = (value - 1) / 4;
  int j = (value - 1) % 4;
  return std::abs(pos / 4 - i) + std::abs(pos % 4 - j);
}

int puzzle_position::probDistance() const {
  unsigned char table[gameSIZE];
  int result = 0;
  for (int i = 0; i < gameSIZE; i++) {
    table[i] = getFrom(i);
    result += manDist(table[i], i);
  }
  for (int k = 0; k < 4; k++)
    for (int i = 0; i < 4; i++)
      for (int j = i + 1; j < 4; j++)
        if (table[4 * k + i] > table[4 * k + j]) result += 2;
  return result;
}
