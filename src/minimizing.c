// int global_redundant_count=0;
int* neighbour_redundants_finds(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int** adjacency_list,int** parent_nodes){
	// printf("ENTER to  neighbour_redundants_finds\n");
// STAGE:1 : start >>>>>>>>>>>>>>>>>>>>>	
	int i,j,k=0; 
	int dom_count=0;
	int dominating_set_node[Nodeno];
	for(j=0;j<Nodeno;j++){
		dominating_set_node[j]=0;
	}
	// printf("##############************############\nstage1: chromosome_redundant\n");
	// printf("chromosome:\n");
	// for(i=0;i<Nodeno;i++){
	// 	if(chromosome[i]==1){
	// 		printf("%d ",i);
	// 	}
	// }
	// printf("\n");
	int temp_chromosome[Nodeno];
	for(j=0;j<Nodeno;j++){
		temp_chromosome[j]=0;
	}
	// check(Nodeno,chromosome,directed_graph,1,-1000,2);
	for(i=0;i<Nodeno;i++){
		temp_chromosome[i]=chromosome[i];
		if(chromosome[i]==1){
			dominating_set_node[dom_count]=i;
			dom_count++;
		}
	}
	
	// printf("temp_chromosome_1\n");
	// for(i=0;i<Nodeno;i++){
	// 	printf("%d ",temp_chromosome[i]);
	// }
	// printf("\n");
	// for(i=0;i<dom_count;i++){
	// 	printf("%d ",dominating_set_node[i]);
	// }
	// printf("\n");
	// sleep(2);

	int redundant_nodes[Nodeno];
	for(i=0;i<Nodeno;i++){
		redundant_nodes[i]=0;
	}
	for(i=0;i<dom_count;i++){
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
	/*
	int sleeper=0;
	for(i=0;i<Nodeno;i++){
		redundant_nodes[i]=0;
		if(new_chromosome_set[i]==0){
			redundant_nodes[i]=1;
		}
		else if(chromosome[i]==0&&new_chromosome_set[i]==1){
			printf("#^^^^^^^^^^^-----ERROR: immpossible happen at %d-----^^^^^^^^^^#\n",i);fflush(stdout);sleeper=1;
		}
		else if(chromosome[i]!=0 &&chromosome[i]!=1 || new_chromosome_set[i]!=1 && new_chromosome_set[i]!=0){
			printf("MEMORY PROBLEM at %d: chromosome:%d \tnew_chromosome_set:%d \n",i,chromosome[i],new_chromosome_set[i]);fflush(stdout);sleeper=1;
		}
	}
	 
	*/
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
	// check(Nodeno,check_chromosome,directed_graph,1,-300,1);
	
	// sleep(2);
	return final_redundant_node_set;

//STAGE:3 END >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

}


int* minimization(int chromosome[],int Nodeno,int** diagraph,int nodeweightarr[],int** adjacency_list,int** parent_nodes){
	// printf("\n\t\t***ENTER TO MINIMIZATION***\n");
	int i,j;
	// printf("---++\n");
	for(i=0;i<Nodeno;i++){
		// printf("%d ",chromosome[i]);
		if(chromosome[i]!=1&&chromosome[i]!=0){
				printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",i,chromosome[i]); fflush(stdout);sleep(10);
			}
	}
	int loop_counter=0;
	int* redundant_nodes;
	// int permission_entry_stage2=1;
	redundant_nodes = neighbour_redundants_finds(chromosome,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	// redundant_nodes = redundant_finds_again(chromosome,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	int count=0;
	// global_redundant_count=count;
	for(i=0;i<Nodeno;i++){
		// printf("%d ",redundant_nodes[i]);
		if(redundant_nodes[i]==1){
			count++;
			
		}
	}

	int new_chromosome_set[Nodeno];
	for(i=0;i<Nodeno;i++){
		if(redundant_nodes[i]==1){
			new_chromosome_set[i]=0;
		}
		else{
			new_chromosome_set[i]=chromosome[i];
		}
	}
	// printf("\n\n\n");
	// for(i=0;i<Nodeno;i++){
	// 	printf("%d ",new_chromosome_set[i]);
	// }
	// printf("\n\n\n");
	// check(Nodeno,new_chromosome_set,diagraph,1,-900,1);
	int* chromosome_stage_one;
	chromosome_stage_one=minimize_more(new_chromosome_set,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
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
	//**********************************
	// // printf("count_one_1:%d\n",count_one );
	// int* chromosome_stage_x;
	// int fitter_1=0;
	// chromosome_stage_x=minimize_more(chromosome,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	
	//********************************************************
	// for(i=0;i<Nodeno;i++){
	// 	if(chromosome_stage_one[i]==1){
	// 		fitter_1+=nodeweightarr[i]*chromosome_stage_one[i];
	// 	}
	// }
	// redundant_nodes_x=neighbour_redundants_finds(chromosome_stage_one,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
	// int count_one_x=0;
	// // global_redundant_count=count;
	// for(i=0;i<Nodeno;i++){
	// 	// printf("%d ",redundant_nodes[i]);
	// 	if(redundant_nodes_x[i]==1){
	// 		count_one_x++;
			
	// 	}
	// }
	// // printf("count_one_2:%d\n",count_one_x );
	
//****************************************	
	// check(Nodeno,chromosome_stage_one,diagraph,1,-1234,1);
	

	// int second_count=0;
	// int redundant_nodes_one[Nodeno];
	// for(i=0;i<Nodeno;i++){
	// 	redundant_nodes_one[i]=0;
	// 	if(new_chromosome_set[i]==1&& chromosome_stage_one[i]==0){
	// 		redundant_nodes_one[i]=1;
	// 		second_count++;
	// 	}

	// }
	int visited_chromosome_set[Nodeno];
	for(i=0;i<Nodeno;i++){
		visited_chromosome_set[i]=0;
		if(chromosome[i]==1){
			visited_chromosome_set[i]=1;
		}
		else if(chromosome[i]==0 && chromosome_stage_one[i]==1){
			visited_chromosome_set[i]=1;
			// printf(":::::::::::::::::::::::::Non_dom to dom:%d,",i);
		}
		else{
			visited_chromosome_set[i]=0;
		}
	}
	// if(second_count>0){
	// 	printf("YES some nodes are redundant_nodes : count:%d\n",second_count);
	// 	fflush(stdout);
	// 	sleep(1);
	// }



	int counter_x=0;
	int final_redundant_nodes[Nodeno];
	for(i=0;i<Nodeno;i++){
		final_redundant_nodes[i]=0;
		if(chromosome_stage_one[i]==0 && visited_chromosome_set[i]==1){
			final_redundant_nodes[i]=1;
			counter_x++;
		}
		// //***********trail**************
		// if(selective_non_doms[i]==1){
		// 	final_redundant_nodes[i]=1;
		// 	counter_x++;
		// }
		// //**************end************
	}
	int final_chromosome_set[Nodeno];
	for(i=0;i<Nodeno;i++){
		final_chromosome_set[i]=chromosome_stage_one[i];
	}
	count=counter_x;
	// printf("count:%d\n final_redundant_nodes:\n",counter_x );
	// for(i=0;i<Nodeno;i++){
	// 	if(final_redundant_nodes[i]==1){
	// 		printf("%d ",i);
	// 	}
	// }
	// printf("\nfinal_chromosome_set:\n");
	// for(i=0;i<Nodeno;i++){
	// 	if(final_chromosome_set[i]==1){
	// 		printf("%d ",i);
	// 	}
	// }
	// printf("\n");
	

	if(count>0){
		//second stage
		int outdegree[Nodeno];
		int* out_deg=outdegree_calculation(Nodeno,diagraph);
		for(i=0;i<Nodeno;i++){
			outdegree[i]=out_deg[i];
		}
		
		loop_counter=0;
		// int outdegree[Nodeno];
		// int* out_deg=outdegree_calculation(Nodeno,diagraph);
		// for(i=0;i<Nodeno;i++){
		// 	outdegree[i]=out_deg[i];
		// }
		// float ratio_arr[Nodeno];
		// for(i=0;i<Nodeno;i++){
		// 	ratio_arr[i]=-1;
		// }
					
		// // printf("\n\nredundant_nodes_in_stage:2\n");
		// for(i=0;i<Nodeno;i++){
		// 	// printf("%d ",redundant_nodes[i]);
		// 	if(final_redundant_nodes[i]==1){
		// 		ratio_arr[i]= (float)outdegree[i] / (float)nodeweightarr[i];
		// 		// printf("%d th ratio=%f\n",i,ratio_arr[i]);
		// 		// fflush(stdout);
		// 	}
		// }
		int xt=count;
		while(count!=0 ){
			int final_redundant;
			
			///**************************	
			// float minp=u01;	
			// printf("2\n");
			
			// if(minp<minimize_prob){
			//*******************************	
				//ratio calculation
				// printf("inmin\n");

				
				float ratio_arr[Nodeno];
				for(i=0;i<Nodeno;i++){
					ratio_arr[i]=-1;
				}
							
				// printf("\n\nredundant_nodes_in_stage:2\n");
				for(i=0;i<Nodeno;i++){
					// printf("%d ",redundant_nodes[i]);
					if(final_redundant_nodes[i]==1){
						ratio_arr[i]= (float)outdegree[i] / (float)nodeweightarr[i];
						// printf("%d th ratio=%f\n",i,ratio_arr[i]);
						// fflush(stdout);
					}
				}

				
				// //sleep(5);
				//max ratio redundant node
				float max_ratio=ratio_arr[0];
				int max_ratio_index=0;
				for(i=1;i<Nodeno;i++){
					if(final_redundant_nodes[i]==1&&ratio_arr[i]>max_ratio){
						max_ratio=ratio_arr[i];
						max_ratio_index = i;
					}
				}
				// int same_max_nodes[Nodeno];
				// int same_max=0;
				// int low_weight_node;
				// int less_weight=10000;
				// for(i=0;i<Nodeno;i++){
				// 	if(max_ratio==ratio_arr[i]){
				// 		same_max_nodes[same_max]=i;
				// 		if(nodeweightarr[i]<less_weight){
				// 			less_weight=nodeweightarr[i];
				// 			low_weight_node=i;
				// 		}
				// 		// printf("node:%d\t-->> nodeweight:%d\toutdegree:%d\n",i,nodeweightarr[i],outdegree[i] );
				// 		same_max++;
				// 	}
				// }
				// max_ratio_index=low_weight_node;
				// printf("---------chosen:%d\n",max_ratio_index);
				// if(same_max>1){
				// 	int random_n=(int)(u01*same_max);
				// 	int max_ratio_index=same_max_nodes[random_n];
				// }

				final_redundant=max_ratio_index;
				// mr_index_arr[mr]=final_redundant;
				// mr++;
				

				// printf("\nmax_ratio_index:%d\tmax_ratio:%f\n",max_ratio_index,max_ratio );
				
			//****************************		V
			// }
			// else{
				
			// 	int red_num=0;
			// 	int red_set[Nodeno];
			// 	for(i=0;i<Nodeno;i++){
			// 		if(redundant_nodes[i]==1){
			// 			red_set[red_num]=i;
			// 			red_num++;
			// 		}
			// 	}
			// 	int random=(u01*red_num);
			// 	final_redundant=red_set[random];


			// }
			//********************************	A
			// printf("chromosome checker_point\n");
			// for(i=0;i<Nodeno;i++){
			// 	if(chromosome[i]==1)printf("%d ",i);
			// }
			int fitness_chromosome_one=0;	
			for(i=0;i<Nodeno;i++){
				if(final_chromosome_set[i]==1)
					fitness_chromosome_one+=final_chromosome_set[i]*nodeweightarr[i];
			}	
			final_chromosome_set[final_redundant]=1;
			final_redundant_nodes[final_redundant]=0;
			// printf("\n\t\t*** #%d :STAGE-2 TO redundants_finds***\n",loop_counter);
			// loop_counter;
			int c =0;
			// printf("3hello\n");
			int *R;
			// printf("\n\n\n>>>>>>>>>>>>>>>>>>>>>>\n---->  second_redundant_set: \n");
			
			// int temp_redundant_nodes[Nodeno];
			// for(i=0;i<Nodeno;i++){
			// 	temp_redundant_nodes[i]=redundant_nodes[i];
			// }
			//***************
			

			R= redundants_finds_fixed_outsider(final_redundant,final_chromosome_set,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);
			// R= minimize_more_again(final_redundant,final_chromosome_set,Nodeno,diagraph,nodeweightarr,adjacency_list,parent_nodes);


			//***************
			// for(i=0;i<Nodeno;i++){
			// 	redundant_nodes[i]=R[i];
			// 	if(redundant_nodes[i]==1){
			// 		c++;
			// 		// printf("%d ",i);
			// 	}
			// }
			
			int new_chromosome_list[Nodeno];
			for(i=0;i<Nodeno;i++){
				//new_chromosome_list[i]=R[i];
				if(R[i]==1){
					new_chromosome_list[i]=0;
				}
				else{
					new_chromosome_list[i]=final_chromosome_set[i];
				}
			}
			int new_fitness=0;
			for(i=0;i<Nodeno;i++){
				if(new_chromosome_list[i]==1)
					new_fitness+=new_chromosome_list[i]*nodeweightarr[i];
			}
			if(new_fitness<fitness_chromosome_one){
				
				for(i=0;i<Nodeno;i++){
					final_chromosome_set[i]=new_chromosome_list[i];
				}
				// printf("Yes better better...new fitness:= %d better than old fitness:=%d\n",new_fitness,fitness_chromosome_one);fflush(stdout);
				// printf("new added node:%d\tredundants:",final_redundant);
				// for(i=0;i<Nodeno;i++){
				// 	if(R[i]==1){
				// 		printf("%d",i );
				// 	}
				// }
				// printf("\n");
				// sleep(2);
			}
			else{
				final_chromosome_set[final_redundant]=0;

			}


			
			count =count-1;
			loop_counter++;
			free(R);
			

			

		}
		free(out_deg);
		// printf("5\n");
		// printf("\nend of minimization\n");
	}
	free(redundant_nodes);






	int* last_chromosome=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		last_chromosome[i]=0;
	}
	//*****************************************
	// if(fitness_chromosome_one>fitness_chromosome_two){

	// 	for(i=0;i<Nodeno;i++){
	// 		last_chromosome[i]=chromosome_stage_two[i];//final_chromosome_set[i];
	// 		// if(last_chromosome[i]==1){
	// 		// 	printf("%d ",i);
	// 		// }
	// 	}
	// 	// printf("\n");
	// }
	// else{
	// 	for(i=0;i<Nodeno;i++){
	// 		last_chromosome[i]=final_chromosome_set[i];
	// 		// if(last_chromosome[i]==1){
	// 		// 	printf("%d ",i);
	// 		// }
	// 	}
	// 	// printf("\n");
	// }
	//**************************************************
	for(i=0;i<Nodeno;i++){
		last_chromosome[i]=final_chromosome_set[i];
		// if(last_chromosome[i]==1){
		// 	printf("%d ",i);
		// }
	}
		// printf("\n");
	// int min_chromosome_fitness=0;
	// for(j=0;j<Nodeno;j++){
	// 	min_chromosome_fitness+=nodeweightarr[j]*last_chromosome[j];
	// }
	// printf("fitness:%d\n",min_chromosome_fitness);
	// for(i=0;i<Nodeno;i++){
	// 	if(last_chromosome[i]==1){
	// 		printf("adjacency of %d --->",i);
	// 		for(j=0;j<Nodeno;j++){
	// 			if(diagraph[i][j]==1){
	// 				printf("%d,",j );
	// 			}
	// 		}
	// 		printf("\nparents of %d <---",i);
	// 		for(j=0;j<Nodeno;j++){
	// 			if(diagraph[j][i]==1){
	// 				printf("%d,",j );
	// 			}
	// 		}
	// 		printf("\n");
	// 	}

	// }
	// sleep(30);
	for(i=0;i<Nodeno;i++){
		// printf("%d ",last_chromosome[i]);
		if(last_chromosome[i]!=1&&last_chromosome[i]!=0){
			printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",i,last_chromosome[i]); fflush(stdout);sleep(10);
		}
	}
	return last_chromosome;
	
	

}
