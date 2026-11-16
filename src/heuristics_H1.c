int* heuristics_H1(int chromosome_repairing_1[],int Nodeno,int** directed_graph,int nodeweightarr[],int color[],int white_color_nodes){	
	// printf("************ENTER TO heuristics_H1*************\n");
	int j,k,i;
	int* chromosome=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		chromosome[i]=chromosome_repairing_1[i];
	}

	
	while(white_color_nodes>0){
		
		int white_successor_sum_arr[Nodeno]; //STORES THE W(u) = SUMESATION ( W(v) * CLR(v) ) values
		for(j=0;j<Nodeno;j++){
			white_successor_sum_arr[j]=0;
		}
		for(j=0;j<Nodeno;j++){
			if(chromosome[j]==0){
				int white_successor_sum=0;
				// printf("connection of %d :",j); 
				for(k=0;k<Nodeno;k++){
					if(directed_graph[j][k]==1){ //there is connection u -> v
						// printf("%d ",k);
						white_successor_sum +=(nodeweightarr[k]*color[k]);                   //eq1
					}
				}
				// printf("\n");
				white_successor_sum_arr[j]= white_successor_sum;
			}

		}
		// printf(">>> Eq1: white_successor_sum_arr:[Ws(u)]\n");
		// for(int i=0;i<Nodeno;i++){
		// 	printf("%d ",white_successor_sum_arr[i] );
		// 	fflush(stdout);
		// }
		// printf("\n");
		//score
		float score_arr[Nodeno];
		for (int i = 0; i < Nodeno; i++){
			score_arr[i]=0;
		}
		for(j=0;j<Nodeno;j++){
			score_arr[j]=((float)white_successor_sum_arr[j] + ( (float)nodeweightarr[j] * (float)color[j] ) ) / (float)nodeweightarr[j];         //eq2
		}
		// printf(">>> Eq2: score_arr : score(u)\n");
		// for(int i=0;i<Nodeno;i++){
			// printf("%f ",score_arr[i] );
			// fflush(stdout);
		// }
		// printf("\n");
		// printf("\n");
		float max_score = 0;
		int v_index_final;
		int v_index=0;
		for(j=0;j<Nodeno;j++){
			if(chromosome[j]!=1 && score_arr[j]>max_score ){
				max_score = score_arr[j];													//eq3
				v_index = j;
			}
		}
		// printf("max_score : %f\n",max_score);
		// printf("v_index: %d\n",v_index);

		int max_score_arr[Nodeno];
		int no_of_max_scores=0;
		k=0;
		for(j=0;j<Nodeno;j++){
			if(max_score ==score_arr[j]){
				no_of_max_scores++;
				max_score_arr[k]=j;
				k++;
			}
		}
			
		int WOUT_degree_child_arr[Nodeno];
		for (j = 0; j < Nodeno ; j++){
			WOUT_degree_child_arr[j]=0;
		}
		// printf("no_of_max_scores:%d\n",no_of_max_scores);
		if(no_of_max_scores>1){

			if(u01<0.8){

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
				// printf("WOUT_degree_child_arr:\n");
				// for(j=0;j<k;j++){
					// printf("%d ",WOUT_degree_child_arr[j]);
				// }		
				// printf("\n");
				
				float score_tie_arr[Nodeno];
				for(j=0;j<k;j++){
					score_tie_arr[j]=((float)WOUT_degree_child_arr[j] + (float)color[max_score_arr[j]] ) / (float)nodeweightarr[max_score_arr[j]];         //eq5
				}
				// printf("Eq5: score_tie_arr : [ SCOREtie(u) ]\n");
				// for(j=0;j<k;j++){
				// 	printf("%f ",score_tie_arr[j]);
				// }		
				// printf("\n");
				
				

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
			}
			else{
				int random_point = u01*no_of_max_scores;
				v_index_final=max_score_arr[random_point];
			}
			// printf("first_tie_enter\n");
			
					

						
		}
		else{
			v_index_final = v_index;
		}
		// printf("v_index_final:%d\n",v_index_final );		
		//----
				
		chromosome[v_index_final]=1;
		if(color[v_index_final]==1){
					
			white_color_nodes--;
		}
		// for(int i=0;i<Nodeno;i++){
		// 	printf("%d ",color[i] );
		// 	fflush(stdout);
		// }
		// printf("\n");
		color[v_index_final]=0;	
		// for(int i=0;i<Nodeno;i++){
		// 	printf("%d ",color[i] );
		// 	fflush(stdout);
		// }
		// printf("\n");
		for(j=0;j<Nodeno;j++){
			if(directed_graph[v_index_final][j]==1){
				if(color[j]!=0){
					color[j]=0; 		//grey color
					white_color_nodes--;
				}
			}
					
		}
		// for(int i=0;i<Nodeno;i++){
		// 	printf("%d ",color[i] );
		// 	fflush(stdout);
		// }
		// printf("\n");
	}
	// sleep(10);
	return chromosome;
}