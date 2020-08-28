#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/PointStamped.h"
#include "std_msgs/Header.h"
#include "nav_msgs/MapMetaData.h"
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"
#include <tf/transform_listener.h>
#include "signal.h"

visualization_msgs::Marker points;

void rvizcallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
	geometry_msgs::Point p;
	p.x = msg->pose.position.x;
	p.y = msg->pose.position.y;
	p.z = msg->pose.position.z;

	points.points.push_back(p);
	
}



int main(int argc , char** argv)
{
	ros::init(argc,argv,"marker_pose");
	ros::NodeHandle nh;

	ros::Subscriber rviz_sub = nh.subscribe("/Cycle_Goal",100,rvizcallback);



	ros::Publisher pub = nh.advertise<visualization_msgs::Marker>("lichao_goal_marker",10);
	
	ros::Rate r(2);

while(ros::ok())
{

	points.header.frame_id="map";
	points.header.stamp=ros::Time::now();
	points.id = 0;
	points.ns = "markers";
	points.type = points.POINTS;
	points.action =points.ADD;
	points.pose.orientation.w =1.0;
	points.scale.x=0.3; 
	points.scale.y=0.3; 
	points.color.r = 255.0/255.0;
	points.color.g = 255.0/255.0;
	points.color.b = 0.0/255.0;
	points.color.a=1.0;
	points.lifetime = ros::Duration();



		ros::spinOnce();


		pub.publish(points) ;
		r.sleep();
}

}
