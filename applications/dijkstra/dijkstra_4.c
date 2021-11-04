
#include "dijkstra.h"

static char end_print[] =   "Dijkstra_4 finished.\n";
static char start_print[] =   "Starting Dijkstra_4.\n";

volatile static Message msg;

int main()
{
	int i, j, v;
	int source = 0;
	int q[NUM_NODES];
	int dist[NUM_NODES];
	int prev[NUM_NODES];
	int shortest, u;
	int alt;
	int calc = 0;

	int AdjMatrix[NUM_NODES][NUM_NODES];

	sys_Prints((unsigned int)&start_print);

	while(1){
		msg.length = NUM_NODES;
		for (i=0; i<NUM_NODES; i++) {
			sys_Receive(&msg, divider);
			for (j=0; j<NUM_NODES; j++)
				AdjMatrix[i][j] = msg.msg[j];
		}
		calc = AdjMatrix[0][0];
		if (calc == KILL) break;

		for (i=0;i<NUM_NODES;i++){
			dist[i] = INFINITY;
			prev[i] = INFINITY;
			q[i] = i;
		}
		dist[source] = 0;
		//u = 0;

		for (i=0;i<NUM_NODES;i++) {
			shortest = INFINITY;
			for (j=0;j<NUM_NODES;j++){
				if (dist[j] < shortest && q[j] != INFINITY){		
					shortest = dist[j];
					u = j;
				}
			}
			q[u] = INFINITY;

			for (v=0; v<NUM_NODES; v++){
				if (q[v] != INFINITY && AdjMatrix[u][v] != INFINITY){
					alt = dist[u] + AdjMatrix[u][v];
					if (alt < dist[v]){
						dist[v] = alt;
						prev[v] = u;
					}
				}
			}
		}
	}

	msg.length = NUM_NODES*2;
	for (i=0;i<NUM_NODES;i++)
		msg.msg[i] = dist[i];

	for (i=0;i<NUM_NODES;i++)
		msg.msg[i+NUM_NODES] = prev[i];

	sys_Send(&msg, print_dij);

    sys_Prints((unsigned int)&end_print);
	sys_Finish();
}
