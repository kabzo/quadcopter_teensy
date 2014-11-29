#ifndef Thread_h
#define Thread_h

#define THREADTASK(func, period,enable) { func,period,0,0,enable }
#define THREADEND {NULL,0,0,0,false}

class Thread
{
	public:

		typedef void (*task_fn_t)(void);

		Thread()
		{
		}

		struct Task
		{
				task_fn_t funct;
				uint16_t period;
				uint32_t last_run;
				uint32_t _cached_next_run;
				bool enable;
		};

		static struct Task _tasks[];

		static uint8_t _num_tasks;

		// Return if the Thread should be runned or not
		static bool shouldRun(Task *task, uint32_t time);
		// Runs Thread
		static void run(uint32_t time);
		static void runned(Task *task, uint32_t time);

		static uint8_t countTasks();
		static bool setEnableThread(task_fn_t func, bool enable);
		static bool getEnableThread(task_fn_t func);

};

bool Thread::setEnableThread(task_fn_t func, bool enable)
{

	for (uint8_t i = 0; i < _num_tasks; i++) {
		if (_tasks[i].funct == func) {
			_tasks[i].enable = enable;
			return true;
		}
	}
	return false;

}

void Thread::runned(Task *task, uint32_t time)
{
	// Saves last_run
	task->last_run = time;
	// Cache next run
	task->_cached_next_run = task->last_run + task->period;
}

bool Thread::shouldRun(Task *task, uint32_t time)
{
	return ((time >= task->_cached_next_run) && task->enable);
}

void Thread::run(uint32_t time)
{
	for (int i = 0; i < _num_tasks; i++) {
		if (Thread::shouldRun(&_tasks[i], time)) {
			_tasks[i].funct();
			runned(&_tasks[i], time);
		}
	}
}

uint8_t Thread::countTasks()
{
	uint8_t i = 0;
	for (; _tasks[i].funct != NULL; i++) {

	}
	return i;
}

bool Thread::getEnableThread(task_fn_t func)
{
	for (uint8_t i = 0; i < _num_tasks; i++) {
		if (_tasks[i].funct == func) {
			return _tasks[i].enable;
		}
	}
	return false;
}


#endif
