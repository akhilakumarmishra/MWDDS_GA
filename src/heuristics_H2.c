// #include "heuristics_H1.c"
int* heuristics_H2(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int color[],int white_color_nodes){	
	int i,j;
	int* chromosome_repairing=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome_repairing[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		int count=0;
		for(j=0;j<Nodeno;j++){
			if(directed_graph[j][i]==0){
				count++;
			}
		}
		if(count==Nodeno){
			chromosome[i]=1;
			if(color[i]==1){
				color[i]=0;
				white_color_nodes--;
			}
			
			
			int k;
			for(k=0;k<Nodeno;k++){
				if(directed_graph[i][k]==1&&color[k]==1){
					color[k]=0;
					white_color_nodes--;
				}
			}
		}
	}
	int* chromosome_string=heuristics_H1(chromosome,Nodeno,directed_graph,nodeweightarr,color,white_color_nodes);
	
	for(i=0;i<Nodeno;i++){
		chromosome_repairing[i]=chromosome_string[i];
	}
	// printf("Am2\n");
	free(chromosome_string);
	// printf("rx_R2_100\n");
	for(j=0;j<Nodeno;j++){
		// printf("%d ",chromosome_repairing[j]);fflush(stdout);
		if(chromosome_repairing[j]!=1&&chromosome_repairing[j]!=0){
			printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",j,chromosome_repairing[j]); fflush(stdout);sleep(10);
		}
	}
	// sleep(3);
	// printf("\n");
	return chromosome_repairing;
}
