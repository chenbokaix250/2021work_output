# coding=utf-8

import configparser
import webbrowser

#返回config对象
conf = configparser.ConfigParser()
conf.read('demo.conf','utf-8')

#读取配置文件
def readConf():
	sections = conf.sections()
	print(sections)

	options_sec_a = conf.options('sec_a')
	print(options_sec_a)

	options_sec_b = conf.options('sec_b')
	print(options_sec_b)

	items_ssec_a = conf.items('sec_a')
	print(items_ssec_a)

	items_ssec_b = conf.items('sec_b')
	print(items_ssec_b)

	sec_a_key1 = conf.get('sec_a','a_key1')
	print(sec_a_key1)




readConf()



def writeConf():
	conf.set('sec_a','a_key1','100')
	value = conf.get('sec_a','a_key1')
	print(value)

	conf.add_section('new_section')
	conf.set('new_section','new_option_name','new_option_value')

	new_sections = conf.sections()

	print(new_sections)
	print(conf.get('new_section','new_option_name'))

writeConf()


def jump():
	url = conf.get('website','url')
	webbrowser.open(url)


jump()