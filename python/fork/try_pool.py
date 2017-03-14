#!/usr/bin/python

from multiprocessing import Pool

import os, time, random

def functions(name):
	print('该子进程的id为(%d),pid为(%s)'%(name, os.getpid()))

if __name__ == '__main__':
	print('父进程的pid为(%d)'%os.getpid())
	p = Pool(5)	#创建5个进程池子
	for i in range(5):
		p.apply_async(functions, (i, ))
	p.close()
	p.join()
