## Skeleton
Each example should include common dependencies

```INI
#Softeq Firmware Common project
[env]
lib_extra_dirs =
  ../../
  ../../psp
  boards
lib_deps =
  sfc_hal
```

## Directories structure
- boards - your board configuration: json file for platformio.ini and library board_{YOUR_BOARD} based on your PSP
- src - sources based on SFC. should not include vendor specific code

TODO: need to create skeleton or project generator
