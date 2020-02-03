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

#=================================================
#                   Utils
#=================================================

function source_apollo_base() {
  DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )" //取得当前执行的shell文件所在的路径及文件名 和 当前工作目录 作为DIR
  cd "${DIR}"
  //进入DIR
  source "${DIR}/scripts/apollo_base.sh"
  //进入该目录执行apollo_base.sh脚本
  
}

function apollo_check_system_config() {
  # check operating system
  OP_SYSTEM=$(uname -s)    //检测系统 传入OP_SYSTEM
  case $OP_SYSTEM in
    "Linux")               //如果是linux
      echo "System check passed. Build continue ..."
    
      # check system configuration
      DEFAULT_MEM_SIZE="2.0" // 默认2GB空间
      MEM_SIZE=$(free | grep Mem | awk '{printf("%0.2f", $2 / 1024.0 / 1024.0)}')//读取剩余空间 
      if (( $(echo "$MEM_SIZE < $DEFAULT_MEM_SIZE" | bc -l) )); then
         warning "System memory [${MEM_SIZE}G] is lower than minimum required memory size [2.0G]. Apollo build could fail." //计算空间小于2GB时,提示
      fi
      ;;
    "Darwin")          //苹果系统时,提示不支持
      warning "Mac OS is not officially supported in the current version. Build could fail. We recommend using Ubuntu 14.04."
      ;;
    *)
      error "Unsupported system: ${OP_SYSTEM}."
      error "Please use Linux, we recommend Ubuntu 14.04."
      exit 1
      ;;
  esac //case结束
}

function check_machine_arch() {
  # the machine type, currently support x86_64, aarch64
  MACHINE_ARCH=$(uname -m) //获取电脑类型

  # Generate WORKSPACE file based on marchine architecture
  if [ "$MACHINE_ARCH" == 'x86_64' ]; then
    sed "s/MACHINE_ARCH/x86_64/g" WORKSPACE.in > WORKSPACE //将MACHINE_ARCH与替换为x86_64并保存为WORKSPACE
    
  elif [ "$MACHINE_ARCH" == 'aarch64' ]; then
    sed "s/MACHINE_ARCH/aarch64/g" WORKSPACE.in > WORKSPACE
  else
    fail "Unknown machine architecture $MACHINE_ARCH"
    exit 1
  fi

  #setup vtk folder name for different systems.
  VTK_VERSION=$(find /usr/include/ -type d  -name "vtk-*" | tail -n1 | cut -d '-' -f 2)
  sed -i "s/VTK_VERSION/${VTK_VERSION}/g" WORKSPACE //将VTK的版本插入WORKSPACE
}

function check_esd_files() {
  CAN_CARD="fake_can"

  if [ -f ./third_party/can_card_library/esd_can/include/ntcan.h \   //检测三个文件存在
      -a -f ./third_party/can_card_library/esd_can/lib/libntcan.so.4 \
      -a -f ./third_party/can_card_library/esd_can/lib/libntcan.so.4.0.1 ]; then
      USE_ESD_CAN=true
      CAN_CARD="esd_can"  //更新标识位
  else
      warning "ESD CAN library supplied by ESD Electronics does not exist. If you need ESD CAN, please refer to third_party/can_card_library/esd_can/README.md."
      USE_ESD_CAN=false
  fi
}

function generate_build_targets() {
  if [ -z $NOT_BUILD_PERCEPTION ] ; then
    BUILD_TARGETS=`bazel query //...` //是否编译感知部分
  else
    info 'Skip building perception module!'
    BUILD_TARGETS=`bazel query //... except //modules/perception/... except //modules/calibration/lidar_ex_checker/...`
  fi

  if [ $? -ne 0 ]; then //如果执行返回值!=0,则编译失败
    fail 'Build failed!'
  fi
  if ! $USE_ESD_CAN; then
     BUILD_TARGETS=$(echo $BUILD_TARGETS |tr ' ' '\n' | grep -v "esd")
  fi
  #skip msf for non x86_64 platforms
  if [ ${MACHINE_ARCH} != "x86_64" ]; then
     BUILD_TARGETS=$(echo $BUILD_TARGETS |tr ' ' '\n' | grep -v "msf")
  fi
}

