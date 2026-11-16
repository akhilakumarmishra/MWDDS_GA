int* heurisitics_call(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int heuristics_number){
	// printf("heuristics_number_x:%d\n",heuristics_number);
	// int* color = (int*)malloc(Nodeno*sizeof(int));
	int color[Nodeno];
	int i,j;
	// printf("\n***start of repairing function***\n");
	// for(i=0;i<Nodeno;i++){
	// 	printf("%d ",chromosome[i]);
	// }
	// printf("\n");
	int* chromosome_repairing=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome_repairing[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		color[i]=1;
	}
	for(i=0;i<Nodeno;i++){
		if(chromosome[i]==1){
			color[i]=0;
			int k;
			for(k=0;k<Nodeno;k++){
				if(directed_graph[i][k]==1){
					color[k]=0;
				}
			}	
		}
	}
	int white_color_nodes=0;
	for(i=0;i<Nodeno;i++){
		if(color[i]==1)
		{
			white_color_nodes++;
		}
	}

	if(heuristics_number==1){
		// printf("REPAIRING: heuristics-1:\n");
		//int request=0;
		int* chromosome_string=heuristics_H1(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
		// printf("end of repairing\n");
		for(i=0;i<Nodeno;i++){
			chromosome_repairing[i]=chromosome_string[i];
		}
		free(chromosome_string);
	}
	else if(heuristics_number==2){
		// printf("REPAIRING: heuristics-2:\n");
		//int request=0;
		int* chromosome_string=heuristics_H2(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
		// printf("end of repairing\n");
		for(i=0;i<Nodeno;i++){
			chromosome_repairing[i]=chromosome_string[i];
		}
		free(chromosome_string);
	}
	else if(heuristics_number==3){
		// printf("++REPAIRING: heuristics-3:\n");
		//int request=0;
		int* chromosome_string=heuristics_H3(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
		// printf("end of repairing\n");
		for(i=0;i<Nodeno;i++){
			chromosome_repairing[i]=chromosome_string[i];
		}
		free(chromosome_string);
	}
	else if(heuristics_number==4){
		// printf("REPAIRING:  heuristics-4:\n");
		//int request=0;
		int* chromosome_string=heuristics_H4(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
		// printf("end of repairing\n");
		for(i=0;i<Nodeno;i++){
			chromosome_repairing[i]=chromosome_string[i];
		}
		free(chromosome_string);
	}
	else{
		printf(" ERROR : choose correct heuristic\n");
	}
	return chromosome;


}
