一、功能包综述
	1、cbh：开启包括建图、导航、自主探索等各功能的主要功能包
	2、nav_panel(CBH_cycle_nav下)：rviz插件，用以接收单个导航点，设置循环次数，发布多个导航点和循环次数
	3、nav_tool(CBH_cycle_nav下)：rviz工具，发布单个导航点
	4、cycle_nav(CBH_cycle_nav下)：接收多个导航点和循环次数，实现多点循环导航功能
	5、depthimage_to_laserscan：深度摄像机数据转换为激光数据
	6、pointcloud_to_laserscan：点云数据转换为激光数据
	7、rrt_exploration：快速探索随机数巡墙自主建图算法

二、依赖安装
	sudo apt-get install python-numpy python-opencv python-scikits-learn 

三、使用指南
	1、所有功能的开启都在cbh功能包中，下面就开始介绍cbh下launch文件
	2、roslaunch CBH_gmapping_all.launch     
	   使用手柄进行gmapping建图
	3、roslaunch CBH_navigation.launch
	   可视化循环导航。注意事项：必须先在rviz中使用Cycle_Goal给出导航点，再使用NavPanel给出循环次数和发起导航。使用NavPanel时输入循环次数后需要按下回车建（只能按一次），发起导航需要按回车键（只能按一次），按多了回车就重启launch文件吧。
	4、关于如何使用Cycle_Goal请查看pictures文件夹下名为cycle_goal的图片
	5、关于如何使用NavPanel请查看pictures文件夹下名为NavPanel的图片
	6、关于循环导航效果请查看pictures文件夹下名为nav_demo的图片
	7、roslaunch CBH_selfexplore.launch
	   自主巡墙建图。开启以后需要使用Publish Point点四个点标出需要探索的范围，再在有地图的地方点最后一个点使探索树可行。点完五个点以后，需要使用2D Nav Goal开启自主探索
	8、自主巡墙建图效果请查看pictures文件下名为rrt的图片

