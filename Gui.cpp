

#include "GUI.h"

#include "RenderManager.h"

#include <algorithm>
#include "tinyxml2.h"
#include "Controls.h"
#include "input.h"
#include "Menu.h"

CGUI GUI;

bool SaveFile = false;
bool LoadFile = false;

CGUI::CGUI()
{

}

// Draws all windows 
void CGUI::Draw()
{
	bool ShouldDrawCursor = false;

	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			ShouldDrawCursor = true;
			DrawWindow(window);
		}

	}

	if (ShouldDrawCursor)
	{
		static Vertex_t MouseVt[3];

#define UI_CURSORSIZE		12

		MouseVt[0].Init(Vector2D(Mouse.x, Mouse.y));
		MouseVt[1].Init(Vector2D(Mouse.x + UI_CURSORSIZE, Mouse.y));
		MouseVt[2].Init(Vector2D(Mouse.x, Mouse.y + UI_CURSORSIZE));

		Render::PolygonOutline(3, MouseVt, Color(102, 255, 102, 230), Color(0, 0, 0, 240));
	}
}

// Handle all input etc
void CGUI::Update()
{

	static int bWasntHolding = false;
	static int bGrabbing = false;
	static int iOffsetX = 0, iOffsetY = 0;
	//Key Array
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		//oldKeys[x] = oldKeys[x] & keys[x];
		keys[x] = (GetAsyncKeyState(x));
	}

	// Mouse Location
	POINT mp = Input->GetMousePos();
	Mouse.x = mp.x; Mouse.y = mp.y;

	RECT Screen = Render::GetViewport();

	// Window Binds
	for (auto& bind : WindowBinds)
	{
		if (GetKeyPress(bind.first))
		{
			bind.second->Toggle();
		}
	}

	// Stop dragging
	if (IsDragging && !GetKeyState(VK_LBUTTON))
	{
		IsDragging = false;
		DraggingWindow = nullptr;

	}

	// If we are in the proccess of dragging a window
	if (IsDragging && GetKeyState(VK_LBUTTON) && !GetKeyPress(VK_LBUTTON))
	{
		if (DraggingWindow)
		{
			DraggingWindow->m_x = Mouse.x - DragOffsetX;
			DraggingWindow->m_y = Mouse.y - DragOffsetY;
		}
	}

	//bWasntHolding = Input->Hovering(x, y, width, 28) && !GetAsyncKeyState(VK_LBUTTON);

	// Process some windows
	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			// Used to tell the widget processing that there could be a click
			bool bCheckWidgetClicks = false;

			// If the user clicks inside the window
			if (GetKeyPress(VK_LBUTTON))
			{
				if (IsMouseInRegion(window->m_x, window->m_y, window->m_x + window->m_iWidth, window->m_y + window->m_iHeight))
				{
					// Is it inside the client area?
					if (IsMouseInRegion(window->GetClientArea1()))
					{
						// User is selecting a new tab
						if (IsMouseInRegion(window->GetTabArea()))
						{
							// Loose focus on the control
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;

							int iTab = 0;
							int TabCount = window->Tabs.size();
							if (TabCount) // If there are some tabs
							{
								int TabSize = (window->m_iWidth - 4 - 12) / TabCount;
								int Dist = Mouse.x - (window->m_x + 8);
								while (Dist > TabSize)
								{
									if (Dist > TabSize)
									{
										iTab++;
										Dist -= TabSize;
									}
								}
								window->SelectedTab = window->Tabs[iTab];
							}

						}
						else
							bCheckWidgetClicks = true;
					}
					else
					{
						// Must be in the around the title or side of the window
						// So we assume the user is trying to drag the window
						IsDragging = true;

						DraggingWindow = window;

						DragOffsetX = Mouse.x - window->m_x;
						DragOffsetY = Mouse.y - window->m_y;

						// Loose focus on the control
						window->IsFocusingControl = false;
						window->FocusedControl = nullptr;
					}
				}
				else
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}


			// Controls 
			if (window->SelectedTab != nullptr)
			{
				// Focused widget
				bool SkipWidget = false;
				CControl* SkipMe = nullptr;

				// this window is focusing on a widget??
				if (window->IsFocusingControl)
				{
					if (window->FocusedControl != nullptr)
					{
						// We've processed it once, skip it later
						SkipWidget = true;
						SkipMe = window->FocusedControl;

						POINT cAbs = window->FocusedControl->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, window->FocusedControl->m_iWidth, window->FocusedControl->m_iHeight };
						window->FocusedControl->OnUpdate();

						if (window->FocusedControl->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							window->FocusedControl->OnClick();

							// If it gets clicked we loose focus
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
							bCheckWidgetClicks = false;
						}
					}
				}

				// Itterate over the rest of the control
				for (auto control : window->SelectedTab->Controls)
				{
					if (control != nullptr)
					{
						if (SkipWidget && SkipMe == control)
							continue;

						POINT cAbs = control->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
						control->OnUpdate();

						if (control->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							control->OnClick();
							bCheckWidgetClicks = false;

							// Change of focus
							if (control->Flag(UIFlags::UI_Focusable))
							{
								window->IsFocusingControl = true;
								window->FocusedControl = control;
							}
							else
							{
								window->IsFocusingControl = false;
								window->FocusedControl = nullptr;
							}

						}
					}
				}

				// We must have clicked whitespace
				if (bCheckWidgetClicks)
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}
		}
	}
}

