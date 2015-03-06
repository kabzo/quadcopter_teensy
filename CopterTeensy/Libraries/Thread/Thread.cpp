/*
 * Thread.cpp
 *
 *  Created on: 19.2.2015
 *      Author: Juraj
 */

#include <Thread.hpp>

uint8_t Thread::_num_tasks = 0;
struct Thread::Task *Thread::_tasks = 0;

void Thread::load_tasks(Task *tasks)
{
	Thread::_tasks = tasks;
	_num_tasks = countTasks();
}

uint16_t Thread::getPeriodThread(task_fn_t func)
{
	for (uint8_t i = 0; i < _num_tasks; i++)
	{
		if (_tasks[i].funct == func)
		{
			return _tasks[i].period;
		}
	}
	return 0;
}

bool Thread::setEnableThread(task_fn_t func, bool enable)
{

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

void Thread::runned(Task *task, float time)
{
	// Saves last_run
	task->last_run = time;
	// Cache next run
	task->_cached_next_run = task->last_run + task->period;
}

bool Thread::shouldRun(Task &task, float time)
{
	return ((time >= task._cached_next_run) && task.enable);
}

void Thread::run(uint32_t time)
{
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

uint8_t Thread::countTasks()
{
	uint8_t i = 0;
	for (; _tasks[i].funct != NULL; i++)
	{
	}
	return i;
}

bool Thread::getEnableThread(task_fn_t func)
{
	for (uint8_t i = 0; i < _num_tasks; i++)
	{
		if (_tasks[i].funct == func)
		{
			return _tasks[i].enable;
		}
	}
	return false;
}
