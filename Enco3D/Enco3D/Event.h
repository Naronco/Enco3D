#ifndef _ENCO3D_EVENT_H_
#define _ENCO3D_EVENT_H_
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		/// <summary>Enumeration of event types</summary>
		enum DLL_EXPORT EventType
		{
			Quit,
			Window,
			KeyDown,
			KeyUp,
			MouseMove,
			MouseClick,
			MouseRelease,
			MouseWheel,
			JoystickAxis,
			JoystickBall,
			JoystickHat,
			JoystickButtonDown,
			JoystickButtonUp,
			JoystickAdded,
			JoystickRemoved,
			ControllerAxis,
			ControllerButtonDown,
			ControllerButtonUp,
			ControllerAdded,
			ControllerRemoved,
			DropFile,
			User
		};

		/// <summary>The hat data in the struct "Event"</summary>
		struct DLL_EXPORT HatData
		{
			unsigned char value;
			unsigned char hatIndex;
		};

		/// <summary>The ball data in the struct "Event"</summary>
		struct DLL_EXPORT BallData
		{
			unsigned char ballIndex;
			short x;
			short y;
		};

		/// <summary>The button data in the struct "Event"</summary>
		struct DLL_EXPORT ButtonData
		{
			unsigned char button;
		};

		/// <summary>The axis data in the struct "Event"</summary>
		struct DLL_EXPORT AxisData
		{
			unsigned char axis;
			short value;
		};

		/// <summary>The keyboard data in the struct "Event"</summary>
		struct DLL_EXPORT KeyboardData
		{
			unsigned short modifiers;
			int keyCode;
		};

		/// <summary>The mouse button data in the struct "Event"</summary>
		struct DLL_EXPORT MouseButtonData
		{
			unsigned char button;
			int x, y;
		};

		/// <summary>The scroll data in the struct "Event"</summary>
		struct DLL_EXPORT ScrollData
		{
			int x, y;
		};

		/// <summary>The motion data in the struct "Event"</summary>
		struct DLL_EXPORT MotionData
		{
			int destinationX;
			int destinationY;
			int relativeX;
			int relativeY;
		};

		/// <summary>The window data in the struct "Event"</summary>
		struct DLL_EXPORT WindowData
		{
			unsigned char event;
			int data1, data2;
		};

		/// <summary>The user specific data in the struct "Event"</summary>
		struct DLL_EXPORT UserData
		{
			int code;
			void *data1, *data2;
		};

		/// <summary>Contains the type of the event, the window, the event id and the data of the event</summary>
		struct DLL_EXPORT Event
		{
			EventType type;
			unsigned int window;
			unsigned int id;
			MouseButtonData mouseButton;
			AxisData cjAxis;
			ButtonData cjButton;
			HatData hat;
			BallData ball;
			KeyboardData keyboard;
			ScrollData scroll;
			MotionData mouseMove;
			WindowData windowEvent;
			UserData user;
			char* file;
		};
	}
}

#endif