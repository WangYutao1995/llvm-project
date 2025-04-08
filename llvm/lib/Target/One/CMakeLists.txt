add_llvm_component_group(One)

# 目标定义的入口文件
set(LLVM_TARGET_DEFINITIONS One.td)

tablegen(LLVM OneGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM OneGenCallingConv.inc -gen-callingconv)
tablegen(LLVM OneGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM OneGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM OneGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM OneGenMCPseudoLowering.inc -gen-pseudo-lowering)

add_public_tablegen_target(OneCommonTableGen)

add_llvm_target(OneCodeGen
  OneTargetMachine.cpp
  OneInstrInfo.cpp
  OneRegisterInfo.cpp
  OneSubtarget.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
  SelectionDAG
  OneDesc
  OneInfo
  Support
  TargetParser
  Target
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
