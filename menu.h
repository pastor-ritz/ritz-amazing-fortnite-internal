#include "xor.h"
using DrawTransitionOrg = void(*)(uintptr_t _this, uintptr_t canvas);
DrawTransitionOrg DrawTransitionOriginal = 0;
bool fakeunload = false;
UCanvas* static_canvas;
int width;
int height;
#pragma warning(disable : 4996)
//static wchar_t* s2wc(const char* c)
//{
//	const size_t cSize = strlen(c) + 1;
//	wchar_t* wc = new wchar_t[cSize];
//	mbstowcs(wc, c, cSize);
//
//	return wc;
//}
//#define ZeroGUI_MIN(A, B)            (((A) < (B)) ? (A) : (B))
//#define ZeroGUI_MAX(A, B)            (((A) >= (B)) ? (A) : (B))
APlayerController* PlayerController;
ue::FKey InsertKey;
ue::FKey F7Key;
ue::FKey RBKey;
ue::FKey LBKey;
//
//namespace ZeroGUI
//{
//
//	namespace Input
//	{
//		static bool mouseDown[5];
//		static bool mouseDownAlready[256];
//
//		static bool keysDown[256];
//		static bool keysDownAlready[256];
//
//		static bool IsAnyMouseDown()
//		{
//			if (mouseDown[0]) return true;
//			if (mouseDown[1]) return true;
//			if (mouseDown[2]) return true;
//			if (mouseDown[3]) return true;
//			if (mouseDown[4]) return true;
//
//			return false;
//		}
//
//		static bool IsMouseClicked(int button, int element_id, bool repeat)
//		{
//			if (mouseDown[button])
//			{
//				if (!mouseDownAlready[element_id])
//				{
//					mouseDownAlready[element_id] = true;
//					return true;
//				}
//				if (repeat)
//					return true;
//			}
//			else
//			{
//				mouseDownAlready[element_id] = false;
//			}
//			return false;
//		}
//		static bool IsKeyPressed(int key, bool repeat)
//		{
//			if (keysDown[key])
//			{
//				if (!keysDownAlready[key])
//				{
//					keysDownAlready[key] = true;
//					return true;
//				}
//				if (repeat)
//					return true;
//			}
//			else
//			{
//				keysDownAlready[key] = false;
//			}
//			return false;
//		}
//
//		static void Handle()
//		{
//			if (safe_call(safe_call(GetAsyncKeyState))(0x01))
//				mouseDown[0] = true;
//			else
//				mouseDown[0] = false;
//		}
//	}
//
//	namespace Colors
//	{
//		//Text
//		static ue::FLinearColor Text{ 1.0f, 1.0f, 1.0f, 1.0f };
//		static ue::FLinearColor Text_Shadow{ 0.0f, 0.0f, 0.0f, 0.0f };
//		static ue::FLinearColor Text_Outline{ 0.0f, 0.0f, 0.0f, 0.30f };
//
//		//Window
//		static ue::FLinearColor Window_Background{ 0.009f, 0.009f, 0.009f, 1.0f };
//		static ue::FLinearColor Window_Header{ 0.10f, 0.15f, 0.84f, 1.0f };
//
//		//Buttons
//		static ue::FLinearColor Button_Idle{ 5 / 255.f, 5 / 255.f, 5 / 255.f, 1.0f };
//		static ue::FLinearColor Button_Hovered{ 7 / 255.f, 7 / 255.f, 7 / 255.f, 1.0f };
//		static ue::FLinearColor Button_Active{ 8 / 255.f, 8 / 255.f, 8 / 255.f, 1.0f };
//
//		//Combobox
//		static ue::FLinearColor Combobox_Idle{ 5 / 255.f, 5 / 255.f, 5 / 255.f, 1.0f };
//		static ue::FLinearColor Combobox_Hovered{ 7 / 255.f, 7 / 255.f, 7 / 255.f, 1.0f };
//		static ue::FLinearColor Combobox_Elements{ 5 / 255.f, 5 / 255.f, 5 / 255.f, 1.0f };
//
//		//Sliders
//		static ue::FLinearColor Slider_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
//		static ue::FLinearColor Slider_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
//		static ue::FLinearColor Slider_Progress{ 0.22f, 0.30f, 0.72f, 1.0f };
//		static ue::FLinearColor Slider_Button{ 0.10f, 0.15f, 0.84f, 1.0f };
//
//		static ue::FLinearColor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 1.0f };
//	}
//
//	namespace PostRenderer
//	{
//		struct DrawList
//		{
//			int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
//			Vector2 pos;
//			Vector2 size;
//			ue::FLinearColor color;
//			char* name;
//			bool outline;
//
//			Vector2 from;
//			Vector2 to;
//			int thickness;
//		};
//		static DrawList drawlist[128];
//
//		static void drawFilledRect(Vector2 pos, float w, float h, ue::FLinearColor color)
//		{
//			for (int i = 0; i < 128; i++)
//			{
//				if (drawlist[i].type == -1)
//				{
//					drawlist[i].type = 1;
//					drawlist[i].pos = pos;
//					drawlist[i].size = Vector2{ w, h };
//					drawlist[i].color = color;
//					return;
//				}
//			}
//		}
//		static void TextLeft(char* name, Vector2 pos, ue::FLinearColor color, bool outline)
//		{
//			for (int i = 0; i < 128; i++)
//			{
//				if (drawlist[i].type == -1)
//				{
//					drawlist[i].type = 2;
//					drawlist[i].name = name;
//					drawlist[i].pos = pos;
//					drawlist[i].outline = outline;
//					drawlist[i].color = color;
//					return;
//				}
//			}
//		}
//		static void TextCenter(char* name, Vector2 pos, ue::FLinearColor color, bool outline)
//		{
//			for (int i = 0; i < 128; i++)
//			{
//				if (drawlist[i].type == -1)
//				{
//					drawlist[i].type = 3;
//					drawlist[i].name = name;
//					drawlist[i].pos = pos;
//					drawlist[i].outline = outline;
//					drawlist[i].color = color;
//					return;
//				}
//			}
//		}
//		static void Draw_Line(Vector2 from, Vector2 to, int thickness, ue::FLinearColor color)
//		{
//			for (int i = 0; i < 128; i++)
//			{
//				if (drawlist[i].type == -1)
//				{
//					drawlist[i].type = 4;
//					drawlist[i].from = from;
//					drawlist[i].to = to;
//					drawlist[i].thickness = thickness;
//					drawlist[i].color = color;
//					return;
//				}
//			}
//		}
//	}
//
//
//	static bool hover_element = false;
//	static Vector2 menu_pos = Vector2{ 0, 0 };
//	static float offset_x = 0.0f;
//	static float offset_y = 0.0f;
//
//	static Vector2 first_element_pos = Vector2{ 0, 0 };
//
//	static Vector2 last_element_pos = Vector2{ 0, 0 };
//	static Vector2 last_element_size = Vector2{ 0, 0 };
//
//	static int current_element = -1;
//	static Vector2 current_element_pos = Vector2{ 0, 0 };
//	static Vector2 current_element_size = Vector2{ 0, 0 };
//	static int elements_count = 0;
//
//	static bool sameLine = false;
//
//	static bool pushY = false;
//	static float pushYvalue = 0.0f;
//
//
//	static Vector2 CursorPos()
//	{
//		float cursorPosX;
//		float cursorPosY;
//		PlayerController->GetMousePosition(&cursorPosX, &cursorPosY);
//		
//		return Vector2{ cursorPosX, cursorPosY };
//	}
//	static bool MouseInZone(Vector2 pos, Vector2 size)
//	{
//		Vector2 cursor_pos = CursorPos();
//
//		if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
//			if (cursor_pos.x < pos.x + size.y && cursor_pos.y < pos.y + size.y)
//				return true;
//
//		return false;
//	}
//	
//	static void Draw_Cursor(bool toogle)
//	{
//		if (toogle)
//		{
//			Vector2 cursorPos = CursorPos();
//			//static_canvas->K2_DrawLine(Vector2{ cursorPos.x, cursorPos.x }, Vector2{ cursorPos.x + 35, cursorPos.y + 10 }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
//
//
//			int x = 35;
//			int y = 10;
//			while (y != 30) //20 steps
//			{
//				x -= 1; if (x < 15) x = 15;
//				y += 1; if (y > 30) y = 30;
//
//				static_canvas->K2_DrawLine(Vector2{ cursorPos.x, cursorPos.y }, Vector2{ cursorPos.x + x, cursorPos.y + y }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
//			}
//
//			static_canvas->K2_DrawLine(Vector2{ cursorPos.x, cursorPos.y }, Vector2{ cursorPos.x + 15, cursorPos.y + 30 }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
//			static_canvas->K2_DrawLine(Vector2{ cursorPos.x + 35, cursorPos.y + 10 }, Vector2{ cursorPos.x + 15, cursorPos.y + 30 }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
//		}
//	}
//
//	static void SameLine()
//	{
//		sameLine = true;
//	}
//	static void PushNextElementY(float y, bool from_last_element = true)
//	{
//		pushY = true;
//		if (from_last_element)
//			pushYvalue = last_element_pos.y + last_element_size.y + y;
//		else
//			pushYvalue = menu_pos.y + y;
//	}
//	static void NextColumn(float x)
//	{
//		offset_x = x;
//		PushNextElementY(first_element_pos.y, false);
//	}
//	static void PushElementX(float value)
//	{
//		offset_x = value;
//	}
//	static void PushElementY(float value)
//	{
//		pushY = true;
//		pushYvalue = menu_pos.y + value - 10;
//	}
//	static void ClearFirstPos()
//	{
//		first_element_pos = Vector2{ 0, 0 };
//	}
//
//	static void TextLeft(char* name, Vector2 pos, ue::FLinearColor color, bool outline, bool big = false)
//	{
//		if(big)
//			static_canvas->K2_DrawText(pos, color, ue::FString(s2wc(name)), false, true);
//		else
//			static_canvas->K2_DrawText(pos, color, ue::FString(s2wc(name)), false, true);
//			
//	}
//	static void TextCenter(char* name, Vector2 pos, ue::FLinearColor color, bool outline, bool big = false)
//	{
//		if (big)
//			static_canvas->K2_DrawText(pos, color, ue::FString(s2wc(name)), true, true);
//		else
//			static_canvas->K2_DrawText(pos , color, ue::FString(s2wc(name)), true, true);
//	}
//
//	static void GetColor(ue::FLinearColor* color, float* r, float* g, float* b, float* a)
//	{
//		*r = color->R;
//		*g = color->G;
//		*b = color->B;
//		*a = color->A;
//	}
//	static UINT32 GetColorUINT(int r, int g, int b, int a)
//	{
//		UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
//		return result;
//	}
//
//	static void Draw_Line(Vector2 from, Vector2 to, int thickness, ue::FLinearColor color)
//	{
//		static_canvas->K2_DrawLine(Vector2{ from.x, from.y }, Vector2{ to.x, to.y }, thickness, color);
//	}
//	static void drawFilledRect(Vector2 initial_pos, float w, float h, ue::FLinearColor color)
//	{
//		for (float i = 0.0f; i < h; i += 1.0f)
//			static_canvas->K2_DrawLine(Vector2{ initial_pos.x, initial_pos.y + i }, Vector2{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
//	}
//	static void DrawFilledCircle(Vector2 pos, float r, ue::FLinearColor color)
//	{
//		float smooth = 0.07f;
//
//		double PI = 3.14159265359;
//		int size = (int)(2.0f * PI / smooth) + 1;
//
//		float angle = 0.0f;
//		int i = 0;
//
//		for (; angle < 2 * PI; angle += smooth, i++)
//		{
//			Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
//		}
//	}
//	static void DrawCircle(Vector2 pos, int radius, int numSides, ue::FLinearColor Color)
//	{
//		float PI = 3.1415927f;
//
//		float Step = PI * 2.0 / numSides;
//		int Count = 0;
//		Vector2 V[128];
//		for (float a = 0; a < PI * 2.0; a += Step) {
//			float X1 = radius * cos(a) + pos.x;
//			float Y1 = radius * sin(a) + pos.y;
//			float X2 = radius * cos(a + Step) + pos.x;
//			float Y2 = radius * sin(a + Step) + pos.y;
//			V[Count].x = X1;
//			V[Count].x = Y1;
//			V[Count + 1].x = X2;
//			V[Count + 1].x = Y2;
//			//Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
//			Draw_Line(Vector2{ V[Count].x, V[Count].x }, Vector2{ X2, Y2 }, 1.5f, Color);// Circle Around
//		}
//	}
//
//	static Vector2 dragPos;
//	static bool Window(char* name, Vector2* pos, Vector2 size, bool isOpen, bool WindowInvisible)
//	{
//		elements_count = 0;
//
//		if (!isOpen)
//			return false;
//
//		bool isHovered = MouseInZone(Vector2{ pos->x, pos->y }, size);
//
//		//Drop last element
//		if (current_element != -1 && !safe_call(safe_call(GetAsyncKeyState))(0x1))
//		{
//			current_element = -1;
//		}
//
//		//Drag
//		if (hover_element && safe_call(safe_call(GetAsyncKeyState))(0x1))
//		{
//
//		}
//		else if ((isHovered || dragPos.x != 0) && !hover_element)
//		{
//			if (Input::IsMouseClicked(0, elements_count, true))
//			{
//				/*Vector2 cursorPos = CursorPos();
//
//				cursorPos.x -= size.x;
//				cursorPos.y -= size.y;
//
//				if (dragPos.x == 0)
//				{
//					dragPos.x = (cursorPos.x - pos->x);
//					dragPos.x = (cursorPos.x - pos->y);
//				}
//				pos->x = cursorPos.x - dragPos.x;
//				pos->y = cursorPos.y - dragPos.y;*/
//			}
//			else
//			{
//				dragPos = Vector2{ 0, 0 };
//			}
//		}
//		else
//		{
//			hover_element = false;
//		}
//
//
//		offset_x = 0.0f; offset_y = 0.0f;
//		menu_pos = Vector2{ pos->x, pos->y };
//		first_element_pos = Vector2{ 0, 0 };
//		current_element_pos = Vector2{ 0, 0 };
//		current_element_size = Vector2{ 0, 0 };
//
//		if (!WindowInvisible) {
//			//Bg
//			drawFilledRect(Vector2{ pos->x, pos->y }, size.x, size.y, Colors::Window_Background);
//			//drawFilledRect(Vector2{ pos->x, pos->y }, 122, size.y, ue::FLinearColor{ 0.006f, 0.006f, 0.006f, 1.0f });//My tabs bg
//
//			//Header
//			drawFilledRect(Vector2{ pos->x, pos->y }, size.x, 25.0f, Colors::Window_Header);
//
//			offset_y += 25.0f;
//
//			//Title
//			Vector2 titlePos = Vector2{ pos->x + size.x / 2, pos->y + 25 / 2 };
//			TextCenter(name, titlePos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//		}
//		else {
//			offset_y += 25.0f;
//		}
//		return true;
//	}
//
//	static void Text(char* text, bool center = false, bool outline = false)
//	{
//		elements_count++;
//
//		float size = 25;
//		Vector2 padding = Vector2{ 10, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//
//		if (!sameLine)
//			offset_y += size + padding.y;
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x + 5.0f, pos.y + size / 2 };
//		if (center)
//			TextCenter(text, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
//		else
//			TextLeft(text, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
//
//		sameLine = false;
//		last_element_pos = pos;
//		//last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//	}
//	static bool ButtonTab(char* name, Vector2 size, bool active)
//	{
//		elements_count++;
//
//		Vector2 padding = Vector2{ 5, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
//
//		//Bg
//		if (active)
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Active);
//		}
//		else if (isHovered)
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
//			hover_element = true;
//		}
//		else
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
//		}
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
//		TextCenter(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//
//		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
//			return true;
//
//		return false;
//	}
//	static bool Button(char* name, Vector2 size)
//	{
//		elements_count++;
//
//		Vector2 padding = Vector2{ 5, 10 };
//
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//
//		
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
//
//		//Bg
//		if (isHovered)
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
//			hover_element = true;
//		}
//		else
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
//		}
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
//		//if (!TextOverlapedFromActiveElement(textPos))
//		TextCenter(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//
//		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
//			return true;
//
//		return false;
//	}
//	static bool InvisibleButton(char* name, Vector2 size)
//	{
//		elements_count++;
//
//		Vector2 padding = Vector2{ 5, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//
//		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
//			return true;
//
//		return false;
//	}
//	static void FakeElement()
//	{
//		Vector2 size = Vector2(1, 1);
//		elements_count++;
//
//		Vector2 padding = Vector2{ 1, 1 };
//
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//
//
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//
//
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//
//		return;
//	}
//
//	static void Checkbox(char* name, bool* value)
//	{
//		elements_count++;
//
//		Vector2 size = Vector2(20, 20);
//		Vector2 padding = Vector2{ 10, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ size.x, size.y });
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//
//		const float check_sz = ZeroGUI_MIN(size.x, size.y);
//		const float pad = ZeroGUI_MAX(1.0f, (float)(int)(check_sz / 6.0f));
//
//
//		Vector2 CheckMarkPos = Vector2(pos.x, pos.y);
//
//
//		float sz = size.x - pad * 2.0f;
//
//
//		float thickness = ZeroGUI_MAX(sz / 5.0f, 1.0f);
//		sz -= thickness * 0.5f;
//		CheckMarkPos = CheckMarkPos + Vector2(thickness * 0.25f, thickness * 0.25f);
//
//		float third = sz / 3.0f;
//		float bx = CheckMarkPos.x + third;
//		float by = CheckMarkPos.y + sz - third * 0.5f;
//
//		Vector2 TopLeft = Vector2(bx + third * 2 - sz, by - third * 2);
//		Vector2 TopRight = Vector2(bx + third * 2, by - third * 2);
//		Vector2 BottomLeft = Vector2(bx + third * 2 - sz, by - third * 2 + sz);
//		Vector2 BottomRight = Vector2(bx + third * 2, by - third * 2 + sz);
//
//		if (!*value)
//		{
//			//Top Left -> Bottom Right
//			//Draw_Line(TopLeft, BottomRight, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//			
//			//Bottom Left -> Top Right			
//			//Draw_Line(BottomLeft, TopRight, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//
//			Draw_Line(TopLeft, TopRight, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//			Draw_Line(TopRight, BottomRight, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//			Draw_Line(BottomRight, BottomLeft, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//			Draw_Line(BottomLeft, TopLeft, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//		}
//		else {
//
//			//Third -> Center
//			Draw_Line(Vector2(bx - third, by - third), Vector2(bx, by), thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//
//			//Center -> Top Right
//			Draw_Line(Vector2(bx, by), TopRight, thickness, ue::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
//		}
//
//
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x + size.x + 5.0f, pos.y/* + size.y / 2 */};
//		//if (!TextOverlapedFromActiveElement(textPos))
//		TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		//last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//
//		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
//			*value = !*value;
//	}
//	static void SliderInt(char* name, int* value, int min, int max)
//	{
//		elements_count++;
//
//		Vector2 size = Vector2{ 240, 50 };
//		Vector2 slider_size = Vector2{ 200, 10 };
//		Vector2 padding = Vector2{ 10, 15 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size);
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//		//Bg
//		if (isHovered || current_element == elements_count)
//		{
//			//Drag
//			if (Input::IsMouseClicked(0, elements_count, true))
//			{
//				current_element = elements_count;
//
//				Vector2 cursorPos = CursorPos();
//				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
//				if (*value < min) *value = min;
//				if (*value > max) *value = max;
//			}
//
//			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered);
//			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress);
//
//			hover_element = true;
//		}
//		else
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle);
//			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress);
//		}
//
//
//		//Value
//		float oneP = slider_size.x / (max - min);
//		drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress);
//		//drawFilledRect(Vector2{ pos.x + oneP * (*value - min) - 10.0f, pos.y + slider_size.y - 5.0f + padding.y }, 20.0f, 20.0f, Colors::Slider_Button);
//		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 3.3f + padding.y }, 10.0f, Colors::Slider_Button);
//		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 3.3f + padding.y }, 5.0f, Colors::Slider_Progress);
//
//		char buffer[32];
//		sprintf_s(buffer, "%i", *value);
//		Vector2 valuePos = Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 25 + padding.y };
//		TextCenter(buffer, valuePos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x + 5, pos.y + 10 };
//		TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//	}
//	static void SliderFloat(char* name, float* value, float min, float max, const char* format = "%.1f")
//	{
//		elements_count++;
//
//		Vector2 size = Vector2{ 210, 40 };
//		Vector2 slider_size = Vector2{ 421, 2 };
//		Vector2 adjust_zone = Vector2{ 0, 20 };
//		Vector2 padding = Vector2{ 10, 20 }; //15
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, Vector2{ pos.x + slider_size.x, slider_size.y + adjust_zone.y * 1.5f });
//		
//		if (!sameLine)
//			offset_y += size.y + padding.y - 5;
//
//		//Bg
//		if (isHovered || current_element == elements_count)
//		{
//			//Drag
//			if (Input::IsMouseClicked(0, elements_count, true))
//			{
//				current_element = elements_count;
//
//				Vector2 cursorPos = CursorPos();
//
//				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
//				if (*value < min) *value = min;
//				if (*value > max) *value = max;
//			}
//
//			//drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered);
//			//DrawFilledCircle(Vector2{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
//			//DrawFilledCircle(Vector2{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Hovered);
//
//			hover_element = true;
//		}
//		else
//		{
//			//drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle);
//			//DrawFilledCircle(Vector2{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
//			//DrawFilledCircle(Vector2{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Idle);
//		}
//
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x, pos.y + 5 };
//		TextLeft(name, textPos, Colors::Text, false);
//
//		//Empty
//		float oneP = slider_size.x / (max - min);
//		drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, ue::FLinearColor(0.21f, 0.20f, 0.21f, 1.00f));
//
//		//Value
//		drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, ue::FLinearColor(0.76f, 0.10f, 0.24f, 1.00f));
//
//		Vector2 GrabPosition = Vector2(pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y);
//		if (*value != min)
//			Draw_Line(Vector2(GrabPosition.x, GrabPosition.y + 5), Vector2(GrabPosition.x, GrabPosition.y - 10), 2.1f, ue::FLinearColor(0.76f, 0.10f, 0.24f, 1.00f));
//
//		char buffer[32];
//		sprintf_s(buffer, format, *value);
//		Vector2 valuePos = Vector2{ pos.x + slider_size.x, pos.y + 5 };
//		TextCenter(buffer, valuePos, Colors::Text, false);
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//	}
//
//
//
//	static bool checkbox_enabled[256];
//	static void Combobox(char* name, Vector2 size, int* value, const char* arg, ...)
//	{
//		elements_count++;
//
//		Vector2 padding = Vector2{ 5, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y - 15 }, size);
//
//		//Bg
//		if (isHovered || checkbox_enabled[elements_count])
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Combobox_Hovered);
//
//			hover_element = true;
//		}
//		else
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Combobox_Idle);
//		}
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//		//Text
//		Vector2 textPos = Vector2{ pos.x + size.x + 5.0f, pos.y/* + size.y / 2*/ };
//		TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//		//Elements
//		bool isHovered2 = false;
//		Vector2 element_pos = pos;
//		int num = 0;
//
//		if (checkbox_enabled[elements_count])
//		{
//			current_element_size.x = element_pos.x - 5.0f;
//			current_element_size.y = element_pos.y - 5.0f;
//		}
//		va_list arguments;
//		for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char*))
//		{
//			//Selected Element
//			if (num == *value)
//			{
//				Vector2 _textPos = Vector2{ pos.x + 5.0f, pos.y/*+ size.y / 2*/ };
//				TextLeft((char*)arg, _textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//			}
//
//			if (checkbox_enabled[elements_count])
//			{
//				element_pos.y += 25.0f;
//
//				isHovered2 = MouseInZone(Vector2{ element_pos.x, element_pos.y }, Vector2{ size.x, 25.0f });
//				if (isHovered2)
//				{
//					hover_element = true;
//					PostRenderer::drawFilledRect(Vector2{ element_pos.x, element_pos.y }, size.x, 25.0f, Colors::Combobox_Hovered);
//
//					//Click
//					if (Input::IsMouseClicked(0, elements_count, false))
//					{
//						*value = num;
//						checkbox_enabled[elements_count] = false;
//					}
//				}
//				else
//				{
//					PostRenderer::drawFilledRect(Vector2{ element_pos.x, element_pos.y }, size.x, 25.0f, Colors::Combobox_Idle);
//				}
//
//				PostRenderer::TextLeft((char*)arg, Vector2{ element_pos.x + 5.0f, element_pos.y/* + 13.0f*/ }, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//			}
//			num++;
//		}
//		va_end(arguments);
//		if (checkbox_enabled[elements_count])
//		{
//			current_element_size.x = element_pos.x + 5.0f;
//			current_element_size.y = element_pos.y + 5.0f;
//		}
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//
//		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
//		{
//			checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
//		}
//		if (!isHovered && !isHovered2 && Input::IsMouseClicked(0, elements_count, false))
//		{
//			checkbox_enabled[elements_count] = false;
//		}
//	}
//
//	static int active_hotkey = -1;
//	static bool already_pressed = false;
//	static std::string VirtualKeyCodeToString(UCHAR virtualKey)
//	{
//		UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
//
//		if (virtualKey == VK_LBUTTON)
//		{
//			return ("MOUSE0");
//		}
//		if (virtualKey == VK_RBUTTON)
//		{
//			return ("MOUSE1");
//		}
//		if (virtualKey == VK_MBUTTON)
//		{
//			return ("MBUTTON");
//		}
//		if (virtualKey == VK_XBUTTON1)
//		{
//			return ("XBUTTON1");
//		}
//		if (virtualKey == VK_XBUTTON2)
//		{
//			return ("XBUTTON2");
//		}
//
//		CHAR szName[128];
//		int result = 0;
//		switch (virtualKey)
//		{
//		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
//		case VK_RCONTROL: case VK_RMENU:
//		case VK_LWIN: case VK_RWIN: case VK_APPS:
//		case VK_PRIOR: case VK_NEXT:
//		case VK_END: case VK_HOME:
//		case VK_INSERT: case VK_DELETE:
//		case VK_DIVIDE:
//		case VK_NUMLOCK:
//			scanCode |= KF_EXTENDED;
//		default:
//			result = GetKeyNameTextA(scanCode << 16, szName, 128);
//		}
//
//		return szName;
//	}
//	static void Hotkey(char* name, Vector2 size, int* key)
//	{
//		elements_count++;
//
//		Vector2 padding = Vector2{ 5, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
//
//		//Bg
//		if (isHovered)
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
//			hover_element = true;
//		}
//		else
//		{
//			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
//		}
//
//		if (!sameLine)
//			offset_y += size.y + padding.y;
//
//		if (active_hotkey == elements_count)
//		{
//			//Text
//			Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
//			TextCenter(xorstr("[Press Key]"), textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//			if (!ZeroGUI::Input::IsAnyMouseDown())
//			{
//				already_pressed = false;
//			}
//
//			if (!already_pressed)
//			{
//				for (int code = 0; code < 255; code++)
//				{
//					if (safe_call(safe_call(GetAsyncKeyState))(code))
//					{
//						*key = code;
//						active_hotkey = -1;
//					}
//				}
//			}
//		}
//		else
//		{
//			//Text
//			Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
//			TextCenter((char*)VirtualKeyCodeToString(*key).c_str(), textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//			if (isHovered)
//			{
//				if (Input::IsMouseClicked(0, elements_count, false))
//				{
//					already_pressed = true;
//					active_hotkey = elements_count;
//
//					//Queue Fix
//					for (int code = 0; code < 255; code++)
//						if (safe_call(safe_call(GetAsyncKeyState))(code)) {}
//				}
//			}
//			else
//			{
//				if (Input::IsMouseClicked(0, elements_count, false))
//				{
//					active_hotkey = -1;
//				}
//			}
//		}
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//	}
//
//	static int active_picker = -1;
//	static ue::FLinearColor saved_color;
//	static bool ColorPixel(Vector2 pos, Vector2 size, ue::FLinearColor* original, ue::FLinearColor color)
//	{
//		PostRenderer::drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, color);
//
//		//Выбранный цвет
//		if (original->R == color.R && original->G == color.G && original->B == color.B)
//		{
//			PostRenderer::Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x + size.x - 1, pos.y }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
//			PostRenderer::Draw_Line(Vector2{ pos.x, pos.y + size.y - 1 }, Vector2{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
//			PostRenderer::Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x, pos.y + size.y - 1 }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
//			PostRenderer::Draw_Line(Vector2{ pos.x + size.x - 1, pos.y }, Vector2{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
//		}
//
//		//Смена цвета
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
//		if (isHovered)
//		{
//			if (Input::IsMouseClicked(0, elements_count, false))
//				*original = color;
//		}
//
//		return true;
//	}
//	static void ColorPicker(char* name, ue::FLinearColor* color)
//	{
//		elements_count++;
//
//		float size = 25;
//		Vector2 padding = Vector2{ 10, 10 };
//		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//		if (sameLine)
//		{
//			pos.x = last_element_pos.x + last_element_size.x + padding.x;
//			pos.y = last_element_pos.y;
//		}
//		if (pushY)
//		{
//			pos.y = pushYvalue;
//			pushY = false;
//			pushYvalue = 0.0f;
//			offset_y = pos.y - menu_pos.y;
//		}
//		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ size, size });
//
//		if (!sameLine)
//			offset_y += size + padding.y;
//
//		if (active_picker == elements_count)
//		{
//			hover_element = true;
//
//			float sizePickerX = 250;
//			float sizePickerY = 250;
//			bool isHoveredPicker = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ sizePickerX, sizePickerY - 60 });
//
//			//Background
//			PostRenderer::drawFilledRect(Vector2{ pos.x, pos.y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);
//
//			//float pixedSize = sizePickerY / pixels;
//			//ue::FLinearColor temp_color{1.0f, 1.0f, 1.0f, 1.0f};
//			//float iterator = 0.0f;
//			//
//			//for (int y = 0; y < pixels; y++)
//			//{
//			//	for (int x = 0; x < pixels; x++)
//			//	{
//			//		ColorPixel(Vector2{ pos.x + pixedSize * x, pos.y + pixedSize * y }, pixedSize, color, temp_color);
//			//		temp_color.R -= (1.0f - saved_color.R) / pixels;
//			//		temp_color.G -= (1.0f - saved_color.G) / pixels;
//			//		temp_color.B -= (1.0f - saved_color.B) / pixels;
//			//	}
//			//	
//			//	iterator += 1.0f / pixels;
//			//	temp_color = ue::FLinearColor{ 1.0f - iterator, 1.0f - iterator, 1.0f - iterator, 1.0f };
//			//}
//
//			Vector2 pixelSize = Vector2{ sizePickerX / 12, sizePickerY / 12 };
//
//			//0
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
//			}
//			//1
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
//			}
//			//2
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
//			}
//			//3
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
//			}
//			//4
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
//			}
//			//5
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
//			}
//			//6
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
//			}
//			//7
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
//			}
//			//8
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
//			}
//			//9
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
//			}
//			//10
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
//			}
//			//11
//			{
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
//				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
//			}
//
//
//
//			if (isHoveredPicker)
//			{
//				if (Input::IsMouseClicked(0, elements_count, false))
//				{
//
//				}
//			}
//			else
//			{
//				if (Input::IsMouseClicked(0, elements_count, false))
//				{
//					active_picker = -1;
//					//hover_element = false;
//				}
//			}
//		}
//		else
//		{
//
//			//Color
//			drawFilledRect(Vector2{ pos.x + 4, pos.y + 4 }, size - 8, size - 8, *color);
//
//			//Text
//			Vector2 textPos = Vector2{ pos.x + size + 5.0f, pos.y + size / 2 };
//			TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
//
//			if (isHovered && Input::IsMouseClicked(0, elements_count, false))
//			{
//				saved_color = *color;
//				active_picker = elements_count;
//			}
//		}
//
//
//		sameLine = false;
//		last_element_pos = pos;
//		//last_element_size = size;
//		if (first_element_pos.x == 0.0f)
//			first_element_pos = pos;
//	}
//
//
//	static void Render()
//	{
//		for (int i = 0; i < 128; i++)
//		{
//			if (PostRenderer::drawlist[i].type != -1)
//			{
//				//Filled Rect
//				if (PostRenderer::drawlist[i].type == 1)
//				{
//					ZeroGUI::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
//				}
//				//TextLeft
//				else if (PostRenderer::drawlist[i].type == 2)
//				{
//					ZeroGUI::TextLeft(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
//				}
//				//TextCenter
//				else if (PostRenderer::drawlist[i].type == 3)
//				{
//					ZeroGUI::TextCenter(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
//				}
//				//Draw_Line
//				else if (PostRenderer::drawlist[i].type == 4)
//				{
//					Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
//				}
//
//				PostRenderer::drawlist[i].type = -1;
//			}
//		}
//	}
//}
#include <Windows.h>

