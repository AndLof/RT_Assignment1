#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include <iostream>
#include <string>

int main(int argc, char **argv){
	ros::init(argc, argv, "user_interface");
	ros::NodeHandle n;
	ros::Publisher turtle_pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
	ros::ServiceClient turtle_client = n.serviceClient<turtlesim::Spawn>("/spawn");
	
	turtlesim::Spawn my_spawn;
	my_spawn.request.x = 2.0;
	my_spawn.request.y = 2.0;
	my_spawn.request.theta = 0.0;
	my_spawn.request.name = "turtle2";
	
	turtle_client.call(my_spawn);
	
	ros::Publisher turtle_pub2 = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
	
	ros::Rate loop_rate(10);
	geometry_msgs::Twist my_vel;
	
	std::string robot;
	double x,y,z;
	
	while(ros::ok()){
		do {
			std::cout<<"Do you want to control turtle1 or turtle2? ";		
			std::cin>>robot;
		} while ((robot != "turtle1") and (robot != "turtle2"));
		std::cout<<"Insert the desired x velocity: ";
		std::cin>>x;
		std::cout<<"Insert the desired y velocity: ";
		std::cin>>y;
		std::cout<<"Insert the desired angular velocity: ";
		std::cin>>z;
		my_vel.linear.x = x;
		my_vel.linear.y = y;
		my_vel.angular.z = z;
		if (robot == "turtle1"){
			turtle_pub1.publish(my_vel);
			
			}
		else if (robot == "turtle2"){
			turtle_pub2.publish(my_vel);
			
		}
		ros::spinOnce();
		ros::Duration(1.0).sleep();

	}
	
	return 0;
}
