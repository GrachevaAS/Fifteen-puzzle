#include <vector>

#include "puzzle_position.h"
#include "common_functions.h"

const int MAXDepth = 100;
int minWay = MAXDepth;
std::string WAY = "";

int searchFrom(puzzle_position data, puzzle_position prev, int depth, int bound) {
	int heur = data.probDistance();
	if (data.getData() == FINAL) {
		if (depth < minWay) {
			minWay = depth;
		}
		return 0;
	}
	if (depth + heur > MAXDepth) {
		return MAXDepth;
	}
	if (depth + heur > bound) {
		return depth + heur;
	}
	std::vector<puzzle_position> nextPositions;
	data.getNext(nextPositions);
	int minDepth = MAXDepth;
	int current = 0;
	for (unsigned int i = 0; i < nextPositions.size(); i++) {
		if (nextPositions[i].getData() != prev.getData()) {
			current = searchFrom(nextPositions[i], data, depth + 1, bound);
			if (current == 0) {
				WAY += getDir(data.getNull(), nextPositions[i].getNull());
				return 0;
			}
			if (current < minDepth)
				minDepth = current;
		}
	}
	return minDepth;
}

int preciseWaySearch(puzzle_position start, std::string& way) {
	way = "";
	if (start.getData() == FINAL)
		return 0;
	int bound = start.probDistance();
	while (true) {
		int temp = searchFrom(start, start, 0, bound);
		if (temp == MAXDepth)
			return -1;
		if (temp == 0) {
			for (int i = WAY.size() - 1; i >= 0; i--) {
				way += WAY[i];
			}
			return minWay;
		}
		bound = temp;
	}
	return -1;
}
