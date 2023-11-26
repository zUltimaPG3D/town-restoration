#pragma once

namespace UnityEngine
{
	namespace Input
	{
		enum TouchPhase{
			Began,
			Moved,
			Stationary,
			Ended,
			Canceled
		};

		enum TouchType
		{
			Direct,
			Indirect,
			Stylus
		};

		struct Touch{
			int m_FingerId{};
			il2cppVector2 m_Position;
			il2cppVector2 m_RawPosition;
			il2cppVector2 m_PositionDelta;
			float m_TimeDelta{};
			int m_TapCount{};
			TouchPhase m_Phase{};
			TouchType m_Type{};
			float m_Pressure{};
			float m_maximumPossiblePressure{};
			float m_Radius{};
			float m_RadiusVariance{};
			float m_AltitudeAngle{};
			float m_AzimuthAngle{};
		};

		static bool is_done = false;

		bool (*GetMouseButtonDown)(int button);

		Touch (*old_FakeGetTouch)(int index);

		Touch FakeGetTouch(int index)
		{
			Touch _touch = old_FakeGetTouch(index);

			if (!init)
				return _touch;

			if (index == 0)
			{
				ImGuiIO &io = ImGui::GetIO();
				float x = _touch.m_Position.X;
				float y = static_cast<float>(std::round(UnityEngine::Screen::Height())) - _touch.m_Position.Y;

				if (_touch.m_Phase == TouchPhase::Began)
				{
					io.AddMousePosEvent(x,y);
					io.AddMouseButtonEvent(0, UnityEngine::Input::GetMouseButtonDown(0));
				}
				if (_touch.m_Phase == TouchPhase::Moved)
				{
					io.AddMousePosEvent(x,y);
				}
				if (_touch.m_Phase == TouchPhase::Ended)
				{
					io.AddMouseButtonEvent(0, UnityEngine::Input::GetMouseButtonDown(0));
					io.AddMouseButtonEvent(1, UnityEngine::Input::GetMouseButtonDown(1));
					io.AddMouseButtonEvent(2, UnityEngine::Input::GetMouseButtonDown(3));
				}

				if (io.WantCaptureMouse)
					return old_FakeGetTouch(-1);
			}

			return _touch;
		}

		void Setup()
		{
			GetMouseButtonDown = (bool(*)(int)) POINTER("0x17DABA4");
			HOOK("0x17DADF0", FakeGetTouch, old_FakeGetTouch);
			is_done = true;
		}
	}
}