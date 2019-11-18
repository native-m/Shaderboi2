#pragma once
#include "imgui.h"
#include "GuiComponent.h"
#include <type_traits>

template<typename T>
struct InputType;

template<typename T, typename Input = InputType<T>>
class GuiInput;

template<typename T>
struct InputType
{
	// Empty
};

template<>
struct InputType<float>
{
	struct Listener
	{
		virtual void OnInputFloatChanged(GuiInput<float>* input) { }
		virtual void OnInputFloatActive(GuiInput<float>* input) { }
	};

	void AddListener(Listener* l) { listener = l; }								
	void SetValue(float val) { data = val; }										
	void SetStep(float val) { step = val; }										
	void SetStepFast(float val) { stepFast = val; }								
	float GetValue() { return data; }	
	bool IsActive() { return isActive; }
																					
	void InputDraw(GuiInput<float>* input, const char* label, unsigned int flags)
	{
		isActive = false;

		if (ImGui::InputFloat(label, &data, step, stepFast, decimalPrec, flags))
			if (listener)
				listener->OnInputFloatChanged(input);

		if (ImGui::IsItemActive())
		{
			if(listener) listener->OnInputFloatActive(input);
			isActive = true;
		}
	}
																					
private:						
	bool isActive;
	float data = 0.0f;
	float step = 0.0f;
	float stepFast = 0.0f;
	int decimalPrec = 3;
	Listener* listener = nullptr;
};

template<>
struct InputType<double>
{
	struct Listener
	{
		virtual void OnInputDoubleChanged(GuiInput<double>* input) { }
		virtual void OnInputDoubleActive(GuiInput<double>* input) { }
	};

	void AddListener(Listener* l) { listener = l; }
	void SetValue(double val) { data = val; }
	void SetStep(double val) { step = val; }
	void SetStepFast(double val) { stepFast = val; }
	void SetDisplayFormat(const char* f) { format = f; }
	double GetValue() { return data; }
	bool IsActive() { return isActive; }

	void InputDraw(GuiInput<double>* input, const char* label, unsigned int flags)
	{
		isActive = false;

		if (ImGui::InputDouble(label, &data, step, stepFast, format, flags))
			if (listener)
				listener->OnInputDoubleChanged(input);

		if (ImGui::IsItemActive())
		{
			if(listener) listener->OnInputDoubleActive(input);
			isActive = false;
		}
	}

private:
	bool isActive;
	double data = 0.0f;
	double step = 0.0f;
	double stepFast = 0.0f;
	const char* format = "%.6f";
	Listener* listener = nullptr;
};

// "Input" is just in case if you have custom input type
// you can pass your custom input here!
template<typename T, typename Input>
class GuiInput : public GuiComponent, public Input
{
public:
	GuiInput(const char* label = "Input Label", unsigned int flags = 0)
		: label(label), flags(flags)
	{
	}

	void SetLabel(const char* label)
	{
		this->label = label;
	}

	void SetFlags(unsigned int flags)
	{
		this->flags = flags;
	}

	void Draw() override
	{
		InputDraw(this, label, flags);
	}

private:
	const char* label;
	unsigned int flags;
};

typedef GuiInput<int> GuiInputInt;
typedef GuiInput<float> GuiInputFloat;
typedef GuiInput<double> GuiInputDouble;
