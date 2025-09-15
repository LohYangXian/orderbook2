### Building the Project with CMake

This project uses CMake for building and managing dependencies. The main configuration is in `CMakeLists.txt`, which sets up the build process as follows:

- **CMake Version**: Requires CMake 3.12 or higher.
- **Project Name**: The project is named `OrderBookDemo`.
- **C++ Standard**: The build uses the C++11 standard for compiling all source files.
- **Source Files**: The main executable is built from `main.cpp`.
- **Executable**: An executable named `OrderBookDemo` is created.
- **Include Directories**: The `OrderBook` directory is added to the compiler's include path.
- **Subdirectories**: The `OrderBook` and `OrderBookTests` directories are included as subprojects, allowing modular development and testing.
- **Linking**: The `OrderBookDemo` executable is linked against the `OrderBook` library.

#### How to Build

1. Create a build directory:
   ```sh
   mkdir build && cd build
   ```
2. Run CMake to configure the project:
   ```sh
   cmake ..
   ```
3. Build the project:
   ```sh
   make
   ```

This will generate the `OrderBookDemo` executable and build all necessary libraries and tests.

#### To run Orderbook
``` bash 
cd build
./OrderBookDemo
```

#### To run Orderbook Tests
``` bash 
cd build/OrderBookTests
./RunTests
```



---

### Notes

- **Boost Dependency**:  
  If you see errors about missing `boost/optional.hpp`, install Boost with:
  ```sh
  brew install boost
  ```
  CMake will automatically find Boost if installed in standard locations.

- **Google Test**:  
  No manual setup is needed; CMake will fetch and build Google Test for you.

- **IntelliSense Issues in VS Code**:  
  If you see include errors in VS Code, update your `.vscode/c_cpp_properties.json` to include:
  - `${workspaceFolder}/OrderBook`
  - `${workspaceFolder}/build/_deps/googletest-src/googletest/include`
  - `${workspaceFolder}/build/_deps/googletest-src/googlemock/include`
  - Boost include path (usually `/opt/homebrew/include` on Mac)

- **Rebuilding**:  
  After the initial `cmake ..`, you only need to run `make` for subsequent builds unless you change `CMakeLists.txt` or add/remove source files.

---

### Project Structure

- `OrderBook/` — Core order book implementation
- `OrderBookTests/` — Unit tests using Google Test
- `main.cpp` — Demo executable entry point
- `CMakeLists.txt` — Build configuration

---

### OrderBook Design Highlights

- Uses `std::map` for bids and asks, allowing efficient lookup and iteration.
- Uses `boost::optional` for representing best bid/ask, making code safer and clearer.
- Provides friend `operator<<` for easy printing of order book state.
- Inline functions are defined in headers for performance and visibility.