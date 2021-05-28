Example usage of Catalyst. Instructions for running the demo, changing Catalyst implementations at runtime, and using `catalyst_replay` for debugging are given below. Assumes Linux OS for the time being.

## Prerequisites

1. Build and install Catalyst. You can find the source code here: https://gitlab.kitware.com/paraview/catalyst, and the documentation here: https://catalyst-in-situ.readthedocs.io/en/latest/index.html. See the documentation for build and install instructions. Ensure that `CATALYST_BUILD_REPLAY` is `ON`.
2. Download this code into a new directory.
3. Create a separate build directory and run `cmake {path_to_demo_src}`. Use any build tool of your choice to build. For example, `make` was used during the original demo.
4. source the `setup_demo.sh` file, which will set some helpful environment variables, listed below.
    1. `DEMO_IMPLEMENTATION_LIB_DIRECTORY`, which is the location of our custom catalyst implementation library. We'll use this environment variable to switch to our custom implementation at runtime.
    2. `DEMO_CATALYST_DATA_DUMP_DIRECTORY`, the location where we can write nodes to disk using the stub implementation. This by default is `${CMAKE_CURRENT_BINARY_DIR}/data_dumps`. The directory is created automatically by CMake.
    3. `DEMO_OLD_LD_LIBRARY_PATH`, the value of the `LD_LIBRARY_PATH` environment variable at the time of cmake configuration. We'll use this to switch from our custom implementation to Catalyst's stub implementation.
5. Copy the `catalyst_replay` executable from Catalyst's build directory to the build directory of the demo. This should be located in `bin/` under Catalyst's build directory.

## Running the demo

1. To run the driver, run `./demo_driver`. Note that at first, we are using the stub implementation.
2. To switch to the custom implementation provided here, run `export LD_LIBRARY_PATH="$DEMO_IMPLEMENTATION_LIB_DIRECTORY"`. Re-executing `demo_driver` should output:

   ```
   On stage Initialize
   On stage Execute
   On stage Finalize
   ```
   This indicates that the custom implementation has been called.
   
### Using Catalyst Replay

1. First, reset the LD_LIBRARY_PATH environment variable by running `export LD_LIBRARY_PATH="$DEMO_OLD_LD_LIBRARY_PATH"`. This ensures that our custom Catalyst implementation isn't found and is instead replaced by the stub implementation.
2. Next, tell Catalyst where to write the nodes by running `export CATALYST_DATA_DUMP_DIRECTORY="$DEMO_CATALYST_DATA_DUMP_DIRECTORY"`.
3. Re-run the driver again.
4. After the driver finishes, the data dump directory should be populated. Run `ls data_dumps/` from the build directory to confirm.
5. Now that the `conduit_nodes` have been written to disk, switch back to the custom Catalyst implementation: `export LD_LIBRARY_PATH="$DEMO_IMPLEMENTATION_LIB_DIRECTORY"`.
6. Now call `catalyst_replay`, which expects the data_dump directory as argument: `./catalyst_replay "$CATALYST_DATA_DUMP_DIRECTORY"`. This will read in the `conduit_nodes` that were previously written to disk and call our custom API. The output should be exactly the same as when we called our custom API implementation manually.




