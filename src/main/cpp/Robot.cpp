// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>

#include <frc/drive/DifferentialDrive.h>
#include "rev/CANSparkMax.h"
#include <frc/XboxController.h>


/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  rev::CANSparkMax m_FLM{10, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_FRM{8, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_RLM{11, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_RRM{9, rev::CANSparkMax::MotorType::kBrushless};

  frc::DifferentialDrive m_robotDrive{m_FLM, m_FRM};
  frc::XboxController m_stick{0};

 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_RRM.Follow(m_FRM);
    m_RLM.Follow(m_FLM);

    m_FRM.SetInverted(true);

    m_robotDrive.SetDeadband(.1);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style
    m_robotDrive.ArcadeDrive(m_stick.GetLeftY(), m_stick.GetRightX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
