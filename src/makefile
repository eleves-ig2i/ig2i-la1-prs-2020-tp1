CC=gcc
EXE_DIR=../out/
W_FLAGS=-Wall

all: pid login check-fork ctrlc-handler ctrlc-handler-v2 zombie-process schedule

pid: pid.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe

login: login.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe
	
check-fork: check-fork.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe
	
ctrlc-handler: ctrlc-handler.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe
	
ctrlc-handler-v2: ctrlc-handler-v2.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe
	
zombie-process: zombie-process.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe

schedule: schedule.c
	$(CC) $< $(W_FLAGS) -o $(EXE_DIR)$@.exe
	
clean :
	rm -f $(EXE_DIR)*.exe
