#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

#include "puzzle_position.h"
#include "common_functions.h"

inline unsigned char getDir(unsigned char first, unsigned char second);

struct dist_to {
	dist_to(int raw, int Distance, puzzle_position Position, puzzle_position Previous) :
		raw_dist(raw), dist(Distance), pos(Position), prev(Previous) {}
	dist_to(const dist_to& another) :
		raw_dist(another.raw_dist), dist(another.dist), pos(another.pos), prev(another.prev) {}
	int raw_dist;
	int dist;
	puzzle_position pos;
	puzzle_position prev;
	bool operator < (const dist_to& another) const {
		return this->dist >= another.dist;
	}
};

std::string recoverPath(puzzle_position start, const std::unordered_map<long long, dist_to>& passed, int dist) {
	puzzle_position prev = (passed.find(start.getData())->second).prev;
	puzzle_position it = start;
	int count = 0;
	std::string result = "";
	result += getDir(start.getNull(), 15);
	while (count < dist) {
		count++;
		result += getDir(prev.getNull(), it.getNull());
		it = prev;
		prev = (passed.find(it.getData())->second).prev;
	}
	std::string result_rev = "";
	for (int i = result.size() - 1; i >= 0; i--)
		result_rev += result[i];
	return result_rev;
}

int fastWaySearch(puzzle_position start, std::string& way) {
	way = "";
	if (start.getData() == FINAL)
		return 0;
	bool flag = true;
	std::priority_queue<dist_to> queue;
	std::unordered_map<long long, dist_to> passed;
	queue.emplace(0, start.probDistance(), start, start);
	while (!queue.empty()) {
		dist_to current = queue.top();
		int current_dist = current.raw_dist;
		puzzle_position data = current.pos;
		queue.pop();
		std::unordered_map<long long, dist_to>::iterator old_pos = passed.find(data.getData());
		if (old_pos != passed.end())
			continue;
		std::vector<puzzle_position> nextPositions;
		data.getNext(nextPositions);
		for (unsigned int i = 0; i < nextPositions.size(); i++) {
			puzzle_position newData = nextPositions[i];
			if (newData.getData() == FINAL) {
				passed.insert({ data.getData(), current });
				way = recoverPath(data, passed, current_dist);
				return current_dist + 1;
			}
			if (passed.find(newData.getData()) == passed.end()) {
				queue.emplace(current_dist + 1, 11 * (current_dist + 1) / 12 + newData.probDistance(), newData, data);
			}
		}
		passed.insert({ data.getData(), current });
	}
	return -1;
}