#include "GuiComponent.h"
#include "GuiWindow.h"

class GuiTabItem : public GuiWindow
{
public:
	GuiTabItem(const char* title = "TabItem");
	
	void SetCloseable(bool canClose);

	bool BeginDraw(const char* name, bool* pOpen, ImGuiWindowFlags windowFlags) override { return ImGui::BeginTabItem(name, pOpen, windowFlags); }
	void EndDraw() override { ImGui::EndTabItem(); }

	void Draw() override;

private:
	bool closeable;
};
