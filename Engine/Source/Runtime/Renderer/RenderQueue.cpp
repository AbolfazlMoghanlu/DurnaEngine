#include "DurnaPCH.h"
#include "RenderQueue.h"

namespace Durna
{
	void RenderQueue::Clear(uint32 SlackSize /*= 0*/)
	{
		Queue.clear();
		Queue.reserve(SlackSize);
	}

	void RenderQueue::AddPrimitive(PrimitiveComponent* Pr)
	{
		Queue.push_back(Pr);
	}

	void RenderQueue::Resize(uint32 Size)
	{
		Queue.resize(Size);
	}

	void RenderQueue::Reserve(uint32 Size)
	{
		Queue.reserve(Size);
	}
}