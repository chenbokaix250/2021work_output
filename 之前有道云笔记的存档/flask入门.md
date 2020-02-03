### 简介
Flask是一个使用Python编写的轻量级Web应用框架。基于Werkzeug WSGI(PythonWeb服务器网关接口（Python Web Server Gateway Interface，缩写为WSGI)是Python应用程序或框架和Web服务器之间的一种接口，已经被广泛接受, 它已基本达成它的可移植性方面的目标)工具箱和Jinja2 模板引擎。 Flask使用BSD授权。 Flask也被称为“microframework”，因为它使用简单的核心，用extension增加其他功能。Flask没有默认使用的数据库、窗体验证工具。然而，Flask保留了扩增的弹性，可以用Flask-extension加入这些功能：ORM、窗体验证工具、文件上传、各种开放式身份验证技术


flask的安装 `pip install flask`

最小的flask应用
```
from flask import Flask
app = Flask(__name__)
@app.route("/")
def hello():
    return "Hello World!"
    
if __name__ == "__main__":
    app.run()
```
*　导入Flask类
*　创建应用模块或者包的名称
*　使用route()装饰器来告诉Flask出发函数的URL
*　函数名称可用于生成相关联的URL,并返回需要在用户浏览器中显示的信息
*　使用run()函数来运行本地服务和应用
*　ctrl-C可以停止服务器

