#pragma once

namespace Hydra {
	class Component
	{
		virtual std::string GetStringName() const { return "DefaultComponentName"; }
	};
}