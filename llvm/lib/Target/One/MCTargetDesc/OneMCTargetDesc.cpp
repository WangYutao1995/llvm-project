#include "OneMCTargetDesc.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/OneTargetInfo.h"
#include "OneMCAsmInfo.h"
#include "OneInstrInfo.h"
#include "OneRegisterInfo.h"
#include "OneSubtarget.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "OneGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "OneGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "OneGenRegisterInfo.inc"

static MCAsmInfo *createOneMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
    return new OneMCAsmInfo(TT);
}

static MCRegisterInfo *createOneMCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new OneRegisterInfo();
    InitOneMCRegisterInfo(X, One::X1);
    return X;
}

static MCInstrInfo *createOneMCInstrInfo() {
    MCInstrInfo *X = new OneInstrInfo();
    InitOneMCInstrInfo(X);
    return X;
}

static MCSubtargetInfo *createOneMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
    if (CPU.empty() || CPU == "generic") {
        CPU = "one";
    }
    return createOneMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOneTargetMC() {
    TargetRegistry::RegisterMCAsmInfo(getTheOneTarget(), createOneMCAsmInfo);
    TargetRegistry::RegisterMCRegInfo(getTheOneTarget(), createOneMCRegisterInfo);
    TargetRegistry::RegisterMCInstrInfo(getTheOneTarget(), createOneMCInstrInfo);
    TargetRegistry::RegisterMCSubtargetInfo(getTheOneTarget(), createOneMCSubtargetInfo);
}
