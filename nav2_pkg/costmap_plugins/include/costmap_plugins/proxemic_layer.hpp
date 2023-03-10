#ifndef PROXEMIC_LAYER_HPP_
#define PROXEMIC_LAYER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav2_costmap_2d/layer.hpp"
#include "nav2_costmap_2d/costmap_layer.hpp"
#include "nav2_costmap_2d/layered_costmap.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"

namespace nav2_proxemic_costmap_plugin
{

class ProxemicLayer : public nav2_costmap_2d::CostmapLayer
{
public:
  ProxemicLayer();

  virtual void onInitialize();

  virtual void getFrameNames();

  bool getAgentTFs(std::vector<tf2::Transform> & agents) const;

  virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double * min_x, double * min_y, double * max_x, double * max_y);

  void peopleCallBack(const geometry_msgs::msg::Pose::SharedPtr msg);

  virtual void updateCosts(nav2_costmap_2d::Costmap2D & master_grid, int min_i, int min_j, int max_i, int max_j);

  virtual void matchSize();

  virtual void onFootprintChanged();

  virtual void reset();

  virtual bool isClearable();

private:

  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr sub_;
  
  double last_min_x_, last_min_y_, last_max_x_, last_max_y_;

  //geometry_msgs::msg::Pose::SharedPtr pose_;
  geometry_msgs::msg::Pose pose_;

  // Indicates that the entire gradient should be recalculated next time.
  bool need_recalculation_;
  
  //std::vector<std::string> agent_ids_;
  //std::string tf_prefix_;
  //std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  //std::string global_frame_;

  // Size of gradient in cells
  // int GRADIENT_SIZE = 20;
  // Step of increasing cost per one cell in gradient
  // int GRADIENT_FACTOR = 10;
};

}  // namespace nav2_proxemic_costmap_plugin

#endif  // PROXEMIC_LAYER_HPP_