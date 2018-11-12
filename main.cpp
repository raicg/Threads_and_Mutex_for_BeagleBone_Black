#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <math.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

using namespace BlackLib;

int valueADC1, valueADC2, valueADC3, valueADC4;

ADC adc1(AIN0);
ADC adc2(AIN2);
ADC adc3(AIN6);
ADC adc4(AIN4);
BlackGPIO led1(GPIO_67, output);
BlackGPIO led2(GPIO_68, output);
BlackGPIO led3(GPIO_44, output);
BlackGPIO led4(GPIO_26, output);
BlackGPIO led5(GPIO_46, output);
BlackGPIO led6(GPIO_65, output);
BlackGPIO led7(GPIO_61, output);
BlackGPIO led8(GPIO_66, output);
BlackGPIO led9(GPIO_69, output);
BlackGPIO led10(GPIO_45, output);
BlackGPIO led11(GPIO_47, output);
BlackGPIO led12(GPIO_27, output);
//BlackGPIO led13(GPIO_60, output);
BlackGPIO led14(GPIO_48, output);
BlackGPIO led15(GPIO_49, output);
BlackGPIO led16(GPIO_60, output);
BlackGPIO led17(GPIO_20, output);
//BlackGPIO led18(GPIO_20, output);
pthread_t thread1, thread2, thread3, thread4;
pthread_mutex_t semaphore1, semaphore2, semaphore3, semaphore4, semaphore5, semaphore6, semaphore7;

void createThread (void);
void createMutex (void);
void *train1 (void *arg);
void *train2 (void *arg);
void *train3 (void *arg);
void *train4 (void *arg);
int reloadvelADC1 (void);
int reloadvelADC2 (void);
int reloadvelADC3 (void);
int reloadvelADC4 (void);
void load (int k);
void printAndWait (int train, int loc, int vel);

int main(){
    createMutex();
    createThread();
    
    while(1){
		valueADC1 = adc1.getIntValue();
		valueADC2 = adc2.getIntValue();
		valueADC3 = adc3.getIntValue();
		valueADC4 = adc4.getIntValue();
        usleep(1000000);
    }

    return 0;
}


void printAndWait (int train, int loc, int wait){
    int vel = ((-1)*wait)+5;
    printf("Sou o trem %d, estou na linha %d, com velocidade %d. \n", train, loc, vel);
    usleep(wait*1000000);
}

