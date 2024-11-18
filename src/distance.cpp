#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <unistd.h>


double turtle_distance; //,corner_distance_x1,corner_distance_y1,corner_distance_x2,corner_distance_y2;
double new_turtle_distance; //,new_corner_distance_x1,new_corner_distance_y1,new_corner_distance_x2,new_corner_distance_y2;

double turtle_x1;
double turtle_y1;
double turtle_theta1;

void turtlesimCallback1(const turtlesim::Pose::ConstPtr& msg){
	//ROS_INFO("Position: %f, %f, %f", msg->x, msg->y, msg->theta);
	turtle_x1 = msg->x;
	turtle_y1 = msg->y;
	turtle_theta1 = msg->theta;
}

double turtle_x2;
double turtle_y2;
double turtle_theta2;

void turtlesimCallback2(const turtlesim::Pose::ConstPtr& msg){
	//ROS_INFO("Position: %f, %f, %f", msg->x, msg->y, msg->theta);
	turtle_x2 = msg->x;
	turtle_y2 = msg->y;
	turtle_theta2 = msg->theta;
}



int main(int argc, char **argv){
	ros::init(argc, argv, "turtlesim_control");
	ros::NodeHandle n;
	ros::Subscriber turtle_sub1 = n.subscribe("/turtle1/pose", 10, turtlesimCallback1);
	ros::Subscriber turtle_sub2 = n.subscribe("/turtle2/pose", 10, turtlesimCallback2);
	ros::Publisher turtle_pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
	ros::Publisher turtle_pub2 = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
	
	//ros::Publisher custom_pub = n.advertise<turtlesim_controller::Vel>("new_vel_topic", 10);
	ros::Rate loop_rate(10);
	geometry_msgs::Twist my_vel;
	my_vel.linear.x = 0.0;
	my_vel.linear.y = 0.0;
	//my_vel.angular.z = z;
	
	
	while(ros::ok()){
		
		turtle_distance = sqrt(((turtle_x1 - turtle_x2)*(turtle_x1 - turtle_x2)) + ((turtle_y1 - turtle_y2)*(turtle_y1 - turtle_y2)));
		//corner_distance_x1 = sqrt((8 - x1)^2);
		loop_rate.sleep();
		new_turtle_distance = sqrt(((turtle_x1 - turtle_x2)*(turtle_x1 - turtle_x2)) + ((turtle_y1 - turtle_y2)*(turtle_y1 - turtle_y2)));
		
		if (((new_turtle_distance < turtle_distance) and (turtle_distance < 1)) or (turtle_x1 > 8.0 or turtle_x1 < 1.0) or (turtle_x2 > 8.0 or turtle_x2 < 1.0) or (turtle_y1 > 8.0 or turtle_y1 < 1.0) or (turtle_y2 > 8.0 or turtle_y2 < 1.0)){
			turtle_pub1.publish(my_vel);
			turtle_pub2.publish(my_vel);
		}
		ros::spinOnce();
		loop_rate.sleep();
		//ros::Duration(1.0).sleep();

	}
	
	return 0;
}
