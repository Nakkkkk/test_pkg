project(src2)

cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED)

set(HOGE_SRCS
  main.cpp
  listenerpc2.cpp
)
set(HOGE_HDRS
  listenerpc2.h
)
add_executable(listenerpc2
    ${HOGE_SRCS}
    ${HOGE_HDRS}
)
target_link_libraries(listenerpc2 ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${PCL_LIBRARIES})

