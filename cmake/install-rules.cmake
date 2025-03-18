install(
    TARGETS arcade_exe
    RUNTIME COMPONENT arcade_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