// Returns 
bool CGUI::GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

bool CGUI::GetKeyState(unsigned int key)
{
	return keys[key];
}

bool CGUI::IsMouseInRegion(int x, int y, int x2, int y2)
{
	if (Mouse.x > x && Mouse.y > y && Mouse.x < x2 && Mouse.y < y2)
		return true;
	else
		return false;
}

bool CGUI::IsMouseInRegion(RECT region)
{
	return IsMouseInRegion(region.left, region.top, region.left + region.right, region.top + region.bottom);
}

POINT CGUI::GetMouse()
{
	return Mouse;
}

bool CGUI::DrawWindow(CWindow* window)
{
	static float rainbow;
	//rainbow += 0.005f;
	//if (rainbow > 1.f) rainbow = 0.f;

	// Main Window
	Render::Outline(window->m_x, window->m_y, window->m_iWidth, window->m_iHeight, Color(1, 1, 1, 255));
	Render::GradientV(window->m_x + 2, window->m_y + 2, window->m_iWidth - 4, 26, Color(1, 1, 1, 255), Color(1, 1, 1, 255));
	Render::GradientV(window->m_x + 1, window->m_y + 1 , window->m_iWidth - 1, window->m_iHeight - 1 - 1, Color(32, 159, 250, 255), Color(32, 159, 250, 255));
	Render::Outline(window->m_x + 0, window->m_y + 0, window->m_iWidth - 0, window->m_iHeight - 0, Color(255, 255, 255, 255));
    Render::Text(window->m_x + 25, window->m_y + 6, Color(255, 255, 255, 255), Render::Fonts::TITLE, window->Title.c_str());

	//Inner
	//Render::Outline(window->m_x + 7, window->m_y + 1 + 26, window->m_iWidth - 4 - 10, window->m_iHeight - 2 - 6 - 26, Color(0, 60, 255, 255));
	Render::GradientV(window->m_x + 8, window->m_y + 1 + 27, window->m_iWidth - 4 - 12, window->m_iHeight - 2 - 8 - 26, Color(1, 1, 1, 255), Color(5, 5, 5, 255));

	//Tab
	Render::GradientV(window->m_x + 8, window->m_y + 1 + 27, window->m_iWidth - 4 - 12, 29, Color(1, 1, 1, 255), Color(1, 1, 1, 255));
	int TabCount = window->Tabs.size();
	if (TabCount) // If there are some tabs
	{
		int TabSize = (window->m_iWidth - 4 - 12) / TabCount;
		for (int i = 0; i < TabCount; i++)
		{
			RECT TabArea = { window->m_x + 8 + (i*TabSize), window->m_y + 1 + 27, TabSize, 29 };
			CTab *tab = window->Tabs[i];
			if (window->SelectedTab == tab)
			{
				Render::GradientV(window->m_x + 8 + (i*TabSize), window->m_y + 3 + 28, TabSize, 30, Color(32, 159, 250, 255), Color(30, 100, 255, 255));
			}
			else if (IsMouseInRegion(TabArea))
			{
				Render::GradientV(window->m_x + 8 + (i*TabSize), window->m_y + 1 + 27, TabSize, 29, Color(1, 1, 1, 255), Color(1, 1, 1, 255));
			}
			RECT TextSize = Render::GetTextSize(Render::Fonts::Tabs, tab->Title.c_str());
			Render::Text(TabArea.left + (TabSize / 2) - (TextSize.right / 2), TabArea.top + 8, Color(255, 255, 255, 255), Render::Fonts::Tabs, tab->Title.c_str());
		}
	}



	// Controls 
	if (window->SelectedTab != nullptr)
	{
		// Focused widget
		bool SkipWidget = false;
		CControl* SkipMe = nullptr;

		// this window is focusing on a widget??
		if (window->IsFocusingControl)
		{
			if (window->FocusedControl != nullptr)
			{
				// We need to draw it last, so skip it in the regular loop
				SkipWidget = true;
				SkipMe = window->FocusedControl;
			}
		}


		// Itterate over all the other controls
		for (auto control : window->SelectedTab->Controls)
		{
			if (SkipWidget && SkipMe == control)
				continue;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

		// Draw the skipped widget last
		if (SkipWidget)
		{
			auto control = window->FocusedControl;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

	}


	return true;
}

void CGUI::RegisterWindow(CWindow* window)
{
	Windows.push_back(window);

	// Resorting to put groupboxes at the start
}

void CGUI::BindWindow(unsigned char Key, CWindow* window)
{
	if (window)
		WindowBinds[Key] = window;
	else
		WindowBinds.erase(Key);
}

void CGUI::SaveWindowState(CWindow* window, std::string Filename)
{
	// Create a whole new document and we'll just save over top of the old one
	tinyxml2::XMLDocument Doc;

	// Root Element is called "INTERX"
	tinyxml2::XMLElement *Root = Doc.NewElement("rape.gang");
	Doc.LinkEndChild(Root);

	// If the window has some tabs..
	if (Root && window->Tabs.size() > 0)
	{
		for (auto Tab : window->Tabs)
		{
			// Add a new section for this tab
			tinyxml2::XMLElement *TabElement = Doc.NewElement(Tab->Title.c_str());
			Root->LinkEndChild(TabElement);

			// Now we itterate the controls this tab contains
			if (TabElement && Tab->Controls.size() > 1)
			{
				for (auto Control : Tab->Controls)
				{
					// If the control is ok to be saved
					if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
					{
						// Create an element for the control
						tinyxml2::XMLElement *ControlElement = Doc.NewElement(Control->FileIdentifier.c_str());
						TabElement->LinkEndChild(ControlElement);

						if (!ControlElement)
						{
							return;
						}

						CCheckBox* cbx = nullptr;
						CComboBox* cbo = nullptr;
						CKeyBind* key = nullptr;
						CSlider* sld = nullptr;

						// Figure out what kind of control and data this is
						switch (Control->FileControlType)
						{
						case UIControlTypes::UIC_CheckBox:
							cbx = (CCheckBox*)Control;
							ControlElement->SetText(cbx->GetState());
							break;
						case UIControlTypes::UIC_ComboBox:
							cbo = (CComboBox*)Control;
							ControlElement->SetText(cbo->GetIndex());
							break;
						case UIControlTypes::UIC_KeyBind:
							key = (CKeyBind*)Control;
							ControlElement->SetText(key->GetKey());
							break;
						case UIControlTypes::UIC_Slider:
							sld = (CSlider*)Control;
							ControlElement->SetText(sld->GetValue());
							break;
						}
					}
				}
			}
		}
	}

	//Save the file
	if (Doc.SaveFile(Filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		MessageBox(NULL, "Failed To Save Config File!", "rape.gang", MB_OK);
	}

}

void CGUI::LoadWindowState(CWindow* window, std::string Filename)
{
	// Lets load our meme
	tinyxml2::XMLDocument Doc;
	if (Doc.LoadFile(Filename.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *Root = Doc.RootElement();

		// The root "ayy" element
		if (Root)
		{
			// If the window has some tabs..
			if (Root && window->Tabs.size() > 0)
			{
				for (auto Tab : window->Tabs)
				{
					// We find the corresponding element for this tab
					tinyxml2::XMLElement *TabElement = Root->FirstChildElement(Tab->Title.c_str());
					if (TabElement)
					{
						// Now we itterate the controls this tab contains
						if (TabElement && Tab->Controls.size() > 0)
						{
							for (auto Control : Tab->Controls)
							{
								// If the control is ok to be saved
								if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
								{
									// Get the controls element
									tinyxml2::XMLElement *ControlElement = TabElement->FirstChildElement(Control->FileIdentifier.c_str());

									if (ControlElement)
									{
										CCheckBox* cbx = nullptr;
										CComboBox* cbo = nullptr;
										CKeyBind* key = nullptr;
										CSlider* sld = nullptr;

										// Figure out what kind of control and data this is
										switch (Control->FileControlType)
										{
										case UIControlTypes::UIC_CheckBox:
											cbx = (CCheckBox*)Control;
											cbx->SetState(ControlElement->GetText()[0] == '1' ? true : false);
											break;
										case UIControlTypes::UIC_ComboBox:
											cbo = (CComboBox*)Control;
											cbo->SelectIndex(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_KeyBind:
											key = (CKeyBind*)Control;
											key->SetKey(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Slider:
											sld = (CSlider*)Control;
											sld->SetValue(atof(ControlElement->GetText()));
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}