#include<sstream>
#include<ros/ros.h>
#include<geometry_msgs/PoseWithCovarianceStamped.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "Pose_init");
	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose",1);
	
	geometry_msgs::Point point;
	geometry_msgs::Quaternion quaternion;
	geometry_msgs::PoseWithCovarianceStamped pose1;
	
	point.x = 7.394;
	point.y = 1.540;
	point.z = 0.000;
	quaternion.x = 0.000;
	quaternion.y = 0.000;
	quaternion.z = -1.000;
	quaternion.w = 0.018;
	pose1.pose.pose.position = point;
	pose1.pose.pose.orientation = quaternion;
	pose1.pose.covariance = {0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06853891945200942};
	 
	pose1.header.frame_id = "map";
        ros::Rate loop_rate(4);
	for(int i=0;i<5;i++)
	{
   	     pose1.header.stamp = ros::Time::now ();
   	     loop_rate.sleep ();
   	     pub.publish (pose1);
	}


  	
}
