/*����� ����� ���141
������ �8 FIFO*/

#include "fifo.h"
#include <fstream>

using namespace std;

/*Simulation*/
void fifo::simulate(string file) {
	loadworkload(file);

	int next = 0;//next job length
	int totaljobs = 0;
	int latency = 0;
	event e, n;

	/*output file*/
	ofstream out;
	out.open("output.out");
	out << "FIFO Simulation\n\n";

	for (int time = 0; !workload.empty() || !waiting.empty(); time++)//start timing
	{
		/*If time's come, registering all jobs that arrived at the same time*/
		while (!workload.empty() && time == workload.front().arrival_time()) {
			e = workload.front();
			waiting.push(e);
			workload.pop();


			out << "\tArriving: " << e.getjob().getuser() << " at " <<
			e.arrival_time() << " seconds" << endl;
		}

		/*Servicing*/
		if (next == 0 && !waiting.empty()) {
			n = waiting.front();
			totaljobs++;
			waiting.pop();
			next = n.getjob().getnumpages() * seconds_per_page;
			latency += time - n.arrival_time();

			out << "\tServicing: " << n.getjob().getuser()
			<< " at " <<
			time << " seconds" << endl;

		}
		if (next > 0)//decrementing current job time
		{
			next--;
		}

	}
	out << "\nTotal jobs: " << totaljobs << endl;
	out << "Aggregate latency: " << latency << " seconds" << endl;
	out << "Mean latency: " << (float) latency / totaljobs << " seconds" << endl;

}



