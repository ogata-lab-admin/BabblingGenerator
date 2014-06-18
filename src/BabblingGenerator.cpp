// -*- C++ -*-
/*!
 * @file  BabblingGenerator.cpp
 * @brief Babbling Motion Generator
 * @date $Date$
 *
 * $Id$
 */

#include "BabblingGenerator.h"

// Module specification
// <rtc-template block="module_spec">
static const char* babblinggenerator_spec[] =
  {
    "implementation_id", "BabblingGenerator",
    "type_name",         "BabblingGenerator",
    "description",       "Babbling Motion Generator",
    "version",           "1.0.0",
    "vendor",            "ogata-lab",
    "category",          "Experimental",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    "conf.default.random_seed", "-1",
    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.random_seed", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
BabblingGenerator::BabblingGenerator(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_currentPositionIn("currentPosition", m_currentPosition),
    m_targetPositionOut("targetPosition", m_targetPosition)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
BabblingGenerator::~BabblingGenerator()
{
}



RTC::ReturnCode_t BabblingGenerator::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("currentPosition", m_currentPositionIn);
  
  // Set OutPort buffer
  addOutPort("targetPosition", m_targetPositionOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  bindParameter("random_seed", m_random_seed, "-1");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t BabblingGenerator::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t BabblingGenerator::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t BabblingGenerator::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t BabblingGenerator::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t BabblingGenerator::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t BabblingGenerator::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t BabblingGenerator::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t BabblingGenerator::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t BabblingGenerator::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t BabblingGenerator::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t BabblingGenerator::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void BabblingGeneratorInit(RTC::Manager* manager)
  {
    coil::Properties profile(babblinggenerator_spec);
    manager->registerFactory(profile,
                             RTC::Create<BabblingGenerator>,
                             RTC::Delete<BabblingGenerator>);
  }
  
};


