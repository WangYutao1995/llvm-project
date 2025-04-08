#include "OneSubtarget.h"

using namespace llvm;

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "OneGenSubtargetInfo.inc"

OneSubtarget::OneSubtarget(const Triple &&TT,
             StringRef CPU, StringRef FS, const TargetMachine &TM)
    : OneGenSubtargetInfo(TT, CPU, CPU, FS) {
                
}

OneSubtarget &OneSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS, const TargetMachine &TM) {
    if (CPU.empty() || CPU == "generic") {
        CPU = "one";
    }
    ParseSubtargetFeatures(CPU, CPU, FS);

    return *this;
}