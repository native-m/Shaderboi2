#pragma once
#include <functional>
#include <cstdint>

class TimerFunction
{
public:
	typedef std::function<void(uint32_t, void*)> Callback;

public:
	TimerFunction();

	void SetDataPtr(void* newData);
	void SetCallbackFunction(const Callback& callback);

	int GetTimerID() { return id; }

	void StartTimer(uint32_t interval);
	void StopTimer();

	static uint32_t RunTimer(uint32_t interval, void* data);

private:
	Callback callbackFn;
	void* data;
	int id;
};
