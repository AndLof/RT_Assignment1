# RT_Assignment1

# **ROS Package Documentation**

## **Description**

This ROS package consists of two nodes implemented in C++. The purpose of the project is to manage and control two turtles within the `turtlesim` simulation environment. The nodes allow users to spawn a second turtle, control the movement of both turtles, and ensure they operate safely by avoiding collisions with each other or the environment's boundaries.

---

## **Nodes Description**

### **First Node - `ui_node`**

The primary purpose of this node is to:
1. **Spawn a new turtle** in the environment. 
   This is done using the `Spawn` service client provided by the `turtlesim` node. The newly created turtle is named **"turtle2"**, and its initial position is as follows:
   - **x** = 2.0 
   - **y** = 2.0 
   - **theta** = 0.0 

2. **Provide a user interface** for controlling the turtles. 
   The interface allows the user to:
   - Choose which turtle to control (`turtle1` or `turtle2`).
   - Set the desired velocities (linear velocities along the x and y axes, and angular velocity). 

   Based on the selected turtle, the node publishes the corresponding velocity commands to the appropriate topic. The user can repeat the process multiple times since the interface is enclosed in a **while loop**. The velocity commands are applied for one second, using `ros::Duration(1.0).sleep()`.

---

### **Second Node - `distance`**

The purpose of this node is to stop the motion of any turtle if it gets too close to:
   - The boundaries of the environment.
   - The other turtle.

To achieve this, the node:
- Subscribes to the position topics of both turtles and stores their **x** and **y** coordinates.
- Calculates the distances between the turtles and the distances of each turtle from the environment's boundaries.
- Repeats the calculations after a short delay (using `ros::Duration(0.1).sleep()` and `ros::spinOnce()`) to determine if the moving turtle is exiting the critical region. 

If a turtle remains in the critical region, the node sets the linear velocities (x and y) of both turtles to zero through the respective publishers.

Additionally, the **relative distance** between the two turtles is published on the topic `turtles/distance`.

The node is continuously executed with a frequency = 1000 Hz.


#### **Notes**

1. **Ignoring Angular Velocity** 
   The implementation ignores angular velocity because distance checks are performed in Cartesian coordinates (x and y), which are independent of the turtles' orientations.

2. **Alternative Approaches** 
   An alternative solution could involve reversing the moving turtle's velocity when entering a critical region. However, this would result in unexpected and uncontrolled movements, potentially confusing the user. 
   The current implementation balances **safety** (avoiding collisions) and **consistency** by ensuring turtles do not move in directions contrary to the user's input. Nonetheless, if the user repeatedly commands the turtles to move toward critical regions, collisions may still occur. Preventing such collisions depends on both the program's control logic and the user's inputs.

3. **Speed Limitations** 
   Due to the program's loop rate, it is advisable to avoid setting excessively high input velocities.

---

## **How to Run the Package**

Since the two nodes are interdependent, they must be executed in the following order:

1. **Run `turtlesim_node`** 
   Start the `turtlesim_node` to create the environment and initialize the default turtle (`turtle1`). 

2. **Run `ui_node`** 
   Launch the `ui_node` executable (Note: the executable name matches the name of the `.cpp` file, without the extension). This node spawns a new turtle (`turtle2`), so it is essential to ensure that `turtlesim_node` is already running. 

3. **Run `distance`** 
   Finally, launch the `distance` executable (Again, the executable name matches the `.cpp` file name without the extension). Since this node relies on the presence of both turtles, it is necessary to ensure that `ui_node` has already been executed.

---




