int* redundants_finds_fixed_outsider(int outsider,int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int** adjacency_list,int** parent_nodes){
	// printf("ENTER to  fix_outsider:%d\n",ix);
// STAGE:1 : start >>>>>>>>>>>>>>>>>>>>>	
	int i,j,k=0; 
	int dom_count=0;
	int dominating_set_node[Nodeno];
	for(j=0;j<Nodeno;j++){
		dominating_set_node[j]=0;
	}
	int temp_chromosome[Nodeno];
	for(j=0;j<Nodeno;j++){
		temp_chromosome[j]=0;
	}
	// check(Nodeno,chromosome,directed_graph,1,-1991,2);
	for(i=0;i<Nodeno;i++){
		temp_chromosome[i]=chromosome[i];
		if(chromosome[i]==1){
			dominating_set_node[dom_count]=i;
			dom_count++;
		}
	}
	

	int redundant_nodes[Nodeno];
	for(i=0;i<Nodeno;i++){
		redundant_nodes[i]=0;
	}
	for(i=0;i<dom_count;i++){
		if(dominating_set_node[i]!=outsider){
			int remove_node=dominating_set_node[i];
			// printf("remove_node: %d \n",remove_node);
			dominating_set_node[i]=-1;
			temp_chromosome[remove_node]=-1;
			int close_neightbour[Nodeno];
			// int open_neighbour[Nodeno];
			for(j=0;j<Nodeno;j++){
				close_neightbour[j]=0;
				// open_neighbour[j]=0;
			}		
			
			int close_count=0;
			close_count=adjacency_list[remove_node][0];
			for(j=1;j<close_count+1;j++){
				close_neightbour[j]=adjacency_list[remove_node][j];
			}
			close_neightbour[0]=remove_node;
			close_count++;
			
			int cover_count=0;
			for(j=0;j<close_count;j++){
				int parent_dom=0;
				// printf("close_neightbour:%d has no of parents: %d\n",close_neightbour[j],parent_nodes[close_neightbour[j]][0]);
				for(k=1;k<parent_nodes[close_neightbour[j]][0]+1;k++){	
					// printf("parent_node: %d\n",parent_nodes[close_neightbour[j]][k]);
					int temp=parent_nodes[close_neightbour[j]][k];
					// printf("temp:%d\t\ttemp_chrom : %d\n",temp,temp_chromosome[temp]);
					if(temp!=remove_node && temp_chromosome[temp]==1){
						// cover_count++;
						// printf("yes parent node is dom set\n");
						parent_dom++;
					}
					
				}
				// printf("parent_dom:%d\n",parent_dom);
				if(parent_dom>=1){
					cover_count++;
				}

			}
			// printf("cover_count:%d\n\n\n",cover_count );
			if(cover_count==close_count){
				redundant_nodes[remove_node]=1;
				// printf("enter to remove_node : %d\n",remove_node);
			}
			else{
				dominating_set_node[i]=remove_node;
				temp_chromosome[remove_node]=1;
			}
		}
			
	}


	int redundant_nodes_count=0;
	// printf("STAGE:1 redundant_nodes:\n");
	for(i=0;i<Nodeno;i++){
		if(redundant_nodes[i]==1){
			// printf("%d ",i );
			redundant_nodes_count++;
			// fflush(stdout);
		}
	}


//STAGE:3 START	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	int* final_redundant_node_set=(int*)malloc((Nodeno)*sizeof(int));
	for(i=0;i<Nodeno;i++){
		final_redundant_node_set[i]=0;
	}
	 // printf("\n\nfinal_redundant_node_set:\n");
	for(j=0;j<Nodeno;j++){
		final_redundant_node_set[j]=redundant_nodes[j];
	 	if(redundant_nodes[j]==1){
	 		// red_alert++;
	 		// printf("%d ",j);
	 		// fflush(stdout);
	 	}
	 }
	 // printf("\n");
	 
	 // 
	 // printf("end of redundant_find : chromosome_set\n");
	int check_chromosome[Nodeno];
	for(i=0;i<Nodeno;i++){
		if(redundant_nodes[i]==1){
			check_chromosome[i]=0;
		}
		else{
			check_chromosome[i]=chromosome[i];
			// if(check_chromosome[i]==1){
			// 	printf("%d ",i);
			// }
		}
	}
	// printf("CHECK_POINT_3 : FINAL ONE\n");

	// printf("\nA*\n\n");	
	// check(Nodeno,check_chromosome,directed_graph,1,-1551,1);
	
	// sleep(2);
	return final_redundant_node_set;

//STAGE:3 END >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

}

