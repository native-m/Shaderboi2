#include "TimerFunction.h"
#include "SDL.h"

TimerFunction::TimerFunction()
	: data(nullptr), id(0)
{
}

void TimerFunction::SetDataPtr(void* newData)
{
	data = newData;
}

void TimerFunction::SetCallbackFunction(const Callback& callback)
{
	if (id)
		StopTimer();

	callbackFn = callback;
}

void TimerFunction::StartTimer(uint32_t interval)
{
	id = SDL_AddTimer(interval, RunTimer, this);
}

void TimerFunction::StopTimer()
{
	if (id)
		SDL_RemoveTimer(id);

	id = 0;
}

uint32_t TimerFunction::RunTimer(uint32_t interval, void* data)
{
	TimerFunction* thiz = reinterpret_cast<TimerFunction*>(data);
	thiz->callbackFn(interval, thiz->data);
	return 0;
}
