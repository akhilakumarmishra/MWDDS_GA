int* redundant_finds_again(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int** adjacency_list,int** parent_nodes){
	// printf("1\n");
	int i,j,k;
	int chromosome_set_new[Nodeno];
	// int* chromosome_set_new=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome_set_new[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		chromosome_set_new[i]=chromosome[i];
	}
	// for(i=0;i<Nodeno;i++){
	// 	if(chromosome[i]==1)printf("%d ",i);
	// }
	// printf("\n2\n");
	

	int** parents_list=(int **)malloc(Nodeno* sizeof(int *));
			// printf("connected_list\n");
	for(int k=0;k<Nodeno;k++){
		int each_size=parent_nodes[k][0] + 1;
		parents_list[k] = (int *)malloc(each_size*sizeof(int));
		for(int l=0;l<each_size;l++){
			parents_list[k][l]=-1;
		}
		for(int l=0;l<each_size;l++){
			parents_list[k][l]=parent_nodes[k][l];
		}
		// printf("size : %d 	|| ",connected_list[k][0]);
		int l=1;
		each_size=parents_list[k][0]+1;
		while(l<each_size){
			if(chromosome_set_new[ parents_list[k][l] ]==0){	
				parents_list[k][l]=-1;
			}
			l++;
		}
		i=1;
		while(i<each_size){
			if(parents_list[k][i]==-1){
				for(j=i;j<each_size-1;j++){
					parents_list[k][j]=parents_list[k][j+1];
				}
				parents_list[k][0]=parents_list[k][0]-1;
				each_size=each_size-1;
			}
			else{
				i++;
			}
		}

		// printf("%d-->",k);
		// for(j=0;j<parents_list[k][0]+1;j++){
		// 		printf("%d ",parents_list[k][j]);
		// }
		// printf("\n");			
	}
	// printf("3\n");
	//********************END : PARENT LIST----------------
	int temp_chromosome[Nodeno];
	for(j=0;j<Nodeno;j++){
		temp_chromosome[j]=0;
	}
	int new_dominating_set[Nodeno];
	int dom_count=0;
	for(i=0;i<Nodeno;i++){
		new_dominating_set[i]=0;
		temp_chromosome[i]=chromosome_set_new[i];
		if(chromosome_set_new[i]==1){
			new_dominating_set[dom_count]=i;
			dom_count++;
		}
	}
	

	// }
	// printf("B\n");
	//START : REDUNDANT _FIND 
	// printf("4\n");
	// int* new_redundant_nodes=(int*)malloc(Nodeno*sizeof(int));
	int new_redundant_nodes[Nodeno];
	for(i=0;i<Nodeno;i++){
		new_redundant_nodes[i]=0;
	}
	for(i=0;i<dom_count;i++){
		int remove_node=new_dominating_set[i];
		// printf("remove_node: %d ----->",remove_node);
		new_dominating_set[i]=-1;
		temp_chromosome[remove_node]=-1;
		int close_neightbour[Nodeno];
		// int open_neighbour[Nodeno];
		for(j=0;j<Nodeno;j++){
			close_neightbour[j]=0;
		}				
		int close_count=0;
		close_count=adjacency_list[remove_node][0];
		for(j=1;j<close_count+1;j++){
			close_neightbour[j]=adjacency_list[remove_node][j];
			// printf("%d ",close_neightbour[j]);
		}
		// printf("\n5\n");
		close_neightbour[0]=remove_node;
		close_count++;
		// printf("close_count:%d\n",close_count);	
		// int cover_count=0;
		int node_covered=0;
		// printf("**%d--->%d %d\n",close_neightbour[0],parents_list[close_neightbour[0]][0],parent_nodes[close_neightbour[0]][0]);
		if(parents_list[close_neightbour[0]][0]>0){
			node_covered++;
		}
		
		for(j=1;j<close_count;j++){
			// printf("**%d--->%d %d\n",close_neightbour[j],parents_list[close_neightbour[j]][0],parent_nodes[close_neightbour[j]][0]);
			if(parents_list[close_neightbour[j]][0]>1){
				node_covered++;
			}
		}
		// printf("node_covered:%d\n",node_covered);
		// printf("6\n");
		if(node_covered==close_count){
			// printf("7:%d\n",remove_node);
			new_redundant_nodes[remove_node]=1;

			for(j=1;j<close_count;j++){
				int size=parents_list[close_neightbour[j]][0]+1;
				int side_node=close_neightbour[j];
				for(k=1;k<size;k++){
					if(parents_list[side_node][k]==remove_node){
						int each_size=parents_list[side_node][0]+1;
						for(j=k;j<each_size-1;j++){
							parents_list[side_node][j]=parents_list[side_node][j+1];
						}
						parents_list[side_node][0]=parents_list[side_node][0]-1;

					}
				}
			}
		}
		else{
			new_dominating_set[i]=remove_node;
			temp_chromosome[remove_node]=1;
		}
	}


