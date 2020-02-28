#coding = utf-8

def mydecorator(func):
	def wrapper(*args,**kw):
		print('hi,now is:')
		return func(*args,**kw)
	return wrapper

@mydecorator
def now():
	print('2015-12-9')

now()

