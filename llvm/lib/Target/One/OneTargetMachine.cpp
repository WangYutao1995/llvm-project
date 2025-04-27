#include "OneTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/OneTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "One.h"

using namespace llvm;

// llvm/MC/TargetRegistry.h RegisterTargetMachine
/// RegisterTargetMachine - Helper template for registering a target machine
/// implementation, for use in the target machine initialization
/// function. Usage:
///
/// extern "C" void LLVMInitializeFooTarget() {
///   extern Target TheFooTarget;
///   RegisterTargetMachine<FooTargetMachine> X(TheFooTarget);
/// }
// 
// template <class TargetMachineImpl> struct RegisterTargetMachine {
//   RegisterTargetMachine(Target &T) {
//     TargetRegistry::RegisterTargetMachine(T, &Allocator);
//   }
// private:
//   static TargetMachine *
//   Allocator(const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
//             const TargetOptions &Options, std::optional<Reloc::Model> RM,
//             std::optional<CodeModel::Model> CM, CodeGenOptLevel OL, bool JIT) {
//     return new TargetMachineImpl(T, TT, CPU, FS, Options, RM, CM, OL, JIT);
//   }
// };
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOneTarget() {
    RegisterTargetMachine<OneTargetMachine> X(getTheOneTarget());
    auto *PR = PassRegistry::getPassRegistry();
    initializeOneDAGToDAGISelLegacyPass(*PR);
}

static StringRef computeDataLayout(const Triple &TT, const TargetOptions &options) {
    assert(TT.isArch32Bit() && "only 32 bit are currently supported");
    return "e-m:e-p:32:32-i64:64-n32-S128";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT, std::optional<Reloc::Model> RM) {
    return RM.value_or(Reloc::Static);
}

OneTargetMachine::OneTargetMachine(const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
                                    const TargetOptions &Options, std::optional<Reloc::Model> RM,
                                    std::optional<CodeModel::Model> CM, CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT, Options), TT, CPU, FS, Options,
                        getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
                        TLOF(std::unique_ptr<TargetLoweringObjectFileELF>()), Subtarget(TT, CPU, FS, *this) {
    initAsmInfo();
}

namespace {
class OnePassConfig : public TargetPassConfig {
public:
    OnePassConfig(OneTargetMachine &TM, PassManagerBase &PM)
        : TargetPassConfig(TM, PM) {}

    OneTargetMachine &getOneTargetMachine() const {
        return getTM<OneTargetMachine>();
    }

    const OneSubtarget &getOneSubtarget() const {
        return *getOneTargetMachine().getSubtargetImpl();
    }

    bool addInstSelector() override;
};
} // namespace

TargetPassConfig *OneTargetMachine::createPassConfig(PassManagerBase &PM) {
    return new OnePassConfig(*this, PM);
}

bool OnePassConfig::addInstSelector() {
    // Install an instruction selector.
    addPass(createOneISelDag(getOneTargetMachine()));
    return false;
}