#include "Event.h"

namespace Hydra {
	class EditorCameraAddOffsetEvent : public Event
	{
	public:
		EditorCameraAddOffsetEvent(Vector2<float> offset)
			: m_Offset(offset)
		{

		}

		inline Vector2<float> GetOffset() const { return m_Offset; }
	private:
		Vector2<float> m_Offset;
	};
}