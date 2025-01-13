#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//#include "turtlesim/Pose.h"
#include <iostream>
#include <string>
#include message_type/Obstacle.h

void ObstaclesCallback(const package_name::Obstacle::ConstPtr& msg){

	distance = msg->distances;
	


int main(int argc, char **argv){
	ros::init(argc, argv, "avoiding_obstacles");
	ros::NodeHandle n;
	ros::Subscriber turtle_sub1 = n.subscribe("/obstacles", 1000, ObstaclesCallback);
	ros::Publisher turtle_pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

	
	ros::Rate loop_rate(1000);
	geometry_msgs::Twist my_vel;
	my_vel.linear.x = 0.0;
	my_vel.linear.y = 0.0;
	
	while(ros::ok()){
		
		ros::spinOnce();
		
		for (int i = 0; i < 16; i++){
			if(distance[i] < 1.0){
			turtle_pub1.publish(my_vel);
			}
		}
		
		ros::spinOnce();
		loop_rate.sleep();		

	}
	
	return 0;
}
