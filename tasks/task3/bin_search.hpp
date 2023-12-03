#pragma once

int* LowerBound(int* first, int* last, int value) {
	int* current;
	int count = std::distance(first, last);
	int step = count;

	while (count > 0) {
		current = first;
		step = count / 2;
		std::advance(current, step);

		if (*current < value) {
			first = ++current;
			count -= step + 1;
		}
		else {
			count = step;
		}
	}
	return first;
}