void createThread (void){
    int res;

    res = pthread_create(&thread1, NULL, train1, NULL);
    if (res != 0) {
        perror("Criação da Thread 1 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread2, NULL, train2, NULL);
    if (res != 0) {
        perror("Criação da Thread 2 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread3, NULL, train3, NULL);
    if (res != 0) {
        perror("Criação da Thread 3 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread4, NULL, train4, NULL);
    if (res != 0) {
        perror("Criação da Thread 4 falhou.");
        exit(EXIT_FAILURE);
    }

}

void createMutex (void){
    int res;

    res = pthread_mutex_init(&semaphore1, NULL);
    if (res != 0){
        perror("Criação do Mutex 1 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&semaphore2, NULL);
    if (res != 0){
        perror("Criação do Mutex 2 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&semaphore3, NULL);
    if (res != 0){
        perror("Criação do Mutex 3 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&semaphore4, NULL);
    if (res != 0){
        perror("Criação do Mutex 4 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&semaphore5, NULL);
    if (res != 0){
        perror("Criação do Mutex 5 falhou.");
        exit(EXIT_FAILURE);
    }
    res = pthread_mutex_init(&semaphore6, NULL);
    if (res != 0){
        perror("Criação do Mutex 6 falhou.");
        exit(EXIT_FAILURE);
    }
    res = pthread_mutex_init(&semaphore7, NULL);
    if (res != 0){
        perror("Criação do Mutex 7 falhou.");
        exit(EXIT_FAILURE);
    }
}


int reloadvelADC1 (void){
    int vel;
    vel = ((valueADC1-190)/1000)+1;
    return vel;
}

int reloadvelADC2 (void){
    int vel;
    vel = ((valueADC2-190)/1000)+1;
    return vel;
}

int reloadvelADC3 (void){
    int vel;
    vel = ((valueADC3-190)/1000)+1;
    return vel;
}

int reloadvelADC4 (void){
    int vel;
    vel = ((valueADC4-190)/1000)+1;
    return vel;
}

void *train1 (void *arg){
    int vel=0;
    while (1){
        vel = reloadvelADC1();
        led1.setValue(high);
		led4.setValue(low);
        printAndWait(1, 1, vel);
        vel = reloadvelADC1();
        pthread_mutex_lock(&semaphore6);
        pthread_mutex_lock(&semaphore1);
        led2.setValue(high);
		led1.setValue(low);
        printAndWait(1, 2, vel);
        vel = reloadvelADC1();    
        pthread_mutex_lock(&semaphore2);
        pthread_mutex_unlock(&semaphore6);
        pthread_mutex_unlock(&semaphore1);    
        led3.setValue(high);      
		led2.setValue(low);
        printAndWait(1, 3, vel);
        vel = reloadvelADC1();
        pthread_mutex_unlock(&semaphore2);
        led4.setValue(high);
		led3.setValue(low);
        printAndWait(1, 4, vel);
        vel = reloadvelADC1();
    }
}

void *train2 (void *arg){
    int vel=0;
    while (1){
        vel = reloadvelADC2();
        led5.setValue(high);
		led8.setValue(low);
        printAndWait(2, 5, vel);
        vel = reloadvelADC2();
        pthread_mutex_lock(&semaphore7);
        pthread_mutex_lock(&semaphore3);
        led6.setValue(high);
        led5.setValue(low);
        printAndWait(2, 6, vel);
        vel = reloadvelADC2();
        pthread_mutex_lock(&semaphore6);
        pthread_mutex_lock(&semaphore4);
        pthread_mutex_unlock(&semaphore7);
        pthread_mutex_unlock(&semaphore3);
        led7.setValue(high);
	    led6.setValue(low);
        printAndWait(2, 7, vel);
        vel = reloadvelADC2();
        pthread_mutex_lock(&semaphore1);
        pthread_mutex_unlock(&semaphore4);
        pthread_mutex_unlock(&semaphore6);
        led8.setValue(high);
		led7.setValue(low);
        printAndWait(2, 8, vel);
        vel = reloadvelADC2();
        pthread_mutex_unlock(&semaphore1);
    }
}

void *train3 (void *arg){
    int vel=0;
    while (1){
        vel = reloadvelADC3();
        led9.setValue(high);
		led12.setValue(low);
        printAndWait(3, 9, vel);
        vel = reloadvelADC3();
        led10.setValue(high);
		led9.setValue(low);
        printAndWait(3, 10, vel);
        vel = reloadvelADC3();
        pthread_mutex_lock(&semaphore7);
        pthread_mutex_lock(&semaphore5);
        led11.setValue(high);
		led10.setValue(low);
        printAndWait(3, 11, vel);
        vel = reloadvelADC3();
        pthread_mutex_lock(&semaphore3);
        pthread_mutex_unlock(&semaphore5);
        pthread_mutex_unlock(&semaphore7);
        led12.setValue(high);
		led11.setValue(low);
        printAndWait(3, 12, vel);
        vel = reloadvelADC3();
        pthread_mutex_unlock(&semaphore3);
    }
}

void *train4 (void *arg){
    int vel=0;
    while (1){
        vel = reloadvelADC4();
		led17.setValue(high);
        printAndWait(4, 13, vel);
        vel = reloadvelADC4();
        pthread_mutex_lock(&semaphore2);
		led14.setValue(high);
		led17.setValue(low);
        printAndWait(4, 14, vel);
        vel = reloadvelADC4();
        pthread_mutex_lock(&semaphore4);
        pthread_mutex_unlock(&semaphore2);
		led15.setValue(high);
		led14.setValue(low);
        printAndWait(4, 15, vel);
        vel = reloadvelADC4();
        pthread_mutex_lock(&semaphore5);
        pthread_mutex_unlock(&semaphore4);
		led16.setValue(high);
		led15.setValue(low);
        printAndWait(4, 16, vel);
        vel = reloadvelADC4();
        pthread_mutex_unlock(&semaphore5);
		led17.setValue(high);
		led16.setValue(low);
        printAndWait(4, 17, vel);
        vel = reloadvelADC4();
        printAndWait(4, 18, vel);
        vel = reloadvelADC4();
    }
}


