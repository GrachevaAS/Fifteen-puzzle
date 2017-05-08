#ifndef PUZZLEPOS_H
#define PUZZLEPOS_H

#include <vector>

struct puzzle_position {
public:
	explicit puzzle_position(unsigned long long position, unsigned char null) :
		table_pos(position), null_pos(null) {}
	puzzle_position(const puzzle_position& another) : table_pos(another.getData()), null_pos(another.getNull()) {}
	~puzzle_position() {}
	void getNext(std::vector<puzzle_position>& nextPositions) const;
	unsigned long long setTo(int place, unsigned char value) const;
	unsigned char getFrom(int place) const;
	unsigned long long Left() const;
	unsigned long long Right() const;
	unsigned long long Up() const;
	unsigned long long Down() const;
	unsigned long long getData() const { return table_pos; }
	unsigned char getNull() const { return null_pos; }
	int probDistance() const;
	int manDist(unsigned char value, int pos) const;
private:
	unsigned long long table_pos;
	unsigned char null_pos;
	static const int gameSIZE = 16;
};

#endif