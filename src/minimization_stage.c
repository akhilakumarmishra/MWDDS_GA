int* minimization(int chromosome[],int Nodeno,int** diagraph,int nodeweightarr[],int** adjacency_list,int** parent_nodes){
	// printf("\n\t\t***ENTER TO MINIMIZATION***\n");
	int i,j;
	
	int loop_counter=0;
	int* redundant_nodes;
	// int permission_entry_stage2=1;
	printf("Z\n");
	redundant_nodes = redundant_finds_again(chromosome,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	int counter_x=0;
	// global_redundant_count=count;
	for(i=0;i<Nodeno;i++){
		// printf("%d ",redundant_nodes[i]);
		if(redundant_nodes[i]==1){
			counter_x++;
			
		}
	}
	// int new_chromosome_set[Nodeno];
	// for(i=0;i<Nodeno;i++){
	// 	if(redundant_nodes[i]==1){
	// 		new_chromosome_set[i]=0;
	// 	}
	// 	else{
	// 		new_chromosome_set[i]=chromosome[i];
	// 	}
	// }
	
	// check(Nodeno,new_chromosome_set,diagraph,1,-900,1);
	// int* chromosome_stage_one;
	// chromosome_stage_one=minimize_more(new_chromosome_set,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	// int* redundant_nodes_x;
	// redundant_nodes_x=neighbour_redundants_finds(chromosome_stage_one,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	// int count_one=0;
	// // global_redundant_count=count;
	// for(i=0;i<Nodeno;i++){
	// 	// printf("%d ",redundant_nodes[i]);
	// 	if(redundant_nodes_x[i]==1){
	// 		count_one++;
			
	// 	}
	// }
	// //**********************************
	// // printf("count_one_1:%d\n",count_one );
	// int* chromosome_stage_x;
	// int fitter_1=0;
	// chromosome_stage_x=minimize_more(chromosome,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	
	// //********************************************************
	// for(i=0;i<Nodeno;i++){
	// 	if(chromosome_stage_one[i]==1){
	// 		fitter_1+=nodeweightarr[i]*chromosome_stage_one[i];
	// 	}
	// }
	// redundant_nodes_x=neighbour_redundants_finds(chromosome_stage_x,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	// int count_one_x=0;
	// // global_redundant_count=count;
	// for(i=0;i<Nodeno;i++){
	// 	// printf("%d ",redundant_nodes[i]);
	// 	if(redundant_nodes_x[i]==1){
	// 		count_one_x++;
			
	// 	}
	// }
	// printf("count_one_2:%d\n",count_one_x );
	
//****************************************	
	// check(Nodeno,chromosome_stage_one,diagraph,1,-1234,1);


	// int visited_chromosome_set[Nodeno];
	// for(i=0;i<Nodeno;i++){
	// 	visited_chromosome_set[i]=0;
	// 	if(chromosome[i]==1){
	// 		visited_chromosome_set[i]=1;
	// 	}
	// 	else if(chromosome[i]==0 && chromosome_stage_x[i]==1){
	// 		visited_chromosome_set[i]=1;
	// 		// printf(":::::::::::::::::::::::::Non_dom to dom:%d,",i);
	// 	}
	// 	else{
	// 		visited_chromosome_set[i]=0;
	// 	}
	// }
	
	// int counter_x=0;
	int final_redundant_nodes[Nodeno];
	for(i=0;i<Nodeno;i++){
		// final_redundant_nodes[i]=0;
		// if(chromosome_stage_x[i]==0 && visited_chromosome_set[i]==1){
			final_redundant_nodes[i]=redundant_nodes[i];
			// counter_x++;
		// }
	}
	int visited_chromosome_set[Nodeno];

	for(i=0;i<Nodeno;i++){
		visited_chromosome_set[i]=chromosome[i];
	}
	int count=0;
	count=counter_x;
	

	if(count>0){
		int outdegree[Nodeno];
		int* out_deg=outdegree_calculation(Nodeno,diagraph);
		for(i=0;i<Nodeno;i++){
			outdegree[i]=out_deg[i];
		}
		loop_counter=0;
		float ratio_arr[Nodeno];
		for(i=0;i<Nodeno;i++){
			ratio_arr[i]=-1;
		}
		
		for(i=0;i<Nodeno;i++){
			// if(final_redundant_nodes[i]==1){
				ratio_arr[i]=(float)nodeweightarr[i]/(float)outdegree[i];
			// }
		}
		int xt=count;
		while(count!=0 ){
			int final_redundant;
			
			//max ratio redundant node
			float max_ratio=-1;
			int max_ratio_index=0;
			for(i=1;i<Nodeno;i++){
				if(final_redundant_nodes[i]==1&&ratio_arr[i]>max_ratio){
					max_ratio=ratio_arr[i];
					max_ratio_index = i;
				}
			}
			

			final_redundant=max_ratio_index;
			int temp_stage_record_red[Nodeno];
			for(i=0;i<Nodeno;i++){
				temp_stage_record_red[i]=0;
				if(final_redundant_nodes[i]==1){
					temp_stage_record_red[i]=final_redundant_nodes[i];
				}
				
			}
		
			visited_chromosome_set[final_redundant]=0;
			final_redundant_nodes[final_redundant]=0;
			int c =0;
			printf("Z1\n");
			int *new_chromosome_stage_2;

			// R= redundants_finds_fixed_outsider(final_redundant,visited_chromosome_set,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
			new_chromosome_stage_2= redundant_finds_again(visited_chromosome_set,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);

			
			for(i=0;i<Nodeno;i++){
				final_redundant_nodes[i]=0;
			}
			int counter_x=0;
			for(i=0;i<Nodeno;i++){
				//final_redundant_nodes[i]=0;
				if(new_chromosome_stage_2[i]==1){
					// && visited_chromosome_set[i]==1){
					final_redundant_nodes[i]=1;
					counter_x++;
				}
			}
			printf("count:%d\n",count);
			
			count=counter_x;
			sleep(1);
			

			
			// count =count-1;
			// loop_counter++;
			free(new_chromosome_stage_2);
			

			

		}
		free(redundant_nodes);
		// printf("5\n");
		// printf("\nend of minimization\n");
	}
	int final_chromosome_set[Nodeno];
	for(i=0;i<Nodeno;i++){
		if(visited_chromosome_set[i]==1&&final_redundant_nodes[i]==0){
			final_chromosome_set[i]=1;
		}
		else{
			final_chromosome_set[i]=0;
		}
	}
	check(Nodeno,final_chromosome_set,diagraph,1,-300,1);


	int* last_chromosome=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		last_chromosome[i]=0;
	}
	
	for(i=0;i<Nodeno;i++){
		last_chromosome[i]=final_chromosome_set[i];
	}
	

	return last_chromosome;
	
	

}