#=================================================
#              Build functions
#=================================================

function build() {
  START_TIME=$(get_now) //获得当前时间

  info "Start building, please wait ..."
  generate_build_targets //
  info "Building on $MACHINE_ARCH..."

  MACHINE_ARCH=$(uname -m)  //获取硬件信息 i686或X86_64
  JOB_ARG=""
  if [ "$MACHINE_ARCH" == 'aarch64' ]; then
    JOB_ARG="--jobs=3"
  fi
  echo "$BUILD_TARGETS" | xargs bazel build $JOB_ARG $DEFINES -c $@  //打印 BUILD_TARGETS
  if [ $? -ne 0 ]; then
    fail 'Build failed!' 
  fi

  # Build python proto
  build_py_proto

  # Clear KV DB and update commit_id after compiling.
  rm -fr data/kv_db
  python modules/tools/common/kv_db.py put \
      "apollo:data:commit_id" "$(git rev-parse HEAD)" //传送kvas_db的参数

  if [ -d /apollo-simulator ] && [ -e /apollo-simulator/build.sh ]; then
    cd /apollo-simulator && bash build.sh build  //如果目录存在
    if [ $? -ne 0 ]; then //执行出现异常,则返回 失败
      fail 'Build failed!'
    fi
  fi
  if [ $? -eq 0 ]; then //执行完成,则显示成功
    success 'Build passed!'
  fi
}

function cibuild() {
  START_TIME=$(get_now)

  echo "Start building, please wait ..."
  generate_build_targets
  echo "Building on $MACHINE_ARCH..."
  BUILD_TARGETS="
  //modules/control
  //modules/dreamview
  //modules/localization
  //modules/perception
  //modules/planning
  //modules/prediction
  //modules/routing
  "
  bazel build $DEFINES $@ $BUILD_TARGETS
  if [ $? -eq 0 ]; then
    success 'Build passed!'
  else
    fail 'Build failed!'
  fi
}

function apollo_build_dbg() {
  build "dbg" $@ //dbg是编译调试版本 
}

function apollo_build_opt() {
  build "opt" $@ //opt是编译优化版本
}

