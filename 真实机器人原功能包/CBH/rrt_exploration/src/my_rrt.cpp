#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>
#include <geometry_msgs/PoseArray.h>
#include <signal.h>
#include <iostream>

void two_d_nav();

std::vector<geometry_msgs::Pose> pose_list; //目标点序列

//回调函数
void callback(const geometry_msgs::PoseArray::ConstPtr& msg)
{
	int len = msg->poses.size();
	
	for(int i=0;i<len;i++)	
		pose_list.push_back(msg->poses[i]);

	ROS_INFO("msg->poses %d", len);

	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

	ROS_INFO("Waitting for move_base action server...");

	if(!ac.waitForServer(ros::Duration(30)))
	{
		ROS_INFO("can not connected to move base server");
	}

	ROS_INFO("Connected to move base server");
	ROS_INFO("Starting navigation test");
	
	int count = pose_list.size();

	ROS_INFO("count %d", count);

	for(int i=0;i<count;i++)
	{
		move_base_msgs::MoveBaseGoal goal;
		
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose = pose_list[i];

		ac.sendGoal(goal);

		bool finished_within_time = ac.waitForResult();//必须要，不然目标点会出错

		if(!finished_within_time)
    	{
        	ac.cancelGoal();
        	ROS_INFO("Timed out achieving goal");
    	}
		else
		{
			if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				ROS_INFO("Goal succeeded!");
			}
			else
			{
				ROS_INFO("Goal has some truble!");
			}
		}
	}

}


//导航函数
void two_d_nav()
{
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

	ROS_INFO("Waitting for move_base action server...");

	if(!ac.waitForServer(ros::Duration(30)))
	{
		ROS_INFO("can not connected to move base server");
	}

	ROS_INFO("Connected to move base server");
	ROS_INFO("Starting navigation test");
	
	int count = pose_list.size();

	for(int i=0;i<count;i++)
	{
		move_base_msgs::MoveBaseGoal goal;
		
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose = pose_list[i];

		ac.sendGoal(goal);

		bool finished_within_time = ac.waitForResult();//必须要，不然目标点会出错

		if(!finished_within_time)
    	{
        	ac.cancelGoal();
        	ROS_INFO("Timed out achieving goal");
    	}
		else
		{
			if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				ROS_INFO("Goal succeeded!");
			}
			else
			{
				ROS_INFO("Goal has some truble!");
			}
		}
	}
} 

int main(int argc, char** argv)
{
	ros::init(argc, argv, "our_2dnav");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("filtered_points", 1000, callback);

	ros::spin();

	return 0;
}
