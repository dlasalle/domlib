function(setup_test test_file)
  file(GLOB source ${test_file}.c)
  list(APPEND source ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
	add_executable(${test_file} ${source})
	target_link_libraries(${test_file} domlib m)
	add_test(NAME ${test_file} COMMAND ${test_file})
endfunction()


file(GLOB files "*.c")
list(REMOVE_ITEM files ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
foreach(file ${files})
  get_filename_component(basename "${file}" NAME_WE)
  setup_test(${basename})
endforeach()

