
#include "dijkstrax10.h"

static char end_print[] =   "Dijkstra_1 finished.\n";
static char start_print[] =   "Starting Dijkstra_1.\n";
static char new_value[] =   "> dijkstra1 new value. \n";

volatile static Message msg;

int main(){
	static int i, j, v;
	static int source;
	static int q[NUM_NODES];
	static int dist[NUM_NODES];
	static int prev[NUM_NODES];
	static int shortest, u;
	static int alt;
	static int calc;
	static int AdjMatrix[NUM_NODES][NUM_NODES];

	if ( !isMigration() ){
		source = 0;
		calc = 0;
	}

	sys_Prints((unsigned int)&start_print);

	while(1){

		checkMigration();

		msg.length = NUM_NODES;
		for (i=0; i<NUM_NODES; i++) {
			sys_Receive(&msg, divider);
			// sys_Printi(msg.msg[0]);
			// sys_Prints((unsigned int)&new_value);
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

