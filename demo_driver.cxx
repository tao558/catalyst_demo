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

  conduit_cpp::Node node;

  usleep(3000000);

  int a = 10;
  node["data"].set_int32(a);
  catalyst_initialize(conduit_cpp::c_node(&node));

  node["data"] = ++a;
  catalyst_execute(conduit_cpp::c_node(&node));

  node["data"] = ++a;
  catalyst_finalize(conduit_cpp::c_node(&node));

  catalyst_about(conduit_cpp::c_node(&node));

#ifdef CATALYST_USE_MPI
  MPI_Finalize();
#endif

  return EXIT_SUCCESS;
}
