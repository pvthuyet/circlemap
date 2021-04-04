# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project(CircleMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SG_BOOST_INC_DIR "D:/work/SGEyes/saigonlib/boost_1_75_0")

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)
  # all the remaining CMake code will be placed here
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	# Prevent GoogleTest from using PThreads
	set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

	# adds the targers: gtest, gtest_main, gmock, gmock_main
	add_subdirectory(
		${googletest_SOURCE_DIR}
		${googletest_BINARY_DIR}
    )

	# Silence std::tr1 warning on MSVC
	if(MSVC)
		foreach(_tgt gtest gtest_main gmock gmock_main)
			target_compile_definitions(${_tgt}
				PRIVATE
					"_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
				)
		endforeach()
	endif()
endif()

add_executable(test_circle_map "")

target_sources(test_circle_map PRIVATE
    "test_circle_map2.cpp"
  )

target_include_directories(test_circle_map PRIVATE
	${SG_BOOST_INC_DIR}
	)

target_link_libraries(test_circle_map PRIVATE
    gtest_main
	)

enable_testing()

add_test(
  NAME google_test
  COMMAND $<TARGET_FILE:test_circle_map>
  )