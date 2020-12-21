
#include <sst_config.h>
#include <sst/core/output.h>

#include <cstdio>
#include <vector>

#include "WolfPIM.h"

using namespace SST::WolfPIM;

WolfPIMComponent::WolfPIMComponent(SST::ComponentId_t id, SST::Params& params) :
	Component(id) {







	registerAsPrimaryComponent();
    	primaryComponentDoNotEndSim();
}

WolfPIMComponent::~WolfPIMComponent() {

}

bool WolfPIMComponent::tick(SST::Cycle_t cycle) {
//	if( current_cycle >= max_cycle ) {
//		output->verbose(CALL_INFO, 1, 0, "Reached maximum cycle %" PRIu64 ". Core stops processing.\n", current_cycle );
		primaryComponentOKToEndSim();
//		return true;
//	}
}



void WolfPIMComponent::setup() {

}

void WolfPIMComponent::finish() {

}


void WolfPIMComponent::init(unsigned int phase) {

}

