# STL app: Web Interface

Built using Django, which is a high-level Python Web framework. [Find Django documentation here.](https://www.djangoproject.com/)

## Usage

```bash
cd <virtual_environment_directory> # go to work area: where Django project is stored

source bin/activate # to activate python virtual environment

make run # run Web Interface 
```

Once your done:
```bash
deactivate # to stop virtual environment
```

### Get Host
Run in PC shell and in RaspeberryPi:
```bash
ifconfig | grep broadcast | awk -F  " " '/1/ {print $2}'
```
Update PC_HOST and Pi_HOST variables in makefiles and ./src/pages/views.py

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright &copy;
Circuititos S.A.
