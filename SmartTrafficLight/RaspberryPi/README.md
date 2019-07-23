# STL app

Built using Python3

## Usage

```bash
cd <RaspberryPi_directory> # go to work area: source files

make run # run App 
```

### Get Host
Run in PC shell and in RaspeberryPi:
```bash
ifconfig | grep broadcast | awk -F  " " '/1/ {print $2}'
```
Update PC_HOST and Pi_HOST variables in makefiles and ./source/trafficlightmanager.py.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright &copy;
Circuititos S.A.
