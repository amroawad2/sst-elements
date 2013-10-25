
#ifndef _H_SST_ARIEL_EVENT
#define _H_SST_ARIEL_EVENT

#include <sst/core/sst_types.h>
#include <sst/core/event.h>
#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/timeConverter.h>

#include <sst/core/interfaces/memEvent.h>
#include <sst/core/output.h>
#include <sst/elements/memHierarchy/dmaEngine.h>

#include <map>

using namespace SST;

namespace SST {
namespace ArielComponent {

enum ArielEventType {
	READ_ADDRESS,
	WRITE_ADDRESS,
	START_DMA_TRANSFER,
	WAIT_ON_DMA_TRANSFER,
	CORE_EXIT
};

class ArielEvent {

	public:
		ArielEvent();
		~ArielEvent();
		virtual ArielEventType getEventType() = 0;

};

}
}

#endif
