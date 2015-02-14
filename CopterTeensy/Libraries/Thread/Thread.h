#ifndef Thread_h
#define Thread_h

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

uint16_t Thread::getPeriodThread(task_fn_t func) {
	for (uint8_t i = 0; i < _num_tasks; i++)
	{
		if (_tasks[i].funct == func)
		{
			return _tasks[i].period;
		}
	}
	return 0;
}

bool Thread::setEnableThread(task_fn_t func, bool enable) {

	for (uint8_t i = 0; i < _num_tasks; i++)
	{
		if (_tasks[i].funct == func)
		{
			_tasks[i].enable = enable;
			return true;
		}
	}
	return false;

}

void Thread::runned(Task *task, float time) {
	// Saves last_run
	task->last_run = time;
	// Cache next run
	task->_cached_next_run = task->last_run + task->period;
}

bool Thread::shouldRun(Task &task, float time) {
	return ((time >= task._cached_next_run) && task.enable);
}

void Thread::run(uint32_t time) {
	float timeMilis = time / 1000;
	for (int i = 0; i < _num_tasks; i++)
	{
		if (Thread::shouldRun(_tasks[i], timeMilis))
		{
			_tasks[i].funct();
			runned(&_tasks[i], timeMilis);
		}
	}
}

uint8_t Thread::countTasks() {
	uint8_t i = 0;
	for (; _tasks[i].funct != NULL; i++)
	{
	}
	return i;
}

bool Thread::getEnableThread(task_fn_t func) {
	for (uint8_t i = 0; i < _num_tasks; i++)
	{
		if (_tasks[i].funct == func)
		{
			return _tasks[i].enable;
		}
	}
	return false;
}

#endif
