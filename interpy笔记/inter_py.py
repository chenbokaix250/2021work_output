'''les1
def test_var_args(f_arg,*argv):
	print('first normal arg:',f_arg)
	for arg in argv:
		print('another arg through *argv:',arg) 

test_var_args('yasoob','python','eggs','test')
'''

'''les2
def greet_me(**kwargs):
	for key,value in kwargs.items():
		print('{0} == {1}'.format(key,value))

greet_me(name='yasoob')
'''
'''
import pdb

def make_bread():
	pdb.set_trace()
	return "I don't have time."

print(make_bread())
print('debug over!')
'''
'''les4
def multiply(x):
	return (x*x)
def add(x):
	return (x+x)

funcs = [multiply,add]
'''
'''
number_list = range(-5,5)
less_than_zero = filter(lambda x:x<0,number_list)
print(list(less_than_zero))
'''
'''
from functools import reduce
product = reduce((lambda x,y:x*y),[1,2,3,4])
print(product)
'''
'''
some_list = ['a','b','c','b','d','m','n','n']

duplicates = []
for value in some_list:
    if some_list.count(value)>1:
        if value not in duplicates:
            duplicates.append(value)
print(duplicates)
'''
'''
some_list = ['a','b','c','b','d','m','n','n']

duplicates = set([x for x in some_list if some_list.count(x)>1])
print(duplicates)

'''
'''
fat = True
fitness = ('skinny','fat')[fat]
print('Ali is',fitness)

'''
'''
def hi(name='yasoob'):
	return 'hi ' + name 
print(hi())

greet = hi
print(greet())


del hi 

#print(hi())

print(greet())

'''

'''
def hi(name='yasoob'):
    print('now you are inside the hi() function')

    def greet():
        return 'now you are in the greet() function'
    def welcome():
        return 'now you are in the welcome() function'

    print(greet())
    print(welcome())
    print('now you are back in the hi() function')

hi()

greet()
'''
'''
def hi(name='yasoob'):
    def greet():
        return 'now you are in the greet() function'

    def welcome():
        return 'now you are in the welcome() function'

    if name == 'yasoob':
        return greet
    else:
        return welcome

a = hi()
print(a)
print(a())
'''
'''
def hi():
    return  'hi  yasoob!'
def doSomethingBeforeHi(func):
    print('I am doing some boring work before executing hi()')
    print(func())

doSomethingBeforeHi(hi)
'''
'''
def a_new_decorator(a_func):
    def wrapTheFunction():
        print('I am doing some boring work before executing a_func()')
        a_func()
        print('I am doing some boring work after executing  a_func()')
    return wrapTheFunction

def a_function_requiring_decoration():
    print('I am the function which needs some decoration to remove my foul smell')

a_function_requiring_decoration()

a_function_requiring_decoration = a_new_decorator(a_function_requiring_decoration)

a_function_requiring_decoration()
'''
'''
def a_new_decorator(a_func):
    def wrapTheFunction():
        print('I am doing some boring work before executing a_func()')
        a_func()
        print('I am doing some boring work after executing  a_func()')
    return wrapTheFunction

@a_new_decorator
def a_function_requiring_decoration():
    print('I am the function which needs some decoration to remove my foul smell')

#a_function_requiring_decoration()

a_function_requiring_decoration = a_new_decorator(a_function_requiring_decoration)

a_function_requiring_decoration()
'''
'''
from functools import wraps

def a_new_decorator(a_func):
    @wraps(a_func)
    def wrapTheFunction():
        print('I am doing some boring work before executing a func()')
        a_func()
        print('I am doing some boring work after executing a func()')
    return wrapTheFunction

@a_new_decorator
def a_function_requiring_decoration():
    print('I am the function which needs some decoration to remvoe my foul smell')
print(a_function_requiring_decoration)
print(a_function_requiring_decoration.__name__)
'''
'''
from functools import wraps

def logit(func):
    @wraps(func)
    def with_logging(*args,**kwargs):
        print(func.__name__+'was called')
        return func(*args,**kwargs)
    return with_logging
@logit
def addition_func(x):
    return x+x
result = addition_func(4)
'''
'''
from functools import wraps

def logit(logfile='out.log'):
    def logging_decorator(func):
        @wraps(func)
        def wrapped_function(*args,**kwargs):
            log_string = func.__name__ + 'was called'
            print(log_string)
            with open(logfile,'a') as opened_file:
                opened_file.write(log_string + '/n')
            return func(*args,**kwargs)
        return wrapped_function
    return logging_decorator
@logit()
def myfunc1():
    pass
myfunc1()

@logit(logfile='func2.log')
def myfunc2():
    pass
myfunc2()
'''
'''
from functools import wraps

class logit(object):
    def __init__(self,logfile='out.log'):
        self.logfile = logfile 
    def __call__(self,func):
        @wraps(func)
        def wrapped_function(*args,**kwargs):
            log_string = func.__name__ + 'was called'
            print(log_string)
            with open(self.logfile,'a') as opened_file:
                opened_file.write(log_string + '\n')
            self.notify()
            return func(*args,**kwargs)
        return wrapped_function

    def notify(self):
        print('notify!')

@logit
def myfunc1():
    pass

#myfunc1()
'''
'''
foo = ['hi'] 
print(foo) # Output: ['hi']

bar = foo 
bar += ['bye'] 
print(foo)
'''
'''
foo = ['hi'] 
print(foo) # Output: ['hi']

bar = foo 
bar += ['bye']

print(foo) # Output: ['hi']

print(bar) # Output: ['hi', 'bye']

'''

from collections import Counter

colours = (
    ('Yasoob', 'Yellow'), 
    ('Ali', 'Blue'), 
    ('Arham', 'Green'), 
    ('Ali', 'Black'), 
    ('Yasoob', 'Red'), 
    ('Ahmed', 'Silver'),
)

favs = Counter(name for name,colour in colours)
print(favs)






