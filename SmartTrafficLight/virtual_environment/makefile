SHELL := /bin/bash
SRC_PATH = ./src
FILE_NAME:= flags.txt

init:
	echo "FLAGS LOG" > $(FILE_NAME)

exec:
	$(MAKE) run -C $(SRC_PATH)

clean:
	rm -rf $(FILE_NAME)

run: init exec
