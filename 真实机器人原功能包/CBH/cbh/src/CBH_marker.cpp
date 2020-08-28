#include "ros/ros.h"
#include "std_msgs/String.h"

#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Header.h"
#include "nav_msgs/MapMetaData.h"
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"

#include <string>

int counter = 0;
visualization_msgs::Marker mark;

void callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
	geometry_msgs::Point p;

	p.x=msg->pose.position.x;
	p.y=msg->pose.position.y;
	p.z=msg->pose.position.z;
	mark.points.push_back(p);

	counter += 1;
}

int main(int argc, char** argv)
{
	std::string sub_topic;

	ros::init(argc, argv, "marker");
	ros::NodeHandle n;

	sub_topic = ros::this_node::getName();
	ros::param::param<std::string>("/sub_topic", sub_topic, "/Cycle_Goal");

	ros::Publisher pub = n.advertise<visualization_msgs::Marker>("/cbh_marker", 100);
	ros::Subscriber sub = n.subscribe(sub_topic, 100, callback);
	
	ros::Rate r(2);

	while(ros::ok())
	{
		mark.action =mark.ADD;
		mark.header.stamp = ros::Time::now();
		mark.header.frame_id = "/map";
		mark.lifetime = ros::Duration();
		mark.ns = "markers";
		mark.id = 0;
		mark.type = mark.POINTS;
		mark.pose.orientation.w =1.0;
		mark.scale.x=0.3; 
		mark.scale.y=0.3; 	
		mark.color.r = 154.0/255.0;	
		mark.color.g = 50.0/255.0;
		mark.color.b = 205.0/255.0;
		mark.color.a=1.0;

		ros::spinOnce();

		pub.publish(mark);

		r.sleep();

		//ROS_INFO("counter: %d", counter);
	}
	return 0;
}
