#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include <time.h>
int total_count=0;
struct args {
	char * str;
	int num;
};
pthread_mutex_t lock;
void *gateN(void *input)
{

	int max_count=((struct args*)input)->num;
	int count=0, random=0;
	while(count<max_count){
		pthread_mutex_lock(&lock);
	
		
		count= count + 1;
		total_count= total_count+ 1;
		if((count%500)==0)
			printf("%d have entered from the %s gate.\nTotal poeple = %d Remaining seats = %d\n",count, ((struct args*)input)->str, total_count, max_count-count);
		if(count==max_count)
			printf("The %s closed is now closed.\n", ((struct args*)input)->str);
	  	pthread_mutex_unlock(&lock);
	  }

	return NULL;
}
int main()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3; 
	pthread_t thread_id4;
	pthread_mutex_init(&lock,NULL);
	struct args *sendit = (struct args *)malloc(sizeof(struct args));
	char gatename[] = "east";
	sendit->str= gatename;
	sendit->num = 5000;
	pthread_create(&thread_id1,NULL,gateN, (void *)sendit);
	struct args *sendit1 = (struct args *)malloc(sizeof(struct args));
    char gatename1[] = "west";
	sendit1->str= gatename1;
	sendit1->num = 5000;
	pthread_create(&thread_id2,NULL,gateN, (void *)sendit1);
	struct args *sendit2 = (struct args *)malloc(sizeof(struct args));
	char gatename2[] = "north";
	sendit2->str= gatename2;
	sendit2->num = 10000;
	pthread_create(&thread_id3,NULL,gateN, (void *)sendit2);
	struct args *sendit3 = (struct args *)malloc(sizeof(struct args));
    char gatename3[] = "south";
	sendit3->str= gatename3;
	sendit3->num = 15000;
	pthread_create(&thread_id4,NULL,gateN, (void *)sendit3);
	pthread_join(thread_id1,NULL);
	pthread_join(thread_id2,NULL);
	pthread_join(thread_id3,NULL);
	pthread_join(thread_id4,NULL);
	pthread_exit(NULL);
	return (0);}