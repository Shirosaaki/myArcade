# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(arcadeTests LANGUAGES CXX)

# ---- Tests ----

add_executable(arcade_test source/arcade_test.cpp)
target_link_libraries(arcade_test PRIVATE arcade_lib)
target_compile_features(arcade_test PRIVATE cxx_std_20)

add_test(NAME arcade_test COMMAND arcade_test)

# ---- End-of-file commands ----

add_folders(Test)
