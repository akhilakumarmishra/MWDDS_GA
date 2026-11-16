int* repairing(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[]){
	int* color = (int*)malloc(Nodeno*sizeof(int));
	int i,j;
	
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
	int k;
//	float Ph=0.6;
	float p =u01;
	float pp =u01;
	//float PPh=0.4;
	if(pp < PPh){
		//if(p < Ph){

			printf("in_if_in_pop_gen\n");
			//int request=0;
			while(white_color_nodes>0){
				printf("in_if_in_pop_gen\n");
			/*	for(j=0;j<Nodeno;j++){
					if(color[j]==1){
						printf("special node:%d ",j);
						int white_successor_count=0;
						int non_black_predecessor_count=0;
						int non_black_predecessor_pos =0;
						for(k=0;k<Nodeno;k++){
							if(directed_graph[j][k]==1 && color[k]==1){
								white_successor_count++;
							}
							if(directed_graph[k][j]==1 && color[k]==0){
								non_black_predecessor_count++;
								non_black_predecessor_pos=k;

							}
						}
						printf("white_successor_count=%d  non_black_predecessor_count=%d\n",white_successor_count,non_black_predecessor_count);
						if(white_successor_count==0 && non_black_predecessor_count==1){
							printf("congulation enter\n");
							float score_of_single_node= 1;
							int ws_non_black_predecessor=0;
							int l;
							for(l=0;l<Nodeno;l++){
								if(directed_graph[non_black_predecessor_pos][l]==1){
									ws_non_black_predecessor+= nodeweightarr[l]*color[l];
								}
							}
							float score_of_single_predecessor = (float)ws_non_black_predecessor/(float)nodeweightarr[non_black_predecessor_pos];
							if(score_of_single_predecessor >= score_of_single_node){
								chromosome[non_black_predecessor_pos]=1;
								color[non_black_predecessor_pos]=0;
								int m;
								for(m=0;m<Nodeno;m++){
									if(directed_graph[non_black_predecessor_pos][m]==1){
										if(color[m]==1){
											color[m]=0;
											white_color_nodes--;
										}
									}
								}

							}
							else{
								chromosome[j]=1;
								color[j]=0;
								white_color_nodes--;
							}
						}

					}
				}
			*/
				//*********************
				printf("--->>start_while_color\n");
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
				int WOUT_degree_child_arr[Nodeno];
				for (j = 0; j < Nodeno ; j++){
					WOUT_degree_child_arr[j]=0;
				}
				if(no_of_max_scores>1){
					// printf("first_tie_enter\n");
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
					// printf("WOUT_degree_child\n");
					// for(j=0;j<k;j++){
					// 	printf("%d ",WOUT_degree_child_arr[j] );
					// }
						
					// printf("\n");
					float score_tie_arr[Nodeno];
					for(j=0;j<k;j++){
						score_tie_arr[j]=((float)WOUT_degree_child_arr[max_score_arr[j]] +  (float)color[max_score_arr[j]] ) / (float)nodeweightarr[max_score_arr[j]];         //eq5
					}

					// printf("score_tie_arr\n");
					// for(j=0;j<k;j++){
					// 	printf("%.2f ",score_tie_arr[j] );
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
						

						
				}
				else{
					// printf("only_one_max_no_tie\n");
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
			}//

	/*	}
		else{
			while(white_color_nodes>0){
				printf("in_else_in_pop_gen\n");
				for(j=0;j<Nodeno;j++){
					if(color[j]==1){
						printf("special node:%d ",j);
						int white_successor_count=0;
						int non_black_predecessor_count=0;
						int non_black_predecessor_pos =0;
						for(k=0;k<Nodeno;k++){
							if(directed_graph[j][k]==1 && color[k]==1){
								white_successor_count++;
							}
							if(directed_graph[k][j]==1 && color[k]==0){
								non_black_predecessor_count++;
								non_black_predecessor_pos=k;

							}
						}
						printf("white_successor_count=%d  non_black_predecessor_count=%d\n",white_successor_count,non_black_predecessor_count);
						if(white_successor_count==0 && non_black_predecessor_count==1){
							printf("congulation enter\n");
							float score_of_single_node= 1;
							int ws_non_black_predecessor=0;
							int l;
							for(l=0;l<Nodeno;l++){
								if(directed_graph[non_black_predecessor_pos][l]==1){
									ws_non_black_predecessor+= nodeweightarr[l]*color[l];
								}
							}
							float score_of_single_predecessor = (float)ws_non_black_predecessor/(float)nodeweightarr[non_black_predecessor_pos];
							if(score_of_single_predecessor >= score_of_single_node){
								chromosome[non_black_predecessor_pos]=1;
								color[non_black_predecessor_pos]=0;
								int m;
								for(m=0;m<Nodeno;m++){
									if(directed_graph[non_black_predecessor_pos][m]==1){
										if(color[m]==1){
											color[m]=0;
											white_color_nodes--;
										}
									}
								}

							}
							else{
								chromosome[j]=1;
								color[j]=0;
								white_color_nodes--;
							}
						}

					}
				}
				//*********************
				printf("--->>start_while_color\n");
				for(j=0;j<Nodeno;j++){
					printf("%d ",color[j]);
				}
				printf("\n");
				printf("white_color_nodes : %d\n",white_color_nodes);
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
				printf("Ws(u) arr : \n");
				for(j=0;j<Nodeno;j++){
					printf("%d ",white_successor_sum_arr[j]);
				}
				printf("\n");
				//score
				float score_arr[Nodeno];
				for(j=0;j<Nodeno;j++){
					score_arr[j]=((float)white_successor_sum_arr[j] + ( (float)nodeweightarr[j] * (float)color[j] ) ) / (float)nodeweightarr[j];         //eq2
				}
				printf("score(u) arr : \n");
				for(j=0;j<Nodeno;j++){
					printf("%.2f ",score_arr[j]);
				}
				printf("\n");
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
				printf("1st_v_index:%d,  no_of_max_scores:%d\n",v_index,no_of_max_scores);
				printf("max_score_arr:1 :%f\n",max_score);
				for(j=0;j<k;j++){
					printf("%d ",max_score_arr[j]);
				}
				printf("\n");
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
							printf("color[] =%d\n",color[max_score_arr[j]]);
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
						printf("\nin_degree_arr\n");
						for(j=0;j<m;j++){
							printf("%d ",in_degree_arr[j]);
						}
						printf("\n");
						printf("\nin_degree_node\n");
						for(j=0;j<m;j++){
							printf("%d ",in_degree_node[j]);
						}
						printf("\n");
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
					
				printf("v_index_final : %d\n",v_index_final);
				//----
					
				chromosome[v_index_final]=1;
				if(color[v_index_final]==1){
					white_color_nodes--;
				}
				color[v_index_final]=0;
				for(j=0;j<Nodeno;j++){
					if(directed_graph[v_index_final][j]==1){
						if(color[j]!=0){
							printf("%d's neighbour:%d\n",v_index_final,j);
							color[j]=0; 		//grey color
							white_color_nodes--;
						}
					}
						
				}
				printf("white_color_nodes:%d\n",white_color_nodes);
				printf("color_in_while\n");
				for(j=0;j<Nodeno;j++){
					printf("%d ",color[j]);
				}
				printf("\n\n\n");
			}//

		}
	*/
	}
	else{
		printf("REPAIRING : random_node_repair\n");
			
			int kk=0;
			int non_dominated_nodes_set[Nodeno];
			for(j=0;j<Nodeno;j++){
				if(chromosome[j]==0){
					non_dominated_nodes_set[kk]=j;
					kk++;
				}
			}
			while(white_color_nodes!=0){
				printf("in_while_in_else\n");
				int random_node = (int)(u01*kk);
				printf("random_node : %d\n",random_node);
				// printf(".\n");
				if(color[non_dominated_nodes_set[random_node]]==1){
					white_color_nodes--;
				}
				color[non_dominated_nodes_set[random_node]]=0;
				int rand_node_pos = non_dominated_nodes_set[random_node];
				chromosome[non_dominated_nodes_set[random_node]]=1;
				// printf(".\n");
				
				// printf(".\n");
				
				// printf(".\n");
				for(j=random_node;j<kk;j++){
					non_dominated_nodes_set[j]=non_dominated_nodes_set[j+1];
				}
				printf(".\n");
				kk =kk-1;
				for(j=0;j<Nodeno;j++){ 
					if(directed_graph[rand_node_pos][j]==1){
						if(color[j]!=0){
							color[j]=0; 		//grey color
							white_color_nodes--;
							
						}
					}

				}
				printf("\n");

			}
	}
	printf("chromosome_in_REPAIRING_FUNCTION:\n");
	for(i=0;i<Nodeno;i++){
		printf("%d ",chromosome[i]);
	}	
	printf("\n");
	return chromosome;	
		
}

