#ifndef _ENCO3D_INPUT_H_
#define _ENCO3D_INPUT_H_

#include <SDL.h>
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		namespace Mouse
		{
			/// <summary>Enumeration of the mouse button ids</summary>
			enum MouseButton : unsigned int
			{
				Left = 1,
				Middle = 2,
				Right = 3,
			};
		}

		namespace Keyboard
		{
			enum KeyboardKey : unsigned int
			{
				Unknown = 0,
				A = 4,
				B = 5,
				C = 6,
				D = 7,
				E = 8,
				F = 9,
				G = 10,
				H = 11,
				I = 12,
				J = 13,
				K = 14,
				L = 15,
				M = 16,
				N = 17,
				O = 18,
				P = 19,
				Q = 20,
				R = 21,
				S = 22,
				T = 23,
				U = 24,
				V = 25,
				W = 26,
				X = 27,
				Y = 28,
				Z = 29,
				One = 30,
				Two = 31,
				Three = 32,
				Four = 33,
				Five = 34,
				Six = 35,
				Seven = 36,
				Eight = 37,
				Nine = 38,
				Zero = 39,
				Return = 40,
				Escape = 41,
				Backspace = 42,
				Tab = 43,
				Space = 44,
				Minus = 45,
				Equals = 46,
				LeftBracket = 47,
				RightBracket = 48,
				Backslash = 49,
				Semicolon = 51,
				Apostrophe = 52,
				Grave = 53,
				Comma = 54,
				Period = 55,
				Slash = 56,
				Capslock = 57,
				F1 = 58,
				F2 = 59,
				F3 = 60,
				F4 = 61,
				F5 = 62,
				F6 = 63,
				F7 = 64,
				F8 = 65,
				F9 = 66,
				F10 = 67,
				F11 = 68,
				F12 = 69,
				PrintScreen = 70,
				ScrollLock = 71,
				Pause = 72,
				Insert = 73,
				Home = 74,
				PageUp = 75,
				Delete = 76,
				End = 77,
				PageDown = 78,
				Right = 79,
				Left = 80,
				Down = 81,
				Up = 82,
				NumLockClear = 83,
				Num_Divide = 84,
				Num_Multiply = 85,
				Num_Minus = 86,
				Num_Plus = 87,
				Num_Enter = 88,
				Num_One = 89,
				Num_Two = 90,
				Num_Three = 91,
				Num_Four = 92,
				Num_Five = 93,
				Num_Six = 94,
				Num_Seven = 95,
				Num_Eight = 96,
				Num_Nine = 97,
				Num_Zero = 98,
				Num_Period = 99,
				Application = 101,
				Power = 102,
				Num_Equals = 103,
				F13 = 104,
				F14 = 105,
				F15 = 106,
				F16 = 107,
				F17 = 108,
				F18 = 109,
				F19 = 110,
				F20 = 111,
				F21 = 112,
				F22 = 113,
				F23 = 114,
				F24 = 115,
				Execute = 116,
				Help = 117,
				Menu = 118,
				Select = 119,
				Stop = 120,
				Redo = 121,
				Undo = 122,
				Cut = 123,
				Copy = 124,
				Paste = 125,
				Find = 126,
				Mute = 127,
				VolumeUp = 128,
				VolumeDown = 129,
				Num_Comma = 133,
				Num_EqualsAS400 = 134,
				International1 = 135,
				International2 = 136,
				International3 = 137,
				International4 = 138,
				International5 = 139,
				International6 = 140,
				International7 = 141,
				International8 = 142,
				International9 = 143,
				Lang1 = 144,
				Lang2 = 145,
				Lang3 = 146,
				Lang4 = 147,
				Lang5 = 148,
				Lang6 = 149,
				Lang7 = 150,
				Lang8 = 151,
				Lang9 = 152,
				AltErase = 153,
				SysReq = 154,
				Cancel = 155,
				Clear = 156,
				Prior = 157,
				Return2 = 158,
				Seperator = 159,
				Out = 160,
				Oper = 161,
				ClearAgain = 162,
				Ctrl = 224,
				RCtrl = 228,
				Shift = 225,
				RShift = 229,
				Alt = 226,
				RAlt = 230
			};
		}

		/// <summary>The wrapper of the input events, doens't needs to be instanced</summary>
		class DLL_EXPORT Input
		{
		private:
			/// <summary>Array of all the keys</summary>
			static bool *m_keys;

			/// <summary>Array of the mouse buttons</summary>
			static bool *m_mouseButtons;

			/// <summary>X coordinate of the mouse</summary>
			static int m_mouseX;

			/// <summary>Y coordinate of the mouse</summary>
			static int m_mouseY;

			/// <summary>The X motion of the mouse since the last frame</summary>
			static int m_relativeX;

			/// <summary>The Y motion of the mouse since the last frame</summary>
			static int m_relativeY;

		public:
			/// <summary>Initializes the input data</summary>
			inline static void Init()
			{
				m_keys = new bool[512];
				for (int i = 0; i < 512; i++)
				{
					m_keys[i] = false;
				}

				m_mouseButtons = new bool[8];
				for (int i = 0; i < 8; i++)
				{
					m_mouseButtons[i] = false;
				}
			}

			/// <summary>De-Initializes the input data</summary>
			inline static void Deinit()
			{
				if (m_keys)
				{
					delete[] m_keys;
					m_keys = nullptr;
				}

				if (m_mouseButtons)
				{
					delete[] m_mouseButtons;
					m_mouseButtons = nullptr;
				}
			}

			/// <summary>Sets a key state at the given key code</summary>
			/// <param name="keyCode">The id of the key</summary>
			/// <param name="down">True = the key is pressed; False = The key is not pressed</summary>
			inline static void setKey(int keyCode, bool down) { m_keys[keyCode] = down; }

			/// <summary>Sets a mouse button state</summary>
			/// <param name="mouseButton">The id of the mouse button</summary>
			/// <param name="down">True = the button is pressed; False = The button is not pressed</summary>
			inline static void setMouseButton(int mouseButton, bool down) { m_mouseButtons[mouseButton] = down; }

			/// <summary>Sets the mouse position internally, if you want to set the cursor position, use the GLWindow class</summary>
			/// <param name="mouseX">The X coordinate of the mouse</summary>
			/// <param name="mouseY">The Y coordinate of the mouse</summary>
			inline static void setMousePos(int mouseX, int mouseY) { m_mouseX = mouseX; m_mouseY = mouseY; }

			/// <summary>Sets the motion of the mouse since the last frame internally</summary>
			/// <param name="relativeX">The X motion of the mouse</summary>
			/// <param name="relativeY">The Y motion of the mouse</summary>
			inline static void setRelativeMouse(int relativeX, int relativeY) { m_relativeX = relativeX; m_relativeY = relativeY; }

			/// <summary>Returns true, if the key is pressed</summary>
			/// <param name="keyCode">The id of the key</summary>
			inline static bool isKeyDown(int keyCode) { return m_keys[keyCode]; }

			/// <summary>Returns true, if the mouse button is pressed</summary>
			/// <param name="mouseButton">The id of the mouse button, use the enumeration "MouseButton"</summary>
			inline static bool isMouseButtonDown(int mouseButton) { return m_mouseButtons[mouseButton]; }

			/// <summary>Returns the X coordinate of the mouse relative to the window</summary>
			inline static int getMouseX() { return m_mouseX; }

			/// <summary>Returns the Y coordinate of the mouse relative to the window</summary>
			inline static int getMouseY() { return m_mouseY; }

			/// <summary>Returns the X motion of the mouse since the last frame</summary>
			inline static int getRelativeX() { return m_relativeX; }

			/// <summary>Returns the Y motion of the mouse since the last frame</summary>
			inline static int getRelativeY() { return m_relativeY; }
		};
	}
}

#endif