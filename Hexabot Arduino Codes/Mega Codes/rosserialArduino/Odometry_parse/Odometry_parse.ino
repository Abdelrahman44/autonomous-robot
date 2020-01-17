String command_ultra, command_encoders;
int ultraL1, ultraL2, ultraR1, ultraR2, ultraF, ultraB;
long encoderL, encoderR;
String part1_ultra, part2_ultra, part3_ultra, part4_ultra, part5_ultra, part6_ultra;
String part1_encoders, part2_encoders;
char c_ultra, c_encoders;
unsigned long previousmills = 0, currentmills = 0;
const long interval = 200;

/*-----------------ROS Odometry------------------------*/

#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

ros::NodeHandle  nh;

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;


char base_link[] = "/base_link";
char odom[] = "/odom";
double theta=0, x=0, y=0;


/*-------------------Functions init---------------------*/
int count = 0;
void r_ultra();
void r_encoders();
void parse_ultra(String command_ultra1);
void parse_encoders(String command_encoders1);
void t_data1();
void from_dxdy_to_xytheta(long pos_l, long pos_r);

/*---------------------Main code------------------------*/
// Ultrasonics Nano on Serial 3
// Encoders Nano on Serial 2
// Raspberry pi on Serial 1


void setup(){
  nh.initNode();
  broadcaster.init(nh);
  Serial3.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
}



void loop() {
  r_ultra();
  r_encoders();
  from_dxdy_to_xytheta(encoderL, encoderR);
  if(theta > 3.14) theta=-3.14;
  if(theta < -3.14) theta=+3.14;
  t.header.frame_id = odom;
  t.child_frame_id = base_link;
  
  t.transform.translation.x = x;
  t.transform.translation.y = y;
  
  t.transform.rotation = tf::createQuaternionFromYaw(theta);
  t.header.stamp = nh.now();
  
  broadcaster.sendTransform(t);
  nh.spinOnce();
  /*
  r_ultra();
  r_encoders();
  */
}

























/*------------------------------------Functions---------------------------------*/

//receiving from ultrasonics
void r_ultra(){
  if (Serial3.available()) {
    c_ultra = Serial3.read();

    if (c_ultra == '\n') {
      parse_ultra(command_ultra);
      command_ultra = "";
    }
    else {
      command_ultra += c_ultra;
    }
  }
}



//receiving from encoders
void r_encoders(){
  if (Serial2.available()) {
    c_encoders = Serial2.read();

    if (c_encoders == '\n') {
      parse_encoders(command_encoders);
      command_encoders = "";
    }
    else {
      command_encoders += c_encoders;
    }
  }
}



//parse Ultrasonic data
void parse_ultra(String command_ultra1){
  part1_ultra = command_ultra1.substring(0, command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part2_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part3_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part4_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part5_ultra = command_ultra1.substring(0, command_ultra1.indexOf("\t"));
  command_ultra1.remove(0, command_ultra1.indexOf("\t")+1);
  part6_ultra = command_ultra1.substring(0,command_ultra1.indexOf("\n"));
  
  ultraL1 = part1_ultra.toFloat();
  ultraL2 = part2_ultra.toFloat();
  ultraR1 = part3_ultra.toFloat();
  ultraR2 = part4_ultra.toFloat();
  ultraF = part5_ultra.toFloat();
  ultraB = part6_ultra.toFloat();
}



//parse GPS data
void parse_encoders(String command_encoders1){
  part1_encoders = command_encoders1.substring(0, command_encoders1.indexOf("\t"));
  command_encoders1.remove(0, command_encoders1.indexOf("\t")+1);
  part2_encoders = command_encoders1.substring(0,command_encoders1.indexOf("\n"));
  
  encoderL = part1_encoders.toFloat();
  encoderR = part2_encoders.toFloat();
}

void t_data(){
  
  Serial.print(ultraL1);        //1
  Serial.print("\t");
  
  Serial.print(ultraL2);         //2
  Serial.print("\t");
  
  Serial.print(ultraR1);        //3
  Serial.print("\t");
  
  Serial.print(ultraR2);        //4
  Serial.print("\t");
  
  Serial.print(ultraF);        //5
  Serial.print("\t");
  
  Serial.print(ultraB);        //6
  Serial.print("\t");
  
  Serial.print(encoderL);        //7
  Serial.print("\t");
  
  Serial.print(encoderR);        //8
  Serial.println();
}

void from_dxdy_to_xytheta(long pos_l, long pos_r){
  theta = (1/0.29)*(pos_r-pos_l)*0.01;
  x = 0.5*(pos_l+pos_r)*cos(theta)*(1/10.0);
  y = 0.5*(pos_l+pos_r)*sin(theta)*(1/10.0);
  }

