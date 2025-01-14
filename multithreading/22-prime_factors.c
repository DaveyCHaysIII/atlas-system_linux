#include "multithreading.h"

pthread_mutex_t mmutex;

__attribute__((constructor)) void mmutex_init(void)
{
	pthread_mutex_init(&mmutex, NULL);
}

__attribute__((destructor)) void mmutex_destroy(void)
{
	pthread_mutex_destroy(&mmutex);
}

/**
 * create_task - create a new task
 * @entry: the entry point to the thread
 * @param: the parameters passed to the thread
 *
 * Return: task_t
 */

task_t *create_task(task_entry_t entry, void *param)
{
	task_t *ret = malloc(sizeof(task_t));
	if (ret == NULL)
		exit(1);

	ret->entry = entry;
	ret->param = param;
	ret->status = PENDING;
	ret->result = NULL;
	ret->lock = mmutex;

	return (ret);
}


/**
 * destroy_task - destroys a task
 * @task: the task in question
 *
 * Return: no return
 */

void destroy_task(task_t *task)
{
	if (task != NULL)
	{
		list_destroy(task->result, free);
		free((list_t *)task->result);
		free(task);
	}
}

/**
 * exec_tasks - executes a list of tasks
 * @tasks: the list of tasks
 *
 * Return: no return
 */

void *exec_tasks(list_t const *tasks)
{
	node_t *current = NULL;
	task_t *task = NULL;
	size_t id = 0;

	if (!tasks)
		return (NULL);
	for (current = tasks->head; id < tasks->size; ++id)
	{
		if (current == NULL)
			return (NULL);
		task = current->content;
		pthread_mutex_lock(&mmutex);
		if (task->status == PENDING)
		{
			task->status = STARTED;
			pthread_mutex_unlock(&mmutex);
			tprintf("[%02lu] Started\n", id);
			task->result = task->entry(task->param);
			task->status = task->result ? SUCCESS : FAILURE;
			tprintf("[%02lu] %s\n", id, task->result ? "Success" : "Failure");
		}
		else
			pthread_mutex_unlock(&mmutex);
		current = current->next;
	}
	return (NULL);
}
