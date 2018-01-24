#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include <cstdlib>
#include <ctime>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <tf/transform_listener.h>
#include <math.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


class FrontierExplorer
{
private:
  ros::NodeHandle nh_;
  ros::Publisher cmd_vel_pub_;
  ros::Subscriber laserSub;


public:

  FrontierExplorer(ros::NodeHandle &nh)
  {
    nh_ = nh;
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
//    laserSub = nh_.subscribe("robot_1/base_scan", 1, &FrontierExplorer::scanCallback, this);
  }
  void initMap();
  bool moveToGoal(double xGoal,double yGoal);
  char choose();

  bool goalReached=false;
};
 //arbitrary coordinates for goal point
 double x = 1.369;
 double y = 7.243;

/**To be implemented to rotate the robot at the initial position in order to 
 * obtain a working map.
 */
void FrontierExplorer::initMap()
{

}
/* Returns a boolean value and also uses actionlib in order to send a goal	 * to the robot with an already defined coordinate. Returns false
 * if unable to make it to the destination. 
 */
bool moveToGoal(double xGoal,double yGoal)
{
  actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> 
           ac("move_base",true);

  while(!ac.waitForServer( ros::Duration(5.0) ) )
  {
    ROS_INFO("Waiting for move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
 
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = xGoal;
  goal.target_pose.pose.position.y = yGoal;
  goal.target_pose.pose.position.z = 0.0;
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.0;
  goal.target_pose.pose.orientation.w = 1.0;
 
  ROS_INFO("Sending goal location ...");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
     ROS_INFO("Reached the destination");
     return true;
  }
  else
  {
    ROS_INFO("Failed to reach destination..");
    return false;
  }
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "explorer");
  ros::NodeHandle n;
  ros::spinOnce();
  moveToGoal(x,y);
  return 0;

}
