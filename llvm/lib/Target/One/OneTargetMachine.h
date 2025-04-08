#ifndef LLVM_LIB_TARGET_ONE_ONETARGETMACHINE_H
#define LLVM_LIB_TARGET_ONE_ONETARGETMACHINE_H

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "OneSubtarget.h"

namespace llvm {
class OneTargetMachine : public CodeGenTargetMachineImpl {
    std::unique_ptr<TargetLoweringObjectFile> TLOF;
    OneSubtarget Subtarget;
public:
    OneTargetMachine(const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
                    const TargetOptions &Options, std::optional<Reloc::Model> RM, 
                    std::optional<CodeModel::Model> CM, CodeGenOptLevel OL, bool JIT);

    const OneSubtarget *getSubtargetImpl() const { return &Subtarget; }
    const OneSubtarget *getSubtargetImpl(const Function &) const override { return &Subtarget; }

    TargetLoweringObjectFile *getObjFileLowering() const override {
        return TLOF.get();
    }
};
}

#endif