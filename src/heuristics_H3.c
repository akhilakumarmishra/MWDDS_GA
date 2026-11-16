int* heuristics_H3(int chromosome_repairing_3[],int Nodeno,int** directed_graph,int nodeweightarr[],int color[],int white_color_nodes){
	int i,j,k;
	int* chromosome=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		chromosome[i]=chromosome_repairing_3[i];
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
			
			
			
			for(k=0;k<Nodeno;k++){
				if(directed_graph[i][k]==1&&color[k]==1){
					color[k]=0;
					white_color_nodes--;
				}
			}
		}
	}			

	while(white_color_nodes>0){
		// printf("in_else_in_pop_gen\n");
				
		//*********************
		// printf("--->>start_while_color\n");
		// for(j=0;j<Nodeno;j++){
		// 	printf("%d ",color[j]);
		// }
		// printf("\n");
		// printf("white_color_nodes : %d\n",white_color_nodes);
		int white_successor_sum_arr[Nodeno]; //STORES THE W(u) = SUMESATION ( W(v) * CLR(v) ) values
		for(j=0;j<Nodeno;j++){
			int white_successor_sum=0; 
			for(k=0;k<Nodeno;k++){
				if(directed_graph[j][k]==1){ //there is connection u -> v
					white_successor_sum +=(nodeweightarr[k]*color[k]);                   //eq1
				}
			}
			white_successor_sum_arr[j]= white_successor_sum;

		}
		// printf("Ws(u) arr : \n");
		// for(j=0;j<Nodeno;j++){
		// 	printf("%d ",white_successor_sum_arr[j]);
		// }
		// printf("\n");
		//score
		float score_arr[Nodeno];
		for(j=0;j<Nodeno;j++){
			score_arr[j]=((float)white_successor_sum_arr[j] + ( (float)nodeweightarr[j] * (float)color[j] ) ) / (float)nodeweightarr[j];         //eq2
		}
		// printf("score(u) arr : \n");
		// for(j=0;j<Nodeno;j++){
		// 	printf("%.2f ",score_arr[j]);
		// }
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
		//tie rule
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
		// printf("1st_v_index:%d,  no_of_max_scores:%d\n",v_index,no_of_max_scores);
		// printf("max_score_arr:1 :%f\n",max_score);
		// for(j=0;j<k;j++){
		// 	printf("%d ",max_score_arr[j]);
		// }
		// printf("\n");
		int white_count=0;
		for(j=0;j<k;j++){
			if(color[max_score_arr[j]]==1){
				white_count++;
			}
		}
		if(no_of_max_scores>1){
			if(white_count>0){
				int l;
				int in_degree_arr[Nodeno];
				int in_degree_node[Nodeno];
				for(j=0;j<k;j++){
					in_degree_arr[j]=0;
					in_degree_node[j]=0;
				}
				int m=0;
				for(j=0;j<k;j++){
					// printf("color[] =%d\n",color[max_score_arr[j]]);
					if(color[max_score_arr[j]]==1){
						int in_degree_child =0;
						for(l=0;l<Nodeno;l++){
							if(directed_graph[l][max_score_arr[j]]==1){
								in_degree_child += 1;										
							}
						}
						in_degree_arr[m]=in_degree_child;
						in_degree_node[m] =max_score_arr[j] ;
						m++;
					}
				}
				// printf("\nin_degree_arr\n");
				// for(j=0;j<m;j++){
				// 	printf("%d ",in_degree_arr[j]);
				// }
				// printf("\n");
				// printf("\nin_degree_node\n");
				// for(j=0;j<m;j++){
				// 	printf("%d ",in_degree_node[j]);
				// }
				// printf("\n");
				int min_score_tie= in_degree_arr[0];
				int v_index_tie = in_degree_node[0];
				for(j=0;j<m;j++){
					if(in_degree_arr[j] < min_score_tie){
						min_score_tie = in_degree_arr[j];													
						v_index_tie = in_degree_node[j];
					}
				}
				int min_score_counter=0;
				l=0;
				int second_tie_score_arr[Nodeno];
				for(j=0;j<m;j++){
					if(min_score_tie == in_degree_arr[j]){
						second_tie_score_arr[l]=in_degree_node[j];
						min_score_counter++;
						l++;
					}
				}

				if(min_score_counter>1){
					int random_point=(u01 * min_score_counter);
					v_index_final = second_tie_score_arr[random_point];
				}
				else{
					v_index_final = v_index_tie;
				}
							
			}
			else{
				int random_grey=(u01*no_of_max_scores);
				v_index_final=max_score_arr[random_grey];
			}
						
		}
		else{
			v_index_final = v_index;
		}
					
		// printf("v_index_final : %d\n",v_index_final);
		//----
					
		chromosome[v_index_final]=1;
		if(color[v_index_final]==1){
			white_color_nodes--;
		}
		color[v_index_final]=0;
		for(j=0;j<Nodeno;j++){
			if(directed_graph[v_index_final][j]==1){
				if(color[j]!=0){
					// printf("%d's neighbour:%d\n",v_index_final,j);
					color[j]=0; 		//grey color
					white_color_nodes--;
				}
			}
						
		}
		// printf("white_color_nodes:%d\n",white_color_nodes);
		// printf("color_in_while\n");
		// for(j=0;j<Nodeno;j++){
		// 	printf("%d ",color[j]);
		// }
		// printf("\n\n\n");
	}
	return chromosome;
}
		