#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; 
int T_NUM = 5;
void *runner(void *param);

struct two{
    char* tname;
    int lower;
    int upper;
};

int main(int argc,char *argv[]) {
    pthread_t tid1; /* the thread identifier */
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    pthread_t tid5;
    pthread_attr_t attr;  /* set of thread attributes */

    if (argc != 2) {
        fprintf(stderr," usage: semaj.o <interger value > \n");
        return -1;
    }
    if (atoi(argv[1]) < 0){
        fprintf(stderr," %d must be >= 0 \n", atoi(argv[1]));
        return -1;
    }
    
    /*for (int i = 0 ; i < T_NUM; i++) {
    struct two *l[i] = (struct two *)malloc(sizeof(struct two));
    }                                                           */
    
    struct two *l1 = (struct two *)malloc(sizeof(struct two));
    struct two *l2 = (struct two *)malloc(sizeof(struct two));
    struct two *l3 = (struct two *)malloc(sizeof(struct two));
    struct two *l4 = (struct two *)malloc(sizeof(struct two));
    struct two *l5 = (struct two *)malloc(sizeof(struct two));

    int max = atoi(argv[1]);
    
    sum = 0 ;
    ((struct two *)l1)-> tname = "Thread #1 lower";
    ((struct two *)l1)-> lower = 0;         /*Start form Zero*/
    ((struct two *)l1)-> upper = ((struct two *)l1)->lower +(max/T_NUM);

    ((struct two *)l2)-> tname = "Thread #2 middle lower";
    ((struct two *)l2)-> lower = ((struct two *)l1)->upper +1;
    ((struct two *)l2)-> upper = ((struct two *)l2)->lower +(max/T_NUM);
    
    ((struct two *)l3)-> tname = "Thread #3 middle";
    ((struct two *)l3)-> lower = ((struct two *)l2)->upper +1;        
    ((struct two *)l3)-> upper = ((struct two *)l3)->lower +(max/T_NUM);

    ((struct two *)l4)-> tname = "Thread #4 middle upper";
    ((struct two *)l4)-> lower = ((struct two *)l3)->upper +1;        
    ((struct two *)l4)-> upper = ((struct two *)l4)->lower +(max/T_NUM);
    
    ((struct two *)l5)-> tname = "Thread #5 upper";
    ((struct two *)l5)-> lower = ((struct two *)l4)->upper +1;
    ((struct two *)l5)-> upper = max;
    
    /*for(int i = 0; i < T_NUM; i++) {
        pthread_create(&tid[i],&attr,runner,(void *) l[i]);
        pthread_join(tid[i], NULL);
    }
        printf("sum  =  %d \n",sum);*/
    
    
    
    
    
    pthread_attr_init(&attr); // atr = pthread_attr_init();
    pthread_create(&tid1,&attr,runner,(void *) l1);
    pthread_create(&tid2,&attr,runner,(void *) l2);
    pthread_create(&tid3,&attr,runner,(void *) l3);
    pthread_create(&tid4,&attr,runner,(void *) l4);
    pthread_create(&tid5,&attr,runner,(void *) l5);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL); 
    pthread_join(tid5, NULL);
    
    printf("sum  =  %d \n",sum);

    
}
void *runner (void *param){
    int upper = ((struct two *)param)->upper;
    int lower = ((struct two *)param)->lower;
    char *name = ((struct two *)param)->tname;

    for(int i = lower; i <= upper; i++)
        printf("Working on %s and get %d\n",name , sum += i);
    
    pthread_exit(0);

            
}