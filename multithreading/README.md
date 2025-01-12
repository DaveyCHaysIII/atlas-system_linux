Readme!

pthread_exit
pthread_self
pthread_join
pthread_detach

prthread_mutex_init
pthread_mutex_lock
pthread_mutex_try
pthread_mutex_unlock
pthread_mutex_destroy


pthread_exit(void p); //terminates the calling thread and makes the value value_ptr available to any successful join with the terminating thread.
int pthread_join(pthread_t thread, void ppvalue_ptr); //suspends execution of the calling thread until the target thread terminates
int pthread_detach(pthread_t thread); //indicate to the implementation that storage for the thread can be reclaimed when that thread terminates

int pthread_mutex_init(pthread_mutex_t *mutex,
    const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

The pthread_self() function returns the thread ID of the calling thread.
