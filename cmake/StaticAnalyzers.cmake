option(MOMO_ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(MOMO_ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)

if(MOMO_ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK}
        --enable=all
        --suppress=missingInclude
        --suppress=unmatchedSuppression:${CMAKE_SOURCE_DIR}/lib/*
        --suppress=*:${CMAKE_SOURCE_DIR}/lib/*
        --suppress=unusedFunction:${CMAKE_SOURCE_DIR}/*
        --suppress=useStlAlgorithm:${CMAKE_SOURCE_DIR}/*
        --suppress=constStatement:${CMAKE_SOURCE_DIR}/*
        --suppress=functionStatic:${CMAKE_SOURCE_DIR}/*
        --suppress=preprocessorErrorDirective:${CMAKE_SOURCE_DIR}/*
        --suppress=unmatchedSuppression:${CMAKE_SOURCE_DIR}/*
        --inline-suppr
        --inconclusive)
  else()
    message(SEND_ERROR "cppcheck requested but executable not found")
  endif()
endif()

if(MOMO_ENABLE_INCLUDE_WHAT_YOU_USE)
  find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
  if(INCLUDE_WHAT_YOU_USE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
  else()
    message(SEND_ERROR "include-what-you-use requested but executable not found")
  endif()
endif()