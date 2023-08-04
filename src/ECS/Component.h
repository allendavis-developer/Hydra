#pragma once
#include <string>

namespace Hydra {
	class Component
	{
		virtual std::string GetStringName() const { return "DefaultComponentName"; }
	};
}