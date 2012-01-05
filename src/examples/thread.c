/*
 * A simple example, showcasing SIEGE threads, mutexes and semaphores.
 *
 * It is a case of having N printers with M "clients", and the client
 * doesn't care which printer does the job, as long as it is one.
 *
 * In other words, we have a resource with N instances, with M threads
 * trying to access it.
 */

#include <siege/siege.h>

#include <stdio.h>
#include <stdarg.h>

// the number of printers available
#define NUMPRINTERS 2
// the number of "clients" trying to print
#define NUMTHREADS 10

SGSemaphore* sem;
SGMutex* mut;

/*
 * These two prevent printf from racing against itself
 */
int mvprintf(const char* format, va_list args)
{
	sgMutexLock(mut);
	int ret = vprintf(format, args);
	sgMutexUnlock(mut);
	return ret;
}
int mprintf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = mvprintf(format, args);
	va_end(args);
	return ret;
}

/*
 * This function tries to access the printer, and upon (eventually)
 * doing so, it starts printing - that process takes somewhere between
 * 0 and 9 seconds.
 * It then releases the printer for the next thread (client) to use.
 */
SGint SG_EXPORT client(SGThread* thread, void* data)
{
	unsigned int* i = data;
	srand(*i);

	mprintf("%u: Waiting for printer...\n", *i);
	sgSemaphoreWait(sem);
	mprintf("%u: Printing...\n", *i);
	sgMSleep(1000 * (rand() % 10));
	mprintf("%u: Done printing\n", *i);
	sgSemaphorePost(sem);
	return 0;
}

int main(void)
{
	// note the lack of sgInit or sgLoadModule(s)

	sem = sgSemaphoreCreate(NUMPRINTERS, NUMPRINTERS);
	mut = sgMutexCreate();

	SGThread* threads[NUMTHREADS];
	unsigned int tdata[NUMTHREADS]; // I didn't bother with thread-local storage - this'll do
	size_t i;
	for(i = 0; i < NUMTHREADS; i++)
	{
		tdata[i] = i + 1;
		// note that this does not start the thread!
		threads[i] = sgThreadCreate(0, client, &tdata[i]);
		// we have to start each thread explicitly
		sgThreadStart(threads[i]);
	}

	for(i = 0; i < NUMTHREADS; i++)
		sgThreadJoin(threads[i]); // we wait for each thread to finish

	sgMutexDestroy(mut);
	sgSemaphoreDestroy(sem);

	return 0;
}
