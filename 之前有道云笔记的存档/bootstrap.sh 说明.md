```
#!/usr/bin/env bash

###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "${DIR}/.."

source "${DIR}/apollo_base.sh"

function start() {
    echo "Start roscore..."
    ROSCORELOG="${APOLLO_ROOT_DIR}/data/log/roscore.out"
    nohup roscore </dev/null >"${ROSCORELOG}" 2>&1 &
    if [ "$HOSTNAME" == "in_release_docker" ]; then
        supervisord -c /apollo/modules/tools/supervisord/release.conf >& /tmp/supervisord.start.log
        echo "Started supervisord with release conf"
    else
        supervisord -c /apollo/modules/tools/supervisord/dev.conf >& /tmp/supervisord.start.log
        echo "Started supervisord with dev conf"
    fi
    supervisorctl start monitor > /dev/null

    supervisorctl start dreamview > /dev/null
    echo "Dreamview is running at http://localhost:8888"
}

function stop() {
    supervisorctl stop dreamview
    supervisorctl stop monitor
    pkill -f roscore
}

case $1 in
  start)
    start
    ;;
  stop)
    stop
    ;;
  *)
    start
    ;;
esac

```


nuhup 能使原程序在后台运行的同时,标准输出被自动改向到当掐么目录下的nohup.out文件,起到了log的作用

如果使用命令提交作业,那么在缺省情况下该作业的所有输出都被重定向到一个名为nohup.out的文件中,除非定外指定了输出文件:

`nuhup command > myout.file 2>&1 &`
输出被重定向到myout.file文件中.使用jobs查看任务.使用fg %n 关闭


Supervisor是基于Python的进程管理工具,可以帮助我们更简单的启动/重启和关闭服务器后台的进程

`supervisord -c /etc/supervisord.conf`

