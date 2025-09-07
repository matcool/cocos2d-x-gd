add_executable(matapp
    main.cpp
    AppDelegate.cpp
    HelloWorldScene.cpp
)

target_link_libraries(matapp libcocos2d)

if (EMSCRIPTEN)
	set_target_properties(matapp PROPERTIES LINK_FLAGS "${LINK_FLAGS} --embed-file ../dlls@/ -s STB_IMAGE=1")
endif()

if (WIN32)
	install(TARGETS matapp RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../dlls)
endif()