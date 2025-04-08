#ifndef LLVM_LIB_TARGET_ONE_MCTARGETDESC_ONEMCASMINFO_H
#define LLVM_LIB_TARGET_ONE_MCTARGETDESC_ONEMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class OneMCAsmInfo : public MCAsmInfoELF {
public:
    explicit OneMCAsmInfo(const Triple &TargetTriple);
};

}

#endif