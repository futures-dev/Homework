/*����� ����� ���141
������ �8 FIFO*/

#include <queue>
#include <string>
#include "simulator.h"

class fifo : public simulator {
protected:
	queue<event> waiting;

public:
	void simulate(string file);

	fifo(int seconds_per_page) : simulator(seconds_per_page) { }
};
