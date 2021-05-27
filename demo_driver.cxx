/*
 * Distributed under OSI-approved BSD 3-Clause License. See
 * accompanying License.txt
 */

#include "catalyst.hpp"

#ifdef CATALYST_USE_MPI
#include "mpi.h"
#endif

#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
#ifdef CATALYST_USE_MPI
  MPI_Init(&argc, &argv);
#endif

  usleep(3000000);

  conduit_cpp::Node node;

  node["stage"] = "Initialize";
  catalyst_initialize(conduit_cpp::c_node(&node));

  int a = 0;
  node["data"].set_external(&a);
  node["stage"] = "Execute";
  catalyst_execute(conduit_cpp::c_node(&node));

  node["stage"] = "Finalize";
  catalyst_finalize(conduit_cpp::c_node(&node));

  node["stage"] = "About";
  catalyst_about(conduit_cpp::c_node(&node));

#ifdef CATALYST_USE_MPI
  MPI_Finalize();
#endif

  return EXIT_SUCCESS;
}
