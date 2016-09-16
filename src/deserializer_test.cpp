#include <catch.h>

#include <ros_type_introspection/deserializer.hpp>

#include <sensor_msgs/JointState.h>
#include <sensor_msgs/NavSatStatus.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Int16MultiArray.h>

using namespace ros::message_traits;
using namespace RosIntrospection;

TEST_CASE("Deserialize JointState", "Deserialize")
//int func()
{
    ROSTypeList type_map = buildROSTypeMapFromDefinition(
                DataType<sensor_msgs::JointState >::value(),
                Definition<sensor_msgs::JointState >::value() );

    sensor_msgs::JointState joint_state;

    joint_state.header.seq = 2016;
    joint_state.header.stamp.sec  = 1234;
    joint_state.header.stamp.nsec = 567*1000*1000;
    joint_state.header.frame_id = "pippo";

    joint_state.name.resize( 3 );
    joint_state.position.resize( 3 );
    joint_state.velocity.resize( 3 );
    joint_state.effort.resize( 3 );

    std::string names[3];
    names[0] = ("hola");
    names[1] = ("ciao");
    names[2] = ("bye");

    for (int i=0; i<3; i++)
    {
        joint_state.name[i] = names[i];
        joint_state.position[i]= 11+i;
        joint_state.velocity[i]= 21+i;
        joint_state.effort[i]= 31+i;
    }

    std::vector<uint8_t> buffer(64*1024);
    ros::serialization::OStream stream(buffer.data(), buffer.size());
    ros::serialization::Serializer<sensor_msgs::JointState>::write(stream, joint_state);

    uint8_t* buffer_ptr = buffer.data();

    ROSType main_type( DataType<sensor_msgs::JointState >::value() );

    ROSTypeFlat flat_container;
    buildRosFlatType(type_map,
                     main_type,
                     "JointState",
                     &buffer_ptr, &flat_container);

    for(auto&it: flat_container.value) {
        std::cout << it.first << " >> " << it.second << std::endl;
    }

    for(auto&it: flat_container.name_id) {
        std::cout << it.first << " >> " << it.second << std::endl;
    }

    REQUIRE( flat_container.value[0].first  == SString("JointState.header.seq"));
    REQUIRE( flat_container.value[0].second == 2016 );
    REQUIRE( flat_container.value[1].first  == SString("JointState.header.stamp"));
    REQUIRE( flat_container.value[1].second == 1234.567 );

    REQUIRE( flat_container.value[2].first  == SString("JointState.position[0]"));
    REQUIRE( flat_container.value[2].second == 11 );
    REQUIRE( flat_container.value[3].first  == SString("JointState.position[1]"));
    REQUIRE( flat_container.value[3].second == 12 );
    REQUIRE( flat_container.value[4].first  == SString("JointState.position[2]"));
    REQUIRE( flat_container.value[4].second == 13 );

    REQUIRE( flat_container.value[5].first  == SString("JointState.velocity[0]"));
    REQUIRE( flat_container.value[5].second == 21 );
    REQUIRE( flat_container.value[6].first  == SString("JointState.velocity[1]"));
    REQUIRE( flat_container.value[6].second == 22 );
    REQUIRE( flat_container.value[7].first  == SString("JointState.velocity[2]"));
    REQUIRE( flat_container.value[7].second == 23 );

    REQUIRE( flat_container.value[8].first  == SString("JointState.effort[0]"));
    REQUIRE( flat_container.value[8].second == 31 );
    REQUIRE( flat_container.value[9].first  == SString("JointState.effort[1]"));
    REQUIRE( flat_container.value[9].second == 32 );
    REQUIRE( flat_container.value[10].first  == SString("JointState.effort[2]"));
    REQUIRE( flat_container.value[10].second == 33 );

    REQUIRE( flat_container.name_id[0].first  == SString("JointState.header.frame_id"));
    REQUIRE( flat_container.name_id[0].second == SString("pippo") );

    REQUIRE( flat_container.name_id[1].first  == SString("JointState.name[0]"));
    REQUIRE( flat_container.name_id[1].second == SString("hola") );
    REQUIRE( flat_container.name_id[2].first  == SString("JointState.name[1]"));
    REQUIRE( flat_container.name_id[2].second == SString("ciao") );
    REQUIRE( flat_container.name_id[3].first  == SString("JointState.name[2]"));
    REQUIRE( flat_container.name_id[3].second == SString("bye") );
}

TEST_CASE("Deserialize NavSatStatus", "Deserialize")
//int func()
{
    // We test this because we want to test that constant fields are skipped.

    ROSTypeList type_map = buildROSTypeMapFromDefinition(
                DataType<sensor_msgs::NavSatStatus >::value(),
                Definition<sensor_msgs::NavSatStatus >::value() );

    sensor_msgs::NavSatStatus nav_stat;
    nav_stat.status  = nav_stat.STATUS_GBAS_FIX;  // 2
    nav_stat.service = nav_stat.SERVICE_COMPASS; // 4


    std::vector<uint8_t> buffer(64*1024);
    ros::serialization::OStream stream(buffer.data(), buffer.size());
    ros::serialization::Serializer<sensor_msgs::NavSatStatus>::write(stream, nav_stat);

    uint8_t* buffer_ptr = buffer.data();

    ROSType main_type( DataType<sensor_msgs::NavSatStatus >::value() );

    ROSTypeFlat flat_container;
    buildRosFlatType(type_map,
                     main_type,
                     "nav_stat",
                     &buffer_ptr, &flat_container);

    std::cout << " -------------------- " << std::endl;

    for(auto&it: flat_container.value) {
        std::cout << it.first << " >> " << it.second << std::endl;
    }

    REQUIRE( flat_container.value[0].first  == SString("nav_stat.status"));
    REQUIRE( flat_container.value[0].second == nav_stat.STATUS_GBAS_FIX );
    REQUIRE( flat_container.value[1].first  == SString("nav_stat.service"));
    REQUIRE( flat_container.value[1].second == nav_stat.SERVICE_COMPASS );
}

