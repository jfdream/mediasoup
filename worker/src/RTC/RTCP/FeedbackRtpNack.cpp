#define MS_CLASS "RTC::RTCP::FeedbackRtpNack"
// #define MS_LOG_DEV

#include "RTC/RTCP/FeedbackRtpNack.hpp"
#include "Logger.hpp"
#include <bitset> // std::bitset()
#include <cstring>

namespace RTC
{
	namespace RTCP
	{
		/* Instance methods. */
		FeedbackRtpNackItem::FeedbackRtpNackItem(uint16_t packetId, uint16_t lostPacketBitmask)
		{
			this->raw    = new uint8_t[sizeof(Header)];
			this->header = reinterpret_cast<Header*>(this->raw);

			this->header->packetId          = uint16_t{ htons(packetId) };
			this->header->lostPacketBitmask = uint16_t{ htons(lostPacketBitmask) };
		}

		size_t FeedbackRtpNackItem::Serialize(uint8_t* buffer)
		{
			MS_TRACE();

			// Add minimum header.
			std::memcpy(buffer, this->header, sizeof(Header));

			return sizeof(Header);
		}

		void FeedbackRtpNackItem::Dump() const
		{
			MS_TRACE();

			std::bitset<16> nackBitset(this->GetLostPacketBitmask());

			MS_DUMP("<FeedbackRtpNackItem>");
			MS_DUMP("  pid : %" PRIu16, this->GetPacketId());
			MS_DUMP("  bpl : %s", nackBitset.to_string().c_str());
			MS_DUMP("</FeedbackRtpNackItem>");
		}
	} // namespace RTCP
} // namespace RTC
