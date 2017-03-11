#!/usr/bin/python
#-*- coding=utf-8 -*-
import time
import os

print('进程号为(%s)...'%os.getpid())

pid = os.fork()
x = 0
if pid == 0:	#子进程
	while x != 10:
		print(x)
		x += 1
		time.sleep(1)
else:
	while x != 20:
		print(x)
		x += 2
		time.sleep(1)
