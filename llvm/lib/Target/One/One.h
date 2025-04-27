#ifndef LLVM_LIB_TARGET_ONE_ONE_H
#define LLVM_LIB_TARGET_ONE_ONE_H
namespace llvm {

class FunctionPass;
class OneTargetMachine;
class PassRegistry;

/// This pass converts a legalized DAG into a One-specific DAG, ready for
/// instruction scheduling.
FunctionPass *createOneISelDag(OneTargetMachine &TM);

void initializeOneDAGToDAGISelLegacyPass(PassRegistry &);

}
#endif