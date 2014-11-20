/*
 Thread.h - An runnable object

 Thread is responsable for holding the "action" for something,
 also, it responds if it "should" or "should not" run, based on
 the current time;

 For instructions, go to https://github.com/ivanseidel/ArduinoThread

 Created by Ivan Seidel Gomes, March, 2013.
 Released into the public domain.
 */

#ifndef Thread_h
#define Thread_h

#include <Arduino.h>
#include <inttypes.h>

class Thread {

	public:

		typedef void (*task_fn_t)(void);

		Thread(task_fn_t funct , uint16_t _interval, uint8_t id);

		// Return if the Thread should be runned or not
		bool shouldRun(uint32_t time);
		// Runs Thread
		void run(uint32_t time);

		void runned(uint32_t time);

		void setEnabled(bool enable);

		task_fn_t _onRun_Function;

		// Desired interval between runs
		uint16_t period;

		// Last runned time in Ms
		uint32_t last_run;

		// Scheduled run in Ms (MUST BE CACHED)
		uint32_t _cached_next_run;

		bool enabled;

		uint8_t threadID;

		String ThreadName;
};

void Thread::setEnabled(bool enable) {
	enabled = enable;
}

Thread::Thread(task_fn_t funct, uint16_t _interval, uint8_t id)
		:
				enabled(true),
				_onRun_Function(funct),
				last_run(0),
				_cached_next_run(last_run + _interval),
				threadID(id),
				period(_interval) {
}

void Thread::runned(uint32_t time) {
	// Saves last_run
	last_run = time;
	// Cache next run
	_cached_next_run = last_run + period;
}

bool Thread::shouldRun(uint32_t time) {
	return ((time >= _cached_next_run) && enabled);
}

void Thread::run(uint32_t time) {
	if(shouldRun(time) && _onRun_Function != NULL)
			_onRun_Function();
		// Update last_run and _cached_next_run
		runned(time);
}

#endif
