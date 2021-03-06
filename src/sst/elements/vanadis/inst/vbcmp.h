
#ifndef _H_VANADIS_BRANCH_REG_COMPARE
#define _H_VANADIS_BRANCH_REG_COMPARE

#include "inst/vspeculate.h"
#include "inst/vcmptype.h"

#include "util/vcmpop.h"

namespace SST {
namespace Vanadis {

class VanadisBranchRegCompareInstruction : public VanadisSpeculatedInstruction {
public:
	VanadisBranchRegCompareInstruction(
                const uint64_t addr,
                const uint32_t hw_thr,
                const VanadisDecoderOptions* isa_opts,
		const uint16_t src_1,
		const uint16_t src_2,
		const int64_t offst,
		const VanadisDelaySlotRequirement delayT,
		const VanadisRegisterCompareType cType,
		const VanadisRegisterFormat fmt
		) :
		VanadisSpeculatedInstruction(addr, hw_thr, isa_opts, 2, 0, 2, 0, 0, 0, 0, 0, delayT),
			offset(offst), compareType(cType), reg_format(fmt) {
		isa_int_regs_in[0] = src_1;
		isa_int_regs_in[1] = src_2;
	}

	VanadisBranchRegCompareInstruction* clone() {
		return new VanadisBranchRegCompareInstruction( *this );
	}

	virtual const char* getInstCode() const {
		switch( compareType ) {
		case REG_COMPARE_EQ:
			return "BCMP_EQ";
		case REG_COMPARE_NEQ:
			return "BCMP_NEQ";
		case REG_COMPARE_LT:
			return "BCMP_LT";
		case REG_COMPARE_LTE:
			return "BCMP_LTE";
		case REG_COMPARE_GT:
			return "BCMP_GT";
		case REG_COMPARE_GTE:
			return "BCMP_GTE";
		default:
			return "Unknown";
		}
	}

	virtual void printToBuffer(char* buffer, size_t buffer_size ) {
		snprintf( buffer, buffer_size, "BCMP (%s) isa-in: %" PRIu16 ", %" PRIu16 " / phys-in: %" PRIu16 ", %" PRIu16 " offset: %" PRId64 "\n",
			convertCompareTypeToString(compareType), isa_int_regs_in[0], isa_int_regs_in[1], phys_int_regs_in[0], phys_int_regs_in[1], offset);
	}

	virtual void execute( SST::Output* output, VanadisRegisterFile* regFile ) {

		output->verbose(CALL_INFO, 16, 0, "Execute: (addr=0x%0llx) BCMP (%s) isa-in: %" PRIu16 ", %" PRIu16 " / phys-in: %" PRIu16 ", %" PRIu16 " offset: %" PRId64 "\n",
			getInstructionAddress(), convertCompareTypeToString(compareType),isa_int_regs_in[0],
			isa_int_regs_in[1], phys_int_regs_in[0], phys_int_regs_in[1], offset );

		bool compare_result = false;

		switch( reg_format ) {
		case VANADIS_FORMAT_INT64:
			{
				compare_result = registerCompare<int64_t>( compareType, regFile, this, output, phys_int_regs_in[0], phys_int_regs_in[1] );
			}
			break;
		case VANADIS_FORMAT_INT32:
			{
				compare_result = registerCompare<int32_t>( compareType, regFile, this, output, phys_int_regs_in[0], phys_int_regs_in[1] );
			}
			break;
		default:
			{
				flagError();
			}
			break;
		}

		if( compare_result ) {
			takenAddress = (uint64_t) ( ((int64_t) getInstructionAddress()) +  offset + VANADIS_SPECULATE_JUMP_ADDR_ADD );

			output->verbose(CALL_INFO, 16, 0, "-----> taken-address: 0x%llx + %" PRId64 " + %d = 0x%llx\n",
				getInstructionAddress(), offset, VANADIS_SPECULATE_JUMP_ADDR_ADD, takenAddress);
		} else {
			takenAddress = calculateStandardNotTakenAddress();

			output->verbose(CALL_INFO, 16, 0, "-----> not-taken-address: 0x%llx\n", takenAddress);
		}

		markExecuted();
	}

protected:
	const int64_t offset;
	VanadisRegisterFormat reg_format;
	VanadisRegisterCompareType compareType;

};

}
}

#endif
