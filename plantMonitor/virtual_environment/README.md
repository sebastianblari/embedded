# Sensor monitoring app: Framework

Built using Django, which is a high-level Python Web framework. [Find Django documentation here.](https://www.djangoproject.com/)

## Installation

Use the package manager [pip](https://pip.pypa.io/en/stable/) or **pip3** to install.

If running for the first time, it's necessary to set up Python virtual environment:

```bash
cd <virtual_environment_directory> # go to work area: where Django project is stored
sudo apt-get install python-virtualenv

# create virtual environment
virtualenv -p python3 . # use python or python3 depending on the version installed

source bin/activate     # to activate python virtual environment
pip install django==2.0.7 # install Django in venv
pip freeze # to see Django version installed in venv 
deactivate # to stop virtual environment
```

## Usage

```bash
cd <virtual_environment_directory> # go to work area: where Django project is stored
source bin/activate        # to activate python virtual environment

cd src # go to Django project root directory: where 'manage.py' file is
python manage.py runserver # to run project 
```
You should see the following output:
```bash
Django version 2.0.7, using settings <djangoProject_name>
Starting development server at <web_address>
Quit the server with CONTROL-C.
```
Point your browser at **<web_address>** and you should see the Web page for the Sensor Monitoring app.

Once your done:
```bash
deactivate # to stop virtual environment
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Copyright &copy;
Circuititos S.A.
