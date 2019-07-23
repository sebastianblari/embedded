Pi_HOST := 192.168.0.29
TOPIC := stl/message
LOG_PATH := ../flags.txt

exec: 
	make -j 2 local_server local_browser
	
local_server:
	python3 manage.py runserver

local_browser:
	firefox http://127.0.0.1:8000/

listen:
	mosquitto_sub -h $(Pi_HOST) -t "$(TOPIC)" >> $(LOG_PATH) &

run: listen exec
