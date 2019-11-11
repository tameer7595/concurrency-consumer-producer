#include <iostream>
#include <cstdlib>
#include <pthread.h>


using namespace std;

static const int  NUM_PRODUCER_THREADS =  3;
static const int  NUM_CONSUMER_THREADS =  4;
static const int  BOX_SIZE = 6;

int current = 0;
int box[BOX_SIZE] = {0};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


pthread_t threads_producer[NUM_PRODUCER_THREADS];
pthread_t threads_consumer[NUM_CONSUMER_THREADS];




void *Produce(void *threadid) {

   long tid;
   tid = (long)threadid;
   int i=0;
   while( i < 40){
       pthread_mutex_lock(&lock);

       if(current < BOX_SIZE){
           int r = rand() % 1000000 + 1;
           box[current++] = r;
           std::cout << "producer # " << tid << " ,product #" << r << std::endl;
           i++;
       }
       pthread_mutex_unlock(&lock);

   }
   pthread_exit(NULL);
}

void *Consumer(void *threadid) {

    long tid;
    tid = (long)threadid;
    int i=0 ;
    while( i < 30 ){
        pthread_mutex_lock(&lock);

        if(current>0){
            std::cout << "consumer # " << tid << " ,consume #" << box[current--]<< std::endl;
            i++;
        }
        pthread_mutex_unlock(&lock);

    }

    pthread_exit(NULL);
}

void creatingProducers();

void creatingConsumers();

int main () {
    creatingProducers();
    creatingConsumers();

    pthread_exit(NULL);
}
void creatingProducers(){
    int rc,i;
    for( i = 0; i < NUM_PRODUCER_THREADS; i++ ) {
        cout << "main() : creating producer, " << i << endl;
        rc = pthread_create(&threads_producer[i], NULL, Produce, reinterpret_cast<void *>(i));
        //rc = pthread_create(&threads[i], NULL, PrintHello, reinterpret_cast<void *>(i));
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
}
void creatingConsumers(){
    int rc,i;
    for( i = 0; i < NUM_CONSUMER_THREADS; i++ ) {
        cout << "main() : creating consumer, " << i << endl;
        rc = pthread_create(&threads_consumer[i], NULL, Consumer, reinterpret_cast<void *>(i));
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
}