/*
 * Distributed under OSI-approved BSD 3-Clause License. See
 * accompanying License.txt
 */
#include <catalyst.hpp>
#include <catalyst_stub.h>
#include <sstream>
#include <stdexcept>

// Call the stub implementation and check the node passed in.

//-----------------------------------------------------------------------------
void catalyst_initialize(const conduit_node* params)
{
  catalyst_stub_initialize(params);
  std::cout << "Initializing" << std::endl;
  conduit_cpp::Node n = conduit_cpp::cpp_node(const_cast<conduit_node*>(params));

  if (n["data"].as_int32() != 10)
  {
    std::stringstream msg;
    msg << "ERROR: Expected node data to be equal to 10, got " << n["data"].as_int32() << std::endl;
    throw std::runtime_error(msg.str());
  }
}

//-----------------------------------------------------------------------------
void catalyst_execute(const conduit_node* params)
{
  catalyst_stub_execute(params);
  std::cout << "Executing" << std::endl;
  conduit_cpp::Node n = conduit_cpp::cpp_node(const_cast<conduit_node*>(params));

  if (n["data"].as_int32() != 11)
  {
    std::stringstream msg;
    msg << "ERROR: Expected node data to be equal to " << 11 << ", got " << n["data"].as_int32()
        << std::endl;
    throw std::runtime_error(msg.str());
  }
}

//-----------------------------------------------------------------------------
void catalyst_finalize(const conduit_node* params)
{
  catalyst_stub_finalize(params);
  std::cout << "Finalizing" << std::endl;
  conduit_cpp::Node n = conduit_cpp::cpp_node(const_cast<conduit_node*>(params));

  if (n["data"].as_int32() != 12)
  {
    std::stringstream msg;
    msg << "ERROR: Expected node data to be equal to 12, got " << n["data"].as_int32() << std::endl;

    throw std::runtime_error(msg.str());
  }
}

//-----------------------------------------------------------------------------
void catalyst_about(conduit_node* params)
{
  catalyst_stub_about(params);
}
