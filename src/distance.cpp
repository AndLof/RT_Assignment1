#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float32.h>
#include <cmath>
#include <unistd.h>
#include <iostream>


double turtle_distance;
double new_turtle_distance;
double turtle1_corners_distance, turtle2_corners_distance, new_turtle1_corners_distance, new_turtle2_corners_distance;
bool corner_approach;

double turtle_x1;
double turtle_y1;
double turtle_theta1;

void turtlesimCallback1(const turtlesim::Pose::ConstPtr& msg){
	turtle_x1 = msg->x;
	turtle_y1 = msg->y;
	turtle_theta1 = msg->theta;
}

double turtle_x2;
double turtle_y2;
double turtle_theta2;

void turtlesimCallback2(const turtlesim::Pose::ConstPtr& msg){
	turtle_x2 = msg->x;
	turtle_y2 = msg->y;
	turtle_theta2 = msg->theta;
}



int main(int argc, char **argv){
	ros::init(argc, argv, "turtlesim_control");
	ros::NodeHandle n;
	ros::Subscriber turtle_sub1 = n.subscribe("/turtle1/pose", 1000, turtlesimCallback1);
	ros::Subscriber turtle_sub2 = n.subscribe("/turtle2/pose", 1000, turtlesimCallback2);
	ros::Publisher turtle_pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	ros::Publisher turtle_pub2 = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1000);
	ros::Publisher distance_pub = n.advertise<std_msgs::Float32>("/turtles/distance", 100);

	
	ros::Rate loop_rate(1000);
	geometry_msgs::Twist my_vel;
	std_msgs::Float32 distance;
	my_vel.linear.x = 0.0;
	my_vel.linear.y = 0.0;
	
	
	while(ros::ok()){
		
		ros::spinOnce();
		turtle_distance = sqrt(((turtle_x1 - turtle_x2)*(turtle_x1 - turtle_x2)) + ((turtle_y1 - turtle_y2)*(turtle_y1 - turtle_y2)));
		turtle1_corners_distance = ((std::abs(turtle_x1 - 10.0)) + (std::abs(turtle_x1 - 1)) + (std::abs(turtle_y1 - 10.0)) + (std::abs(turtle_y1 - 1)));
		turtle2_corners_distance = ((std::abs(turtle_x2 - 10.0)) + (std::abs(turtle_x2 - 1)) + (std::abs(turtle_y2 - 10.0)) + (std::abs(turtle_y2 - 1)));
		ros::Duration(0.1).sleep();
		ros::spinOnce();
		new_turtle_distance = sqrt(((turtle_x1 - turtle_x2)*(turtle_x1 - turtle_x2)) + ((turtle_y1 - turtle_y2)*(turtle_y1 - turtle_y2)));
		new_turtle1_corners_distance = ((std::abs(turtle_x1 - 10.0)) + (std::abs(turtle_x1 - 1)) + (std::abs(turtle_y1 - 10.0)) + (std::abs(turtle_y1 - 1)));
		new_turtle2_corners_distance = ((std::abs(turtle_x2 - 10.0)) + (std::abs(turtle_x2 - 1)) + (std::abs(turtle_y2 - 10.0)) + (std::abs(turtle_y2 - 1)));
		distance.data = new_turtle_distance;
		distance_pub.publish(distance);
		
		if ((new_turtle1_corners_distance > turtle1_corners_distance) or (new_turtle2_corners_distance > turtle2_corners_distance)){
			corner_approach = true;
		} else{
			corner_approach = false;
		}

		if (((new_turtle_distance < turtle_distance) and (turtle_distance < 1.5)) or ((corner_approach==true) and (new_turtle1_corners_distance > 18.0 or new_turtle2_corners_distance > 18.0))){
			
			turtle_pub1.publish(my_vel);
			turtle_pub2.publish(my_vel);
		}
		ros::spinOnce();
		loop_rate.sleep();		

	}
	
	return 0;
}
