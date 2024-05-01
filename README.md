<!-- ABOUT THE PROJECT -->
## About The Project

This repository contains a simple pool of memory buffers in C. It is intended for embedded systems containing MCUs with limited resources. Operations of allocating and freeing buffers are relatively fast, much faster then standard malloc.

### Key concept

Pool here is a set of buffers of the same size, which can be rented / allocated and returned / freed. The entire structure can be compared to the stack of plastic cups (that is what author inspired from). Cups are taken from the top, and returned to the top. But sometimes they are returned in different order that they were taken. Thats why each buffer contains a pointer to the next buffer in the stack, and the first buffer to be taken is stored in the pool pointer.

### Limitations

* All buffers in the pool are the same size.
* Maximum number of buffers is 255.

<!-- USAGE EXAMPLES -->
## Usage

Example usage can be seen in `tests` folder.

<!-- ROADMAP -->
## Roadmap

- [x] Create first public version
- [ ] Add proper unit tests
- [ ] Add advanced test (either simulated or emulated)

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.