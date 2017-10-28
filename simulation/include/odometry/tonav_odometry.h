//
// Created by Tomas Krejci on 10/28/17.
//

#ifndef TONAV_TONAV_ODOMETRY_H
#define TONAV_TONAV_ODOMETRY_H

#include <json.hpp>
#include <tonav.h>

#include "../odometry.h"
#include "tonav_calibration.h"

using json = nlohmann::json;

class VioSimulation;

class TonavOdometry: public Odometry {
public:
    static std::unique_ptr<TonavOdometry> load(SimSetup* sim_setup, const json& j);
    
    void initialize(VioSimulation *simulation);
    
    void updateAcceleration(double time, const Eigen::Vector3d& accel);
    void updateRotationRate(double time, const Eigen::Vector3d& gyro);
    void updateFrame(double time, const cv::Mat& frame);
    
    Eigen::Vector3d getBodyPositionInGlobalFrame() const;
    tonav::Quaternion getGlobalToBodyFrameRotation() const;
    
    Eigen::Vector3d getCameraPositionInGlobalFrame() const;
    tonav::Quaternion getGlobalToCameraFrameRotation() const;
    
    virtual ~TonavOdometry();

private:
    TonavOdometry(SimSetup *sim_setup);
    
    VioSimulation *vio_simulation_;
    
    double next_propagation_time_;
    Eigen::Vector3d next_accel_;
    Eigen::Vector3d next_gyro_;
    
    std::shared_ptr<TonavCalibration> tonav_calibration_;
    std::shared_ptr<tonav::Tonav> tonav_;
};

#endif //TONAV_TONAV_ODOMETRY_H