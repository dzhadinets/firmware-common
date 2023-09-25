# Firmware Common Library

## Directories structure
hal - library of Hardware Abstraction Level implemetation
sal - library of Software Abstraction Level implementation
psp - is the collection of libraries, Processor Support Packages based on hal driver model
common - is the library collection of common utilities

## Basic library structure/guideline

- /include
  - /sfc
    - {PUBIC HEADER FILES}
- /src
  - {IMPLEMENTATION>
  - {PRIVATE HEADER FILES}

## To build
Go to example dir.
To build
```BASH
pio run
```

To launch on HW
```BASH
pio run -e {YOUR_ENVIRONMENT_NAME} -t upload
```

## Tips
- To configure ESP based boards
  ```BASH
  pio run -e {ESP_ENV_NAME} -t menuconfig
  ```