				printf("offspring_fitness: %d \t",offspring_fitness);
				printf("	best_fitness_value:%d\n",best_fitness_value);
				int uniqueness=1;
				int unique_one = unique(offspring,offspring_fitness,Nodeno,pop_size,population,fitness_arr);//check with population
				printf("		unique_one:%d\t",unique_one);
				if(unique_one==0){
					if(gen==0){
						local_fitness_value=offspring_fitness;
						uniqueness=0;
						similar_fit_chromosome[similar_count]=(int*)malloc(Nodeno*sizeof(int));
						for(i=0;i<Nodeno;i++){
							similar_fit_chromosome[similar_count][i]=offspring[i];
						}
						similar_count++;
					}
					else{
						if(offspring_fitness==local_fitness_value){
							int unique_two = unique_similar(offspring,Nodeno,similar_count,similar_fit_chromosome);
							uniqueness=unique_two;
							if(unique_two==0){
								if(similar_count<similar_set_max_size){
									similar_fit_chromosome[similar_count]=(int*)malloc(Nodeno*sizeof(int));
									for(i=0;i<Nodeno;i++){
										similar_fit_chromosome[similar_count][i]=offspring[i];
									}
									similar_count++;
								}
								// else{

								// }
							}
						}
						else{

							for(i=0;i<similar_count;i++){
								free(similar_fit_chromosome[i]);
							}
							similar_count=0;
							similar_fit_chromosome[similar_count]=(int*)malloc(Nodeno*sizeof(int));
							local_fitness_value=offspring_fitness;
							uniqueness=0;
							for(i=0;i<Nodeno;i++){
								similar_fit_chromosome[similar_count][i]=offspring[i];
							}
							similar_count++;
						}
					}
					
				}
				printf("		uniqueness:%d\n",uniqueness);