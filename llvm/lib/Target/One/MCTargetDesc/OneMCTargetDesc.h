#ifndef LLVM_LIB_TARGET_ONE_MCTARGETDESC_ONEMCTARGETDESC_H
#define LLVM_LIB_TARGET_ONE_MCTARGETDESC_ONEMCTARGETDESC_H

#define GET_REGINFO_ENUM
#include "OneGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "OneGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "OneGenSubtargetInfo.inc"

#endif