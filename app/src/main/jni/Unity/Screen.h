#pragma once

namespace UnityEngine
{
	namespace Screen
	{
		static int (*Height)();
		static int (*Width)();
		static bool is_done = false;

		void Setup()
		{
			Height = (int(*)()) POINTER("0x1B88560");
			Width = (int(*)()) POINTER("0x1B884DC");
			is_done = true;
		}
	}
}