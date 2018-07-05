project(src)

cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED)

set(HOGE_SRCS
  talker.cpp
)
set(HOGE_HDRS
  talker.h
)
add_executable(talkerSet
    ${HOGE_SRCS}
    ${HOGE_HDRS}
)
target_link_libraries(talkerSet ${catkin_LIBRARIES})


set(HUGE_SRCS
  main.cpp
  lisner.cpp
)
set(HUGE_HDRS
  lisner.h
)
add_executable(lisnerSet
    ${HUGE_SRCS}
    ${HUGE_HDRS}
)
target_link_libraries(lisnerSet ${catkin_LIBRARIES})

#add_executable(talker srcHOGE/talker.cpp srcHOGE/talker.h)
#target_link_libraries(talker ${catkin_LIBRARIES})

#add_executable(lisner lisner.cpp)
#target_link_libraries(lisner ${catkin_LIBRARIES})

