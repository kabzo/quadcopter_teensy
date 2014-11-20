#ifndef ThreadController_h
#define ThreadController_h

#include "Thread.h"
#include "inttypes.h"

#define MAX_THREADS		15

class ThreadController: public Thread {

	public:
		// run() Method is overrided
		static void run();

		static Thread* thread[MAX_THREADS];

		static uint8_t cached_size;
};

/*
 ThreadController run() (cool stuf)
 */
void ThreadController::run() {
	long time = millis();
	int checks = 0;
	for (int i = 0; i < MAX_THREADS && checks <= cached_size; i++) {
		if (thread[i]) {
			checks++;
			if (thread[i]->shouldRun(time)) {
				thread[i]->run(time);
			}
		}
	}
}

void ahoj() {

}
void nie() {

}

Thread aaa(ahoj, 10, 00);
Thread* ThreadController::thread[] = {  &aaa
	 };

//#define ADDTHREAD(funct,interval,id) {new Thread}

#endif
