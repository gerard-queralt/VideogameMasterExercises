#pragma once

#include "Window.h"

#include "imgui.h"

class EditorWindow : public Window
{
public:
	~EditorWindow();

	void Draw(bool& io_enabled);

	bool IsFocused() {
		return m_focused;
	}

protected:
	EditorWindow(const std::string& i_name);
	virtual void DrawWindowContents() = 0;

	ImGuiWindowFlags m_flags = ImGuiWindowFlags_None;

private:
	bool m_focused = false;
};

