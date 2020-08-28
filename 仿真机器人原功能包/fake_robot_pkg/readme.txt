这是一个仿真机器人的导航和自主探索的功能包（这里我直接用古月老师的仿真机器人）

robot_mrobot 功能包是机器人仿真模型和导航包
CBH_cycle_nav 是导航创建功能包
turtlebot    是rrt自主探索算法包 
注意：去fake_robot_pkg/turtlebot/rrt_exploration/scripts 把.py文件全加上可执行权限
     还要去rrt的wiki上去简单的看一下，要装一些依赖
     依赖安装:
	sudo apt-get install python-numpy python-opencv python-scikits-learn 



一.自主建图
   1.功能包robot_mrobot是直接用古月老师的机器人，我只是在gmapping_demo.launch里加了一个move_base和修改了move_base的参数配置文件。来完成自主建图。
   2.首先启动  roslaunch mrobot_gazebo mrobot_laser_nav_gazebo.launch 这是打开仿真环境。
   3.再启动    roslaunch mrobot_navigation gmapping_demo.launch  这是启动gampping建图。
   4.最后启动  roslaunch rrt_exploration single.launch 这是启动rrt自主探索的算法包。自主巡墙建图。开启以后需要使用Publish Point点四个点标出需要探索的范围，再点在有地图的地方点最后一个点使探索树可行。点完五个点以后，需要使用2D Nav Goal开启自主探索  
   5.效果图在pictures文件夹中

二.导航
    1.首先使用 roslaunch mrobot_bringup fake_mrobot_with_laser.launch 来加载机器人模型，这里没有启动gazebo，也没有rviz。
    2.再启动   roslaunch mrobot_navigation fake_nav_demo.launch 这里会启动rviz。
    3.导航用法：必须先在rviz中使用Cycle_Goal给出导航点，再使用NavPanel给出循环次数和发起导航。使用NavPanel时输入循环次数后需要按下回车建（只能按一次），发起导航需要按回车键（只能按一次），按多了回车就会重复发送。

	4、关于如何使用Cycle_Goal你可以打开pictures文件夹查看名为cycle_goal的图片
	5、关于如何使用NavPanel你可以打开pictures文件夹查看名为NavPanel的图片
	6、关于导航效果你可以打开pictures文件夹查看名为nav_demo的图片

