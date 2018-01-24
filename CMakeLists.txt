cmake_minimum_required(VERSION 2.8.3)
project(frontier_exploration)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  costmap_2d
  move_base_msgs
  geometry_msgs
  actionlib
  roscpp
  rospy
  std_msgs
  std_srvs
  tf
)

find_package(Boost REQUIRED)




## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   geometry_msgs#   std_msgs
# )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES frontier_exploration
   CATKIN_DEPENDS 
     costmap_2d 
     geometry_msgs 
     roscpp 
     rospy 
     std_msgs 
     std_srvs 
     tf
     actionlib
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/frontier_exploration.cpp
# )


add_executable(frontier_exploration src/frontier_explorer.cpp)
target_link_libraries(frontier_exploration ${catkin_LIBRARIES})
add_dependencies(frontier_exploration ${PROJECT_NAME}_generate_messages_cpp)

