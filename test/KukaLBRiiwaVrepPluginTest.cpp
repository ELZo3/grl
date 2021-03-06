#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE grlTest

// system includes
#include <boost/test/unit_test.hpp>
#include <exception>
#include <boost/math/constants/constants.hpp>
#include <iostream>
#include <vector>

//// local includes
#include "grl/vrep/KukaLBRiiwaVrepPlugin.hpp"

BOOST_AUTO_TEST_SUITE(KukaLBRiiwaVrepPluginTest)

BOOST_AUTO_TEST_CASE(initialization){

BOOST_CHECK_THROW (std::make_shared<grl::KukaVrepPlugin>(),boost::exception);

//// uncomment to test error output
//        try {
//            BOOST_LOG_TRIVIAL(info) << "Starting KUKA LBR iiwa plugin connection to Kuka iiwa\n";
//            auto kukaPluginPG = std::make_shared<grl::KukaVrepPlugin>();
//            kukaPluginPG->construct();
//        } catch (boost::exception& e){
//            // log the error and print it to the screen, don't release the exception
//            BOOST_LOG_TRIVIAL(error) <<  boost::diagnostic_information(e);
//        }

}

BOOST_AUTO_TEST_CASE(connectToFake){

    auto config = std::make_tuple(
                    "LBR_iiwa_14_R820_joint1", // Joint1Handle, 
                    "LBR_iiwa_14_R820_joint2", // Joint2Handle, 
                    "LBR_iiwa_14_R820_joint3", // Joint3Handle, 
                    "LBR_iiwa_14_R820_joint4", // Joint4Handle, 
                    "LBR_iiwa_14_R820_joint5", // Joint5Handle, 
                    "LBR_iiwa_14_R820_joint6", // Joint6Handle, 
                    "LBR_iiwa_14_R820_joint7", // Joint7Handle,
                    "RobotTip#0"             , // RobotTipHandle,
                    "RobotTarget#0"          , // RobotTargetHandle,
                    "Robotiiwa"              , // RobotTargetBaseHandle,
//                    "ImplantCutPath"         , // ImplantCutPathHandle,
//                    "RemoveBallJoint"        , // RemoveBallJointPathHandle,
//                    "FemurBone"              , // FemurBoneHandle
                    "tcp://127.0.0.1:9998"   , // LocalZMQAddress
                    "tcp://127.0.0.1:9998"   , // RemoteZMQAddress
                    "127.0.0.1"              , // LocalHostKukaKoniUDPAddress,
                    "30200"                  , // LocalHostKukaKoniUDPPort,
                    "127.0.0.1"              , // RemoteHostKukaKoniUDPAddress,
                    "30200"                     // RemoteHostKukaKoniUDPPort
                );
auto plugin = std::make_shared<grl::KukaVrepPlugin>(config);
}

BOOST_AUTO_TEST_SUITE_END()
