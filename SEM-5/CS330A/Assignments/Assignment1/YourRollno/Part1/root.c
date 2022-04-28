#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<unistd.h>

void solve(int i, unsigned long long x,char *argv[], int argc){
	if(argc<i+2){printf("%lld",x);} 

		else if(argv[i][0]=='d'){argv[0]="./double";
			argv[i]="-1";
			if(execv(argv[0], argv)){
                                printf("UNABLE TO EXECUTE");
                                exit(-1);
                        }
		}
		else if(argv[i][0]=='r'){argv[0]="./root";
			argv[i]="-1";
			if(execv(argv[0], argv)){
                                printf("UNABLE TO EXECUTE");
                                exit(-1);
                        }
		}
		
		else if(argv[i][0]=='s'){argv[0]="./square";
			argv[i]="-1";
			if(execv(argv[0], argv)){
                                printf("UNABLE TO EXECUTE");
                                exit(-1);
                        }
		}
		else{
			printf("UNABLE TO EXECUTE");
		}
}
int main(int argc, char *argv[])
{

	unsigned long long x=atoi(argv[argc-1]);
	long double y=x;
	y=round(sqrt(y));
	x=y;

	sprintf(argv[argc-1], "%lld", x);
	
	int i=1;
	while(argv[i][0]=='-'){i++;}   

	solve(i, x, argv, argc);
		
	
	return 0;
}
