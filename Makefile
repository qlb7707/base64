#================================================================
#   Copyright (C) 2016 All rights reserved.
#   
#   filename     :Makefile
#   author       :qinlibin
#   create date  :2016/06/08
#   mail         :qin_libin@foxmail.com
#
#================================================================


CC = g++
CFLAGS = -I.
OBJS = encode.o common.o
OBJS2 = decode.o common.o
BIN = b64_encode
BIN2 = b64_decode
INSTALL_DIR = /usr/local/bin/
all: $(BIN) $(BIN2)
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 
$(BIN2):$(OBJS2)
	$(CC) $(CFLAGS) $^ -o $@ 
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
install:
	cp $(BIN) $(BIN2) $(INSTALL_DIR)
uninstall:
	rm $(INSTALL_DIR)$(BIN) $(INSTALL_DIR)$(BIN2)
clean:
	rm -f $(BIN)
	rm -f $(BIN2)
	rm -f ./*.o
