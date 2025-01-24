add_llvm_component_group(One)

add_llvm_target(OneCodeGen
  OneTargetMachine.cpp

  LINK_COMPONENTS
  MC
  OneInfo
  OneDesc
  Support
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
