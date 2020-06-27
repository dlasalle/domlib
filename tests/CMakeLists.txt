function(setup_test test_file)
  file(GLOB source ${test_file}.c)
	add_executable(${test_file} ${test_file} test.c)
	target_link_libraries(${test_file} domlib)
	add_test(NAME ${test_file} COMMAND ${test_file})
endfunction()

include_directories(.)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

file(GLOB files "*_test.c")
foreach(file ${files})
  get_filename_component(basename "${file}" NAME_WE)
  setup_test(${basename})
endforeach()

