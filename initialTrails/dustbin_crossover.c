//3-point crossover
					int random_pt1=u01*(Nodeno-1);
					int random_pt2=u01*(Nodeno-1);
					
					while(random_pt2==random_pt1){
						random_pt2=u01*(Nodeno-1);
					}
					int random_pt3=u01*(Nodeno-1);
					while(random_pt3==random_pt1 || random_pt3==random_pt2){
						random_pt3=u01*(Nodeno-1);
					}
					int first_point,second_point,third_point;
					if(random_pt2<random_pt1 && random_pt2<random_pt3){
						first_point=random_pt2;
						if(random_pt1<random_pt3){
							second_point=random_pt1;
							third_point=random_pt3;
						}
						else{
							second_point=random_pt3;
							third_point=random_pt1;
						}
					}
					else if(random_pt1<random_pt2&&random_pt1<random_pt3){
						first_point=random_pt1;
						if(random_pt2<random_pt3){
							second_point=random_pt2;
							third_point=random_pt3;
						}
						else{
							second_point=random_pt3;
							third_point=random_pt2;
						}

					}
					else{
						first_point=random_pt3;
						if(random_pt1<random_pt2){
							second_point=random_pt1;
							third_point=random_pt2;
						}
						else{
							second_point=random_pt2;
							third_point=random_pt1;
						}
					}
					// else{
					// 	first_point=random_pt1;
					// 	second_point=random_pt2;
					// }
					// int first_point=random_pt1;
					for(i=0;i<Nodeno;i++){
						if(i<first_point || (i>=second_point&&i<third_point)){
							offspring[i]=population[parent1][i];
						}
						else{
							offspring[i]=population[parent2][i];
						}

						
					}
					//END 2-POINT CROSSOVER