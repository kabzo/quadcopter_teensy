#ifndef Thread_hpp
#define Thread_hpp



#include <Arduino.h>

#define THREADTASK(func, period,enable) { func,period,0,0,enable }
#define THREADEND {NULL,0,0,0,false}

class Thread
{
	public:

		typedef void (*task_fn_t)(void);

		Thread() {
		}

		struct Task
		{
				task_fn_t funct;
				uint16_t period;
				float last_run;
				float _cached_next_run;
				bool enable;
		};

		static struct Task _tasks[];

		static uint8_t _num_tasks;

		// Return if the Thread should be runned or not
		static bool shouldRun(Task &task, float time);
		// Runs Thread
		static void run(uint32_t time);
		static void runned(Task *task, float time);

		static uint8_t countTasks();
		static bool setEnableThread(task_fn_t func, bool enable);
		static bool getEnableThread(task_fn_t func);
		static uint16_t getPeriodThread(task_fn_t func);

};


#endif
