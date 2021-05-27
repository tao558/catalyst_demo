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
  conduit_cpp::Node n = conduit_cpp::cpp_node(const_cast<conduit_node*>(params));
  std::cout << "On stage " << n["stage"].as_char8_str() << std::endl;
}

//-----------------------------------------------------------------------------
void catalyst_execute(const conduit_node* params)
{
  conduit_cpp::Node n = conduit_cpp::cpp_node(const_cast<conduit_node*>(params));
  std::cout << "On stage " << n["stage"].as_char8_str() << std::endl;

  int* dat = n["data"].as_int32_ptr();
  if (*dat != 0)
  {
    std::stringstream msg;
    msg << "ERROR: Expected node data to be equal to 0, got " << *dat
        << std::endl;
    throw std::runtime_error(msg.str());
  }
}

//-----------------------------------------------------------------------------
void catalyst_finalize(const conduit_node* params)
{
  conduit_cpp::Node n = conduit_cpp::cpp_node(const_cast<conduit_node*>(params));
  std::cout << "On stage " << n["stage"].as_char8_str() << std::endl;
}

//-----------------------------------------------------------------------------
void catalyst_about(conduit_node* params)
{
  catalyst_stub_about(params);
}
