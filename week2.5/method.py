# coding=utf-8

class Person(object):
	def __init__(self):
		print('init')

	@staticmethod
	def sayHello(hi):
		if hi is None:
			hi = 'hello'
		print(hi)

	@classmethod
	def hi(cls,msg):
		print(msg)
		print(dir(cls))

	def hobby(self,hobby):
		print(hobby)

Person.sayHello('hi')
Person.hi('Hi!')

person = Person()
person.hobby('football')