// Copyright 2009-2020 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2020, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef _VANADIS_COMPONENT_H
#define _VANADIS_COMPONENT_H

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/output.h>
#include <sst/core/params.h>

#include <array>
#include <set>
#include <limits>

namespace SST {
namespace WolfPIM {

class WolfPIMComponent : public SST::Component {
public:

    SST_ELI_REGISTER_COMPONENT(
        WolfPIMComponent,
        "WolfPIM",
        "WolfPIM_block",
        SST_ELI_ELEMENT_VERSION(1,0,0),
	"WolfPIM Processing-in-Memory Component",
        COMPONENT_CATEGORY_PROCESSOR
    )

    SST_ELI_DOCUMENT_PARAMS(
	{ "verbose", 		"Set the level of output verbosity, 0 is no output, higher is more output" },
	{ "max_cycles", 	"Maximum number of cycles to execute" },
	{ "print_fp_reg",		"Print floating-point registers true/false, auto set to true if verbose > 16" }
    )

    SST_ELI_DOCUMENT_STATISTICS(
        { "cycles",  "Number of cycles the core executed", "cycles", 1 },
        { "branches",             "Number of retired branches", "instructions", 1     },
        { "loads_issued", 		  "Number of load instructions issued to the LSQ",  "instructions", 1 },
        { "stores_issued",        "Number of store instructions issued to the LSQ", "instructions", 1 }
    )

    SST_ELI_DOCUMENT_PORTS(
    	{ "icache_link", "Connects the CPU to the instruction cache", {} },
    	{ "dcache_link", "Connects the CPU to the data cache", {} }
    )

    // Optional since there is nothing to document
   // SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS(
//		{ "lsq",                "Load-Store Queue for Memory Access", "SST::Vanadis::VanadisLoadStoreQueue" },
//		{ "mem_interface_inst", "Interface to memory system for instructions", "SST::Interfaces::SimpleMem" },
//		{ "decoder%(hardware_threads)d", "Instruction decoder for a hardware thread", "SST::Vanadis::VanadisDecoder" }
  //  )

    WolfPIMComponent( SST::ComponentId_t id, SST::Params& params );
    ~WolfPIMComponent();

    virtual void init(unsigned int phase);

    void setup();
    void finish();

    //void printStatus( SST::Output& output );

//    void handleIncomingDataCacheEvent( SimpleMem::Request* ev );


private:
    WolfPIMComponent();  // for serialization only
    WolfPIMComponent(const WolfPIMComponent&); // do not implement
    void operator=(const WolfPIMComponent&); // do not implement

    virtual bool tick(SST::Cycle_t);

    uint32_t ins_decoded_this_cycle;

};


} // namespace VanadisComponent
} // namespace SST

#endif /* _VANADIS_COMPONENT_H */
