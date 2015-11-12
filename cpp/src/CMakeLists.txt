add_executable(print_user print_user.cpp user.cpp encoding.cpp hash.cpp)
target_link_libraries(print_user ${GNUTLS_LIBRARIES} jsoncpp)

add_executable(print_shout print_shout.cpp user.cpp encoding.cpp hash.cpp shout.cpp)
target_link_libraries(print_shout ${GNUTLS_LIBRARIES} jsoncpp)

add_executable(webdev server.cpp user.cpp encoding.cpp hash.cpp shout.cpp resource_users.cpp resource_register.cpp access.cpp)
target_link_libraries(webdev ${GNUTLS_LIBRARIES} jsoncpp httpserver redox_static)