function build_py_proto() {
  if [ -d "./py_proto" ];then  //如果存在py_proto则删除该文件夹
    rm -rf py_proto
  fi
  mkdir py_proto  //创建文件集
  PROTOC='./bazel-out/host/bin/external/com_google_protobuf/protoc' //protoc执行位置
  find modules/ -name "*.proto" \ 
      | grep -v node_modules \
      | grep -v modules/drivers/gnss \
      | xargs ${PROTOC} --python_out=py_proto
  find py_proto/* -type d -exec touch "{}/__init__.py" \; //利用proto编译得到__init__.py
}

function check() {
  local check_start_time=$(get_now)

  bash $0 build && bash $0 "test" && bash $0 lint

  START_TIME=$check_start_time
  if [ $? -eq 0 ]; then
    success 'Check passed!'
    return 0
  else
    fail 'Check failed!'
    return 1
  fi
}

function warn_proprietary_sw() {
  echo -e "${RED}The release built contains proprietary software provided by other parties.${NO_COLOR}"
  echo -e "${RED}Make sure you have obtained proper licensing agreement for redistribution${NO_COLOR}"
  echo -e "${RED}if you intend to publish the release package built.${NO_COLOR}"
  echo -e "${RED}Such licensing agreement is solely between you and the other parties,${NO_COLOR}"
  echo -e "${RED}and is not covered by the license terms of the apollo project${NO_COLOR}"
  echo -e "${RED}(see file license).${NO_COLOR}"
}

function release() {
  RELEASE_DIR="${HOME}/.cache/apollo_release"
  if [ -d "${RELEASE_DIR}" ]; then
    rm -rf "${RELEASE_DIR}"
  fi
  APOLLO_RELEASE_DIR="${RELEASE_DIR}/apollo"
  mkdir -p "${APOLLO_RELEASE_DIR}"

  # Find binaries and convert from //path:target to path/target
  BINARIES=$(bazel query "kind(cc_binary, //...)" | sed 's/^\/\///' | sed 's/:/\//')
  # Copy binaries to release dir.
  for BIN in ${BINARIES}; do
    SRC_PATH="bazel-bin/${BIN}"
    DST_PATH="${APOLLO_RELEASE_DIR}/${BIN}"
    if [ -e "${SRC_PATH}" ]; then
      mkdir -p "$(dirname "${DST_PATH}")"
      cp "${SRC_PATH}" "${DST_PATH}"
    fi
  done

  # modules data and conf
  CONFS=$(find modules/ -name "conf")
  DATAS=$(find modules/ -name "data")
  rm -rf test/*
  for conf in $CONFS; do
    mkdir -p $APOLLO_RELEASE_DIR/$conf
    rsync -a $conf/* $APOLLO_RELEASE_DIR/$conf
  done
  for data in $DATAS; do
    mkdir -p $APOLLO_RELEASE_DIR/$data
    if [ $data != "modules/map/data" ]; then
      rsync -a $data/* $APOLLO_RELEASE_DIR/$data
    fi
  done

  # dreamview frontend
  cp -a modules/dreamview/frontend $APOLLO_RELEASE_DIR/modules/dreamview

  # remove all pyc file in modules/
  find modules/ -name "*.pyc" | xargs -I {} rm {}

  # scripts
  cp -r scripts ${APOLLO_RELEASE_DIR}

  # lib
  LIB_DIR="${APOLLO_RELEASE_DIR}/lib"
  mkdir "${LIB_DIR}"
  if $USE_ESD_CAN; then
    warn_proprietary_sw
    for m in esd_can
    do
      cp third_party/can_card_library/$m/lib/* $LIB_DIR
    done
  fi
  cp -r bazel-genfiles/external $LIB_DIR
  cp -r py_proto/modules $LIB_DIR

  # doc
  cp -r docs "${APOLLO_RELEASE_DIR}"
  cp LICENSE "${APOLLO_RELEASE_DIR}"
  cp third_party/ACKNOWLEDGEMENT.txt "${APOLLO_RELEASE_DIR}"

  # release info
  META="${APOLLO_RELEASE_DIR}/meta.ini"
  echo "git_commit: $(git rev-parse HEAD)" >> $META
  echo "car_type: LINCOLN.MKZ" >> $META
  echo "arch: ${MACHINE_ARCH}" >> $META
}

function gen_coverage() {
  bazel clean
  generate_build_targets
  echo "$BUILD_TARGETS" | grep -v "cnn_segmentation_test" | xargs bazel test $DEFINES -c dbg --config=coverage $@
  if [ $? -ne 0 ]; then
    fail 'run test failed!'
  fi

  COV_DIR=data/cov
  rm -rf $COV_DIR
  files=$(find bazel-out/local-dbg/bin/modules/ -iname "*.gcda" -o -iname "*.gcno" | grep -v external)
  for f in $files; do
    target="$COV_DIR/objs/modules/${f##*modules}"
    mkdir -p "$(dirname "$target")"
    cp "$f" "$target"
  done

  files=$(find bazel-out/local-opt/bin/modules/ -iname "*.gcda" -o -iname "*.gcno" | grep -v external)
  for f in $files; do
    target="$COV_DIR/objs/modules/${f##*modules}"
    mkdir -p "$(dirname "$target")"
    cp "$f" "$target"
  done

  lcov --capture --directory "$COV_DIR/objs" --output-file "$COV_DIR/conv.info"
  if [ $? -ne 0 ]; then
    fail 'lcov failed!'
  fi
  lcov --remove "$COV_DIR/conv.info" \
      "external/*" \
      "/usr/*" \
      "bazel-out/*" \
      "*third_party/*" \
      "tools/*" \
      -o $COV_DIR/stripped_conv.info
  genhtml $COV_DIR/stripped_conv.info --output-directory $COV_DIR/report
  echo "Generated coverage report in $COV_DIR/report/index.html"
}

function run_test() {
  START_TIME=$(get_now)

  generate_build_targets
  if [ "$USE_GPU" == "1" ]; then
    echo -e "${RED}Need GPU to run the tests.${NO_COLOR}"
    echo "$BUILD_TARGETS" | xargs bazel test $DEFINES --config=unit_test -c dbg --test_verbose_timeout_warnings $@
  else
    echo "$BUILD_TARGETS" | grep -v "cnn_segmentation_test" | xargs bazel test $DEFINES --config=unit_test -c dbg --test_verbose_timeout_warnings $@
  fi
  if [ $? -ne 0 ]; then
    fail 'Test failed!'
    return 1
  fi

  if [ -d /apollo-simulator ] && [ -e /apollo-simulator/build.sh ]; then
      cd /apollo-simulator && bash build.sh test
      if [ $? -ne 0 ]; then
        fail 'Test failed!'
        return 1
      fi
  fi

  if [ $? -eq 0 ]; then
    success 'Test passed!'
    return 0
  fi
}

function citest() {
  START_TIME=$(get_now)
  BUILD_TARGETS="
  //modules/planning/integration_tests:garage_test
  //modules/planning/integration_tests:sunnyvale_loop_test
  //modules/control/integration_tests:simple_control_test
  //modules/prediction/container/obstacles:obstacle_test
  //modules/dreamview/backend/simulation_world:simulation_world_service_test
  "
  bazel test $DEFINES --config=unit_test --test_verbose_timeout_warnings $@ $BUILD_TARGETS
  if [ $? -eq 0 ]; then
    success 'Test passed!'
    return 0
  else
    fail 'Test failed!'
    return 1
  fi
}

function run_cpp_lint() {
  generate_build_targets
  echo "$BUILD_TARGETS" | xargs bazel test --config=cpplint -c dbg
}

function run_bash_lint() {
  FILES=$(find "${APOLLO_ROOT_DIR}" -type f -name "*.sh" | grep -v ros)
  echo "${FILES}" | xargs shellcheck
}

function run_lint() {
  START_TIME=$(get_now)

  # Add cpplint rule to BUILD files that do not contain it.
  for file in $(find modules -name BUILD | \
    xargs grep -l -E 'cc_library|cc_test|cc_binary' | xargs grep -L 'cpplint()')
  do
    sed -i '1i\load("//tools:cpplint.bzl", "cpplint")\n' $file
    sed -i -e '$a\\ncpplint()' $file
  done

  run_cpp_lint

  if [ $? -eq 0 ]; then
    success 'Lint passed!'
  else
    fail 'Lint failed!'
  fi
}

function clean() {
  bazel clean --async
}

function buildify() {
  START_TIME=$(get_now)

  local buildifier_url=https://github.com/bazelbuild/buildtools/releases/download/0.4.5/buildifier
  wget $buildifier_url -O ~/.buildifier
  chmod +x ~/.buildifier
  find . -name '*BUILD' -type f -exec ~/.buildifier -showlog -mode=fix {} +
  if [ $? -eq 0 ]; then
    success 'Buildify worked!'
  else
    fail 'Buildify failed!'
  fi
  rm ~/.buildifier
}

function build_fe() {
  cd modules/dreamview/frontend
  yarn build
}

function gen_doc() {
  rm -rf docs/doxygen
  doxygen apollo.doxygen
}

function version() {
  commit=$(git log -1 --pretty=%H)
  date=$(git log -1 --pretty=%cd)
  echo "Commit: ${commit}"
  echo "Date: ${date}"
}

function build_gnss() {
  CURRENT_PATH=$(pwd)
  if [ -d "${ROS_ROOT}" ]; then
    ROS_PATH="${ROS_ROOT}/../.."
  else
    warning "ROS not found. Run apolllo.sh build first."
    exit 1
  fi

  source "${ROS_PATH}/setup.bash"

  protoc modules/common/proto/error_code.proto --cpp_out=./
  protoc modules/common/proto/header.proto --cpp_out=./
  protoc modules/common/proto/geometry.proto --cpp_out=./

  protoc modules/localization/proto/imu.proto --cpp_out=./
  protoc modules/localization/proto/gps.proto --cpp_out=./
  protoc modules/localization/proto/pose.proto --cpp_out=./

  protoc modules/drivers/gnss/proto/gnss.proto --cpp_out=./
  protoc modules/drivers/gnss/proto/imu.proto --cpp_out=./
  protoc modules/drivers/gnss/proto/ins.proto --cpp_out=./ --python_out=./
  protoc modules/drivers/gnss/proto/config.proto --cpp_out=./
  protoc modules/drivers/gnss/proto/gnss_status.proto --cpp_out=./ --python_out=./
  protoc modules/drivers/gnss/proto/gpgga.proto --cpp_out=./
  protoc modules/drivers/gnss/proto/gnss_raw_observation.proto --cpp_out=./ --python_out=./
  protoc modules/drivers/gnss/proto/gnss_best_pose.proto --cpp_out=./ --python_out=./

  cd modules
  catkin_make_isolated --install --source drivers/gnss \
    --install-space "${ROS_PATH}" -DCMAKE_BUILD_TYPE=Release \
    --cmake-args --no-warn-unused-cli
  find "${ROS_PATH}" -name "*.pyc" -print0 | xargs -0 rm -rf
  cd -

  rm -rf modules/common/proto/*.pb.cc
  rm -rf modules/common/proto/*.pb.h
  rm -rf modules/drivers/gnss/proto/*.pb.cc
  rm -rf modules/drivers/gnss/proto/*.pb.h
  rm -rf modules/drivers/gnss/proto/*_pb2.py
  rm -rf modules/localization/proto/*.pb.cc
  rm -rf modules/localization/proto/*.pb.h

  rm -rf modules/.catkin_workspace
  rm -rf modules/build_isolated/
  rm -rf modules/devel_isolated/
}

function build_velodyne() {
  CURRENT_PATH=$(pwd)
  if [ -d "${ROS_ROOT}" ]; then
    ROS_PATH="${ROS_ROOT}/../.."
  else
    warning "ROS not found. Run apolllo.sh build first."
    exit 1
  fi

  source "${ROS_PATH}/setup.bash"

  cd modules
  catkin_make_isolated --install --source drivers/velodyne \
    --install-space "${ROS_PATH}" -DCMAKE_BUILD_TYPE=Release \
    --cmake-args --no-warn-unused-cli
  find "${ROS_PATH}" -name "*.pyc" -print0 | xargs -0 rm -rf
  cd -

  rm -rf modules/.catkin_workspace
  rm -rf modules/build_isolated/
  rm -rf modules/devel_isolated/
}

function build_usbcam() {
  CURRENT_PATH=$(pwd)
  if [ -d "${ROS_ROOT}" ]; then
    ROS_PATH="${ROS_ROOT}/../.."
  else
    warning "ROS not found. Run apolllo.sh build first."
    exit 1
  fi

  source "${ROS_PATH}/setup.bash"

  cd modules
  catkin_make_isolated --install --source drivers/usb_cam \
    --install-space "${ROS_PATH}" -DCMAKE_BUILD_TYPE=Release \
    --cmake-args --no-warn-unused-cli
  find "${ROS_PATH}" -name "*.pyc" -print0 | xargs -0 rm -rf
  cd -

  rm -rf modules/.catkin_workspace
  rm -rf modules/build_isolated/
  rm -rf modules/devel_isolated/
}

function config() {
  ${APOLLO_ROOT_DIR}/scripts/configurator.sh
}

function print_usage() {
  RED='\033[0;31m'
  BLUE='\033[0;34m'
  BOLD='\033[1m'
  NONE='\033[0m'

  echo -e "\n${RED}Usage${NONE}:
  .${BOLD}/apollo.sh${NONE} [OPTION]"

  echo -e "\n${RED}Options${NONE}:
  ${BLUE}build${NONE}: run build only
  ${BLUE}build_opt${NONE}: build optimized binary for the code
  ${BLUE}build_gpu${NONE}: run build only with Caffe GPU mode support
  ${BLUE}build_gnss${NONE}: build gnss driver
  ${BLUE}build_velodyne${NONE}: build velodyne driver
  ${BLUE}build_usbcam${NONE}: build velodyne driver
  ${BLUE}build_opt_gpu${NONE}: build optimized binary with Caffe GPU mode support
  ${BLUE}build_fe${NONE}: compile frontend javascript code, this requires all the node_modules to be installed already
  ${BLUE}build_no_perception [dbg|opt]${NONE}: run build build skip building perception module, useful when some perception dependencies are not satisified, e.g., CUDA, CUDNN, LIDAR, etc.
  ${BLUE}build_prof${NONE}: build for gprof support.
  ${BLUE}buildify${NONE}: fix style of BUILD files
  ${BLUE}check${NONE}: run build/lint/test, please make sure it passes before checking in new code
  ${BLUE}clean${NONE}: run Bazel clean
  ${BLUE}config${NONE}: run configurator tool
  ${BLUE}coverage${NONE}: generate test coverage report
  ${BLUE}doc${NONE}: generate doxygen document
  ${BLUE}lint${NONE}: run code style check
  ${BLUE}usage${NONE}: print this menu
  ${BLUE}release${NONE}: build release version
  ${BLUE}test${NONE}: run all unit tests
  ${BLUE}version${NONE}: display current commit and date
  "
}

function main() {
  source_apollo_base   //执行script中的apollo_base.sh
  apollo_check_system_config
  check_machine_arch
  check_esd_files

  DEFINES="--define ARCH=${MACHINE_ARCH} --define CAN_CARD=${CAN_CARD} --cxxopt=-DUSE_ESD_CAN=${USE_ESD_CAN}"
    
    
  if [ ${MACHINE_ARCH} == "x86_64" ]; then
    DEFINES="${DEFINES} --copt=-mavx2"
  fi

  local cmd=$1
  shift

  case $cmd in
    check)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      check $@
      ;;
    build)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      apollo_build_dbg $@  
      ;;
    build_prof)
      DEFINES="${DEFINES} --config=cpu_prof --cxxopt=-DCPU_ONLY"
      apollo_build_dbg $@
      ;;
    build_no_perception)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      NOT_BUILD_PERCEPTION=true
      if [ "$1" == "opt" ]; then
        shift
        apollo_build_opt $@
      elif [ "$1" == "dbg" ]; then
        shift
        apollo_build_dbg $@
      fi
      ;;
    cibuild)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      cibuild $@
      ;;
    build_opt)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      apollo_build_opt $@
      ;;
    build_gpu)
      DEFINES="${DEFINES} --cxxopt=-DUSE_CAFFE_GPU"
      apollo_build_dbg $@
      ;;
    build_opt_gpu)
      DEFINES="${DEFINES} --cxxopt=-DUSE_CAFFE_GPU"
      apollo_build_opt $@
      ;;
    build_fe)
      build_fe
      ;;
    buildify)
      buildify
      ;;
    build_gnss)
      build_gnss
      ;;
    build_py)
      build_py_proto
      ;;
    build_velodyne)
      build_velodyne
      ;;
    build_usbcam)
      build_usbcam
      ;;
    config)
      config
      ;;
    doc)
      gen_doc
      ;;
    lint)
      run_lint
      ;;
    test)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      run_test $@
      ;;
    citest)
      DEFINES="${DEFINES} --cxxopt=-DCPU_ONLY"
      citest $@
      ;;
    test_gpu)
      DEFINES="${DEFINES} --cxxopt=-DUSE_CAFFE_GPU"
      USE_GPU="1"
      run_test $@
      ;;
    release)
      release 1
      ;;
    release_noproprietary)
      release 0
      ;;
    coverage)
      gen_coverage $@
      ;;
    clean)
      clean
      ;;
    version)
      version
      ;;
    usage)
      print_usage
      ;;
    *)
      print_usage
      ;;
  esac
}

main $@   //执行main函数

```


















***
***

### apollo_app.h

```
/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 */

#ifndef MODULES_COMMON_APOLLO_APP_H_
#define MODULES_COMMON_APOLLO_APP_H_

#include <csignal>
#include <string>

#include "gflags/gflags.h"
#include "modules/common/log.h"
#include "modules/common/status/status.h"

#include "ros/include/ros/ros.h"

/**
 * @namespace apollo::common
 * @brief apollo::common
 */
namespace apollo {
namespace common {

/**
 * @class ApolloApp
 *
 * @brief The base module class to define the interface of an Apollo app.
 * An Apollo app runs infinitely until being shutdown by SIGINT or ROS. Many
 * essential components in Apollo, such as localization and control are examples
 * of Apollo apps. The APOLLO_MAIN macro helps developer to setup glog, gflag
 * and ROS in one line.
 */
class ApolloApp {
 public:
  /**
   * @brief module name. It is used to uniquely identify the app.
   */
  virtual std::string Name() const = 0;

  /**
   * @brief this is the entry point of an Apollo App. It initializes the app,
   * starts the app, and stop the app when the ros has shutdown.
   */
  virtual int Spin();

  /**
   * The default destructor.
   */
  virtual ~ApolloApp() = default;

  /**
   * @brief set the number of threads to handle ros message callbacks.
   * The default thread number is 1
   */
  void SetCallbackThreadNumber(uint32_t callback_thread_num);

 protected:
  /**
   * @brief The module initialization function. This is the first function being
   * called when the App starts. Usually this function loads the configurations,
   * subscribe the data from sensors or other modules.
   * @return Status initialization status
   */
  virtual apollo::common::Status Init() = 0;

  /**
   * @brief The module start function. Apollo app usually triggered to execute
   * in two ways: 1. Triggered by upstream messages, or 2. Triggered by timer.
   * If an app is triggered by upstream messages, the Start() function usually
   * register a call back function that will be called when an upstream message
   * is received. If an app is triggered by timer, the Start() function usually
   * register a timer callback function.
   * @return Status start status
   */
  virtual apollo::common::Status Start() = 0;

  /**
   * @brief The module stop function. This function will be called when
   * after ros::shutdown() has finished. In the default APOLLO_MAIN macro,
   * ros::shutdown() is called when SIGINT is received.
   */
  virtual void Stop() = 0;

  /** The callback thread number
   */
  uint32_t callback_thread_num_ = 1;

 private:
  /**
   * @brief Export flag values to <FLAGS_log_dir>/<name>.flags.
   */
  void ExportFlags() const;
};

void apollo_app_sigint_handler(int signal_num);

}  // namespace common
}  // namespace apollo

#define APOLLO_MAIN(APP)                                       \
  int main(int argc, char **argv) {                            \//Apollo的主函数入口
    google::InitGoogleLogging(argv[0]);                        \
    google::ParseCommandLineFlags(&argc, &argv, true);         \
    signal(SIGINT, apollo::common::apollo_app_sigint_handler); \
    APP apollo_app_;                                           \
    ros::init(argc, argv, apollo_app_.Name());                 \
    apollo_app_.Spin();                                        \
    return 0;                                                  \
  }

#endif  // MODULES_COMMON_APOLLO_APP_H_
```