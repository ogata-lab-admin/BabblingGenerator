// -*- C++ -*-
/*!
 * @file  BabblingGenerator.cpp
 * @brief Babbling Motion Generator
 * @date $Date$
 *
 * $Id$
 */

#include "BabblingGenerator.h"
#include <random>

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
    "conf.default.number_of_joint", "2",
    "conf.default.min", "-1.0, -1.0",
    "conf.default.max", "+1.0, +1.0",
    "conf.default.random_type", "mersenne_twister",
    "conf.default.distribution_type", "uniform", 
    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.random_seed", "text",
    "conf.__widget__.number_of_joint", "text", 
    "conf.__widget__.min", "text",
    "conf.__widget__.max", "text",
    "conf.__widget__.random_type", "radio",
    "conf.__widget__.distribution_type", "radio",
    // Constraints
    "conf.__constraint__.random_type", "mersenne_twister",
    "conf.__constraint__.distribution_type", "normal, uniform",
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
  , m_pMT(NULL)
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
  bindParameter("number_of_joint", m_number_of_joint, "1");
  bindParameter("min", m_min, "-1.0, -1.0");
  bindParameter("max", m_max, "+1.0, +1.0");
  bindParameter("random_type", m_random_type, "mersenne_twister");
  bindParameter("distribution_type", m_distribution_type, "uniform");
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
  int seed = m_random_seed;
  if (m_random_seed < 0) {
    std::random_device seed_gen;
    seed = seed_gen();
  }
  m_pMT = new std::mt19937(seed);
  
  m_Maxs.clear();
  m_Mins.clear();

  std::string token;
  std::stringstream minss(m_min);
  double buf;
  while(std::getline(minss, token, ',')) {
    std::stringstream trimmer;
    trimmer << token;
    token.clear();
    trimmer >> buf;
    m_Mins.push_back(buf);
  }

  std::stringstream maxss(m_max);
  while(std::getline(maxss, token, ',')) {
    std::stringstream trimmer;
    trimmer << token;
    token.clear();
    trimmer >> buf;
    m_Maxs.push_back(buf);
  }

  if (m_Maxs.size() != m_number_of_joint || m_Mins.size () != m_number_of_joint) {
    std::cout << "[RTC.BabblingGenerator] " << "Invalid Number of Joint or Min/Max values" << std::endl;
    std::cout << "[RTC.BabblingGenerator] " << "m_numberof_joint: " << m_number_of_joint << std::endl;
    std::cout << "[RTC.BabblingGenerator] " << "m_max: " << m_max << std::endl;
    std::cout << "[RTC.BabblingGenerator] " << "m_min: " << m_min << std::endl;
    return RTC::RTC_ERROR;
  }

  for(int i = 0;i < m_Maxs.size();i++) {
    m_dist.push_back(std::uniform_real_distribution<double>(m_Mins[i], m_Maxs[i]));
  }

  m_targetPosition.data.length(m_number_of_joint);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t BabblingGenerator::onDeactivated(RTC::UniqueId ec_id)
{
  m_dist.clear();
  delete m_pMT; m_pMT = NULL;
  m_Maxs.clear();
  m_Mins.clear();

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t BabblingGenerator::onExecute(RTC::UniqueId ec_id)
{
  for(int i = 0;i < m_number_of_joint;i++) {
    m_targetPosition.data[i] =
      m_dist[i](*m_pMT);
  }
  m_targetPositionOut.write();
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