/*	int redundant_nodes_two[Nodeno];
	for(i=0;i<Nodeno;i++){
		redundant_nodes_two[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		if(new_redundant_nodes[i]==1){
			redundant_nodes_two[i]=new_redundant_nodes[i];
			printf("%d ",i);
		}
	}
	int chromosome_set_two[Nodeno];
	for(i=0;i<Nodeno;i++){
		if(chromosome_set_new[i]==1&&redundant_nodes_two[i]==0){
			chromosome_set_two[i]=1;
		}
		if(chromosome_set_new[i]==0&&redundant_nodes_two[i]==1){
			// chromosome_set_two[i]=1;
			printf("error\n");
			sleep(2);
		}

	}

	//START : CONNECTED_LIST
	int** connected_list=(int **)malloc(Nodeno* sizeof(int *));
			// printf("connected_list\n");
	for(int k=0;k<Nodeno;k++){
		int each_size=adjacency_list[k][0] + 1;
				
		connected_list[k] = (int *)malloc(each_size*sizeof(int));
		for(int l=0;l<each_size;l++){
			connected_list[k][l]=-1;
		}
		for(int l=0;l<each_size;l++){
			connected_list[k][l]=adjacency_list[k][l];
		}
		// printf("size : %d 	|| ",connected_list[k][0]);
		int l=1;
		each_size=connected_list[k][0]+1;
		while(l<each_size){
			if(chromosome_set_two[ connected_list[k][l] ]==1){	
				connected_list[k][l]=-1;
			}
			l++;
		}
		i=1;
		while(i<each_size){
			if(connected_list[k][i]==-1){
				for(j=i;j<each_size-1;j++){
					connected_list[k][j]=connected_list[k][j+1];
				}
				connected_list[k][0]=connected_list[k][0]-1;
				each_size=each_size-1;
			}
			else{
				i++;
			}
		}

		// printf("%d-->",k);
		// for(j=0;j<connected_list[k][0]+1;j++){
		// 	printf("%d ",connected_list[k][j]);
		// }
		// printf("\n");

				
	}
	//END: CONNECTED LIST

	// int temp_chromosome[Nodeno];
	for(j=0;j<Nodeno;j++){
		temp_chromosome[j]=0;
	}
	new_dominating_set[Nodeno];
	dom_count=0;
	for(i=0;i<Nodeno;i++){
		new_dominating_set[i]=0;
		temp_chromosome[i]=chromosome_set_two[i];
		if(chromosome_set_two[i]==1){
			new_dominating_set[dom_count]=i;
			dom_count++;
		}
	}
		// printf("B\n");
	//START : REDUNDANT _FIND 
	// printf("4\n");
	// int* new_redundant_nodes=(int*)malloc(Nodeno*sizeof(int));
	new_redundant_nodes[Nodeno];
	for(i=0;i<Nodeno;i++){
		new_redundant_nodes[i]=0;
	}
	for(i=0;i<dom_count;i++){
		int remove_node=new_dominating_set[i];
		// printf("remove_node: %d ----->",remove_node);
		new_dominating_set[i]=-1;
		temp_chromosome[remove_node]=-1;
		int close_neightbour[Nodeno];
		// int open_neighbour[Nodeno];
		for(j=0;j<Nodeno;j++){
			close_neightbour[j]=0;
		}				
		int close_count=0;
		close_count=connected_list[remove_node][0];
		for(j=1;j<close_count+1;j++){
			close_neightbour[j]=connected_list[remove_node][j];
			// printf("%d ",close_neightbour[j]);
		}
		// printf("\n5\n");
		close_neightbour[0]=remove_node;
		close_count++;
		// printf("close_count:%d\n",close_count);	
		// int cover_count=0;
		int node_covered=0;
		// printf("**%d--->%d %d\n",close_neightbour[0],parents_list[close_neightbour[0]][0],parent_nodes[close_neightbour[0]][0]);
		if(parents_list[close_neightbour[0]][0]>0){
			node_covered++;
		}
		
		for(j=1;j<close_count;j++){
			// printf("**%d--->%d %d\n",close_neightbour[j],parents_list[close_neightbour[j]][0],parent_nodes[close_neightbour[j]][0]);
			if(parents_list[close_neightbour[j]][0]>1){
				node_covered++;
			}
		}
		// printf("node_covered:%d\n",node_covered);
		// printf("6\n");
		if(node_covered==close_count){
			// printf("7:%d\n",remove_node);
			new_redundant_nodes[remove_node]=1;

			//REMOVE FROM PARENTS_LIST
			int neightbour_child[Nodeno];
			// int open_neighbour[Nodeno];
			for(j=0;j<Nodeno;j++){
				neightbour_child[j]=0;
			}				
			close_count=0;
			close_count=adjacency_list[remove_node][0];
			for(j=1;j<close_count+1;j++){
				neightbour_child[j]=adjacency_list[remove_node][j];
				// printf("%d ",close_neightbour[j]);
			}
			// printf("\n5\n");
			neightbour_child[0]=remove_node;
			close_count++;

			for(j=1;j<close_count;j++){
				int size=parents_list[neightbour_child[j]][0]+1;
				int side_node=neightbour_child[j];
				for(k=1;k<size;k++){
					if(parents_list[side_node][k]==remove_node){
						int each_size=parents_list[side_node][0]+1;
						for(j=k;j<each_size-1;j++){
							parents_list[side_node][j]=parents_list[side_node][j+1];
						}
						parents_list[side_node][0]=parents_list[side_node][0]-1;

					}
				}

			}

			// ADD IN CONNECTED_LIST
			int neightbour_parent[Nodeno];
			// int open_neighbour[Nodeno];
			for(j=0;j<Nodeno;j++){
				neightbour_parent[j]=0;
			}				
			int close_count=0;
			close_count=parent_nodes[remove_node][0];
			for(j=1;j<close_count+1;j++){
				neightbour_parent[j]=parent_nodes[remove_node][j];
				// printf("%d ",close_neightbour[j]);
			}
			// printf("\n5\n");
			neightbour_parent[0]=remove_node;
			close_count++;

			for(j=1;j<close_count;j++){
				int size=connected_list[neightbour_parent[j]][0]+1;
				int side_node=neightbour_parent[j];

				for(k=0;k<size;k++){
					if(connected_list[side_node][k]==remove_node){
						printf("ERROR--------REMOVE NODE IN connected_list\n");
					}
				}
				connected_list[neightbour_parent[j]][0]=connected_list[neightbour_parent[j]][0]+1;
				connected_list[side_node][size]=remove_node;

			}
			


		}
		else{
			new_dominating_set[i]=remove_node;
			temp_chromosome[remove_node]=1;
		}
	}


*/
	



//***************************************
	fflush(stdout);
	for(i=0;i<Nodeno;i++){
		free(parents_list[i]);
	}
	free(parents_list);
	// for(i=0;i<Nodeno;i++){
	// 	free(connected_list[i]);
	// }
	// free(connected_list);
	// for(i=0;i<Nodeno;i++){
	// 	if(new_redundant_nodes[i]==1&&redundant_nodes_two[i]){
	// 		printf("------------------------------------------------------------------------------ERROR--------SAME redundant_nodes_AGAIN\n");

	// 	}
	// 	if(new_redundant_nodes[i]==1){
	// 		redundant_nodes_two[i]=new_redundant_nodes[i];
	// 	}

	// }
	// sleep(1);
	int* final_redundant_nodes=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		final_redundant_nodes[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		final_redundant_nodes[i]=new_redundant_nodes[i];
		if(final_redundant_nodes[i]==1){
			printf("%d ",i);
		}
	}
	return final_redundant_nodes;
			


}