TEST_CASE("Deserialize IMU", "Deserialize")
//int func()
{
    // We test this because to check if arrays with fixed length work.

    ROSTypeList type_map = buildROSTypeMapFromDefinition(
                DataType<sensor_msgs::Imu >::value(),
                Definition<sensor_msgs::Imu >::value() );

    sensor_msgs::Imu imu;

    imu.header.seq = 2016;
    imu.header.stamp.sec  = 1234;
    imu.header.stamp.nsec = 567*1000*1000;
    imu.header.frame_id = "pippo";

    imu.orientation.x = 11;
    imu.orientation.y = 12;
    imu.orientation.z = 13;
    imu.orientation.w = 14;

    imu.angular_velocity.x = 21;
    imu.angular_velocity.y = 22;
    imu.angular_velocity.z = 23;

    imu.linear_acceleration.x = 31;
    imu.linear_acceleration.y = 32;
    imu.linear_acceleration.z = 33;

    for (int i=0; i<9; i++)
    {
        imu.orientation_covariance[i]         = 40+i;
        imu.angular_velocity_covariance[i]    = 50+i;
        imu.linear_acceleration_covariance[i] = 60+i;
    }

    std::vector<uint8_t> buffer(64*1024);
    ros::serialization::OStream stream(buffer.data(), buffer.size());
    ros::serialization::Serializer<sensor_msgs::Imu>::write(stream, imu);

    uint8_t* buffer_ptr = buffer.data();

    ROSType main_type( DataType<sensor_msgs::Imu >::value() );

    ROSTypeFlat flat_container;
    buildRosFlatType(type_map,
                     main_type,
                     "imu",
                     &buffer_ptr, &flat_container);

    std::cout << " -------------------- " << std::endl;
    for(auto&it: flat_container.value) {
        std::cout << it.first << " >> " << it.second << std::endl;
    }

    int index = 0;

    REQUIRE( flat_container.value[index].first  == SString("imu.header.seq"));
    REQUIRE( flat_container.value[index].second == 2016 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.header.stamp"));
    REQUIRE( flat_container.value[index].second == 1234.567 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.orientation.x"));
    REQUIRE( flat_container.value[index].second == 11 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.orientation.y"));
    REQUIRE( flat_container.value[index].second == 12 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.orientation.z"));
    REQUIRE( flat_container.value[index].second == 13 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.orientation.w"));
    REQUIRE( flat_container.value[index].second == 14 );
    index++;

    for(int i=0; i<9; i++)
    {
        char str[64];
        sprintf(str, "imu.orientation_covariance[%d]",i);
        REQUIRE( flat_container.value[index].first  == SString(str) );
        REQUIRE( flat_container.value[index].second == 40+i );
        index++;
    }

    REQUIRE( flat_container.value[index].first  == SString("imu.angular_velocity.x"));
    REQUIRE( flat_container.value[index].second == 21 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.angular_velocity.y"));
    REQUIRE( flat_container.value[index].second == 22 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.angular_velocity.z"));
    REQUIRE( flat_container.value[index].second == 23 );
    index++;

    for(int i=0; i<9; i++)
    {
        char str[64];
        sprintf(str, "imu.angular_velocity_covariance[%d]",i);
        REQUIRE( flat_container.value[index].first  == SString(str) );
        REQUIRE( flat_container.value[index].second == 50+i );
        index++;
    }

    REQUIRE( flat_container.value[index].first  == SString("imu.linear_acceleration.x"));
    REQUIRE( flat_container.value[index].second == 31 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.linear_acceleration.y"));
    REQUIRE( flat_container.value[index].second == 32 );
    index++;
    REQUIRE( flat_container.value[index].first  == SString("imu.linear_acceleration.z"));
    REQUIRE( flat_container.value[index].second == 33 );
    index++;

    for(int i=0; i<9; i++)
    {
        char str[64];
        sprintf(str, "imu.linear_acceleration_covariance[%d]",i);
        REQUIRE( flat_container.value[index].first  == SString(str) );
        REQUIRE( flat_container.value[index].second == 60+i );
        index++;
    }
}



TEST_CASE("Deserialize Int16MultiArray", "Deserialize")
//int func()
{
    ROSTypeList type_map = buildROSTypeMapFromDefinition(
                DataType<std_msgs::Int16MultiArray >::value(),
                Definition<std_msgs::Int16MultiArray >::value() );

    std_msgs::Int16MultiArray multi_array;

    const unsigned N = 6;
    multi_array.layout.data_offset = 42;
    multi_array.data.resize(N);

    for (unsigned i=0; i<N; i++){
        multi_array.data[i] = i;
    }


    std::vector<uint8_t> buffer(64*1024);
    ros::serialization::OStream stream(buffer.data(), buffer.size());
    ros::serialization::Serializer<std_msgs::Int16MultiArray>::write(stream, multi_array);

    uint8_t* buffer_ptr = buffer.data();

    ROSType main_type( DataType<std_msgs::Int16MultiArray>::value() );

    ROSTypeFlat flat_container;
    buildRosFlatType(type_map,
                     main_type,
                     "multi_array",
                     &buffer_ptr, &flat_container);

    std::cout << " -------------------- " << std::endl;

    for(auto&it: flat_container.value) {
        std::cout << it.first << " >> " << it.second << std::endl;
    }

}


