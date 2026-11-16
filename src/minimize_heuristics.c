int minimize_heuristics(int redundant_nodes[],int Nodeno,int** directed_graph,int nodeweightarr[]){
	int i,j,k,redundant_count=0;
	int index_pt;
	// printf("  in_min_heuristics: \n");
	for(i=0;i<Nodeno;i++){
		if(redundant_nodes[i]==1){
			index_pt=i;
			redundant_count++;
			// printf("%d ",i );
			// fflush(stdout);
		}
		
	}
	// printf("\n");

	// printf("\n");
	// for(int i=0;i<Nodeno;i++){
	// 	printf("%d ",nodeweightarr[i] );
	// 	fflush(stdout);
	// }
	// printf("\n");
	// for(int i=0;i<Nodeno;i++){
	// 	printf("%d ",color[i] );
	// 	fflush(stdout);
	// }
	// printf("\n");
	// sleep(20);
	int color[Nodeno];
	for(i=0;i<Nodeno;i++){
		color[i]=1;
	}
	// int no_of_redundant=0;
	// int redundant_nodes_set[Nodeno];
	for(i=0;i<Nodeno;i++){
		if(redundant_nodes[i]==1){

			color[i]=0;
			for(j=0;j<Nodeno;j++){
				if(i!=j&&directed_graph[i][j]==1){
					color[j]=0;
				}
			}
		}
	}

	if(redundant_count>1){
		int white_successor_sum_arr[Nodeno]; //STORES THE W(u) = SUMESATION ( W(v) * CLR(v) ) values
		for(j=0;j<Nodeno;j++){
			white_successor_sum_arr[j]=0;
		}
		for(j=0;j<Nodeno;j++){
			if(redundant_nodes[j]==1){
				int white_successor_sum=0;
				// printf("connection of %d :",j); 
				for(k=0;k<Nodeno;k++){
					if(directed_graph[j][k]==1){ //there is connection u -> v
						// printf("%d ",k);
						white_successor_sum +=(nodeweightarr[k]/* *color[k]  */);                   //eq1
					}
				}
				// printf("\n");
				white_successor_sum_arr[j]= white_successor_sum;
			}

		}
		//score
		float score_arr[Nodeno];
		for (int i = 0; i < Nodeno; i++){
			score_arr[i]=0;
		}
		for(j=0;j<Nodeno;j++){
			score_arr[j]=((float)white_successor_sum_arr[j] /* + ( (float)nodeweightarr[j] * (float)color[j] )  */ ) / (float)nodeweightarr[j];         //eq2
		}

		float max_score = 0;
		int v_index_final;
		int v_index=0;
		for(j=0;j<Nodeno;j++){
			// if(redundant_nodes[j]==1){
			// 	printf(":-> %d 	%f 		%d\n",j,score_arr[j],white_successor_sum_arr[j]);
			// }
			
			if(redundant_nodes[j]==1 && score_arr[j]>max_score ){
				max_score = score_arr[j];													//eq3
				v_index = j;
				// printf("v_index: %d 	%f\n",v_index,score_arr[j]);
			}
		}

		int max_score_arr[Nodeno];
		int no_of_max_scores=0;
		k=0;
		for(j=0;j<Nodeno;j++){
			if(max_score ==score_arr[j] && redundant_nodes[j]==1){
				no_of_max_scores++;
				max_score_arr[k]=j;
				k++;
			}
		}
				
		int WOUT_degree_child_arr[Nodeno];
		for (j = 0; j < Nodeno ; j++){
			WOUT_degree_child_arr[j]=0;
		}

		if(no_of_max_scores>1){
			// if(u01<0.5){
				int l;
				for(j=0;j<k;j++){
					int WOUT_degree_child =0;
					for(l=0;l<Nodeno;l++){
						if(directed_graph[max_score_arr[j]][l]==1){
							WOUT_degree_child += color[l];											//eq4
						}
					}
					WOUT_degree_child_arr[j]=WOUT_degree_child;
				}
					
				float score_tie_arr[Nodeno];
				for(j=0;j<k;j++){
					score_tie_arr[j]=((float)WOUT_degree_child_arr[j] + (float)color[max_score_arr[j]] ) / (float)nodeweightarr[max_score_arr[j]];         //eq5
				}
				float max_score_tie= 0;
				int v_index_tie = 0;
				for(j=0;j<k;j++){
					if(score_tie_arr[j]>max_score_tie){
						max_score_tie = score_tie_arr[j];													//eq6
						v_index_tie = max_score_arr[j];
					}
				}
								
				int max_score_counter=0;
				l=0;
				int second_tie_score_arr[Nodeno];
				int max_score_tie_second[Nodeno];
				for(j=0;j<k;j++){
					if(max_score_tie==score_tie_arr[j]){
						second_tie_score_arr[l]=max_score_arr[j];
						max_score_counter++;
						l++;
										
					}
				}

				if(max_score_counter>1){
					int random_point=(u01*max_score_counter);
					v_index_final = second_tie_score_arr[random_point];
				}
				else{
					v_index_final = v_index_tie;
				}


				//xxxxx	
			// }
			// else{
			// 	int random_point = u01*no_of_max_scores;
			// 	v_index_final=max_score_arr[random_point];
			// }
				// printf("first_tie_enter\n");
				
						

							
		}
		else{
			v_index_final = v_index;
		}
			


		return v_index_final;
	}
	else{
		return index_pt;
	}


	

}


	
		
