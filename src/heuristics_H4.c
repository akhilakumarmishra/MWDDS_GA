int* heuristics_H4(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int color[],int white_color_nodes){
	int i,j,k;
	int* chromosome_repairing=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome_repairing[i]=0;
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
			
			
			int k;
			for(k=0;k<Nodeno;k++){
				if(directed_graph[i][k]==1&&color[k]==1){
					color[k]=0;
					white_color_nodes--;
				}
			}
		}
	}

	// while(white_color_nodes>0){
		// printf("in_if_in_pop_gen\n");
		for(j=0;j<Nodeno;j++){
			if(color[j]==1){
				// printf("special node:%d ",j);
				int white_successor_count=0;
				int non_black_predecessor_count=0;
				int non_black_predecessor_pos =0;
				for(k=0;k<Nodeno;k++){
					if(directed_graph[j][k]==1 && color[k]==1){
						white_successor_count++;
					}
					if(directed_graph[k][j]==1 && chromosome[k]==0){
						non_black_predecessor_count++;
						non_black_predecessor_pos=k;

					}
				}
				// printf("white_successor_count=%d  non_black_predecessor_count=%d\n",white_successor_count,non_black_predecessor_count);
				if(white_successor_count==0 && non_black_predecessor_count==1){
					// printf("congulation enter\n");
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
						if(color[non_black_predecessor_pos]==1){
							color[non_black_predecessor_pos]=0;
							white_color_nodes--;
						}
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
		int* chromosome_string=heuristics_H1(chromosome,Nodeno,directed_graph,nodeweightarr,color,white_color_nodes);
		for(i=0;i<Nodeno;i++){
			chromosome_repairing[i]=chromosome_string[i];
		}
		// printf("Am2\n");
		free(chromosome_string);
		// printf("rx_R2_100\n");
		for(j=0;j<Nodeno;j++){
			// printf("%d ",chromosome_repairing[j]);fflush(stdout);
			if(chromosome_repairing[j]!=1&&chromosome_repairing[j]!=0){
				printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",j,chromosome_repairing[j]); fflush(stdout);sleep(10);
			}
		}
		return chromosome_repairing;
	// }
}