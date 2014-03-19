#ifndef _ENCO3D_INPUT_H_
#define _ENCO3D_INPUT_H_

#include <SDL.h>

/// <summary>Enumeration of the mouse button ids</summary>
enum MouseButton
{
	Left   = 1,
	Middle = 2,
	Right  = 3,
};

/// <summary>The wrapper of the input events, doens't needs to be instanced</summary>
class Input
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
		m_keys = new bool[256];
		for (int i = 0; i < 256; i++)
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
	inline static void SetKey(int keyCode, bool down) { m_keys[keyCode] = down; }

	/// <summary>Sets a mouse button state</summary>
	/// <param name="mouseButton">The id of the mouse button</summary>
	/// <param name="down">True = the button is pressed; False = The button is not pressed</summary>
	inline static void SetMouseButton(int mouseButton, bool down) { m_mouseButtons[mouseButton] = down; }

	/// <summary>Sets the mouse position internally, if you want to set the cursor position, use the GLWindow class</summary>
	/// <param name="mouseX">The X coordinate of the mouse</summary>
	/// <param name="mouseY">The Y coordinate of the mouse</summary>
	inline static void SetMousePos(int mouseX, int mouseY) { m_mouseX = mouseX; m_mouseY = mouseY; }

	/// <summary>Sets the motion of the mouse since the last frame internally</summary>
	/// <param name="relativeX">The X motion of the mouse</summary>
	/// <param name="relativeY">The Y motion of the mouse</summary>
	inline static void SetRelativeMouse(int relativeX, int relativeY) { m_relativeX = relativeX; m_relativeY = relativeY; }

	/// <summary>Returns true, if the key is pressed</summary>
	/// <param name="keyCode">The id of the key</summary>
	inline static bool IsKeyDown(int keyCode) { return m_keys[keyCode]; }

	/// <summary>Returns true, if the mouse button is pressed</summary>
	/// <param name="mouseButton">The id of the mouse button, use the enumeration "MouseButton"</summary>
	inline static bool IsMouseButtonDown(int mouseButton) { return m_mouseButtons[mouseButton]; }

	/// <summary>Returns the X coordinate of the mouse relative to the window</summary>
	inline static int GetMouseX() { return m_mouseX; }

	/// <summary>Returns the Y coordinate of the mouse relative to the window</summary>
	inline static int GetMouseY() { return m_mouseY; }

	/// <summary>Returns the X motion of the mouse since the last frame</summary>
	inline static int GetRelativeX() { return m_relativeX; }

	/// <summary>Returns the Y motion of the mouse since the last frame</summary>
	inline static int GetRelativeY() { return m_relativeY; }
};

#endif