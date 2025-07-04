# ATM2560 Switch Test Suite

This directory contains the unit tests for the ATM2560 Switch project, organized by module.

## Test Structure

```
test/
├── control/           # Tests for control modules
│   └── test_jiggler.c         # Jiggler functionality tests
├── scheduler/         # Tests for scheduler modules  
│   └── test_scheduler_circ_buf.c  # Circular buffer scheduler tests
├── display/          # Tests for display functionality
│   └── test_messageProcessor.c    # LCD message processing tests
└── support/          # Test support files
```

## Running Tests

The project uses [Ceedling](http://www.throwtheswitch.org/ceedling) as the test framework.

### Prerequisites

Install Docker

Pull docker image 
`docker pull throwtheswitch/madsciencelab`

Run docker image

`docker run -it --rm -v {host_folder_with_the_project}:/home/dev/project throwtheswitch/madsciencelab`

inside the docker container:
```
cd atmswitch_uts
ceedling test
```

### Test Commands

```bash
# Run all tests
ceedling test:all

# Run tests for specific module
ceedling test:control
ceedling test:scheduler
ceedling test:display

# Run a specific test file
ceedling test:test_jiggler

# Generate coverage report (if gcov plugin enabled)
ceedling gcov:all

# Clean build artifacts
ceedling clean
```

## Test Organization Guidelines

### Test File Naming
- Test files should be named `test_<module>.c`
- Place tests in the directory corresponding to the source module

### Test Structure
Each test file should:
1. Define `UNIT_TESTS` to enable test-specific code paths
2. Include Unity framework: `#include "unity.h"`
3. Include required headers with correct module paths
4. Implement `setUp()` and `tearDown()` functions
5. Mock hardware registers and external dependencies as needed

### Mock Strategy
- Mock AVR hardware registers as global variables
- Mock external function calls with simple implementations
- Use Unity's built-in assertion macros for verification
