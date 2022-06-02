#pragma once

namespace Durna
{
	struct TimeCode
	{
		TimeCode(int32 InHours, int32 InMinutes, int32 InSeconds)
			: Hours(InHours), Minutes(InMinutes), Seconds(InSeconds)
		{ }

		TimeCode()	: TimeCode(0, 0, 0)
		{ }

		TimeCode(int32 InSeconds)
		{
			Seconds = InSeconds;
			Minutes = Seconds / 60;
			Hours = Minutes / 60;

			Seconds %= 60;
			Minutes %= 60;
			Hours	%= 24;
		}

		int32 Hours;
		int32 Minutes;
		int32 Seconds;
	};
}

