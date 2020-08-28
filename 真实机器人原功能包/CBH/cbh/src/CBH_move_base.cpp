#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <move_base_msgs/MoveBaseAction.h>

int main(int argc, char** argv)
{
	

	ros::init(argc, argv, "nav_move_base");
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true); //初始化actionlib的客户端

	ROS_INFO("move base start navigation");

	geometry_msgs::Quaternion quaternion; //初始化位姿
	geometry_msgs::Point point;
	geometry_msgs::Pose pose_list[10]; //利用数组存放位姿

	ROS_INFO("Waitting for move base server...");

	if(!ac.waitForServer(ros::Duration(60))) //判断是否链接到move base服务器
	{
		ROS_ERROR("Cant connected to move base server.");
		return -1;
	}
	else
	{
		ROS_INFO("Already connected to move base server");
		ROS_INFO("Starting navigation test");
	}

	double x = -1.50;
	double y = -1.50;

	for(int i=0;i<10;i++)
	{
		point.x = x;
		point.y = y;
		point.z = 0.00;
		quaternion.x = 0.00;
		quaternion.y = 0.00;
		quaternion.z = 0.30;
		quaternion.w = 1.00;
		pose_list[i].position = point;
		pose_list[i].orientation = quaternion;

		if(point.y>1.40)
		{
			point.x = x+0.30;
			point.y = -1.50;
			point.z = 0.00;
			pose_list[i].position = point;
			pose_list[i].orientation = quaternion;
		}
	       	
	    move_base_msgs::MoveBaseGoal goal;   //初始化目标点
		goal.target_pose.header.frame_id = "map"; //设置frame_id为map
		goal.target_pose.header.stamp = ros::Time::now(); 
		goal.target_pose.pose = pose_list[i]; //向move base写入目标点
		ac.sendGoal(goal); //向Move base发送目标点

		bool finished = ac.waitForResult(ros::Duration(20)); //判断是否到达目标点

			
		if(!finished)
		{
			ac.cancelGoal(); //取消该点导航
			ROS_WARN("Already cancel the target goal");
		}
			
			
		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) //判断到达目标点后的状态
		{
			ROS_INFO("Goal succeeded");
		}
		else
		{
			ROS_INFO("The base failed for some reason");
			//ac.cancelGoal(); //取消该点导航
		}

		y = y+0.30;			
	}

	ros::spin();

	return 0;
}
