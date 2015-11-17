add_executable(print_user print_user.cpp
                          $<TARGET_OBJECTS:dto>
                          $<TARGET_OBJECTS:support>)

add_executable(print_shout print_shout.cpp
                           $<TARGET_OBJECTS:dto>
                           $<TARGET_OBJECTS:support>)

add_executable(webdev server.cpp
                      $<TARGET_OBJECTS:dto>
                      $<TARGET_OBJECTS:support>
                      $<TARGET_OBJECTS:resources>)

target_link_libraries(print_user gnutls
                                 jsoncpp
                                 redox_static)

target_link_libraries(print_shout gnutls
                                  jsoncpp
                                  redox_static)

target_link_libraries(webdev gnutls
                             httpserver
                             jsoncpp
                             redox_static
                             mstch)