namespace ZeroGUI
{
	namespace Input
	{
		bool mouseDown[5];
		bool mouseDownAlready[256];

		bool keysDown[256];
		bool keysDownAlready[256];

		bool IsAnyMouseDown()
		{
			if (mouseDown[0]) return true;
			if (mouseDown[1]) return true;
			if (mouseDown[2]) return true;
			if (mouseDown[3]) return true;
			if (mouseDown[4]) return true;

			return false;
		}

		bool IsMouseClicked(int button, int element_id, bool repeat)
		{
			if (mouseDown[button])
			{
				if (!mouseDownAlready[element_id])
				{
					mouseDownAlready[element_id] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				mouseDownAlready[element_id] = false;
			}
			return false;
		}
		bool IsKeyPressed(int key, bool repeat)
		{
			if (keysDown[key])
			{
				if (!keysDownAlready[key])
				{
					keysDownAlready[key] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				keysDownAlready[key] = false;
			}
			return false;
		}

		void Handle()
		{
			if (safe_call(GetAsyncKeyState)(0x01))
				mouseDown[0] = true;
			else
				mouseDown[0] = false;
		}
	}
}
wchar_t* s2wc(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

namespace ZeroGUI
{
	namespace Colors
	{
		ue::FLinearColor Text{ 1.0f, 1.0f, 1.0f, 1.0f };
		ue::FLinearColor Text_Shadow{ 0.0f, 0.0f, 0.0f, 0.0f };
		ue::FLinearColor Text_Outline{ 0.0f, 0.0f, 0.0f, 0.30f };

		ue::FLinearColor Window_Background{ 0.009f, 0.009f, 0.009f, 1.0f };
		ue::FLinearColor Window_Header{ 0.10f, 0.15f, 0.84f, 1.0f };

		ue::FLinearColor Button_Idle{ 0.10f, 0.15f, 0.84f, 1.0f };
		ue::FLinearColor Button_Hovered{ 0.15f, 0.20f, 0.89f, 1.0f };
		ue::FLinearColor Button_Active{ 0.20f, 0.25f, 0.94f, 1.0f };

		ue::FLinearColor Checkbox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		ue::FLinearColor Checkbox_Hovered{ 0.22f, 0.30f, 0.72f, 1.0f };
		ue::FLinearColor Checkbox_Enabled{ 0.20f, 0.25f, 0.94f, 1.0f };

		ue::FLinearColor Combobox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		ue::FLinearColor Combobox_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		ue::FLinearColor Combobox_Elements{ 0.239f, 0.42f, 0.82f, 1.0f };

		ue::FLinearColor Slider_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		ue::FLinearColor Slider_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		ue::FLinearColor Slider_Progress{ 0.22f, 0.30f, 0.72f, 1.0f };
		ue::FLinearColor Slider_Button{ 0.10f, 0.15f, 0.84f, 1.0f };

		ue::FLinearColor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 1.0f };
	}

	namespace PostRenderer
	{
		struct DrawList
		{
			int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
			Vector2 pos;
			Vector2 size;
			ue::FLinearColor color;
			char* name;
			bool outline;

			Vector2 from;
			Vector2 to;
			int thickness;
		};
		DrawList drawlist[128];

		void drawFilledRect(Vector2 pos, float w, float h, ue::FLinearColor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 1;
					drawlist[i].pos = pos;
					drawlist[i].size = Vector2{ w, h };
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextLeft(char* name, Vector2 pos, ue::FLinearColor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 2;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextCenter(char* name, Vector2 pos, ue::FLinearColor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 3;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void Draw_Line(Vector2 from, Vector2 to, int thickness, ue::FLinearColor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 4;
					drawlist[i].from = from;
					drawlist[i].to = to;
					drawlist[i].thickness = thickness;
					drawlist[i].color = color;
					return;
				}
			}
		}
	}

	UCanvas* canvas;


	bool hover_element = false;
	Vector2 menu_pos = Vector2{ 0, 0 };
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	Vector2 first_element_pos = Vector2{ 0, 0 };

	Vector2 last_element_pos = Vector2{ 0, 0 };
	Vector2 last_element_size = Vector2{ 0, 0 };

	int current_element = -1;
	Vector2 current_element_pos = Vector2{ 0, 0 };
	Vector2 current_element_size = Vector2{ 0, 0 };
	int elements_count = 0;

	bool sameLine = false;

	bool pushY = false;
	float pushYvalue = 0.0f;

	void SetupCanvas(UCanvas* _canvas)
	{
		canvas = _canvas;
	}

	Vector2 CursorPos()
	{
		//POINT cursorPos;
		//GetCursorPos(&cursorPos);
		float cursorPosX;
		float cursorPosY;
		PlayerController->GetMousePosition(&cursorPosX, &cursorPosY);
		return Vector2{ cursorPosX, cursorPosY };
	}
	bool MouseInZone(Vector2 pos, Vector2 size)
	{
		Vector2 cursor_pos = CursorPos();

		if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
			if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
				return true;

		return false;
	}

	void Draw_Cursor(bool toogle)
	{
		if (toogle)
		{
			Vector2 cursorPos = CursorPos();
			canvas->K2_DrawLine(Vector2{ cursorPos.x, cursorPos.y }, Vector2{ cursorPos.x + 35, cursorPos.y + 10 }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });


			int x = 35;
			int y = 10;
			while (y != 30) //20 steps
			{
				x -= 1; if (x < 15) x = 15;
				y += 1; if (y > 30) y = 30;

				canvas->K2_DrawLine(Vector2{ cursorPos.x, cursorPos.y }, Vector2{ cursorPos.x + x, cursorPos.y + y }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
			}

			canvas->K2_DrawLine(Vector2{ cursorPos.x, cursorPos.y }, Vector2{ cursorPos.x + 15, cursorPos.y + 30 }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
			canvas->K2_DrawLine(Vector2{ cursorPos.x + 35, cursorPos.y + 10 }, Vector2{ cursorPos.x + 15, cursorPos.y + 30 }, 1, ue::FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
		}
	}

	void SameLine()
	{
		sameLine = true;
	}
	void PushNextElementY(float y, bool from_last_element = true)
	{
		pushY = true;
		if (from_last_element)
			pushYvalue = last_element_pos.y + last_element_size.y + y;
		else
			pushYvalue = y;
	}
	void NextColumn(float x)
	{
		offset_x = x;
		PushNextElementY(first_element_pos.y, false);
	}
	void ClearFirstPos()
	{
		first_element_pos = Vector2{ 0, 0 };
	}

	/*void TextLeft(char* name, Vector2 pos, ue::FLinearColor color, bool outline)
	{
		int length = strlen(name) + 1;
		canvas->K2_DrawText(Functions::NamesFont, ue::FString{ s2wc(name), length, length }, pos, Vector2{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, Vector2{ pos.x + 1, pos.y + 1 }, false, true, true, Colors::Text_Outline);
	}
	void TextCenter(char* name, Vector2 pos, ue::FLinearColor color, bool outline)
	{
		int length = strlen(name) + 1;
		canvas->K2_DrawText(Functions::NamesFont, ue::FString{ s2wc(name), length, length }, pos, Vector2{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, Vector2{ pos.x + 1, pos.y + 1 }, true, true, true, Colors::Text_Outline);
	}*/

	static void TextLeft(const char* name, Vector2 pos, ue::FLinearColor color, bool outline, bool big = false)
	{
		if(big)
			static_canvas->K2_DrawText(pos, color, ue::FString(s2wc(name)), false, true);
		else
			static_canvas->K2_DrawText(pos, color, ue::FString(s2wc(name)), false, true);
			
	}
	static void TextCenter(const char* name, Vector2 pos, ue::FLinearColor color, bool outline, bool big = false)
	{
		if (big)
			static_canvas->K2_DrawText(pos, color, ue::FString(s2wc(name)), true, true);
		else
			static_canvas->K2_DrawText(pos , color, ue::FString(s2wc(name)), true, true);
		}
	void GetColor(ue::FLinearColor* color, float* r, float* g, float* b, float* a)
	{
		*r = color->R;
		*g = color->G;
		*b = color->B;
		*a = color->A;
	}
	UINT32 GetColorUINT(int r, int g, int b, int a)
	{
		UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
		return result;
	}

	void Draw_Line(Vector2 from, Vector2 to, int thickness, ue::FLinearColor color)
	{
		canvas->K2_DrawLine(Vector2{ from.x, from.y }, Vector2{ to.x, to.y }, thickness, color);
	}
	void drawFilledRect(Vector2 initial_pos, float w, float h, ue::FLinearColor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->K2_DrawLine(Vector2{ initial_pos.x, initial_pos.y + i }, Vector2{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
	}
	void DrawFilledCircle(Vector2 pos, float r, ue::FLinearColor color)
	{
		float smooth = 0.07f;

		double PI = 3.14159265359;
		int size = (int)(2.0f * PI / smooth) + 1;

		float angle = 0.0f;
		int i = 0;

		for (; angle < 2 * PI; angle += smooth, i++)
		{
			Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
		}
	}
	void DrawCircle(Vector2 pos, int radius, int numSides, ue::FLinearColor Color)
	{
		float PI = 3.1415927f;

		float Step = PI * 2.0 / numSides;
		int Count = 0;
		Vector2 V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * cos(a) + pos.x;
			float Y1 = radius * sin(a) + pos.y;
			float X2 = radius * cos(a + Step) + pos.x;
			float Y2 = radius * sin(a + Step) + pos.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			//Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
			Draw_Line(Vector2{ V[Count].x, V[Count].y }, Vector2{ X2, Y2 }, 1.0f, Color);// Circle Around
		}
	}

	Vector2 dragPos;
	bool Window(const char* name, Vector2* pos, Vector2 size, bool isOpen)
	{
		elements_count = 0;

		if (!isOpen)
			return false;

		bool isHovered = MouseInZone(Vector2{ pos->x, pos->y }, size);

		//Drop last element
		if (current_element != -1 && !safe_call(GetAsyncKeyState)(0x1))
		{
			current_element = -1;
		}

		//Drag
		if (hover_element && safe_call(GetAsyncKeyState)(0x1))
		{

		}
		else if ((isHovered || dragPos.x != 0) && !hover_element)
		{
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				Vector2 cursorPos = CursorPos();

				cursorPos.x -= size.x;
				cursorPos.y -= size.y;

				if (dragPos.x == 0)
				{
					dragPos.x = (cursorPos.x - pos->x);
					dragPos.y = (cursorPos.y - pos->y);
				}
				pos->x = cursorPos.x - dragPos.x;
				pos->y = cursorPos.y - dragPos.y;
			}
			else
			{
				dragPos = Vector2{ 0, 0 };
			}
		}
		else
		{
			hover_element = false;
		}


		offset_x = 0.0f; offset_y = 0.0f;
		menu_pos = Vector2{ pos->x, pos->y };
		first_element_pos = Vector2{ 0, 0 };
		current_element_pos = Vector2{ 0, 0 };
		current_element_size = Vector2{ 0, 0 };

		//Bg
		drawFilledRect(Vector2{ pos->x, pos->y }, size.x, size.y, Colors::Window_Background);
		//drawFilledRect(Vector2{ pos->x, pos->y }, 122, size.y, FLinearColor{ 0.006f, 0.006f, 0.006f, 1.0f });//My tabs bg

		//Header
		drawFilledRect(Vector2{ pos->x, pos->y }, size.x, 25.0f, Colors::Window_Header);

		offset_y += 25.0f;

		//Title
		Vector2 titlePos = Vector2{ pos->x + size.x / 2, pos->y + 25 / 2 };
		TextCenter(name, titlePos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		return true;
	}

	void Text(const char* text, bool center = false, bool outline = false)
	{
		elements_count++;

		float size = 25;
		Vector2 padding = Vector2{ 10, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		if (!sameLine)
			offset_y += size + padding.y;

		//Text
		Vector2 textPos = Vector2{ pos.x + 5.0f, pos.y + size / 2 };
		if (center)
			TextCenter(text, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
		else
			TextLeft(text, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);

		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}
	bool ButtonTab(const char* name, Vector2 size, bool active)
	{
		elements_count++;

		Vector2 padding = Vector2{ 5, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);

		//Bg
		if (active)
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Active);
		}
		else if (isHovered)
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
		TextCenter(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}
	bool Button(const char* name, Vector2 size)
	{
		elements_count++;

		Vector2 padding = Vector2{ 5, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);

		//Bg
		if (isHovered)
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
		//if (!TextOverlapedFromActiveElement(textPos))
		TextCenter(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}
	void Checkbox(const char* name, bool* value)
	{
		elements_count++;

		float size = 18;
		Vector2 padding = Vector2{ 10, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ size, size });

		//Bg
		if (isHovered)
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
		}

		if (!sameLine)
			offset_y += size + padding.y;

		if (*value)
		{
			drawFilledRect(Vector2{ pos.x + 3, pos.y + 3 }, size - 6, size - 6, Colors::Checkbox_Enabled);
			//drawFilledRect(Vector2{ pos.x + 9, pos.y + 9 }, size - 18, size - 18, Colors::Checkbox_Hovered);
		}



		//Text
		Vector2 textPos = Vector2{ pos.x + size + 10, (pos.y + size / 2) - 7};
		//if (!TextOverlapedFromActiveElement(textPos))
		TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			*value = !*value;
	}
	void SliderInt(char* name, int* value, int min, int max)
	{
		elements_count++;

		Vector2 size = Vector2{ 240, 50 };
		Vector2 slider_size = Vector2{ 200, 10 };
		Vector2 padding = Vector2{ 10, 15 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size);

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				Vector2 cursorPos = CursorPos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered);
			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress);

			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle);
			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress);
		}


		//Value
		float oneP = slider_size.x / (max - min);
		drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress);
		//drawFilledRect(Vector2{ pos.x + oneP * (*value - min) - 10.0f, pos.y + slider_size.y - 5.0f + padding.y }, 20.0f, 20.0f, Colors::Slider_Button);
		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 3.3f + padding.y }, 10.0f, Colors::Slider_Button);
		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 3.3f + padding.y }, 5.0f, Colors::Slider_Progress);

		char buffer[32];
		sprintf_s(buffer, "%i", *value);
		Vector2 valuePos = Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 25 + padding.y };
		TextCenter(buffer, valuePos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		//Text
		Vector2 textPos = Vector2{ pos.x + 5, pos.y + 10 };
		TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}
	void SliderFloat(const char* name, float* value, float min, float max, const char* format = "%.0f")
	{
		elements_count++;

		Vector2 size = Vector2{ 210, 40 };
		Vector2 slider_size = Vector2{ 170, 7 };
		Vector2 adjust_zone = Vector2{ 0, 20 };
		Vector2 padding = Vector2{ 10, 15 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, Vector2{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				Vector2 cursorPos = CursorPos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered);
			DrawFilledCircle(Vector2{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
			DrawFilledCircle(Vector2{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Hovered);

			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle);
			DrawFilledCircle(Vector2{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
			DrawFilledCircle(Vector2{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Idle);
		}


		//Text
		Vector2 textPos = Vector2{ pos.x, pos.y  };
		TextLeft(name, textPos, Colors::Text, false);

		//Value
		float oneP = slider_size.x / (max - min);
		drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress);
		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 8.0f, Colors::Slider_Button);
		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 4.0f, Colors::Slider_Progress);

		char buffer[32];
		sprintf_s(buffer, format, *value);
		Vector2 valuePos = Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 20 + padding.y };
		TextCenter(buffer, valuePos, Colors::Text, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}



	bool checkbox_enabled[256];
	void Combobox(const char* name, Vector2 size, int* value, const char* arg, ...)
	{
		elements_count++;

		Vector2 padding = Vector2{ 5, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);

		//Bg
		if (isHovered || checkbox_enabled[elements_count])
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Combobox_Hovered);

			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Combobox_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		Vector2 textPos = Vector2{ pos.x + size.x + 5.0f, pos.y + size.y / 2 };
		TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		//Elements
		bool isHovered2 = false;
		Vector2 element_pos = pos;
		int num = 0;

		if (checkbox_enabled[elements_count])
		{
			current_element_size.x = element_pos.x - 5.0f;
			current_element_size.y = element_pos.y - 5.0f;
		}
		va_list arguments;
		for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char*))
		{
			//Selected Element
			if (num == *value)
			{
				Vector2 _textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
				TextCenter((char*)arg, _textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}

			if (checkbox_enabled[elements_count])
			{
				element_pos.y += 25.0f;

				isHovered2 = MouseInZone(Vector2{ element_pos.x, element_pos.y }, Vector2{ size.x, 25.0f });
				if (isHovered2)
				{
					hover_element = true;
					PostRenderer::drawFilledRect(Vector2{ element_pos.x, element_pos.y }, size.x, 25.0f, Colors::Combobox_Hovered);

					//Click
					if (Input::IsMouseClicked(0, elements_count, false))
					{
						*value = num;
						checkbox_enabled[elements_count] = false;
					}
				}
				else
				{
					PostRenderer::drawFilledRect(Vector2{ element_pos.x, element_pos.y }, size.x, 25.0f, Colors::Combobox_Idle);
				}

				PostRenderer::TextLeft((char*)arg, Vector2{ element_pos.x + 5.0f, element_pos.y + 10.0f }, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}
			num++;
		}
		va_end(arguments);
		if (checkbox_enabled[elements_count])
		{
			current_element_size.x = element_pos.x + 5.0f;
			current_element_size.y = element_pos.y + 5.0f;
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
		}
		if (!isHovered && !isHovered2 && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = false;
		}
	}

	int active_hotkey = -1;
	bool already_pressed = false;
	std::string VirtualKeyCodeToString(UCHAR virtualKey)
	{
		UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

		if (virtualKey == VK_LBUTTON)
		{
			return xorstr("MOUSE0");
		}
		if (virtualKey == VK_RBUTTON)
		{
			return xorstr("MOUSE1");
		}
		if (virtualKey == VK_MBUTTON)
		{
			return xorstr("MBUTTON");
		}
		if (virtualKey == VK_XBUTTON1)
		{
			return xorstr("XBUTTON1");
		}
		if (virtualKey == VK_XBUTTON2)
		{
			return xorstr("XBUTTON2");
		}

		CHAR szName[128];
		int result = 0;
		switch (virtualKey)
		{
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
			scanCode |= KF_EXTENDED;
		default:
			result = GetKeyNameTextA(scanCode << 16, szName, 128);
		}

		return szName;
	}
	void Hotkey(const char* name, Vector2 size, int* key)
	{
		elements_count++;

		Vector2 padding = Vector2{ 5, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);

		//Bg
		if (isHovered)
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		if (active_hotkey == elements_count)
		{
			//Text
			Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
			TextCenter(xorstr("[Press Key]"), textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (!ZeroGUI::Input::IsAnyMouseDown())
			{
				already_pressed = false;
			}

			if (!already_pressed)
			{
				for (int code = 0; code < 255; code++)
				{
					if (safe_call(GetAsyncKeyState)(code))
					{
						*key = code;
						active_hotkey = -1;
					}
				}
			}
		}
		else
		{
			//Text
			Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
			TextCenter((char*)VirtualKeyCodeToString(*key).c_str(), textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (isHovered)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					already_pressed = true;
					active_hotkey = elements_count;

					//Queue Fix
					for (int code = 0; code < 255; code++)
						if (safe_call(GetAsyncKeyState)(code)) {}
				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					active_hotkey = -1;
				}
			}
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	int active_picker = -1;
	ue::FLinearColor saved_color;
	bool ColorPixel(Vector2 pos, Vector2 size, ue::FLinearColor* original, ue::FLinearColor color)
	{
		PostRenderer::drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, color);

		//Выбранный цвет
		if (original->R == color.R && original->G == color.G && original->B == color.B)
		{
			PostRenderer::Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x + size.x - 1, pos.y }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(Vector2{ pos.x, pos.y + size.y - 1 }, Vector2{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x, pos.y + size.y - 1 }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(Vector2{ pos.x + size.x - 1, pos.y }, Vector2{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, ue::FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
		}

		//Смена цвета
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
		if (isHovered)
		{
			if (Input::IsMouseClicked(0, elements_count, false))
				*original = color;
		}

		return true;
	}
	void ColorPicker(const char* name, ue::FLinearColor* color)
	{
		elements_count++;

		float size = 25;
		Vector2 padding = Vector2{ 10, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ size, size });

		if (!sameLine)
			offset_y += size + padding.y;

		if (active_picker == elements_count)
		{
			hover_element = true;

			float sizePickerX = 250;
			float sizePickerY = 250;
			bool isHoveredPicker = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ sizePickerX, sizePickerY - 60 });

			//Background
			PostRenderer::drawFilledRect(Vector2{ pos.x, pos.y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);

			//float pixedSize = sizePickerY / pixels;
			//FLinearColor temp_color{1.0f, 1.0f, 1.0f, 1.0f};
			//float iterator = 0.0f;
			//
			//for (int y = 0; y < pixels; y++)
			//{
			//	for (int x = 0; x < pixels; x++)
			//	{
			//		ColorPixel(Vector2{ pos.x + pixedSize * x, pos.y + pixedSize * y }, pixedSize, color, temp_color);
			//		temp_color.R -= (1.0f - saved_color.R) / pixels;
			//		temp_color.G -= (1.0f - saved_color.G) / pixels;
			//		temp_color.B -= (1.0f - saved_color.B) / pixels;
			//	}
			//	
			//	iterator += 1.0f / pixels;
			//	temp_color = FLinearColor{ 1.0f - iterator, 1.0f - iterator, 1.0f - iterator, 1.0f };
			//}

			Vector2 pixelSize = Vector2{ sizePickerX / 12, sizePickerY / 12 };

			//0
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
			}
			//1
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
			}
			//2
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
			}
			//3
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
			}
			//4
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
			}
			//5
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
			}
			//6
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
			}
			//7
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
			}
			//8
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
			}
			//9
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
			}
			//10
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
			}
			//11
			{
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 0 }, pixelSize, color, ue::FLinearColor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 1 }, pixelSize, color, ue::FLinearColor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 2 }, pixelSize, color, ue::FLinearColor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 3 }, pixelSize, color, ue::FLinearColor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 4 }, pixelSize, color, ue::FLinearColor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 5 }, pixelSize, color, ue::FLinearColor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 6 }, pixelSize, color, ue::FLinearColor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 7 }, pixelSize, color, ue::FLinearColor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
				ColorPixel(Vector2{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 8 }, pixelSize, color, ue::FLinearColor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
			}



			if (isHoveredPicker)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{

				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					active_picker = -1;
					//hover_element = false;
				}
			}
		}
		else
		{
			//Bg
			if (isHovered)
			{
				drawFilledRect(Vector2{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
				hover_element = true;
			}
			else
			{
				drawFilledRect(Vector2{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
			}

			//Color
			drawFilledRect(Vector2{ pos.x + 4, pos.y + 4 }, size - 8, size - 8, *color);

			//Text
			Vector2 textPos = Vector2{ pos.x + size + 5.0f, pos.y + size / 2 };
			TextLeft(name, textPos, ue::FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			{
				saved_color = *color;
				active_picker = elements_count;
			}
		}


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}


	void Render()
	{
		for (int i = 0; i < 128; i++)
		{
			if (PostRenderer::drawlist[i].type != -1)
			{
				//Filled Rect
				if (PostRenderer::drawlist[i].type == 1)
				{
					ZeroGUI::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
				}
				//TextLeft
				else if (PostRenderer::drawlist[i].type == 2)
				{
					ZeroGUI::TextLeft(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//TextCenter
				else if (PostRenderer::drawlist[i].type == 3)
				{
					ZeroGUI::TextCenter(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//Draw_Line
				else if (PostRenderer::drawlist[i].type == 4)
				{
					Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
				}

				PostRenderer::drawlist[i].type = -1;
			}
		}
	}
}
bool ShowMenu = true;

namespace Settings
{
	//Aim
	static bool MemoryAim = 0; //Done
	static bool pmemory = 0; //Done
	static bool SilentAim = 0; //Done
	static bool SniperTp = 0; //Done
	int BoneTarget = 1;
	static int AimBone = 66;
	static float MemoryAimSmooth = 0; //Done

	static bool fov360 = 0; //Done
	static float FovCircle_Value = 430; //Done



	//Player ESP
	static bool BoxESP = 1; //Done
	static bool SkeletonESP = 0; //Done
	static bool LinesESP = 0; //Done
	static bool PlayerNameESP = 0; //Done
	static bool DistanceESP = 0; //Done
	static bool LevelESP = 0; //Done
	static bool KillsESP = 0; //Done
	static bool PlatformESP = 0; //Done
	static bool EnemyWeaponESP = 0; //Done
	static bool AmmoESP = 0; //Done
	static bool RadarESP = 0;
	static float RadarESPRange = 7000.f;
	static int RadarESPOpacity = 255;


	//Exploits
	static bool NoSpread = 0; //Done
	static bool Chams = 0; //Done
	static bool Invisible = 0; //Done
	static bool InstantRevive = 0; //Done
	static bool AimWhileJumping = 0; //Done
	static bool resources = 0;
	static bool RapidFire = 0;
	static float RapidFireValue = 0.001f;
	static bool FirstCamera = 0; //Done
	static bool InstantReload = 0; //Done
	static bool SpeedStuff = 0; //Done
	static float CustomSpeedStuff = 0; //Done

	//Fov Changer
	static bool FovChanger = 0; //Done
	static float FovChanger_Value = 80.f; //Done

	//Boat Speed
	static bool VehicleSpeed = 0;
	static float VehicleSpeedValue = 30.f;

	//Car Exploits
	static bool CarFly = 0; //Done
	static bool CarTpToPing = 0; //Done
	static bool CarTpToPlayer = 0; //Done
	static bool TP_Locations_Start = 0; //Done
	static int TP_Locations = 0; //Done


	static bool TPToAimingPlayer = 0; //Done


	//Misc

	static float MaxESPDistance = 300; //Done
	static bool ShowFovCircle = true; //Done

	static bool PanicButtonFeature = true;
	static bool PanicButtonON = false;



}
int tabs = 0;
float FovSize = 200;
float inr;
float ing;
float inb;
float ino;

float outr;
float outg;
float outb;
float outo;
Vector3 galgan(Vector3& zaz, Vector3& daz) {

	Vector3 dalte = zaz - daz;
	Vector3 ongle;
	float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
	ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
	ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;
	if (dalte.x >= 0.f) ongle.y += 180.f;
	return ongle;
}
#define D2R(d) (d / 180.f) * M_PI
#define MAX_SEGMENTS 180
void Pasted_line(Vector2 one, Vector2 two, ue::FLinearColor color)
{
	static_canvas->K2_DrawLine(one, two, 1, color);
}
void Pasted_PointArray(size_t count, Vector2* ary, ue::FLinearColor color)
{
	for (size_t i = 1; i < count; ++i)
		Pasted_line(ary[i - 1], ary[i], color);
}

int myceilf(float num)
{
	int inum = (int)num;
	if (num == (float)inum) {
		return inum;
	}
	return inum + 1;
}
void Pasted_CircleOutline(Vector2 pos, int r, ue::FLinearColor outline)
{
	float circum = M_PI * 2.f * r;
	int seg = myceilf(circum);

	if (seg > MAX_SEGMENTS) seg = MAX_SEGMENTS;

	float theta = 0.f;
	float step = 360.f / seg;

	Vector2 points[MAX_SEGMENTS] = {};

	for (size_t i = 0; i < seg; ++i)
	{
		theta = i * step;
		points[i] = Vector2(pos.x + roundf(r * sin(D2R(theta))), pos.y + roundf(r * cos(D2R(theta))));
	}

	Pasted_PointArray(seg, points, outline);
}