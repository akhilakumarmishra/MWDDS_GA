int* minimize_more_again(int outsider,int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int** adjacency_list,int** parent_nodes){
		// printf("ENter\n");
		int i,j,k=0; 
		int* new_chromosome_set=(int*)malloc(Nodeno*sizeof(int));

		for(i=0;i<Nodeno;i++){
			new_chromosome_set[i]=chromosome[i];
		}
		int repeat_loop=1;
		while(repeat_loop!=0){

				
			// check(Nodeno,new_chromosome_set,directed_graph,1,-600,1);
			int temp_chromosome[Nodeno];
			for(j=0;j<Nodeno;j++){
				temp_chromosome[j]=0;
			}
			int new_dominating_set[Nodeno];
			int new_dom_count=0;
			for(i=0;i<Nodeno;i++){
				temp_chromosome[i]=new_chromosome_set[i];
				if(new_chromosome_set[i]==1){
					new_dominating_set[new_dom_count]=i;
					new_dom_count++;
				}
			}
			// printf("X\n");
			//START CREATING CONNECTED LIST : a new adjacency list
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
					if(new_chromosome_set[ connected_list[k][l] ]==1){	
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
			// sleep(200);
			//CREATING CONNECTED LIST END
			//STAGE 2 BASIC END
			
			// printf("B\n");
			//START : REDUNDANT _FIND 

			int new_redundant_nodes[Nodeno];
			for(i=0;i<Nodeno;i++){
				new_redundant_nodes[i]=0;
			}
			for(i=0;i<new_dom_count;i++){
				if(new_dominating_set[i]!=outsider){
					int remove_node=new_dominating_set[i];
					// printf("remove_node: %d \n",remove_node);
					new_dominating_set[i]=-1;
					temp_chromosome[remove_node]=-1;
					int close_neightbour[Nodeno];
					// int open_neighbour[Nodeno];
					for(j=0;j<Nodeno;j++){
						close_neightbour[j]=0;
						// open_neighbour[j]=0;
					}				
					int close_count=0;
					close_count=connected_list[remove_node][0];
					for(j=1;j<close_count+1;j++){
						close_neightbour[j]=connected_list[remove_node][j];
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
						new_redundant_nodes[remove_node]=1;
						// printf("enter to remove_node : %d\n",remove_node);
					}
					else{
						new_dominating_set[i]=remove_node;
						temp_chromosome[remove_node]=1;
					}
				}
				
			}
			// printf("A\n");
			//END : REDUNDANT _FIND 	
			
			for(i=0;i<Nodeno;i++){
				free(connected_list[i]);
			}
			free(connected_list);

			int new_infeasible_chromosome_set[Nodeno];
			for(i=0;i<Nodeno;i++){
				if(new_redundant_nodes[i]==1 && new_chromosome_set[i]!=1){
					printf("#---------------ERROR------------#\n");fflush(stdout);
					sleep(10);
				}
				else if(new_redundant_nodes[i]==1 && new_chromosome_set[i]==1){
					new_infeasible_chromosome_set[i]=0;
				}
				else if(new_redundant_nodes[i]==0&&(new_chromosome_set[i]==1 || new_chromosome_set[i]==0)){
					new_infeasible_chromosome_set[i]=new_chromosome_set[i];
					// cx++;
				}
				else{
					printf("ERROR----->>%d has ODD VALUE:-  red:%d \tchromo:%d\n",i,new_redundant_nodes[i],new_chromosome_set[i]); fflush(stdout);sleep(10);
				}
			}
			// printf("\nnew_infeasible_chromosome_set:\n");
			// for(i=0;i<Nodeno;i++){
			// 	if(new_infeasible_chromosome_set[i]==1){
			// 		printf("%d ",i);
			// 	}
			// }
			// printf("\n");
			int* repaired_chromosome_set;
			repaired_chromosome_set=heurisitics_call(new_infeasible_chromosome_set,Nodeno,directed_graph,nodeweightarr,heuristics_number);
			// printf("\n repaired_chromosome_set:\n");
			// for(i=0;i<Nodeno;i++){
			// 	if(repaired_chromosome_set[i]==1){
			// 		printf("%d ",i);
			// 	}
			// }
			// printf("\n");
			check(Nodeno,repaired_chromosome_set,directed_graph,1,-500,1);
			int fitness_repaired_chromosome_set=0;
			for(i=0;i<Nodeno;i++){
				if(repaired_chromosome_set[i]==1)
					fitness_repaired_chromosome_set+=repaired_chromosome_set[i]*nodeweightarr[i];
			}
			int fitness_new_chromosome_set=0;
			for(i=0;i<Nodeno;i++){
				if(new_chromosome_set[i]==1)
					fitness_new_chromosome_set+=new_chromosome_set[i]*nodeweightarr[i];
			}
			
			check(Nodeno,repaired_chromosome_set,directed_graph,1,-100,1);
			if(fitness_repaired_chromosome_set<fitness_new_chromosome_set){
				repeat_loop=1;

				for(i=0;i<Nodeno;i++){
					new_chromosome_set[i]=repaired_chromosome_set[i];
				}
				// printf("CHECK_POINT_2 : in fitness compare:\n");
				check(Nodeno,new_chromosome_set,directed_graph,1,-2,1);
				

			}
			else{
				repeat_loop=0;
			}

		}

		return new_chromosome_set;

}