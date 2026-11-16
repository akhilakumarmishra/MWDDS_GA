// srand(time(0));
#define u01 rand()/(RAND_MAX+1.0)

float	PPh =0.9;//0.7;//0.95;//0.7	//choose repairing or random set


//main
float init_pop_prob=0.1;//0.1;//0.3 
//Genetic
int	pop_size=200;
int	MAX_GEN=10000;
float	Pc=0.9;//0.9			//crossover probability b/w random or genetic
float  prob_select=0.8;//0.9;//0.8; //selection probability
float  Pm=0.01;//0.001;//0.005;			//probability mutation
// float  minimize_prob=1;
float perc_value=0.3;
int similar_set_max_size=20;
int unicon=3;
int k_points=3;




void check(int Nodeno,int chomosome[],int** directed_graph,int gp,int no,int mr){
	//*****************************************
	int vis[Nodeno];
	for(int k=0;k<Nodeno;k++){
			vis[k]=0;
	}
	for(int j=0;j<Nodeno;j++){
		if(chomosome[j]==1){
			vis[j]=1;
			for(int k=0;k<Nodeno;k++){
				if(directed_graph[j][k]==1){
					vis[k]=1;
				}
			}
		}
	}
	int c=0;
	
	for(int k=0;k<Nodeno;k++){
		if(vis[k]==0){
			c++;
			printf("free node: %d \n",k);
			printf("it's parents: ");
			for(int i=0;i<Nodeno;i++){
				if(directed_graph[i][k]==1){
					printf("%d ",i);
				}
			}
			printf("\n");
		}
		else{
			// printf("Noerror \n");
				// sleep(1);
			}
	}
	// printf("\n");

	if(c>0){
		
		printf("\n\n##########################################\n");
		printf(    "#     ERROR : Infeasible solution:%d    #\n",no);
		    printf("##########################################\n\n");
		fflush(stdout);
		if(gp==1){
			if(mr==1){
				printf("in population no:%d _repair\n",no);
				for(int j=0;j<Nodeno;j++){
					if(vis[j]==0)printf("%d ",j);
				}
				printf("\n");
			}
			else{

				printf("in population no:%d _minimize\n",no);
				for(int j=0;j<Nodeno;j++){
					if(vis[j]==0)printf("%d ",j);
				}
				printf("\n");
			}
		}
		else{
			if(mr==1){
				printf("in generation no:%d _repair\n",no);
				for(int j=0;j<Nodeno;j++){
					if(vis[j]==0)printf("%d ",j);
				}
				printf("\n");
			}
			else{

				printf("in generation no:%d _minimize\n",no);
				for(int j=0;j<Nodeno;j++){
					if(vis[j]==0)printf("%d ",j);
				}
				printf("\n");
			}
		}
		sleep(10);

	}
	else{
		// printf("\n\n##########################################\n");
		// printf(	   "#       Noerror : Feasible solution:%d      #\n",no);
		// printf("##########################################\n\n");
		// fflush(stdout);
		// sleep(2);
	}

	//********************************************
}
