# STM32_CAN_abstraction
C++ STM32 Hall CAN warper library

# Usage

The library constitutes of:

- `can_interface.hpp`, the main class responsible for receiving and interpreting frames
- a set of header files containing the structs that are relayed as frames' payloads.
- `message_abstraction.hpp`, a file handling the inner workings of the library

All files are automatically included once the `can_interface.hpp` is included.

**All classes, structs, enumeration types and constants are namespaced.**

# Inclusion requirements

(1) Can interrupt RX0 and RX1 must be enabled
(2) In properties->c/c++>build->includes add relative path to the library\
(3) Do `git submodule add -b <branch> <url> <relative_path_4m_root>` to add the library as a submodule
(4)

# Sending frames

To send a frame, first create a data structure that will be the frame's payload. All data structures are available once `can_interface.hpp` is included:

```c++
Apps_main apps_test{
    .pedal_position = 1200,
    .counter = 0,
    .position_diff = 0,
    .device_state = Apps_states::Normal_operation,
  };
```

Then, create a `PUTM_CAN::Can_tx_message` object. Its constructor takes the payload struct and `CAN_Tx_HeaderTypeDef` as arguments. Both are available in the CanHeaders and included with `can_interface.hpp`:

```c++
auto apps_main_frame = PUTM_CAN::Can_tx_message<Apps_main>(apps_test, can_tx_header_APPS_MAIN);
```

Finally, you can invoke the `send` method upon it. It takes the `CAN_HandleTypeDef`as an argument and will return a `Hal_StatusTypeDef`:

```c++
auto status = apps_main_frame.send(hcan1);
```

You can check if the frame was relayed correctly:

```c++
if (status != HAL_StatusTypeDef::HAL_OK) {}
```

# Receiving frames

The `can_interface.hpp` creates a **global** `PUTM_CAN::Can_interface can` object and registers a callback. The registered callback grants automatic frame interpretation into structs defined in the `CanHeaders/`. If an error is detected, it invokes the `Error_Handler()` function.

Since the frames are automatically interpreted, one can just invoke the proper getter method on the global `PUTM_Can::can` object to get one of the structs defined in `CanHeaders/`:

```c++
//example for bms_hv_main
auto bms = PUTM_CAN::can.get_bms_hv_main();
```

If you'd like to verify that the frame accessed is new, you can call functions such as `get_bms_hv_main_new_data()` that return a bool.

- all frames are zero-initialised
- a frame is not new until it has been received
- once a frame has been accessed, it is not new

# Adding the library as a submodule

To add the library as a submodule, open the terminal in the repo folder and do:

`git submodule add git@github.com:PUT-Motorsport/PUTM_EV_CAN_LIBRARY.git path/to/library`

Git tries to copy the files directly to the `path/to/library` directory, so it's critical to end the path with a new folder name, preferably "PUTM_EV_CAN_LIBRARY".

Example:
```
git submodule add git@github.com:PUT-Motorsport/PUTM_EV_CAN_LIBRARY.git Project/Core/Inc/PUTM_EV_CAN_LIBRARY
```

The PUTM_EV_CAN_LIBRARY *does not* need to exist at that point.

# Cloning a project with submodules

To clone a project with submodules, do:
```
git clone --recursive <link-to-repo>
```

If a project wasn't cloned recursively:
```
git submodule init
git submodule update
```
will initialize and copy the submodule.

## Detached library HEAD

### How to check if the library has a detached HEAD:

The HEAD should be set correctly by default.

Open the terminal in the library folder and invoke `git status`:

1) With the library HEAD correctly pointing to main, the result should be:

```
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

2) With the detached HEAD, the output is:
   
```
HEAD detached at 1cce897
nothing to commit, working tree clean
```
**In the detached HEAD mode, `git pull` won't work.**

### Fixing the HEAD to point at the latest commit

If the library has been added and it points to a specific commit, do:

```git
git checkout main
```