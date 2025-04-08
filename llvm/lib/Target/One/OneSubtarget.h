#ifndef LLVM_LIB_TARGET_ONE_ONESUBTARGET_H
#define LLVM_LIB_TARGET_ONE_ONESUBTARGET_H

#include "OneInstrInfo.h"
#include "OneRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "OneGenSubtargetInfo.inc"

namespace llvm {

class OneSubtarget : public OneGenSubtargetInfo {
private:
    OneInstrInfo InstrInfo;
    OneRegisterInfo RegInfo;
public:
    OneSubtarget(const Triple &&TT,
                 StringRef CPU, StringRef FS, const TargetMachine &TM);
    OneSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS, const TargetMachine &TM);
    const OneInstrInfo *getInstrInfo() const override { return &InstrInfo; }
    const OneRegisterInfo *getRegisterInfo() const override { return &RegInfo; }
};
}

#endif